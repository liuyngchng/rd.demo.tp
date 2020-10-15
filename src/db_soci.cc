<<<<<<< HEAD
/**
 * @file db.cc
 * @author liuyongcheng(liuyongcheng@cetc15.net)
 * @brief 
 * @version 0.1
 * @date 2020-07-31
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "db.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <list>

using namespace std;


// database init flag
static bool is_db_inited = false; 
static sqlite3 *db = NULL;


/**
 * @brief itoa
 * 
 * @param i the int data
 * @return string the string for int
 */
static inline string itoa(int i)
{
    char s[32] = {0};
    snprintf(s, 32, "%d", i);
    string s_s = s;
    return s_s;
}

/**
 * @brief utoa
 * 
 * @param u the data
 * @return string the string for int
 */
static inline string utoa(uint32_t u)
{
    char s[32] = {0};
    snprintf(s, 32, "%u", u);
    string s_s = s;
    return s_s;
}

/**
 * @brief lutoa
 * 
 * @param u the data
 * @return string the string for int
 */
static inline string lutoa(uint64_t u)
{
    char s[32] = {0};
    snprintf(s, 32, "%lu", u);
    string s_s = s;
    return s_s;
}

/**
 * @brief free_db_err_msg
 * 
 * @param err_msg the err msg ptr
 */
void free_db_err_msg(char *err_msg)
{
    sqlite3_free(err_msg);
}

/**
 * @brief free_db
 * 
 */
void free_db()
{
    sqlite3_close(db);
    #ifdef USED_THREAD_DO_SQL
    pthread_exit(&pid);
    #endif
}

#define USED_THREAD_DO_SQL

#ifdef USED_THREAD_DO_SQL

typedef struct 
{
    string sql;
    int  c;
    uint32_t f_id;
    string f_name;
    string save_first;
}sql_queue_t;

list<sql_queue_t*> g_sqls;
pthread_mutex_t g_lock;
pthread_t pid;

#define _STR_TO_HEX(I, O)               \
    if((I) >= '0' && (I) <= '9')        \
    {                                   \
        (O) = (I) - '0';                \
    }                                   \
    else if((I) >= 'A' && (I) <= 'F')   \
    {                                   \
        (O) = (I) - 'A' + 10;           \
    }\


#define _HEX_TO_STR(I, O)               \
    if((I) >= 0 && (I) <= 9)            \
    {                                   \
        (O) = (I) + '0';                \
    }                                   \
    else if((I) >= 0xA && (I) <= 0xF)   \
    {                                   \
        (O) = (I) - 0xA + 'A';          \
    }\
 

#define MAX_RETRY_COUNT  8

/**
 * @brief exec_sql_thread
 * 
 * @param arg 
 * @return void* 
 */
void *exec_sql_thread(void *arg)
{
    sql_queue_t *q;
    int s;
    char *err_msg = NULL;
    string sql;
    int row = 0;
    int c = 0;
    char **result = NULL;
    int ret;
    int s_len;
    int d_len;
    int i;
    char s_tmp;
    char d_tmp;
    int id;
    string s_ack;
    uint32_t num = 0;

    while (true)
    {
        pthread_mutex_lock(&g_lock);
        s = g_sqls.size();
        pthread_mutex_unlock(&g_lock);
        if(s == 0)
        {
            sleep(1);
            continue;
        }

        pthread_mutex_lock(&g_lock);
        q = g_sqls.front();
        pthread_mutex_unlock(&g_lock);

        if(q->f_id)
        {
            row = 0;
            c = 0;
            sql.clear();
            sql = "select slice_ack from file_info where del=0 and file_id='" + 
                            utoa(q->f_id) + "' and name='" + q->f_name + "' limit 1";

            ret = sqlite3_get_table(db , sql.c_str(), &result, &row , &c , &err_msg);

            if (ret != 0) 
            {
                sqlite3_free(err_msg);

                pthread_mutex_lock(&g_lock);
                g_sqls.pop_front();
                g_sqls.push_back(q);
                pthread_mutex_unlock(&g_lock);

                continue;
            }
            
            if(row > 0) 
            {
                sql.clear();
                s_ack.clear();

                sql = "update 'file_info' set ";

                if(result[c])
                {
                    s_len = strlen(result[c]);
                    d_len = q->sql.length();
                    num = 0;
                    if(s_len > d_len)
                    {
                        for(i = 0; i < d_len; ++i)
                        {
                            _STR_TO_HEX(result[c][i], s_tmp);
                            _STR_TO_HEX(q->sql.at(i), d_tmp);
                            s_tmp |= d_tmp;
                            _HEX_TO_STR(s_tmp, result[c][i]); 
                        }
                        s_ack.append(result[c]);
                    }
                    else
                    {

                        for(i = 0; i < s_len; ++i)
                        {
                            _STR_TO_HEX(result[c][i], s_tmp);
                            _STR_TO_HEX(q->sql.at(i), d_tmp);
                            d_tmp |= s_tmp;
                            _HEX_TO_STR(d_tmp, q->sql.at(i));
                        }
                        s_ack = q->sql;
                    }
                }
                else
                {
                    s_ack = q->sql;
                }

                for(i = 0, num = 0; i < (int)s_ack.length(); ++i)
                {
                    _STR_TO_HEX(s_ack.at(i), d_tmp);
                    if ((d_tmp & 0x1) == 0x1)
                    {
                        ++num;
                    }
                    if ((d_tmp & 0x2) == 0x2)
                    {
                        ++num;
                    }
                    if ((d_tmp & 0x4) == 0x4)
                    {
                        ++num;
                    }
                    if ((d_tmp & 0x8) == 0x8)
                    {
                        ++num;
                    }
                }
            }
            sqlite3_free_table(result);

            sql += "slice_ind=" + utoa(num) + ", slice_ack='" + s_ack + "' where file_id=" 
                    + utoa(q->f_id) + " and name='" + q->f_name + "'";

            ret = sqlite3_exec(db, sql.c_str(), NULL, NULL, &err_msg);
            if(ret)
            {
                sqlite3_free(err_msg);
                q->c++;
                if(q->c > MAX_RETRY_COUNT)
                {
                    pthread_mutex_lock(&g_lock);
                    g_sqls.pop_front();
                    pthread_mutex_unlock(&g_lock);
                    delete q;
                    continue;
                }
                else
                {
                    pthread_mutex_lock(&g_lock);
                    g_sqls.pop_front();
                    g_sqls.push_back(q);
                    pthread_mutex_unlock(&g_lock);
                    continue;
                }
            }
            else
            {
                pthread_mutex_lock(&g_lock);
                g_sqls.pop_front();;
                pthread_mutex_unlock(&g_lock);
                delete q;
                continue;
            }
        }
        else if(q->save_first.length())
        {
            row = 0;
            c = 0;
            ret = sqlite3_get_table(db , q->save_first.c_str(), &result, &row , &c , &err_msg);
            if (ret != 0) 
            {
                sqlite3_free(err_msg);
                q->c++;
                if(q->c > MAX_RETRY_COUNT)
                {
                    pthread_mutex_lock(&g_lock);
                    g_sqls.pop_front();
                    pthread_mutex_unlock(&g_lock);
                    delete q;
                    continue;
                }
                else
                {
                    pthread_mutex_lock(&g_lock);
                    g_sqls.pop_front();
                    g_sqls.push_back(q);
                    pthread_mutex_unlock(&g_lock);
                    continue;
                }
            }
            else
            {
                id  = 0;
                if(row > 0) 
                {
                    id = strtoul(result[c], NULL, 10);
                }
                sqlite3_free_table(result);

                if(id == 0)
                {
                    ret = sqlite3_exec(db, q->sql.c_str(), NULL, NULL, &err_msg);
                    if(ret)
                    {
                        sqlite3_free(err_msg);
                        q->c++;
                        if(q->c > MAX_RETRY_COUNT)
                        {
                            pthread_mutex_lock(&g_lock);
                            g_sqls.pop_front();
                            pthread_mutex_unlock(&g_lock);
                            delete q;
                            continue;
                        }
                        else
                        {
                            pthread_mutex_lock(&g_lock);
                            g_sqls.pop_front();
                            g_sqls.push_back(q);
                            pthread_mutex_unlock(&g_lock);
                            continue;
                        }
                    }
                    else
                    {
                        pthread_mutex_lock(&g_lock);
                        g_sqls.pop_front();
                        pthread_mutex_unlock(&g_lock);
                        delete q;
                        continue;
                    }
                }
                else
                {
                    pthread_mutex_lock(&g_lock);
                    g_sqls.pop_front();
                    pthread_mutex_unlock(&g_lock);
                    delete q;
                    continue;
                }
            }
        }
        else
        {
            ret = sqlite3_exec(db, q->sql.c_str(), NULL, NULL, &err_msg);
            if(ret)
            {
                sqlite3_free(err_msg);
                q->c++;
                if(q->c > MAX_RETRY_COUNT)
                {
                    pthread_mutex_lock(&g_lock);
                    g_sqls.pop_front();
                    pthread_mutex_unlock(&g_lock);
                    delete q;
                    continue;
                }
                else
                {
                    pthread_mutex_lock(&g_lock);
                    g_sqls.pop_front();
                    g_sqls.push_back(q);
                    pthread_mutex_unlock(&g_lock);
                    continue;
                }
            }
            else
            {
                pthread_mutex_lock(&g_lock);
                g_sqls.pop_front();
                pthread_mutex_unlock(&g_lock);
                delete q;
                continue;
            }
        }
    }

    return NULL;
}
#endif

/**
 * @brief init_db
 * 
 * @param file_name the db file name
 * @param err_msg the err msg ptr
 * @return int 0:success other:failed
 */
int init_db(char *file_name, char **err_msg)
{
    sqlite3_os_init();
    int rc;
    rc = sqlite3_open(file_name, &db);
    if (rc) 
    {       
        return rc;
    }

    char sql[] = "create table if not exists file_info("
        "id integer primary key,"
        "file_id integer,"	
        "app_id integer,"	
        "name varchar(128),"            // file name
        "size integer,"                    // file size
        "path varchar(128),"            // file path stored on disk or cloud.
        "slice_size integer,"            // unit:MB, file slice size  
        "slice_total integer,"        // total slice cout        
        "md5 char(32),"                    // md5 of file.
        "create_time timestamp not null default(strftime('%Y-%m-%d %H:%M:%S', 'now' ,'localtime')),"
        "finish_time timestamp,"
        "slice_ind integer,"        // numbers of slices have been sent.
        "slice_ack  TEXT,"      //record the slices ack, every bit slices
        "del integer default 0"
        ");";

    char sql1[] = "create table if not exists peer_info("
        "id integer primary key,"
        "source char(16),"
        "target char(16),"
        "ping_ok integer,"
        "create_time timestamp not null default(strftime('%Y-%m-%d %H:%M:%S', 'now' ,'localtime')),"
        "del integer default 0"
        ");";

    char sql2[] = "create table if not exists topo_info("
        "id integer primary key, "
        "source varchar(128),"        // ip address, 192.168.0.1
        "target varchar(128),"        // ip address, 192.168.0.2
        "loss integer,"                // unit:%, 2 means pkt loss = 2%
        "is_connected integer,"        // 1 means from source to target is connected.
        "available_bw integer,"        // unit: Mbps
        "capacity_bw integer,"        // unit: Mbps
        "latency integer,"            // unit: ms
        "type integer"                // 1: fiber, 2: twisted pair, 3: wireless
        ");";

    char sql3[] = "create table if not exists task_info("
        "id integer primary key,"
        "task_name char(128),"
        "app_id integer,"
        "data_size integer,"
        "slice_total integer,"
        "start_no integer,"
        "end_no integer,"
        "slice_sended integer,"
        "uid varchar(128),"
        "target varchar(128),"
        "zone integer,"
        "create_time timestamp not null default(strftime('%Y-%m-%d %H:%M:%S', 'now' ,'localtime')),"
        "update_time timestamp,"
        "interrupt_time timestamp,"
        "restart_time timestamp,"
        "cancel_time timestamp,"
        "finish_time timestamp,"
        "priority integer,"             // min = 0, max = 16
        "op_uid varchar(128),"
        "op_type integer,"
        "status integer,"                //-- 1:start, 2:interrupt, 3:finish, -1:stop
        "del integer default 0"             // unit: Mbps
        ");";
        
	if (!is_db_inited)
    {

        rc = sqlite3_exec(db, sql, NULL, NULL, err_msg);
		if(rc != 0)
        {
            return rc;
        }

        rc = sqlite3_exec(db, sql1, NULL, NULL, err_msg);
        if(rc != 0)
        {
            return rc;
        }

        rc  = sqlite3_exec(db, sql2, NULL, NULL, err_msg);
        if(rc != 0)
        {
            return rc;
        }

        rc = sqlite3_exec(db, sql3, NULL, NULL, err_msg);
        if(rc != 0)
        {
            return rc;
        }

        is_db_inited = true;

        #ifdef USED_THREAD_DO_SQL
        pthread_mutex_init(&g_lock, NULL);
        pthread_create(&pid, NULL, &exec_sql_thread, NULL);
        #endif
    }

    return rc;
}

