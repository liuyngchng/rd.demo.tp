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
}
