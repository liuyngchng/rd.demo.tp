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
#include "file_rcd.h"
#include "task_rcd.h"
#include "topo_rcd.h"

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
	init_db(NULL);
	string sql_base = "update peer_info set ping_ok=1 where del=0 and ";
	string s_str = source;
	string t_str = target;
	string sql_str = sql_base + "source ='" + s_str + "' and target='" + t_str +"' limit 1";
		"sql=%s, at %d in %s ",
    session sql(pool);
    sql << sql_str;
	return 0;
}

bool insert_peer_info(char *source, char *target, bool ping_ok)
{
	init_db(NULL);
	string sql_base = "insert into 'peer_info'(source, target, ping_ok) VALUES ("; 
	string s_str = source;
	string t_str = target;
	string ping_str = ping_ok ? "1" : "0";
	string sql_str = sql_base + "'" + s_str + "','" + t_str + "'," +ping_str + ")" ;
    session sql(pool);
    sql << sql_str;
	return true;
}

//save task info into database.
bool save_task_info(struct task_rcd &rs)
{
	init_db(NULL);
	string sql_str = "insert into task_info(app_id, data_size, uid, target, zone, "
		"update_time, interrupt_time, restart_time, cancel_time, "
		"file_id, priority, progress, op_uid, op_type, status) VALUES ("
        ":app_id, :data_size, :uid, :target, :zone, :update_time, :interrupt_time, :restart_time,"
        ":cancel_time, :file_id, :priority, :progress, :op_uid, :op_type, :status)";
    session sql(pool);
    sql << sql_str, use(rs);
	return true;
}

//update task info in db.
bool update_task_info(struct task_rcd &rs)
{
	log_init();
	sqlite3 *db = NULL;
	init_db(&db);
	char *err_msg = NULL;
	string sql_str = "update task_info set app_id =:app_id, data_size=:data_size, " 
		"target=:target, zone=:zone, file_id=:file_id," 
		"priority=:priority,status=:status where id =:id" ;
    session sql(pool);
    sql << sql_str, use(rs);
	return true;
}

//delete task info in db logically.
bool update_task_info(int id)
{
	init_db(NULL);
	string sql_base = "update task_info set ";
	char id_a[20] = {0};
	itoa(id, id_a);
	string id_str = id_a;
	string sql_str = sql_base + "del = 1 where id = " + id_str + " limit 1";
    session sql(pool);
    sql << sql_str;
	return true;
}

//get task info by uid.
int get_task_by_uid(struct task_rcd &rs, char *uid)
{
	init_db(NULL); 
	char *err_msg = NULL;
	string sql_base = "select id, app_id, data_size, uid, target, zone, create_time, "
		"interrupt_time, restart_time, cancel_time, file_id, priority, progress, "
		"op_uid, op_type, status from task_info where 1=1 ";
	string uid_str = uid;
	string sql_str = sql_base + " and uid='" + uid_str + "' order by create_time desc limit 1";
    session sql(pool);
    sql << sql_str, into(rs);
	return 0;	
}

//get topology list.
int get_topo_list(list<struct topo_rcd> &rs_list)
{
	init_db(NULL);
	string sql_str = "select id, source, target, loss, is_connected, available_bw, capacity_bw,"
		"latency, create_time, update_time where is_connected = 1 limit 100";
    rowset<row> rs = (sql.prepare << sql_str);
    for (rowset<row>::const_iterator it = rs.begin(); it != rs.end(); ++it) {
        const row& row = *it;
		struct topo_rcd rs;
        rs.id = row.get<int>(0);
        rs.source = row.get<string>(1).c_str();
        rs.target = row.get<string>(2).c_str();
        rs.loss = row.get<int>(3);
        rs.is_connected = row.get<bool>(4);
        rs.available_bw = row.get<int>(5);
        rs.capacity_bw = row.get<int>(6);
        rs.latency = row.get<int>(7);
        rs.create_time = row.get<string>(8).c_str();
        rs.update_time = row.get<string>(9).c_str();
        rs_list.push_back(rs);
	} 
	return 0;
	
}