/**
 * @brief Get the file by id name object
 * 
 * @param file_id the file id
 * @param name the file name 
 * @param rs thefile_rcf
 * @param err_msg the err msg ptr
 * @return int 0:success other:failed
 */
int get_file_by_id_name(uint32_t file_id, char *name,  struct file_rcd *rs,
        char **err_msg)
{
	if(!is_db_inited)
    {
        return -1;
    }

	string sql_base = "select id from file_info where del=0 and file_id=";
	string fid_str = utoa(file_id);
	string name_str = name;
	string sql = sql_base + fid_str + " and name='" + name_str + "' limit 1";
	int row = 0;
	int c = 0;
	char **result = NULL;

    #ifdef USED_THREAD_DO_SQL
    pthread_mutex_lock(&g_lock);
    #endif
	int rc = sqlite3_get_table(db , sql.c_str(), &result, &row , &c , err_msg);
    #ifdef USED_THREAD_DO_SQL
    pthread_mutex_unlock(&g_lock);
    #endif

	if (rc != 0) 
    {
		return rc;
	} 
	
	if(row > 0) 
    {
		rs->id = strtoul(result[c], NULL, 10);
	}

	sqlite3_free_table(result);

	return rc;
}

/**
 * @brief Get the file by md5 object
 * 
 * @param md5 the md5 ptr
 * @param rs 
 * @param err_msg the err msg ptr
 * @return int 0:success other:failed
 */
int get_file_by_md5(char *md5, struct file_rcd &rs, char **err_msg)
{
    if(!is_db_inited)
    {
        return -1;
    }

    string sql_base = "select id, file_id, app_id,  name, md5, size, slice_size, "
        "slice_total, slice_ind, path, create_time from file_info where del=0 and md5=";
    string md5_str = md5;
    string sql = sql_base + "'" + md5_str + "' limit 1";
    int row = 0;
    int c = 0;                //column
    char **result = NULL;
    int rc;

    #ifdef USED_THREAD_DO_SQL
    pthread_mutex_lock(&g_lock);
    #endif
    rc = sqlite3_get_table(db , sql.c_str(), &result, &row , &c , err_msg);
    #ifdef USED_THREAD_DO_SQL
    pthread_mutex_unlock(&g_lock);
    #endif

    if (rc != 0) 
    {  
        return rc;
    }
    
    if(row > 0) 
    {
        rs.id = atoi(result[c]);
        rs.file_id = strtoul(result[c+1], NULL, 10);
        rs.app_id = strtoul(result[c+2], NULL, 10);
        strcpy(rs.name, result[c+3]);
        strcpy(rs.md5, result[c+4]);
        rs.size = strtoul(result[c+5], NULL, 10);
        rs.slice_size = strtoul(result[c+6], NULL, 10);
        rs.slice_total = strtoul(result[c+7], NULL, 10);
        rs.slice_ind = strtoul(result[c+8], NULL, 10);
        strcpy(rs.path, result[c+9]);
        strcpy(rs.create_time, result[c+10]);

    }

    sqlite3_free_table(result);

    return rc;
}

/**
 * @brief Get the file by md5 name object
 * 
 * @param md5 the mdt ptr
 * @param name the file name
 * @param rs 
 * @param err_msg the err msg ptr
 * @return int 0:success other:failed
 */
int get_file_by_md5_name(char *md5, char *name,  struct file_rcd &rs, char **err_msg)
{
    if(!is_db_inited)
    {
        return -1;
    }

    string sql_base = "select id, file_id,app_id,  name, md5, size, slice_size, "
        "slice_total, slice_ind, path, create_time from file_info where del=0 and md5=";
    string md5_str = md5;
    string name_str = name;
    string sql = sql_base + "'" + md5_str + "' and name='" + name_str + "' limit 1";
    int row = 0;
    int c = 0;                //column
    char **result = NULL;
    int rc;

    #ifdef USED_THREAD_DO_SQL
    pthread_mutex_lock(&g_lock);
    #endif
    rc = sqlite3_get_table(db , sql.c_str(), &result, &row , &c , err_msg);
    #ifdef USED_THREAD_DO_SQL
    pthread_mutex_unlock(&g_lock);
    #endif

    if (rc != 0) 
    {
        return rc;
    }
    
    if(row > 0) 
    {
        rs.id = atoi(result[c]);
        rs.file_id = strtoul(result[c+1], NULL, 10);
        rs.app_id = strtoul(result[c+2], NULL, 10);
        strcpy(rs.name, result[c+3]);
        strcpy(rs.md5, result[c+4]);
        rs.size = strtoul(result[c+5], NULL, 10);
        rs.slice_size = strtoul(result[c+6], NULL, 10);
        rs.slice_total = strtoul(result[c+7], NULL, 10);
        rs.slice_ind = strtoul(result[c+8], NULL, 10);
        strcpy(rs.path, result[c+9]);
        strcpy(rs.create_time, result[c+10]);
    }

    sqlite3_free_table(result);

    return rc;
}

/**
 * @brief get_slice_ack_by_id
 * 
 * @param id 
 * @param slice_ind 
 * @param err_msg the err msg ptr
 * @return int 0:success other:failed
 */
int get_slice_ack_by_id(int id, char **slice_ack, char **err_msg)
{ 
	string sql_base = "select slice_ack";
    string s_id = itoa(id);
    string sql = sql_base + " from file_info where del=0 and id='" + 
                    s_id +  "' limit 1";

    int row = 0;
    int c = 0;                //column
    char **result = NULL;
    int rc;

    #ifdef USED_THREAD_DO_SQL
    pthread_mutex_lock(&g_lock);
    #endif
    rc = sqlite3_get_table(db , sql.c_str(), &result, &row , &c , err_msg);
    #ifdef USED_THREAD_DO_SQL
    pthread_mutex_unlock(&g_lock);
    #endif

    if (rc != 0) 
    {
        return rc;
    }
    
    if(row > 0) 
    {
        if(result[c])
        {
            strcpy(*slice_ack, result[c]);
        }
    }
    
    sqlite3_free_table(result);

    return rc;
}

/**
 * @brief Get the file slice no object
 * 
 * @param file_id the file id
 * @param name the file name
 * @param slice_no the result here
 * @param err_msg the err msg ptr
 * @return int 0:success other:failed
 */
int get_file_slice_no(uint32_t file_id,char *name, uint32_t *slice_no, char **err_msg)
{    
    if(!is_db_inited)
    {
        return -1;
    }

    string sql_base = "select slice_ack from file_info where file_id = ";
    string file_id_str = utoa(file_id); 
    string s_name = name;
    string sql = sql_base + file_id_str + " and name='" + s_name + "'" + " limit 1";
    int row = 0;
    int c = 0;                //column
    char **result = NULL;
    int rc;
    int i;
    int d_len;

    #ifdef USED_THREAD_DO_SQL
    pthread_mutex_lock(&g_lock);
    #endif
    rc = sqlite3_get_table(db , sql.c_str(), &result, &row , &c , err_msg);
    #ifdef USED_THREAD_DO_SQL
    pthread_mutex_unlock(&g_lock);
    #endif

    if (rc == 0) 
    {
        if(row)
        {
            *slice_no = 0;
            if(result[c])
            {
                d_len = strlen(result[c]);
                for(i = 0; i < d_len; ++i)
                {
                    if(result[c][i] != 'F')
                    {
                        if(result[c][i]=='E')
                        {
                            *slice_no += 3;
                        }
                        else if(result[c][i] == 'C')
                        {
                            *slice_no += 2;
                        }
                        else if(result[c][i] =='8')
                        {
                            *slice_no += 1;
                        }
                        break;
                    }
                    *slice_no += 4;
                }
            }
        }
    }

    sqlite3_free_table(result);
    return rc;
}


/**
 * @brief Get the file slice no object
 * 
 * @param file_id the db id
 * @param slice_no the result here
 * @param err_msg the err msg ptr
 * @return int 0:success other:failed
 */
int get_file_slice_no_by_id(uint id, uint32_t *slice_no, char **err_msg)
{    
    if(!is_db_inited)
    {
        return -1;
    }

    string sql_base = "select slice_ind from file_info where id = ";
    string file_id_str = itoa(id); 
    string sql = sql_base + file_id_str + " limit 1";
    int row = 0;
    int c = 0;                //column
    char **result = NULL;
    int rc;

    #ifdef USED_THREAD_DO_SQL
    pthread_mutex_lock(&g_lock);
    #endif
    rc = sqlite3_get_table(db , sql.c_str(), &result, &row , &c , err_msg);
    #ifdef USED_THREAD_DO_SQL
    pthread_mutex_unlock(&g_lock);
    #endif

    if (rc == 0) 
    {
        if(row)
        {
            *slice_no = strtoul(result[c], NULL, 10);
        }
    }

    sqlite3_free_table(result);
    return rc;
}

/**
 * @brief delete_file_by_md5
 * 
 * @param md5 
 * @param err_msg the err msg ptr
 * @return int 0:success other:failed
 */
int delete_file_by_md5(char *md5,char **err_msg)
{
    if(!is_db_inited)
    {
        return -1;
    }

    string sql_base = "update file_info set del=1 where del=0 and md5=";
    string md5_str = md5;
    string sql = sql_base + "'" + md5_str + "'";

    #ifdef USED_THREAD_DO_SQL
    sql_queue_t *q = new sql_queue_t;
    if(q == NULL)
    {
        return -1;
    }
    q->save_first.clear();
    q->c = 0;
    q->f_id = 0;
    q->sql = sql;
    // pthread_mutex_lock(&g_lock);
    g_sqls.push_back(q);
    // pthread_mutex_unlock(&g_lock);
    return 0;
    #else
    return sqlite3_exec(db, sql.c_str(), NULL, NULL, err_msg);
    #endif
}

/**
 * @brief save_file_info
 * 
 * @param rs 
 * @param err_msg the err msg ptr
 * @return int 0:success other:failed
 */
