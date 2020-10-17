#ifndef _DB_H_
#define _DB_H_
#include <list>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include "log4c.h"
#include "sqlite3.h"
#include "common.h"
#include "const.h"

/**
 * file data stored in db.
 */ 
struct file_rcd
{
	int		id;
	int		app_id;
	int		file_id;
	char 	name[F_NAME_SIZE];
	char 	md5[33];
	int 	size;					// file size.
	char 	path[F_NAME_SIZE];
	int		slice_size;				// unit:MB, file slice size  
    int		slice_total;			// total slice cout
	int		slice_snd;				// numbers of slices have been sent.
	char 	create_time[20];
	char 	update_time[20];
	int		del;					// logic delete flag , 0:not delete, 1:deleted
    int     percent;                // unit:% , percent of file sent.
};

/**
 * task info stored in db.
 */
struct task_rcd
{
	int		id;
	int		app_id;
    int		data_size;
	char	*uid;
    char	*target;
    int		zone;
    char	*create_time;
    char	*update_time;
    char	*interrupt_time;
    char	*restart_time;
    char	*cancel_time;
    int		file_id;
    int		priority;
    int		progress;
    char	*op_uid;
    int		op_type;
    int		status;					// 0:init, 1:start, 2:interrupt,3:stop,4:resume,5:finish, 6:write_over，7:delivery_over
	int 	del;					// logic delete flag, 0: not delete, 1:deleted.
    int     data_rate;              // average data send rate on task level
};

/**
 * network topology data
 */
struct topo_rcd
{
	int		id;
	char	*source;
	char 	*target;
	int	    loss;					//packet loss =0.1%, loss=1; float is not ok in ORM soci
	int	    is_connected;			// is_connected = 1 if ping OK; bool is not ok in ORM soci
	int		available_bw;			// unit = Mbps;
	int		capacity_bw;			// unit = Mbps;
	int		latency;				// unit = ms;
	int		type;					// 1:fiber,2:twisted pair, 3:wireless, 4:4G 
    char	*create_time;
    char	*update_time;
	int 	del;					// logic delete flag, 0: not delete, 1:deleted.
};

// init database, DDL
void init_db(sqlite3 **db);

// get file info by md5, returnd info saved in rs.
bool get_file_by_md5(char *md5, struct file_rcd &rs);

// get file info by md5 and file name.
bool get_file_by_md5_name(char *md5,  char *name,  struct file_rcd &rs);

// delete file logically by update del flag field
bool delete_file_by_md5(char *md5);

// save file info in rs to database.
bool save_file_info(struct file_rcd &rs);

bool update_file_info(struct file_rcd &rs);

// update slice_no by file md5.
int update_file_slice_no_by_md5(char *md5, int slice_no);

// get peer ping info from source to target, return row retrieved.
int get_peer_info(char *source, char *target);

// update peer info.
int update_peer_info(char *source, char *target, bool is_connected);

// insert peer info.
bool insert_peer_info(char *source, char *target, bool is_connected);

//save task info into db.
bool save_task_info(struct task_rcd &rs);

//update task info in db.
bool update_task_info(struct task_rcd &rs);

//delete task info by id.
bool delete_task_info(int id);

//get task info by uid.
int get_task_by_uid(struct task_rcd &rs, char *uid);  

//get topology list only with source and target.
int get_topo_list(list<struct topo_rcd> &rs_list);

//get topology detail with topo from "source" to "target" 
void get_topo_info(char *source, char *target, struct topo_rcd &rs);

//save topology info.
bool save_topo_info(struct topo_rcd &rs);

//update topology info.
bool update_topo_info(struct topo_rcd &rs);

//get multi file receiver by task_id
int get_task_file_receiver(int task_id, int file_id, char receiver_list[][32]);

//get task status by task id.
int get_task_status(int task_id);

//get percentage of file uploaded by file id(db primary key).
int get_file_percent(int file_id);

//get last data transfer rate from db.
int get_last_task_data_rate();

// save data rate of task with id 'task_id' as 'data_rate'.
bool save_data_rate(int task_id, int data_rate);
#endif