//save topology info.
bool save_topo_info(struct topo_rcd &rs)
{
	init_db(NULL); 
	string sql_str = "insert into 'topo_info'(source, target, loss, is_connected, available_bw, capacity_bw, latency, type) VALUES (";
	    ":sql_base, :source, :target, :loss, :is_connected, :available_bw, :capacity_bw, :latency, :type)";
    session sql(pool);
    sql << sql_str, into(rs);
	return true;	
}

//update topology info.
bool update_topo_info(struct topo_rcd &rs)
{
	init_db(NULL);
	string sql_str = "update 'topo_info' set "
	    "source=:source, target=:target,loss=:loss, is_connected=:is_connected,"
        "available_bw=:available_bw, capacity_bw=:capacity_bw, latency=:latency,"
        "type=:type where id =:id";
    session sql(pool);
    sql << sql_str, use(rs);
	return true;
}

//get topology detail with topo from "source" to "target" 
void get_topo_info(char *source, char *target, struct topo_rcd &rs)
{
	init_db(NULL); 
	string sql_str = "select id, source, target, loss, available_bw, capacity_bw,"
		"latency, create_time, update_time from topo_info where is_connected = 1 limit 1";
    session sql(pool);
    sql << sql_str, into(rs);
}

/**
 * get all the file receiver of the task.
 */
int get_task_file_receiver(int task_id, int file_id, char receiver_list[][32])
{
	init_db(NULL); 
	string sql_base = "select id, file_id, target from task_info where id = ";
	string task_id_str = itoa(task_id);
	string file_id_str = itoa(file_id);
	string sql_str = sql_base + task_id_str + " and file_id = " + file_id_str;
    session sql(pool);
    rowset<row> rs = (sql.prepare << sql_str);

    // iteration through the resultset:
    for (rowset<row>::const_iterator it = rs.begin(); it != rs.end(); ++it) {
        const row& row = *it;
        string target = row.get<string>(2);
        char search[2] = ";";
        split_str(target, search, receiver_list);
    }
	return 0;
}

int get_task_status(int task_id)
{
	init_db(NULL); 
	string sql_base = "select status from task_info where id = ";
	char task_id_a[16] = {0};
	itoa(task_id, task_id_a);
	string task_id_str = task_id_a;
	string sql_str = sql_base + task_id_str + " limit 1";
    session sql(pool);
    struct task_rcd t;
    sql << sql_str, into(t);
	return t.status;
}

int get_file_percent(int file_id)
{	
	init_db(NULL); 
	string sql_base = "select progress from file_info where id = ";
	char file_id_a[16] = {0};
	itoa(file_id, file_id_a);
	string file_id_str = file_id_a;
	string sql_str = sql_base + file_id_str + " limit 1";
    session sql(pool);
    struct file_rcd f;
    sql << sql_str, into(f);
	return f.progress;
}

int get_last_task_data_rate()
{	
	init_db(NULL); 
	string sql_str = "select max(id) as id  from task_info";
	sqlite3_get_table(db , sql.c_str(), &result, &row , &c , &err_msg);
	int max_id = 0;
	char max_id_c[32] = {0};
    session sql(pool);
    struct task_rcd t;
    sql << sql_str, into(t);
	if (t.id == 0)
		return -1;
	sql_str = "select data_rate from task_info where id = :id";
    sql << sql_str, use(t), into(t);
	return t1.data_rate;
}

bool save_data_rate(int task_id, int data_rate)
{	
	init_db(NULL);
	string sql_base = "update task_info set ";
	char id_a[32] = {0};
	itoa(task_id, id_a);
	string id_str = id_a;
	char data_r_c[32] = {0};
	itoa(data_rate, data_r_c);
	string data_r_s = data_r_c;
	string sql_str = sql_base + "data_rate = " + data_r_s + " where id = " + id_str + " limit 1";
    session sql(pool);
    sql << sql_str;
	return true;
}

static string itoa(int i)
{
	char s[32] = {0};
	itoa(i, s);
	string s_s = s;
	return s_s;
}