int save_file_info(struct file_rcd &rs,char **err_msg)
{
    if(!is_db_inited)
    {
        return -1;
    }

    string sql_base = "insert into 'file_info'(file_id, app_id, name, md5, size, "
        "slice_size, slice_total,slice_ind, path) VALUES ("; 

    string name = rs.name;
    string md5 = rs.md5;
    string size = lutoa(rs.size);
    string f_id = utoa(rs.file_id);
    string app_id = utoa(rs.app_id);
    string path = rs.path;
    string s_s = utoa(rs.slice_size);
    string s_t = utoa(rs.slice_total);
    string s_sd = utoa(rs.slice_ind);
    string sql = sql_base + "'" + f_id + "'," + "'" + app_id + "','"\
            + name + "','" + md5 + "'," + size \
            + "," + s_s + "," + s_t + "," + s_sd + ",'"+ path + "')" ;

    #ifdef USED_THREAD_DO_SQL

    sql_queue_t *q = new sql_queue_t;
    if(q == NULL)
    {
        return -1;
    }

    q->c = 0;
    q->f_id = 0;
    q->save_first.clear();

    string name_str = rs.name;

    q->save_first = "select id from file_info where del=0 and file_id=" +
            utoa(rs.file_id) + " and name='" + name_str + "' limit 1";

    q->sql = sql;

    g_sqls.push_back(q);
    return 0;

    #else
    struct file_rcd f = {0};
    int rc = get_file_by_id_name(rs.file_id, rs.name, &f, err_msg);
    if(rc != 0)
    {
        return rc;
    }

    if(f.id)
    {
        return 0;
    }

    rc = sqlite3_exec(db, sql.c_str(), NULL, NULL, err_msg);
    return rc;
    #endif
}

/**
 * @brief update_slice_no_by_id
 * 
 * @param id 
 * @param slice_ind 
 * @param err_msg the err msg ptr
 * @return int 0:success other:failed
 */
int update_slice_no_by_id_and_name(uint32_t file_id, char *name,
            char *slice_ack, char **err_msg)
{ 
    #ifdef USED_THREAD_DO_SQL
    sql_queue_t *q = new sql_queue_t;
    if(q == NULL)
    {
        return -1;
    }
    q->save_first.clear();
    q->c = 0;
    q->f_id = file_id;
    q->f_name = name;
    q->sql = slice_ack;
    // pthread_mutex_lock(&g_lock);
    g_sqls.push_back(q);
    // pthread_mutex_unlock(&g_lock);
    return 0;

    #else
    return sqlite3_exec(db, sql.c_str(), NULL, NULL, err_msg);
    #endif
}

/**
 * @brief update_md5_and_finish_by_id
 * 
 * @param id 
 * @param md5 
 * @param err_msg the err msg ptr
 * @return int 0:success other:failed
 */
int update_md5_and_finish_by_id_and_name(uint32_t file_id, char *name, 
    char *md5, time_t t, char **err_msg)
{ 
	string sql_base = "update 'file_info' ";
    string s_md5 = md5;
    string s_id = utoa(file_id);
    string s_name = name;
    struct tm *tmp;
    tmp = localtime(&t);
    char st[20] = {0};
    strftime(st, 20, "%Y-%m-%d %H:%M:%S", tmp);
    string s_st = st;
    string sql = sql_base + "set md5='" + s_md5 + 
            "', finish_time='" + s_st + "' where file_id='" + s_id + "' and name='"
            + s_name + "'";

    #ifdef USED_THREAD_DO_SQL
    sql_queue_t *q = new sql_queue_t;
    if(q == NULL)
    {
        return -1;
    }
    q->save_first.clear();
    q->c = 0;
    q->f_id = 0;
    q->sql = sql;
    // pthread_mutex_lock(&g_lock);
    g_sqls.push_back(q);
    // pthread_mutex_unlock(&g_lock);
    return 0;
    #else
    return sqlite3_exec(db, sql.c_str(), NULL, NULL, err_msg);
    #endif
}

/**
 * @brief update_md5_by_id
 * 
 * @param id 
 * @param md5 
 * @param err_msg the err msg ptr
 * @return int 0:success other:failed
 */
int update_md5_by_id_and_name(uint32_t file_id, char *name, char *md5, 
            char **err_msg)
{ 
	string sql_base = "update 'file_info' ";
    string s_md5 = md5;
    string s_id = utoa(file_id);
    string s_name = name;

    string sql = sql_base + "set md5='" + s_md5 + "' where file_id='" 
        + s_id + "' and name='" + s_name + "'";

    #ifdef USED_THREAD_DO_SQL
    sql_queue_t *q = new sql_queue_t;
    if(q == NULL)
    {
        return -1;
    }
    q->save_first.clear();
    q->c = 0;
    q->f_id = 0;
    q->sql = sql;
    // pthread_mutex_lock(&g_lock);
    g_sqls.push_back(q);
    // pthread_mutex_unlock(&g_lock);
    return 0;
    #else
    return sqlite3_exec(db, sql.c_str(), NULL, NULL, err_msg);
    #endif
}

/**
 * @brief update_file_info
 * 
 * @param rs 
 * @param err_msg the err msg ptr
 * @return int 0:success other:failed
 */
int update_file_info(struct file_rcd &rs,char **err_msg)
{
    if(!is_db_inited)
    {
        return -1;
    }

    string sql_base = "update 'file_info' ";
    string name = rs.name;
    string md5 = rs.md5;
    string size = utoa(rs.size);
    string s_s = utoa(rs.slice_size);
    string s_t = utoa(rs.slice_total);
    string s_sd = utoa(rs.slice_ind);
    string path = rs.path;
    string sql = sql_base + "set name= '" + name + "', size= " 
        + size + ", slice_size=" + s_s + ", slice_total=" + s_t + 
        ", slice_ind=" + s_sd + "," + " path= '" + path + "' where md5='" + md5 + "'";

    #ifdef USED_THREAD_DO_SQL
    sql_queue_t *q = new sql_queue_t;
    if(q == NULL)
    {
        return -1;
    }
    q->save_first.clear();
    q->c = 0;
    q->f_id = 0;
    q->sql = sql;
    // pthread_mutex_lock(&g_lock);
    g_sqls.push_back(q);
    // pthread_mutex_unlock(&g_lock);
    return 0;
    #else
    return sqlite3_exec(db, sql.c_str(), NULL, NULL, err_msg);
    #endif

}

int update_file_md5_info(struct file_rcd &rs,char **err_msg)
{
    if(!is_db_inited)
    {
        return -1;
    }

    string sql_base = "update 'file_info' ";
    string name = rs.name;
    string md5 = rs.md5;
    string size = utoa(rs.size);
    string s_s = utoa(rs.slice_size);
    string s_t = utoa(rs.slice_total);
    string s_sd = utoa(rs.slice_ind);
    string path = rs.path;
    string sql = sql_base + "set name= '" + name + "', size= " 
        + size + ", slice_size=" + s_s + ", slice_total=" + s_t + 
        ", slice_ind=" + s_sd + "," + " path= '" + path + "' where md5='" + md5 + "'";

    #ifdef USED_THREAD_DO_SQL
    sql_queue_t *q = new sql_queue_t;
    if(q == NULL)
    {
        return -1;
    }
    q->save_first.clear();
    q->c = 0;
    q->f_id = 0;
    q->sql = sql;
    // pthread_mutex_lock(&g_lock);
    g_sqls.push_back(q);
    // pthread_mutex_unlock(&g_lock);
    return 0;
    #else
    return sqlite3_exec(db, sql.c_str(), NULL, NULL, err_msg);
    #endif

}

/**
 * @brief Get the peer info object
 * 
 * @param source 
 * @param target 
 * @param err_msg the err msg prr
 * @return int 0:success other:failed
 */
int get_peer_info(char *source, char *target,char **err_msg )
{
    if(!is_db_inited)
    {
        return -1; 
    }

    string sql_base = "select source,target ping_ok, create_time from peer_info where del = 0 and ";
    string s = source;
    string t = target;
    string sql = sql_base + "source='" + s + "' and target='" + t + "' limit 1";
    int row = 0;
    int c = 0;                //column
    char **result = NULL;

    return sqlite3_get_table(db , sql.c_str(), &result, &row , &c , err_msg);

}

/**
 * @brief update_peer_info
 * 
 * @param source 
 * @param target 
 * @param err_msg the err msg ptr
 * @return int 0:success other:failed
 */
int update_peer_info(char *source, char *target,char **err_msg)
{
    if(source == NULL || target == NULL)
    {
        return -1;
    }

    if(!is_db_inited)
    {
        return -1;
    }

    string sql_base = "update peer_info set ping_ok=1 where del=0 and ";
    string s_str = source;
    string t_str = target;
    string sql = sql_base + "source ='" + s_str + "' and target='" + t_str;

    #ifdef USED_THREAD_DO_SQL
    sql_queue_t *q = new sql_queue_t;
    if(q == NULL)
    {
        return -1;
    }
    q->save_first.clear();
    q->c = 0;
    q->f_id = 0;
    q->sql = sql;
    // pthread_mutex_lock(&g_lock);
    g_sqls.push_back(q);
    // pthread_mutex_unlock(&g_lock);
    return 0;
    #else
    return sqlite3_exec(db, sql.c_str(), NULL, NULL, err_msg);
    #endif
}

/**
 * @brief insert_peer_info
 * 
 * @param source 
 * @param target 
 * @param err_msg the err msg ptr
 * @return int 0:success other:failed
 */
int insert_peer_info(char *source, char *target,char **err_msg)
{
    if(source == NULL || target == NULL)
    {
        return -1;
    }

    if(!is_db_inited)
    {
        return -1;
    }

    string sql_base = "insert into 'peer_info'(source, target, ping_ok) VALUES ("; 
    string s_str = source;
    string t_str = target;
    string ping_str ="1" ;
    string sql = sql_base + "'" + s_str + "','" + t_str + "'," +ping_str + ")" ;

    #ifdef USED_THREAD_DO_SQL
    sql_queue_t *q = new sql_queue_t;
    if(q == NULL)
    {
        return -1;
    }
    q->save_first.clear();
    q->c = 0;
    q->f_id = 0;
    q->sql = sql;
    // pthread_mutex_lock(&g_lock);
    g_sqls.push_back(q);
    // pthread_mutex_unlock(&g_lock);
    return 0;
    #else
    return sqlite3_exec(db, sql.c_str(), NULL, NULL, err_msg);
    #endif

}

/**
 * @brief save_task_info
 * 
 * @param rs 
 * @param err_msg the err msg ptr
 * @return int 0:success other:failed
 */
int save_task_info(struct task_rcd &rs, char **err_msg)
{
    if(!is_db_inited)
    {
        return -1;
    }
    int rc;

    string sql_base = "insert into task_info(app_id, uid, task_name, target, zone, "
        "status) VALUES (";
    string app_id = itoa(rs.app_id);
    string name = rs.task_name;
    string zone = itoa(rs.zone);
    string uid = rs.uid;
    string target = rs.target;
    string status = itoa(1);
    string sql = sql_base + app_id + ",'" + uid + "','" + name + "','" + target + "'," \
        + zone + ","  + status + ")" ;

    #ifdef USED_THREAD_DO_SQL
    pthread_mutex_lock(&g_lock);
    #endif
    rc = sqlite3_exec(db, sql.c_str(), NULL, NULL, err_msg);
    #ifdef USED_THREAD_DO_SQL
    pthread_mutex_unlock(&g_lock);
    #endif

    return rc;
}

/**
 * @brief update_task_status_by_uid
 * 
 * @param status the task status
 * @param uid the task uuid
 * @param err_msg the err msg ptr
 * @return int 0:success other:failed
 */
int update_task_status_by_uid(int status, char *uid, char **err_msg)
{
    if(!is_db_inited)
    {
        return -1;
    }

	string sql_base = "update task_info set ";
	string s_stat = itoa(status);
	string s_uid = uid;
	string sql = sql_base + "status =" + s_stat + " where uid='" + s_uid + "'";

    #ifdef USED_THREAD_DO_SQL
    sql_queue_t *q = new sql_queue_t;
    if(q == NULL)
    {
        return -1;
    }
    q->save_first.clear();
    q->c = 0;
    q->f_id = 0;
    q->sql = sql;
    // pthread_mutex_lock(&g_lock);
    g_sqls.push_back(q);
    // pthread_mutex_unlock(&g_lock);
    return 0;
    #else
    return sqlite3_exec(db, sql.c_str(), NULL, NULL, err_msg);
    #endif
}

