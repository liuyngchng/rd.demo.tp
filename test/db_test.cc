#include <sqlite3.h>
#include <stdio.h>
#include <iostream>
#include "db.h"

using namespace std;

void save_topo_test()
{
	cout << "test " << __FUNCTION__ << endl; 
	char s[32] = "192.168.49.23";
	char t[32] = "192.168.49.151";
	struct topo_rcd topo;
	topo.source = s;
	topo.target = t;
	topo.loss = 2;
	topo.is_connected = 1;
	topo.available_bw = 999;
	topo.capacity_bw = 4000;
	topo.latency =12;
	topo.type= 1;
	bool r = save_topo_info(topo);
	cout << r << endl;
	
}


void  init_db_test() 
{
	cout << "test " << __FUNCTION__ << endl; 
	sqlite3 *db = NULL;
	init_db(&db);
}

void save_file_test()
{
	cout << "test " << __FUNCTION__ << endl; 
	struct file_rcd file;
	file.app_id = 67890;
	strcpy(file.name, "test");
	strcpy(file.md5, "123456789adcdefgh");
	file.size = 456;
	strcpy(file.path, "/data/test/123/4565.txt");
	file.slice_size = 10;
	file.slice_total = 200;
	file.slice_snd = 3;
	strcpy(file.create_time, "20200202 18:00 000");
	save_file_info(file);
}

void get_file_by_md5_test()
{
	cout << "test " << __FUNCTION__ << endl; 
	char md5[32] = "123456789adcdefgh";
	struct file_rcd rs;
	get_file_by_md5(md5, rs);
	cout << rs.md5 << endl;
}

void get_file_by_md5_name_test()
{
	cout << "test " << __FUNCTION__ << endl; 
	char md5[32] = "123456789adcdefgh";
	char name[32] = "test";
	struct file_rcd rs;
	get_file_by_md5_name(md5, name, rs);
	cout << rs.md5 << endl;
}

void delete_file_by_md5_test()
{
	cout << "test " << __FUNCTION__ << endl; 
	char md5[32] = "123456789adcdefgh";
	delete_file_by_md5(md5);
}

void update_file_test()
{
	cout << "test " << __FUNCTION__ << endl; 
	char md5[32] = "123456789adcdefgh";
	struct file_rcd rs;
	get_file_by_md5(md5, rs);
	rs.slice_total = 1000;
	update_file_info(rs);
}

void save_task_test()
{
	cout << "test " << __FUNCTION__ << endl; 
	struct task_rcd rs;
	rs.app_id = 12345;
	rs.data_size = 45657;
	char uid[32] = "diuycce90iuo087";
	rs.uid = uid;
	char target[128] = "who@wehreareyou;foo@bar.com;bar@foo.com";
	rs.target = target;
	rs.zone = 4;
	char t[32] = "20200202 18:00 000";
	rs.create_time = t;
	rs.update_time = t;
	rs.interrupt_time = t;
	rs.restart_time= t;
	rs.cancel_time = t;
	rs.file_id = 10;
	rs.priority = 2;
	rs.progress = 3;
	rs.op_uid = uid;
	rs.op_type = 3;
	rs.status = 0;
	rs.del = 0;
	save_task_info(rs);
}

void get_task_by_uid_test()
{
	cout << "test " << __FUNCTION__ << endl;
    struct task_rcd rs;
	char uid[32] = "diuycce90iuo087";
	get_task_by_uid(rs, uid);
}

void get_task_file_receiver_test()
{
	cout << "test " << __FUNCTION__ << endl;
	int task_id = 1;
	int file_id = 10;
	char receiver_list[10][32] = {{0}};
	get_task_file_receiver(task_id, file_id, receiver_list);
	for (int i=0;i < 10; i ++) {
		cout << receiver_list[i] << endl;
	}
}

void get_task_status_test()
{
	int task_id = 1;
	int status = get_task_status(task_id);
	cout << "status = " << status << endl;
}

void update_task_test()
{
	cout << "test " << __FUNCTION__ << endl;
	struct task_rcd rs;	
	char uid[32] = "diuycce90iuo087";
	get_task_by_uid(rs, uid);
	update_task_info(rs);
}

int main()
{
	//init_db_test();
	save_file_test();
	//get_file_by_md5_test();
	//get_file_by_md5_name_test();
	//delete_file_by_md5_test();
	//update_file_test();
	//save_task_test();
	//get_task_by_uid_test();
	//get_task_file_receiver_test();
	get_task_status_test();
	//save_topo_test();
}
