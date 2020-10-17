/**
 * export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/rd/workspace/soci/build/lib
 * export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/rd/dmdbms/bin/
 * odbcinst -j
 */
#include "soci/soci.h"
#include "soci/odbc/soci-odbc.h"
#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <exception>
#include <unistd.h>
#include <assert.h>
#include "person.h"

using namespace std;
using namespace soci;

/**
 * db pool size.
 */
static const size_t pool_size = 10;

/**
 * db pool.
 */
static connection_pool pool(pool_size);

/**
 * database init flag, 
 * true: db inited, 
 * false: not inited.
 */
static bool is_db_inited = false;

/**
 * init db pool, to be compatible with sqlite, the argument sqlite3 is reserved
 * but not be used in function.
 */
void init_db(sqlite3 **db) 
{
	if (is_db_inited) {
		return;
	}
	connection_parameters parameters("odbc", "DSN=dm");
    parameters.set_option(odbc_option_driver_complete, "0" /* SQL_DRIVER_NOPROMPT */);
	for (size_t i = 0; i != pool_size; ++i) {
        session & sql = pool.at(i);
        sql.open(parameters);
    }
	is_db_inited = true;
    cout << "db pool constructed." << endl;
}

/**
 * get file info my md5
 */
bool get_file_by_md5(char *md5, struct file_rcd &rs)
{
	init_db(NULL);
	string sql_base = "select id, app_id,  name, md5, size, slice_size, "
		"slice_total, slice_snd, path, create_time from file_info where del=0 and md5=";
	string md5_str = md5;
	string sql_str = sql_base + "'" + md5_str + "' limit 1";
    session sql(pool);
    sql << sql_str, into rs;
	return true;
}

bool get_file_by_md5_name(char *md5, char *name,  struct file_rcd &rs)
{
	init_db(NULL);
	char *err_msg = NULL;
	string sql_base = "select id, app_id,  name, md5, size, slice_size, "
		"slice_total, slice_snd, path, create_time from file_info where del=0 and md5=";
	string md5_str = md5;
	string name_str = name;
	string sql_str = sql_base + "'" + md5_str + "' and name='" + name_str + "' limit 1";
	session sql(pool);
    sql << sql_str, into rs;
	return true; 
}

bool get_file_by_id_name(int file_id, char *name,  struct file_rcd &rs)
{
	init_db(NULL);
	string sql_base = "select id, app_id, file_id,  name, md5, size, path, slice_size, "
		"slice_total, slice_snd, create_time from file_info where del=0 and file_id=";
	string fid_str = itoa(file_id);
	string name_str = name;
	string sql_str = sql_base + fid_str + " and name='" + name_str + "' limit 1";

	return true;
}
bool delete_file_by_md5(char *md5)
{
	init_db(NULL);
	string sql_base = "update file_info set del=1 where del=0 and md5=";
	string md5_str = md5;
	string sql_str = sql_base + "'" + md5_str + "'";
    session sql(pool);
    sql << sql_str;
	return true;
}

bool save_file_info(struct file_rcd &rs)
{
	init_db(NULL);
	string sql_base = "insert into 'file_info'(app_id, name, md5, size, "
		"slice_size, slice_total,slice_snd, path) VALUES "
        "(:app_id, :name, :md5, :size, :slice_size, :slice_total, :slice_snd, :path)"; 
    session sql(pool);
    sql << sql_str, use(rs);
	return true;
}

int update_slice_no_by_file_id_name(int file_id, char *name, int slice_snd)
{  
	struct file_rcd rs;
	get_file_by_id_name(file_id, name, rs);
	rs.slice_snd = slice_snd;
	update_file_info(rs);
    return 0;
}

bool update_file_info(struct file_rcd &rs)
{
	init_db(NULL);
	string sql_str = "update 'file_info' set app_id=:app_id , file_id=:file_id, name=:name, "
        "size=:size, path=:path, slice_size=:slice_size, slice_total=:slice_total," 
		"slice_snd=:slice_snd where id=:id";
    session sql(pool);
    sql << sql_str, use(rs);
	return true;
}


int get_peer_info(char *source, char *target)
{
	init_db(NULL); 
	string sql_base = "select source,target ping_ok, create_time from peer_info where del = 0 and ";
	string s = source;
	string t = target;
	string sql_str = sql_base + "source='" + s + "' and target='" + t + "' limit 1";
    session sql(pool);
    sql << sql_str;
	return 0;
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
}