/**
 * @brief update_task_finish_by_uid
 * 
 * @param t the finish time
 * @param uid the task uuid
 * @param err_msg the err msg ptr
 * @return int 0:success other:failed
 */
int update_task_finish_by_uid(char *uid, time_t t, char **err_msg)
{
    if(!is_db_inited)
    {
        return -1;
    }

    
	string sql_base = "update task_info set ";
	string s_stat = itoa(3);
	string s_uid = uid;
    struct tm *tmp;
    tmp = localtime(&t);
    char st[20] = {0};
    strftime(st, 20, "%Y-%m-%d %H:%M:%S", tmp);
    string s_st = st;
	string sql = sql_base + " status =" + s_stat + ", finish_time='"+  s_st\
                + "' where uid='" + s_uid + "'";

    #ifdef USED_THREAD_DO_SQL
    sql_queue_t *q = new sql_queue_t;
    if(q == NULL)
    {
        return -1;
    }
    q->save_first.clear();
    q->c = 0;
    q->f_id = 0;
    q->sql = sql;
    // pthread_mutex_lock(&g_lock);
    g_sqls.push_back(q);
    // pthread_mutex_unlock(&g_lock);
    return 0;
    #else
    return sqlite3_exec(db, sql.c_str(), NULL, NULL, err_msg);
    #endif
}


/**
 * @brief update_task_stop_by_uid
 * 
 * @param t the finish time
 * @param uid the task uuid
 * @param err_msg the err msg ptr
 * @return int 0:success other:failed
 */
int update_task_stop_by_uid(char *uid, time_t t, char **err_msg)
{
    if(!is_db_inited)
    {
        return -1;
    }

	string sql_base = "update task_info set ";
	string s_stat = itoa(2);
	string s_uid = uid;
    struct tm *tmp;
    tmp = localtime(&t);
    char st[20] = {0};
    strftime(st, 20, "%Y-%m-%d %H:%M:%S", tmp);
    string s_st = st;
	string sql = sql_base + " status =" + s_stat + ", interrupt_time='"+  s_st\
                + "' where uid='" + s_uid + "'";

    #ifdef USED_THREAD_DO_SQL
    sql_queue_t *q = new sql_queue_t;
    if(q == NULL)
    {
        return -1;
    }
    q->save_first.clear();
    q->c = 0;
    q->f_id = 0;
    q->sql = sql;

    // pthread_mutex_lock(&g_lock);
    g_sqls.push_back(q);
    // pthread_mutex_unlock(&g_lock);
    return 0;
    #else
    return sqlite3_exec(db, sql.c_str(), NULL, NULL, err_msg);
    #endif
}

/**
 * @brief update_task_restart_by_uid
 * 
 * @param t the restart time
 * @param uid the task uuid
 * @param err_msg the err msg ptr
 * @return int 0:success other:failed
 */
int update_task_restart_by_uid(char *uid, time_t t, char **err_msg)
{
    if(!is_db_inited)
    {
        return -1;
    }

	string sql_base = "update task_info set ";
	string s_stat = itoa(1);
	string s_uid = uid;
    struct tm *tmp;
    tmp = localtime(&t);
    char st[20] = {0};
    strftime(st, 20, "%Y-%m-%d %H:%M:%S", tmp);
    string s_st = st;

	string sql = sql_base + " status =" + s_stat + ", restart_time='"+  s_st\
                + "' where uid='" + s_uid + "'";

    #ifdef USED_THREAD_DO_SQL
    sql_queue_t *q = new sql_queue_t;
    if(q == NULL)
    {
        return -1;
    }
    q->save_first.clear();
    q->c = 0;
    q->f_id = 0;
    q->sql = sql;
    // pthread_mutex_lock(&g_lock);
    g_sqls.push_back(q);
    // pthread_mutex_unlock(&g_lock);
    return 0;
    #else
    return sqlite3_exec(db, sql.c_str(), NULL, NULL, err_msg);
    #endif
}

/**
 * @brief update_task_datas_by_uid
 * 
 * @param data_size the task data
 * @param total the total bags
 * @param uid the uuid 
 * @param err_msg the err msg ptr
 * @return int 0:success other:failed
 */
int update_task_datas_by_uid(uint64_t data_size, uint32_t total,
        uint32_t start_no, uint32_t end_no, char *uid, char **err_msg)
{
    if(!is_db_inited)
    {
        return -1;
    }

	string sql_base = "update task_info set ";
    string s_data = lutoa(data_size);
    string s_st = utoa(total);
    string s_s_no = utoa(start_no);
    string s_e_no = utoa(end_no);
	string s_uid = uid;
	string sql = sql_base + "data_size=" + s_data + ",slice_total=" \
                + s_st + ", start_no=" + s_s_no + ", end_no=" 
                + s_e_no + " where uid='" + s_uid + "'";

    #ifdef USED_THREAD_DO_SQL
    sql_queue_t *q = new sql_queue_t;
    if(q == NULL)
    {
        return -1;
    }
    q->save_first.clear();
    q->c = 0;
    q->f_id = 0;
    q->sql = sql;
    // pthread_mutex_lock(&g_lock);
    g_sqls.push_back(q);
    // pthread_mutex_unlock(&g_lock);
    return 0;
    #else
    return sqlite3_exec(db, sql.c_str(), NULL, NULL, err_msg);
    #endif
}

/**
 * @brief update_task_slice_by_uid
 * 
 * @param ind the task send ind
 * @param uid the task uuid
 * @param err_msg the err msg ptr
 * @return int 0:success other:failed
 */
int update_task_slice_by_uid(uint32_t ind, char *uid, char **err_msg)
{
    if(!is_db_inited)
    {
        return -1;
    }

	string sql_base = "update task_info set ";
    string s_ind = utoa(ind);
	string s_uid = uid;
	string sql = sql_base + "slice_sended=" + s_ind + " where uid='" + s_uid + "'";

    #ifdef USED_THREAD_DO_SQL
    sql_queue_t *q = new sql_queue_t;
    if(q == NULL)
    {
        return -1;
    }
    q->save_first.clear();
    q->c = 0;
    q->f_id = 0;
    q->sql = sql;
    // pthread_mutex_lock(&g_lock);
    g_sqls.push_back(q);
    // pthread_mutex_unlock(&g_lock);
    return 0;
    #else
    return sqlite3_exec(db, sql.c_str(), NULL, NULL, err_msg);
    #endif
}
/**
 * @brief update_task_info
 * 
 * @param rs 
 * @param err_msg the err msg ptr
 * @return int 0:success other:failed
 */
int update_task_info(struct task_rcd &rs, char **err_msg)
{
    if(!is_db_inited)
    {
        return -1;
    }

    string sql_base = "update task_info set ";
    string id = itoa(rs.id);
    string app_id = itoa(rs.app_id);
    string data_size = itoa(rs.data_size);
    string target = rs.target;
    string zone = itoa(rs.zone);
    string priority = itoa(rs.priority);
    string status = itoa(rs.status);
    string sql = sql_base + "app_id = '" + app_id + "',data_size='" + data_size 
        + "',target='" + target + "', zone='" + zone 
        + ",status=" + status + " where id = " + id ;

    #ifdef USED_THREAD_DO_SQL
    sql_queue_t *q = new sql_queue_t;
    if(q == NULL)
    {
        return -1;
    }
    q->save_first.clear();
    q->c = 0;
    q->f_id = 0;
    q->sql = sql;
    // pthread_mutex_lock(&g_lock);
    g_sqls.push_back(q);
    // pthread_mutex_unlock(&g_lock);
    return 0;
    #else
    return sqlite3_exec(db, sql.c_str(), NULL, NULL, err_msg);
    #endif

}

/**
 * @brief Get the task stop by uuid object
 * 
 * @param uuid the task uid
 * @param status the result ptr
 * @param err_msg the err msg ptr
 * @return int 0:success other:failed
 */
int get_task_status_by_uuid(char *uuid, int *status, char **err_msg)
{
    if(!is_db_inited)
    {
        return -1;
    }

    string sql_base = "select status from task_info where del=0 and uid='";
    string s_uuid = uuid;
    string sql = sql_base +  s_uuid + "' limit 1";
    int row = 0;
    int c = 0;                //column
    char **result = NULL;
    int rc;

    #ifdef USED_THREAD_DO_SQL
    pthread_mutex_lock(&g_lock);
    #endif
    rc = sqlite3_get_table(db , sql.c_str(), &result, &row , &c , err_msg);
    #ifdef USED_THREAD_DO_SQL
    pthread_mutex_unlock(&g_lock);
    #endif

    if (rc != 0) 
    {
        return rc;
    }
    
    if(row > 0) 
    {
        *status = atoi(result[c]);
    }

    sqlite3_free_table(result);

    return rc;
}

/**
 * @brief delete_update_task_info
 * 
 * @param uuid the task uuid
 * @param err_msg the err msg ptr
 * @return int 0:success other:failed
 */
int delete_update_task_info(char *uuid, char **err_msg)
{
    if(!is_db_inited)
    {
        return -1;
    }

    string sql_base = "update task_info set ";
    string id_str = uuid;

    string sql = sql_base + "del = 1  where uid = '" + id_str + "'";

    #ifdef USED_THREAD_DO_SQL
    sql_queue_t *q = new sql_queue_t;
    if(q == NULL)
    {
        return -1;
    }
    q->save_first.clear();
    q->c = 0;
    q->f_id = 0;
    q->sql = sql;
    // pthread_mutex_lock(&g_lock);
    g_sqls.push_back(q);
    // pthread_mutex_unlock(&g_lock);
    return 0;
    #else
    return sqlite3_exec(db, sql.c_str(), NULL, NULL, err_msg);
    #endif

}

/**
 * @brief Get the task by uid object
 * 
 * @param rs 
 * @param uid 
 * @param err_msg the err msg ptr
 * @return int 0:success other:failed
 */
int get_task_by_uid(struct task_rcd &rs, char *uid, char **err_msg)
{
    if(!is_db_inited)
    {
        return -1;
    }

    string sql_base = "select id, app_id, data_size, uid, target, zone, create_time, "
        "interrupt_time, restart_time, cancel_time, priority, progress, "
        "op_uid, op_type, status from task_info where 1=1 ";
    string uid_str = uid;
    string sql = sql_base + "and uid='" + uid_str + "' order by create_time desc limit 10";
    int row = 0;
    int c = 0;                //column
    char **result = NULL;

    return sqlite3_get_table(db , sql.c_str(), &result, &row , &c , err_msg);
    
}

/**
 * @brief Get the topo list object
 * 
 * @param rs_list 
 * @param err_msg the error msg ptr
 * @return int 0:success other:failed
 */
int get_topo_list(list<struct topo_rcd*> &rs_list, char **err_msg)
{
    if(!is_db_inited)
    {
        return -1;
    }

    string sql_base = "select id, source, target, loss, is_connected, available_bw, capacity_bw,"
        "latency, create_time, update_time where is_connected = 1 limit 100";
    string sql = sql_base;
    int row = 0;
    int c = 0;                //column
    char **result = NULL;
    int rc;

    #ifdef USED_THREAD_DO_SQL
    pthread_mutex_lock(&g_lock);
    #endif
    rc = sqlite3_get_table(db , sql.c_str(), &result, &row , &c , err_msg);
    #ifdef USED_THREAD_DO_SQL
    pthread_mutex_unlock(&g_lock);
    #endif

    if (rc == 0) 
    {

        struct topo_rcd *rs;
        rs = (struct topo_rcd *)malloc(sizeof(struct topo_rcd));
        if(rs == NULL)
        {
            sqlite3_free_table(result);
            return -2;
        }
        for (int i = 0; i < (row+1) * c; i++) 
        {
            if (i % c == 1)
                rs->source = result[i];
            else if (i % c == 2)
                rs->target  = result[i];
            else if (i % c == (c-1))
                rs_list.push_back(rs);
            //cout << result[i] << endl;
        }

    }

    sqlite3_free_table(result);
    return rc;
    
}

/**
 * @brief save_topo_info
 * 
 * @param rs 
 * @param err_msg the err msg ptr
 * @return int 0:success other:failed
 */
int save_topo_info(struct topo_rcd &rs, char **err_msg)
{
    if(!is_db_inited)
    {
        return -1;
    }
    string sql_base = "insert into 'topo_info'(source, target, loss, is_connected, available_bw, capacity_bw, latency, type) VALUES (";
    string source = rs.source;
    string target = rs.target;
    string loss = itoa(rs.loss);
    string is_connected = rs.is_connected ? "1" : "0";
    string available_bw = itoa(rs.available_bw);
    string capacity_bw = itoa(rs.capacity_bw);
    string latency = itoa(rs.latency);
    string type = itoa(rs.type);
    string sql = sql_base + "'" + source + "','" + target + "'," + loss + "," \
        + is_connected + ",'" + available_bw + "','" + capacity_bw    + "'," + latency + "," + type + ")" ;

    #ifdef USED_THREAD_DO_SQL
    sql_queue_t *q = new sql_queue_t;
    if(q == NULL)
    {
        return -1;
    }
    q->save_first.clear();
    q->c = 0;
    q->f_id = 0;
    q->sql = sql;
    // pthread_mutex_lock(&g_lock);
    g_sqls.push_back(q);
    // pthread_mutex_unlock(&g_lock);
    return 0;
    #else
    return sqlite3_exec(db, sql.c_str(), NULL, NULL, err_msg);
    #endif
  
}

/**
 * @brief update_topo_info
 * 
 * @param rs 
 * @param err_msg the err msg ptr
 * @return int 0:success other:failed
 */
int update_topo_info(struct topo_rcd &rs, char **err_msg)
{
    if(!is_db_inited)
    {
        return -1;
    }

    string sql_base = "update 'topo_info' set ";
    string source = rs.source;
    string target = rs.target;
    string id = itoa(rs.id);
    string loss = itoa(rs.loss);
    string is_connected = rs.is_connected ? "1" : "0";
    string available_bw = itoa(rs.available_bw);
    string capacity_bw = itoa(rs.capacity_bw);
    string latency = itoa(rs.latency);
    string type = itoa(rs.type);
    string sql = sql_base + " source='" + source + "', target='" + target + "', loss='" 
        + loss + "', is_connected='" + is_connected + ", available_bw=" + available_bw + 
        ", capacity_bw=" + capacity_bw    + ", latency=" + latency + ", type=" + type + " where id =" + id;

    #ifdef USED_THREAD_DO_SQL
    sql_queue_t *q = new sql_queue_t;
    if(q == NULL)
    {
        return -1;
    }
    q->save_first.clear();
    q->c = 0;
    q->f_id = 0;
    q->sql = sql;
    // pthread_mutex_lock(&g_lock);
    g_sqls.push_back(q);
    // pthread_mutex_unlock(&g_lock);
    return 0;
    #else
    return sqlite3_exec(db, sql.c_str(), NULL, NULL, err_msg);
    #endif

}

//get topology detail with topo from "source" to "target" 
/**
 * @brief Get the topo info object
 * 
 * @param source 
 * @param target 
 * @param rs 
 * @param err_msg the err msg ptr
 * @return int 0:success other:failed
 */
int get_topo_info(char *source, char *target, struct topo_rcd &rs, char **err_msg)
{
    if(!is_db_inited)
    {
        return -1;
    }

    string sql_base = "select id, source, target, loss, available_bw, capacity_bw,"
        "latency, create_time, update_time from topo_info where is_connected = 1 limit 1";
    string sql = sql_base;
    int row = 0;
    int c = 0;                //column
    char **result = NULL;
    int rc;

    #ifdef USED_THREAD_DO_SQL
    pthread_mutex_lock(&g_lock);
    #endif
    rc = sqlite3_get_table(db , sql.c_str(), &result, &row , &c , err_msg);
    #ifdef USED_THREAD_DO_SQL
    pthread_mutex_unlock(&g_lock);
    #endif

    if (rc == 0) 
    {
        if(row)
        {
            rs.id = atoi(result[c]);
            rs.source = result[c+1];
            rs.target = result[c+2];
            rs.loss = atoi(result[c+3]);
            rs.available_bw = atoi(result[c+4]);
            rs.capacity_bw = atoi(result[c+5]);
            rs.latency = atoi(result[c+6]);
            rs.create_time = result[c+7];
            rs.update_time = result[c+8];
            //cout << result[i] << endl;
        }
    }

    sqlite3_free_table(result);
    return rc;
}

/**
 * @brief Get the task file receiver object
 * 
 * @param task_id the task id
 * @param file_id  the file id
 * @param receiver_list the result list
 * @param err_msg the err msg ptr
 * @return int -1:failed other:the result nums
 */
int get_task_file_receiver(int task_id, int file_id, char **receiver_list, char **err_msg)
{
    if(!is_db_inited)
    {
        return -1;
    }

    string sql_base = "select id, target from task_info where id = ";
    string task_id_str = itoa(task_id);
    string sql = sql_base + task_id_str + " limit 1";
    int row = 0;
    int c = 0;                //column
    char **result = NULL;
    int rc;

    #ifdef USED_THREAD_DO_SQL
    pthread_mutex_lock(&g_lock);
    #endif
    rc = sqlite3_get_table(db , sql.c_str(), &result, &row , &c , err_msg);
    #ifdef USED_THREAD_DO_SQL
    pthread_mutex_unlock(&g_lock);
    #endif

    if (rc == 0) 
    {
        if(row)
        {
            rc = split_str(result[2], (char*)";", receiver_list);
        }
    } 

    sqlite3_free_table(result);
    return rc;
}

/**
 * @brief Get the task status object
 * 
 * @param task_id the task id
 * @param err_msg the err msg pr
 * @return int 0:success other:failed
 */
int get_task_status(int task_id, char **err_msg)
{
    if(!is_db_inited)
    {
        return -1;
    }

    string sql_base = "select status from task_info where id = ";
    string task_id_str = itoa(task_id);
    string sql = sql_base + task_id_str + " limit 1";
    int row = 0;
    int c = 0;                //column
    char **result = NULL;
    int status;

    #ifdef USED_THREAD_DO_SQL
    pthread_mutex_lock(&g_lock);
    #endif
    status = sqlite3_get_table(db , sql.c_str(), &result, &row , &c , err_msg);
    #ifdef USED_THREAD_DO_SQL
    pthread_mutex_unlock(&g_lock);
    #endif

    if (status == 0)
    {
        if(row > 0)
        {
            status = atoi(result[c]);
        }
    } 

    sqlite3_free_table(result);
    return status;
}

/**
 * @brief Get the last task data rate object
 * 
 * @param err_msg the err msg ptr
 * @return int -1:failed other:success
 */
int get_last_task_data_rate(char **err_msg)
{    
    if(!is_db_inited)
    {
        return -1;
    }

    string sql = "select max(id) from task_info";
    int row = 0;
    int c = 0;                //column
    char **result = NULL;

    #ifdef USED_THREAD_DO_SQL
    pthread_mutex_lock(&g_lock);
    #endif
    int rc = sqlite3_get_table(db , sql.c_str(), &result, &row , &c , err_msg);
    #ifdef USED_THREAD_DO_SQL
    pthread_mutex_unlock(&g_lock);
    #endif

    int max_id = 0;
    char max_id_c[32] = {0};
    if (rc == 0)
    {
        if(row)
        {
            max_id = atoi(result[c]);
            strcpy(max_id_c, result[c]);
        }
    } 
    else 
    {
        sqlite3_free_table(result);
        return rc;
    }

    if (max_id == 0)
    {
        sqlite3_free_table(result);
        return -1;
    }

    string max_id_s = max_id_c;
    sql = "select start_no, end_no, slice_send from task_info where id = " + max_id_s;
    row = 0;
    c = 0; 
    result = NULL;

    #ifdef USED_THREAD_DO_SQL
    pthread_mutex_lock(&g_lock);
    #endif
    rc = sqlite3_get_table(db , sql.c_str(), &result, &row , &c , err_msg);
    #ifdef USED_THREAD_DO_SQL
    pthread_mutex_unlock(&g_lock);
    #endif

    int data_rate = -1;
    if (rc == 0) 
    {
        if(row && c)
        {
            data_rate = (atoi(result[c+1]) + 1 -atoi(result[c]))/atoi(result[c+2]);
        }
    }

    sqlite3_free_table(result);
    return data_rate;
=======
#include "db.h"

using namespace std;

static log4c_category_t* mycat = NULL;
	
static char file_name[] = "./test.db";

// database init flag
static bool is_db_inited = false; 

static string itoa(int i);

static void log_init()
{
	log4c_init();
	mycat = log4c_category_get("tp.db");
}

void init_db(sqlite3 **db)
{
	sqlite3_os_init();
	int rc;
	rc = sqlite3_open(file_name, db);
	if (rc) {
		log4c_category_log(mycat, LOG4C_PRIORITY_ERROR,
			"db file %s open error, at %d in %s ",
			file_name, __LINE__, __FILE__);
	} else {
		log4c_category_log(mycat, LOG4C_PRIORITY_DEBUG,
			"db file %s open success, at %d in %s ",
			file_name, __LINE__, __FILE__);
	}
	if (is_db_inited) {
		log4c_category_log(mycat, LOG4C_PRIORITY_DEBUG,
			"db inited, at %d in %s ",
			__LINE__, __FILE__);
	} else {
		char *err_msg = NULL;
		char sql[] = " create table if not exists file_info("
			"id integer primary key,"
			"app_id integer,"
			"file_id integer,"
			"name varchar(128),"			// file name
			"size integer,"					// file size
			"path varchar(128),"			// file path stored on disk or cloud.
			"slice_size integer,"			// unit:MB, file slice size  
			"slice_total integer,"		// total slice cout
			"slice_snd integer,"		// numbers of slices have been sent.
			"md5 char(32),"					// md5 of file.
			"create_time timestamp not null default(strftime('%Y-%m-%d %H:%M:%f', 'now' ,'localtime')),"
			"update_time timestamp not null default(strftime('%Y-%m-%d %H:%M:%f', 'now' ,'localtime')),"
			"del integer default 0"
			");";
		sqlite3_exec(*db, sql, NULL, NULL, &err_msg);
		log4c_category_log(mycat, LOG4C_PRIORITY_DEBUG,
			"sql=%s, err=%s, at %d in %s ",
			sql, err_msg, __LINE__, __FILE__);
		sqlite3_free(err_msg);
		char sql1[] = " create table if not exists peer_info("
			"id integer primary key,"
			"source char(16),"
			"target char(16),"
			"ping_ok integer,"
			"create_time timestamp not null default(strftime('%Y-%m-%d %H:%M:%f', 'now' ,'localtime')),"
			"del integer default 0"
			");";
		sqlite3_exec(*db, sql1, NULL, NULL, &err_msg);
		log4c_category_log(mycat, LOG4C_PRIORITY_DEBUG,
			"sql=%s, err=%s, at %d in %s ",
			sql1, err_msg, __LINE__, __FILE__);
		sqlite3_free(err_msg);
		char sql2[] = "create table if not exists topo_info("
			"id integer primary key, "
			"source varchar(128),"		// ip address, 192.168.0.1
			"target varchar(128),"		// ip address, 192.168.0.2
			"loss integer,"				// unit:%, 2 means pkt loss = 2%
			"is_connected integer,"		// 1 means from source to target is connected.
			"available_bw integer,"		// unit: Mbps
			"capacity_bw integer,"		// unit: Mbps
			"latency integer,"			// unit: ms
			"type integer"				// 1: fiber, 2: twisted pair, 3: wireless
			");";
		sqlite3_exec(*db, sql2, NULL, NULL, &err_msg);
		log4c_category_log(mycat, LOG4C_PRIORITY_DEBUG,
			"sql=%s, err=%s, at %d in %s ",
			sql2, err_msg, __LINE__, __FILE__);
		sqlite3_free(err_msg);
		char sql3[] = "create table if not exists task_info("
			"id integer primary key,"
			"app_id integer,"
			"data_size integer,"
			"uid varchar(128),"
			"target varchar(128),"
			"zone integer,"
			"create_time timestamp not null default(strftime('%Y-%m-%d %H:%M:%f', 'now' ,'localtime')),"
			"update_time timestamp,"
			"interrupt_time timestamp,"
			"restart_time timestamp,"
			"cancel_time timestamp,"
			"file_id varchar(128),"			// file id in db. 
			"priority integer,"             // min = 0, max = 16
			"progress integer,"             // min= 1, max  = 100,process = 25 when 1 of 4 file upload finish.
			"op_uid varchar(128),"
			"op_type integer,"
			"status integer,"				//-- 0:init, 1:start, 2:interrupt,3:stop,4:resume,5:finish, 6:wirte_over，7:delivery_over  
			"del integer default 0"         	// unit: Mbps
			");";
		sqlite3_exec(*db, sql3, NULL, NULL, &err_msg);
		log4c_category_log(mycat, LOG4C_PRIORITY_DEBUG,
			"sql=%s, err=%s, at %d in %s ",
			sql3, err_msg, __LINE__, __FILE__);
		sqlite3_free(err_msg);
		is_db_inited = true;
	}
}

bool get_file_by_md5(char *md5, struct file_rcd &rs)
{
	log_init();
	sqlite3 *db = NULL;
	init_db(&db);
	char *err_msg = NULL;
	string sql_base = "select id, app_id,  name, md5, size, slice_size, "
		"slice_total, slice_snd, path, create_time from file_info where del=0 and md5=";
	string md5_str = md5;
	string sql = sql_base + "'" + md5_str + "' limit 1";
	int row = 0;
	int c = 0;				//column
	char **result = NULL;
	log4c_category_log(mycat, LOG4C_PRIORITY_DEBUG,
		"sql=%s, at %d in %s ",
		sql.c_str(), __LINE__, __FILE__);
	sqlite3_get_table(db , sql.c_str(), &result, &row , &c , &err_msg);
	if (NULL == err_msg) {
		log4c_category_log(mycat, LOG4C_PRIORITY_INFO,
			"row=%d,column=%d, at %d in %s", row, c, __LINE__, __FILE__);
	} else {
		log4c_category_log(mycat, LOG4C_PRIORITY_ERROR,
			"err=%s, at %d in %s ", err_msg, __LINE__, __FILE__);
		throw -1;
	}
	
	if(row > 0) {
		rs.id = atoi(result[c]);
		rs.app_id = atoi(result[c+1]);
		strcpy(rs.name, result[c+2]);
		strcpy(rs.md5, result[c+3]);
		rs.size = atoi(result[c+4]);
		rs.slice_size = atoi(result[c+5]);
		rs.slice_total = atoi(result[c+6]);
		rs.slice_snd = atoi(result[c+7]);
		strcpy(rs.path, result[c+8]);
		strcpy(rs.create_time, result[c+9]);
		log4c_category_log(mycat, LOG4C_PRIORITY_DEBUG,
			"id=%d,name=%s, md5=%s,size=%d,slice_size=%d, slice_total=%d, "
			"slice_snd=%d, path=%s,create_time=%s at %d in %s ", 
			rs.id, rs.name, rs.md5, rs.size, rs.slice_size, rs.slice_total,
			rs.slice_snd, rs.path, rs.create_time, __LINE__, __FILE__);
	}
	sqlite3_free(err_msg); 
	sqlite3_free_table(result);
	sqlite3_close(db);
	return row;
}

bool get_file_by_md5_name(char *md5, char *name,  struct file_rcd &rs)
{
	log_init();
	sqlite3 *db = NULL;
	init_db(&db);
	char *err_msg = NULL;
	string sql_base = "select id, app_id,  name, md5, size, slice_size, "
		"slice_total, slice_snd, path, create_time from file_info where del=0 and md5=";
	string md5_str = md5;
	string name_str = name;
	string sql = sql_base + "'" + md5_str + "' and name='" + name_str + "' limit 1";
	int row = 0;
	int c = 0;				//column
	char **result = NULL;
	log4c_category_log(mycat, LOG4C_PRIORITY_DEBUG,
		"sql=%s, at %d in %s ",
		sql.c_str(), __LINE__, __FILE__);
	sqlite3_get_table(db , sql.c_str(), &result, &row , &c , &err_msg);
	if (NULL == err_msg) {
		log4c_category_log(mycat, LOG4C_PRIORITY_INFO,
			"row=%d,column=%d, at %d in %s", row, c, __LINE__, __FILE__);
	} else {
		log4c_category_log(mycat, LOG4C_PRIORITY_ERROR,
			"err=%s, at %d in %s ", err_msg, __LINE__, __FILE__);
		throw -1;
	}
	
	if(row > 0) {
		rs.id = atoi(result[c]);
        rs.app_id = atoi(result[c+1]);
        strcpy(rs.name, result[c+2]);
        strcpy(rs.md5, result[c+3]);
        rs.size = atoi(result[c+4]);
        rs.slice_size = atoi(result[c+5]);
        rs.slice_total = atoi(result[c+6]);
        rs.slice_snd = atoi(result[c+7]);
        strcpy(rs.path, result[c+8]);
        strcpy(rs.create_time, result[c+9]);
        log4c_category_log(mycat, LOG4C_PRIORITY_DEBUG,
            "id=%d,name=%s, md5=%s,size=%d,slice_size=%d, slice_total=%d, "
            "slice_snd=%d, path=%s,create_time=%s at %d in %s ",
            rs.id, rs.name, rs.md5, rs.size, rs.slice_size, rs.slice_total,
            rs.slice_snd, rs.path, rs.create_time, __LINE__, __FILE__);
	}
	sqlite3_free(err_msg); 
	sqlite3_free_table(result);
	sqlite3_close(db);
	return row;
}

bool get_file_by_id_name(int file_id, char *name,  struct file_rcd &rs)
{
	log_init();
	sqlite3 *db = NULL;
	init_db(&db);
	char *err_msg = NULL;
	string sql_base = "select id, app_id, file_id,  name, md5, size, path, slice_size, "
		"slice_total, slice_snd, create_time from file_info where del=0 and file_id=";
	string fid_str = itoa(file_id);
	string name_str = name;
	string sql = sql_base + fid_str + " and name='" + name_str + "' limit 1";
	int row = 0;
	int c = 0;
	char **result = NULL;
	log4c_category_log(mycat, LOG4C_PRIORITY_DEBUG,
		"sql=%s, at %d in %s ",
		sql.c_str(), __LINE__, __FILE__);
	int rc = sqlite3_get_table(db , sql.c_str(), &result, &row , &c , &err_msg);
	if (rc != 0) {
		log4c_category_log(mycat, LOG4C_PRIORITY_INFO,
			"row=%d,column=%d, at %d in %s", row, c, __LINE__, __FILE__);
	} else {
		log4c_category_log(mycat, LOG4C_PRIORITY_ERROR,
			"err=%s, at %d in %s ", err_msg, __LINE__, __FILE__);
		throw -1;
	}
	
	if(row > 0) {
		rs.id = atoi(result[c]);
        rs.app_id = atoi(result[c+1]);
		rs.file_id = atoi(result[c+2]);
        strcpy(rs.name, result[c+3]);
        strcpy(rs.md5, result[c+4]);
        rs.size = atoi(result[c+5]);
		strcpy(rs.path, result[c+6]);
        rs.slice_size = atoi(result[c+7]);
        rs.slice_total = atoi(result[c+8]);
        rs.slice_snd = atoi(result[c+9]);
        strcpy(rs.create_time, result[c+10]);
        log4c_category_log(mycat, LOG4C_PRIORITY_DEBUG,
            "id=%d,name=%s, md5=%s,size=%d,slice_size=%d, slice_total=%d, "
            "slice_snd=%d, path=%s,create_time=%s at %d in %s ",
            rs.id, rs.name, rs.md5, rs.size, rs.slice_size, rs.slice_total,
            rs.slice_snd, rs.path, rs.create_time, __LINE__, __FILE__);
	}
	sqlite3_free(err_msg); 
	sqlite3_free_table(result);
	sqlite3_close(db);
	return row;
}
bool delete_file_by_md5(char *md5)
{
	log_init();
	sqlite3 *db = NULL;
	init_db(&db);
	char *err_msg = NULL;
	string sql_base = "update file_info set del=1 where del=0 and md5=";
	string md5_str = md5;
	string sql = sql_base + "'" + md5_str + "'";
	log4c_category_log(mycat, LOG4C_PRIORITY_DEBUG,
		"sql=%s, at %d in %s ",
		sql.c_str(), __LINE__, __FILE__);
	int ret = sqlite3_exec(db, sql.c_str(), NULL, NULL, &err_msg);
	if (NULL != err_msg) {
		log4c_category_log(mycat, LOG4C_PRIORITY_ERROR,
			"err=%s, ret=%d, at %d in %s ", err_msg, ret, __LINE__, __FILE__);
		throw -1;
	}
	sqlite3_free(err_msg); 
	sqlite3_close(db);
	return ret;
}

bool save_file_info(struct file_rcd &rs)
{
	log_init();
	sqlite3 *db = NULL;
	init_db(&db);
	char *err_msg = NULL;
	string sql_base = "insert into 'file_info'(app_id, name, md5, size, "
		"slice_size, slice_total,slice_snd, path) VALUES ("; 
	string name = rs.name;
	string md5 = rs.md5;
	string size = itoa(rs.size);
	string app_id = itoa(rs.app_id);
	string path = rs.path;
	string s_s = itoa(rs.slice_size);
	string s_t = itoa(rs.slice_total);
	string s_sd = itoa(rs.slice_snd);
	string sql = sql_base + "'" + app_id + "','" + name + "','" + md5 + "'," +size 
		+ "," + s_s + "," + s_t + "," + s_sd + ",'"+ path + "')" ;
	log4c_category_log(mycat, LOG4C_PRIORITY_DEBUG,
		"sql=%s, at %d in %s ", sql.c_str(), __LINE__, __FILE__);
	sqlite3_exec(db, sql.c_str(), NULL, NULL, &err_msg);
	if (NULL != err_msg)
		log4c_category_log(mycat, LOG4C_PRIORITY_ERROR,
			"error=%s, at %d in %s ", err_msg, __LINE__, __FILE__);
	sqlite3_free(err_msg);
	sqlite3_close(db);
	return err_msg == NULL ? true : false;
}

int update_slice_no_by_file_id_name(int file_id, char *name, int slice_snd)
{  
    log_init();
	struct file_rcd rs;
	get_file_by_id_name(file_id, name, rs);
	rs.slice_snd = slice_snd;
	update_file_info(rs);
    return 0;
}

bool update_file_info(struct file_rcd &rs)
{
	log_init();
	sqlite3 *db = NULL;
	init_db(&db);
	char *err_msg = NULL;
	string sql_base = "update 'file_info' ";
	string id = itoa(rs.id);
	string app_id = itoa(rs.app_id);
	string file_id = itoa(rs.file_id);
	string name = rs.name;
	string md5 = rs.md5;
	string size = itoa(rs.size);
	string path = rs.path;
	string s_s = itoa(rs.slice_size);
	string s_t = itoa(rs.slice_total);
	string s_sd = itoa(rs.slice_snd);
	string sql = sql_base + " set app_id=" + app_id + ", file_id="+ file_id+", name= '" + name + "', size= " 
		+ size + ", path= '" + path+ "', slice_size=" + s_s + ", slice_total=" + s_t + 
		", slice_snd=" + s_sd + "," + "' where id=" + id + "";
	log4c_category_log(mycat, LOG4C_PRIORITY_DEBUG,
		"sql=%s, at %d in %s ", sql.c_str(), __LINE__, __FILE__);
	sqlite3_exec(db, sql.c_str(), NULL, NULL, &err_msg);
	if (NULL != err_msg)
		log4c_category_log(mycat, LOG4C_PRIORITY_ERROR,
			"error=%s, at %d in %s ", err_msg, __LINE__, __FILE__);
	sqlite3_free(err_msg);
	sqlite3_close(db);
	return err_msg == NULL ? true : false;
}


int get_peer_info(char *source, char *target)
{
	log_init(); 
	sqlite3 *db = NULL;
	init_db(&db); 
	char *err_msg = NULL;
	string sql_base = "select source,target ping_ok, create_time from peer_info where del = 0 and ";
	string s = source;
	string t = target;
	string sql = sql_base + "source='" + s + "' and target='" + t + "' limit 1";
	int row = 0;
	int c = 0;				//column
	char **result = NULL;
	log4c_category_log(mycat, LOG4C_PRIORITY_DEBUG,
		"sql=%s, at %d in %s ",
		sql.c_str(), __LINE__, __FILE__);
	sqlite3_get_table(db , sql.c_str(), &result, &row , &c , &err_msg);
	if (NULL == err_msg) {
		log4c_category_log(mycat, LOG4C_PRIORITY_INFO,
			"row=%d,column=%d, at %d in %s", row, c, __LINE__, __FILE__);
	} else {
		log4c_category_log(mycat, LOG4C_PRIORITY_ERROR,
			"err=%s, at %d in %s ", err_msg, __LINE__, __FILE__);
		throw -1;
	}
	return row;
}

int update_peer_info(char *source, char *target, bool is_connected)
{
	log_init();
	sqlite3 *db = NULL;
	init_db(&db);
	char *err_msg = NULL;
	string sql_base = "update peer_info set ping_ok=1 where del=0 and ";
	string s_str = source;
	string t_str = target;
	string sql = sql_base + "source ='" + s_str + "' and target='" + t_str +"' limit 1";
	log4c_category_log(mycat, LOG4C_PRIORITY_DEBUG,
		"sql=%s, at %d in %s ",
		sql.c_str(), __LINE__, __FILE__);
	int ret = sqlite3_exec(db, sql.c_str(), NULL, NULL, &err_msg);
	if (NULL != err_msg) {
		log4c_category_log(mycat, LOG4C_PRIORITY_ERROR,
			"err=%s, ret=%d, at %d in %s ", err_msg, ret, __LINE__, __FILE__);
		throw -1;
	}
	sqlite3_free(err_msg); 
	sqlite3_close(db);
	return ret;
}

bool insert_peer_info(char *source, char *target, bool ping_ok)
{
	log_init();
	sqlite3 *db = NULL;
	init_db(&db);
	char *err_msg = NULL;
	string sql_base = "insert into 'peer_info'(source, target, ping_ok) VALUES ("; 
	string s_str = source;
	string t_str = target;
	string ping_str = ping_ok ? "1" : "0";
	string sql = sql_base + "'" + s_str + "','" + t_str + "'," +ping_str + ")" ;
	log4c_category_log(mycat, LOG4C_PRIORITY_DEBUG,
		"sql=%s, at %d in %s ", sql.c_str(), __LINE__, __FILE__);
	sqlite3_exec(db, sql.c_str(), NULL, NULL, &err_msg);
	if (NULL != err_msg)
		log4c_category_log(mycat, LOG4C_PRIORITY_ERROR,
			"error=%s, at %d in %s ", err_msg, __LINE__, __FILE__);
	sqlite3_free(err_msg);
	sqlite3_close(db);
	return err_msg == NULL ? true : false;
}

//save task info into database.
bool save_task_info(struct task_rcd &rs)
{
	log_init();
	sqlite3 *db = NULL;
	init_db(&db);
	char *err_msg = NULL;
	string sql_base = "insert into task_info(app_id, data_size, uid, target, zone, "
		"update_time, interrupt_time, restart_time, cancel_time, "
		"file_id, priority, progress, op_uid, op_type, status) VALUES (";
	string app_id = itoa(rs.app_id);
	string data_size = itoa(rs.data_size);
	string uid = rs.uid;
	string target = rs.target;
	string zone = itoa(rs.zone);
	string u_t = rs.update_time;
	string i_t = rs.interrupt_time;
	string r_t = rs.restart_time;
	string c_t = rs.cancel_time;
	string file_id = itoa(rs.file_id);
	string priority = itoa(rs.priority);
	string progress = itoa(rs.progress);
	string op_uid = rs.op_uid;
	string op_type = itoa(rs.op_type);
	string status = itoa(rs.status);
	string sql = sql_base + app_id + "," + data_size + ",'" + uid + "','" + target + "'," \
		+ zone + ",'" +u_t +"','" +i_t +"','" + r_t +"','" + c_t + "'," + file_id + "," 
		+ priority + "," + progress  + ",'" + op_uid + "'," + op_type + "," + status + ")" ;
	log4c_category_log(mycat, LOG4C_PRIORITY_DEBUG,
		"sql=%s, at %d in %s ", sql.c_str(), __LINE__, __FILE__);
	sqlite3_exec(db, sql.c_str(), NULL, NULL, &err_msg);
	if (NULL != err_msg)
		log4c_category_log(mycat, LOG4C_PRIORITY_ERROR,
			"error=%s, at %d in %s ", err_msg, __LINE__, __FILE__);
	sqlite3_free(err_msg);
	sqlite3_close(db);
	return err_msg == NULL ? true : false;
}

//update task info in db.
bool update_task_info(struct task_rcd &rs)
{
	log_init();
	sqlite3 *db = NULL;
	init_db(&db);
	char *err_msg = NULL;
	string sql_base = "update task_info set ";
	string id = itoa(rs.id);
	string app_id = itoa(rs.app_id);
	string data_size = itoa(rs.data_size);
	string target = rs.target;
	string zone = itoa(rs.zone);
	string file_id = itoa(rs.file_id);
	string priority = itoa(rs.priority);
	string progress = itoa(rs.progress);
	string status = itoa(rs.status);
	string sql = sql_base + "app_id = '" + app_id + "',data_size='" + data_size 
		+ "',target='" + target + "', zone='" + zone + "', file_id=" + file_id 
		+ ",priority=" + priority	+ ",status=" + status + " where id = " + id ;
	log4c_category_log(mycat, LOG4C_PRIORITY_DEBUG,
		"sql=%s, at %d in %s ", sql.c_str(), __LINE__, __FILE__);
	sqlite3_exec(db, sql.c_str(), NULL, NULL, &err_msg);
	if (NULL != err_msg)
		log4c_category_log(mycat, LOG4C_PRIORITY_ERROR,
			"error=%s, at %d in %s ", err_msg, __LINE__, __FILE__);
	sqlite3_free(err_msg);
	sqlite3_close(db);
	return err_msg == NULL ? true : false;
}

//delete task info in db logically.
bool update_task_info(int id)
{
	log_init();
	sqlite3 *db = NULL;
	init_db(&db);
	char *err_msg = NULL;
	string sql_base = "update task_info set ";
	char id_a[20] = {0};
	itoa(id, id_a);
	string id_str = id_a;
	string sql = sql_base + "del = 1 where id = " + id_str + " limit 1";
	log4c_category_log(mycat, LOG4C_PRIORITY_DEBUG,
		"sql=%s, at %d in %s ", sql.c_str(), __LINE__, __FILE__);
	sqlite3_exec(db, sql.c_str(), NULL, NULL, &err_msg);
	if (NULL != err_msg)
		log4c_category_log(mycat, LOG4C_PRIORITY_ERROR,
			"error=%s, at %d in %s ", err_msg, __LINE__, __FILE__);
	sqlite3_free(err_msg);
	sqlite3_close(db);
	return err_msg == NULL ? true : false;
}

//get task info by uid.
int get_task_by_uid(struct task_rcd &rs, char *uid)
{
	log_init(); 
	sqlite3 *db = NULL;
	init_db(&db); 
	char *err_msg = NULL;
	string sql_base = "select id, app_id, data_size, uid, target, zone, create_time, "
		"interrupt_time, restart_time, cancel_time, file_id, priority, progress, "
		"op_uid, op_type, status from task_info where 1=1 ";
	string uid_str = uid;
	string sql = sql_base + " and uid='" + uid_str + "' order by create_time desc limit 10";
	int row = 0;
	int c = 0;				//column
	char **result = NULL;
	log4c_category_log(mycat, LOG4C_PRIORITY_DEBUG,
		"sql=%s, at %d in %s ",
		sql.c_str(), __LINE__, __FILE__);
	sqlite3_get_table(db , sql.c_str(), &result, &row , &c , &err_msg);
	if (NULL == err_msg) {
		log4c_category_log(mycat, LOG4C_PRIORITY_INFO,
			"row=%d,column=%d, at %d in %s", row, c, __LINE__, __FILE__);
		rs.app_id = atoi(result[1]);
		rs.data_size = atoi(result[2]);
		rs.uid = result[3];
		rs.target = result[4];
		rs.zone = atoi(result[5]);
		rs.create_time = result[6];
		rs.interrupt_time = result[7];
		rs.restart_time = result[8];
		rs.cancel_time = result[9];
		rs.file_id = atoi(result[10]);
		rs.priority = atoi(result[11]);
		rs.progress = atoi(result[12]);
		rs.op_uid = result[13];
		rs.op_type = atoi(result[14]);
		rs.status =atoi(result[15]);
	} else {
		log4c_category_log(mycat, LOG4C_PRIORITY_ERROR,
			"err=%s, at %d in %s ", err_msg, __LINE__, __FILE__);
		throw -1;
	}
	return true;	
}

//get topology list.
int get_topo_list(list<struct topo_rcd> &rs_list)
{
	log_init();
	sqlite3 *db = NULL;
	init_db(&db);
	char *err_msg = NULL;
	string sql_base = "select id, source, target, loss, is_connected, available_bw, capacity_bw,"
		"latency, create_time, update_time where is_connected = 1 limit 100";
	string sql = sql_base;
	int row = 0;
	int c = 0;				//column
	char **result = NULL;
	log4c_category_log(mycat, LOG4C_PRIORITY_DEBUG,
		"sql=%s, at %d in %s ",
		sql.c_str(), __LINE__, __FILE__);
	sqlite3_get_table(db , sql.c_str(), &result, &row , &c , &err_msg);
	if (NULL == err_msg) {
		log4c_category_log(mycat, LOG4C_PRIORITY_INFO,
			"row=%d,column=%d, at %d in %s", row, c, __LINE__, __FILE__);
		struct topo_rcd rs;
		for (int i = 0; i < (row+1) * c; i++) {
			if (i % c == 1)
				rs.source = result[i];
			else if (i % c == 2)
				rs.target  = result[i];
			else if (i % c == (c-1))
				rs_list.push_back(rs);
			//cout << result[i] << endl;
		}

	} else {
		log4c_category_log(mycat, LOG4C_PRIORITY_ERROR,
			"err=%s, at %d in %s ", err_msg, __LINE__, __FILE__);
		throw -1;
	}
	return row;
	
}

//save topology info.
bool save_topo_info(struct topo_rcd &rs)
{
	log_init();
	sqlite3 *db = NULL;
	init_db(&db); 
	char *err_msg = NULL;
	string sql_base = "insert into 'topo_info'(source, target, loss, is_connected, available_bw, capacity_bw, latency, type) VALUES (";
	string source = rs.source;
	log4c_category_log(mycat, LOG4C_PRIORITY_ERROR, "rs.source=%s, at %d in %s", rs.source, __LINE__, __FILE__);
	string target = rs.target;
	char loss_a[10] = {0};
	itoa(rs.loss, loss_a);
	string loss = loss_a;
	string is_connected = rs.is_connected ? "1" : "0";
	char available_bw_a[10] = {0};
	itoa(rs.available_bw, available_bw_a);
	string available_bw = available_bw_a;
	char capacity_bw_a[10] = {0};
	itoa(rs.capacity_bw, capacity_bw_a);
	string capacity_bw = capacity_bw_a;
	char latency_a[10] = {0};
	itoa(rs.latency, latency_a); 
	string latency = latency_a;
	char type_a[10]= {0};
	itoa(rs.type, type_a);
	string type = type_a;
	string sql = sql_base + "'" + source + "','" + target + "'," + loss + "," \
		+ is_connected + ",'" + available_bw + "','" + capacity_bw	+ "'," + latency + "," + type + ")" ;
	log4c_category_log(mycat, LOG4C_PRIORITY_DEBUG,
		"sql=%s, at %d in %s ", sql.c_str(), __LINE__, __FILE__);
	sqlite3_exec(db, sql.c_str(), NULL, NULL, &err_msg);
	if (NULL != err_msg)
		log4c_category_log(mycat, LOG4C_PRIORITY_ERROR,
			"error=%s, at %d in %s ", err_msg, __LINE__, __FILE__);
	sqlite3_free(err_msg);
	sqlite3_close(db);
	return err_msg == NULL ? true : false;	
}

//update topology info.
bool update_topo_info(struct topo_rcd &rs)
{
	log_init();
	sqlite3 *db = NULL;
	init_db(&db);
	char *err_msg = NULL;
	string sql_base = "update 'topo_info' set ";
	string source = rs.source;
	string target = rs.target;
	char id_a[20] = {0};
	itoa(rs.id, id_a);
	string id = id_a;
	char loss_a[10] = {0};
	itoa(rs.loss, loss_a);
	string loss = loss_a;
	string is_connected = rs.is_connected ? "1" : "0";
	char available_bw_a[10] = {0};
	itoa(rs.available_bw, available_bw_a);
	string available_bw = available_bw_a;
	char capacity_bw_a[10] = {0};
	itoa(rs.capacity_bw, capacity_bw_a);
	string capacity_bw = capacity_bw_a;
	char latency_a[10] = {0};
	itoa(rs.latency, latency_a);
	string latency = latency_a;
	char type_a[10]= {0};
	itoa(rs.type, type_a);
	string type = type_a;
	string sql = sql_base + " source='" + source + "', target='" + target + "', loss='" 
		+ loss + "', is_connected='" + is_connected + ", available_bw=" + available_bw + 
		", capacity_bw=" + capacity_bw	+ ", latency=" + latency + ", type=" + type + " where id =" + id;
	log4c_category_log(mycat, LOG4C_PRIORITY_DEBUG,
		"sql=%s, at %d in %s ", sql.c_str(), __LINE__, __FILE__);
	sqlite3_exec(db, sql.c_str(), NULL, NULL, &err_msg);
	if (NULL != err_msg)
		log4c_category_log(mycat, LOG4C_PRIORITY_ERROR,
			"error=%s, at %d in %s ", err_msg, __LINE__, __FILE__);
	sqlite3_free(err_msg);
	sqlite3_close(db);
	return err_msg == NULL ? true : false;
}

//get topology detail with topo from "source" to "target" 
void get_topo_info(char *source, char *target, struct topo_rcd &rs)
{
	log_init(); 
	sqlite3 *db = NULL;
	init_db(&db); 
	char *err_msg = NULL;
	string sql_base = "select id, source, target, loss, available_bw, capacity_bw,"
		"latency, create_time, update_time from topo_info where is_connected = 1 limit 1";
	string sql = sql_base;
	int row = 0;
	int c = 0;				//column
	char **result = NULL;
	log4c_category_log(mycat, LOG4C_PRIORITY_DEBUG,
		"sql=%s, at %d in %s ",
		sql.c_str(), __LINE__, __FILE__);
	sqlite3_get_table(db , sql.c_str(), &result, &row , &c , &err_msg);
	if (NULL == err_msg) {
		log4c_category_log(mycat, LOG4C_PRIORITY_INFO,
			"row=%d,column=%d, at %d in %s", row, c, __LINE__, __FILE__);
		rs.id = atoi(result[0]);
		rs.source = result[1];
		rs.target = result[2];
		rs.loss = atoi(result[3]);
		rs.available_bw = atoi(result[4]);
		rs.capacity_bw = atoi(result[5]);
		rs.latency = atoi(result[6]);
		rs.create_time = result[7];
		rs.update_time = result[8];
		//cout << result[i] << endl;
	} else {
		log4c_category_log(mycat, LOG4C_PRIORITY_ERROR,
			"err=%s, at %d in %s ", err_msg, __LINE__, __FILE__);
		throw -1;
	}
}

int get_task_file_receiver(int task_id, int file_id, char receiver_list[][32])
{
	log_init(); 
	sqlite3 *db = NULL;
	init_db(&db); 
	char *err_msg = NULL;
	string sql_base = "select id, file_id, target from task_info where id = ";
	string task_id_str = itoa(task_id);
	string file_id_str = itoa(file_id);
	string sql = sql_base + task_id_str + " and file_id = " + file_id_str;
	int row = 0;
	int c = 0;				//column
	char **result = NULL;
	log4c_category_log(mycat, LOG4C_PRIORITY_DEBUG,
		"sql=%s, at %d in %s ",
		sql.c_str(), __LINE__, __FILE__);
	sqlite3_get_table(db , sql.c_str(), &result, &row , &c , &err_msg);
	if (NULL == err_msg) {
		log4c_category_log(mycat, LOG4C_PRIORITY_INFO,
			"row=%d, column=%d, at %d in %s", row, c, __LINE__, __FILE__);
		if (row != 0) {
			log4c_category_log(mycat, LOG4C_PRIORITY_INFO,
				"target=%s, at %d in %s", result[5], __LINE__, __FILE__);
			char search[2] = ";";
			split_str(result[5], search, receiver_list);
		}
	} else {
		log4c_category_log(mycat, LOG4C_PRIORITY_ERROR,
			"err=%s, at %d in %s ", err_msg, __LINE__, __FILE__);
		throw -1;
	}
	return row;
}

int get_task_status(int task_id)
{
	log_init(); 
	sqlite3 *db = NULL;
	init_db(&db); 
	char *err_msg = NULL;
	string sql_base = "select status from task_info where id = ";
	char task_id_a[16] = {0};
	itoa(task_id, task_id_a);
	string task_id_str = task_id_a;
	string sql = sql_base + task_id_str + " limit 1";
	int row = 0;
	int c = 0;				//column
	char **result = NULL;
	log4c_category_log(mycat, LOG4C_PRIORITY_DEBUG,
		"sql=%s, at %d in %s ",
		sql.c_str(), __LINE__, __FILE__);
	sqlite3_get_table(db , sql.c_str(), &result, &row , &c , &err_msg);
	int status = 0;
	if (NULL == err_msg) {
		log4c_category_log(mycat, LOG4C_PRIORITY_INFO,
			"row=%d,column=%d, at %d in %s", row, c, __LINE__, __FILE__);
		status = atoi(result[0]);
	} else {
		log4c_category_log(mycat, LOG4C_PRIORITY_ERROR,
			"err=%s, at %d in %s ", err_msg, __LINE__, __FILE__);
		throw -1;
	}
	return status;
}

int get_file_percent(int file_id)
{	
	log_init(); 
	sqlite3 *db = NULL;
	init_db(&db); 
	char *err_msg = NULL;
	string sql_base = "select progress from file_info where id = ";
	char file_id_a[16] = {0};
	itoa(file_id, file_id_a);
	string file_id_str = file_id_a;
	string sql = sql_base + file_id_str + " limit 1";
	int row = 0;
	int c = 0;				//column
	char **result = NULL;
	log4c_category_log(mycat, LOG4C_PRIORITY_DEBUG,
		"sql=%s, at %d in %s ",
		sql.c_str(), __LINE__, __FILE__);
	sqlite3_get_table(db , sql.c_str(), &result, &row , &c , &err_msg);
	int progress = 0;
	if (NULL == err_msg) {
		log4c_category_log(mycat, LOG4C_PRIORITY_INFO,
			"row=%d,column=%d, at %d in %s", row, c, __LINE__, __FILE__);
		progress = atoi(result[0]);
	} else {
		log4c_category_log(mycat, LOG4C_PRIORITY_ERROR,
			"err=%s, at %d in %s ", err_msg, __LINE__, __FILE__);
		throw -1;
	}
	return progress;
}

int get_last_task_data_rate()
{	
	log_init(); 
	sqlite3 *db = NULL;
	init_db(&db); 
	char *err_msg = NULL;
	string sql = "select max(id) from task_info";
	int row = 0;
	int c = 0;				//column
	char **result = NULL;
	log4c_category_log(mycat, LOG4C_PRIORITY_DEBUG,
		"sql=%s, at %d in %s ",
		sql.c_str(), __LINE__, __FILE__);
	sqlite3_get_table(db , sql.c_str(), &result, &row , &c , &err_msg);
	int max_id = 0;
	char max_id_c[32] = {0};
	if (NULL == err_msg) {
		log4c_category_log(mycat, LOG4C_PRIORITY_INFO,
			"row=%d,column=%d, at %d in %s", row, c, __LINE__, __FILE__);
		max_id = atoi(result[0]);
		strcpy(max_id_c, result[0]);
	} else {
		log4c_category_log(mycat, LOG4C_PRIORITY_ERROR,
			"err=%s, at %d in %s ", err_msg, __LINE__, __FILE__);
		throw -1;
	}
	if (max_id == 0)
		return -1;
	string max_id_s = max_id_c;
	sql = "select data_rate from task_info where id = " + max_id_s;
    row = 0;
    c = 0; 
    result = NULL;
    log4c_category_log(mycat, LOG4C_PRIORITY_DEBUG,
        "sql=%s, at %d in %s ",
        sql.c_str(), __LINE__, __FILE__);
    sqlite3_get_table(db , sql.c_str(), &result, &row , &c , &err_msg);
    int data_rate = 0;
    if (NULL == err_msg) {
        log4c_category_log(mycat, LOG4C_PRIORITY_INFO,
            "row=%d,column=%d, at %d in %s", row, c, __LINE__, __FILE__);
        data_rate = atoi(result[0]);
    } else {
        log4c_category_log(mycat, LOG4C_PRIORITY_ERROR,
            "err=%s, at %d in %s ", err_msg, __LINE__, __FILE__);
        throw -1;
    }
	
	return data_rate;
}

bool save_data_rate(int task_id, int data_rate)
{	
	log_init();
	sqlite3 *db = NULL;
	init_db(&db);
	char *err_msg = NULL;
	string sql_base = "update task_info set ";
	char id_a[32] = {0};
	itoa(task_id, id_a);
	string id_str = id_a;
	char data_r_c[32] = {0};
	itoa(data_rate, data_r_c);
	string data_r_s = data_r_c;
	string sql = sql_base + "data_rate = " + data_r_s + " where id = " + id_str + " limit 1";
	log4c_category_log(mycat, LOG4C_PRIORITY_DEBUG,
		"sql=%s, at %d in %s ", sql.c_str(), __LINE__, __FILE__);
	sqlite3_exec(db, sql.c_str(), NULL, NULL, &err_msg);
	if (NULL != err_msg)
		log4c_category_log(mycat, LOG4C_PRIORITY_ERROR,
			"error=%s, at %d in %s ", err_msg, __LINE__, __FILE__);
	sqlite3_free(err_msg);
	sqlite3_close(db);
	return err_msg == NULL ? true : false;
}

static string itoa(int i)
{
	char s[32] = {0};
	itoa(i, s);
	string s_s = s;
	return s_s;
>>>>>>> da9e02c398ecabc27b4bd8480167a3334f4b938c
}
