#ifndef __DB_SOCI_H__
#define __DB_SOCI_H__

#include <list>
#include <sqlite3.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#include "common.h"

#pragma pack(1)

#define F_NAME_SIZE 256

/**
 * file data stored in db.
 */ 
struct file_rcd
{
    int             id;
    uint32_t        task_id;
    uint32_t        app_id;
    uint32_t        file_id;
    char            name[F_NAME_SIZE];
    char            md5[33];
    uint64_t        size;                    // file size.
    char            path[F_NAME_SIZE];
    uint32_t        slice_size;                // unit:MB, file slice size  
    uint32_t        slice_total;            // total slice cout
    uint32_t        slice_ind;                // numbers of slices have been sent.
    char            create_time[20];
    char            update_time[20];
    int             del;                    // logic delete flag , 0:not delete, 1:deleted
};

/**
 * task info stored in db.
 */
struct task_rcd
{
    int             id;
    uint32_t        app_id;
    uint64_t        data_size;
    char            task_name[F_NAME_SIZE];
    char            uid[33];
    char            target[128];
    int             zone;
    time_t          update_time;
    time_t          interrupt_time;
    time_t          restart_time;
    time_t          cancel_time;
    uint32_t        total_bags;
    uint32_t        sd_bag;
    int             priority;
    char            op_uid[33];
    int             op_type;
    int             status;                    // 0:init, 1:start, 2:interrupt,3:stop,4:resume,5:finish, 6:write_over，7:delivery_over
    int             del;                    // logic delete flag, 0: not delete, 1:deleted.
};

/**
 * network topology data
 */
struct topo_rcd
{
    int         id;
    char        *source;
    char        *target;
    float       loss;                    //packet loss =0.1%, loss=0.1;
    bool        is_connected;            // is_connected = 1 if ping OK;
    int         available_bw;            // unit = Mbps;
    int         capacity_bw;            // unit = Mbps;
    int         latency;                // unit = ms;
    int         type;                    // 1:fiber,2:twisted pair, 3:wireless, 4:4G 
    char        *create_time;
    char        *update_time;
    int         del;                    // logic delete flag, 0: not delete, 1:deleted.
};

void free_db_err_msg(char *err_msg);

void free_db();

// init database, DDL
int init_db(char *file_name, char **err_msg);

int get_file_by_id_name(uint32_t file_id, char *name,  struct file_rcd *rs,
        char **err_msg);

// get file info by md5, returnd info saved in rs.
int get_file_by_md5(char *md5, struct file_rcd &rs, char **err_msg);

// get file info by md5 and file name.
int get_file_by_md5_name(char *md5, char *name,  struct file_rcd &rs, char **err_msg);

int get_slice_ack_by_id(int id, char **slice_ack, char **err_msg);

int get_file_slice_no_by_id(int id, uint32_t *slice_no, char **err_msg);

// delete file logically by update del flag field
int delete_file_by_md5(char *md5,char **err_msg);

// save file info in rs to database.
int save_file_info(struct file_rcd &rs,char **err_msg);

int update_md5_by_id_and_name(uint32_t file_id, char *name, char *md5, 
            char **err_msg);

int update_md5_and_finish_by_id_and_name(uint32_t file_id, char *name, 
    char *md5, time_t t, char **err_msg);

int update_slice_no_by_id_and_name(uint32_t file_id, char *name,
            char *slice_ack, char **err_msg);

int update_file_info(struct file_rcd &rs,char **err_msg);

// get peer ping info from source to target, return row retrieved.
int get_peer_info(char *source, char *target,char **err_msg );

// update peer info.
int update_peer_info(char *source, char *target,char **err_msg);

// insert peer info.
int insert_peer_info(char *source, char *target,char **err_msg);

//save task info into db.
int save_task_info(struct task_rcd &rs, char **err_msg);

int update_task_status_by_uid(int status, char *uid, char **err_msg);

int update_task_datas_by_uid(uint64_t data_size, uint32_t total, 
uint32_t start_no, uint32_t end_no,char *uid, char **err_msg);

int update_task_restart_by_uid(char *uid, time_t t, char **err_msg);

int update_task_stop_by_uid(char *uid, time_t t, char **err_msg);

int update_task_slice_by_uid(uint32_t ind, char *uid, char **err_msg);

//update task info in db.
int update_task_info(struct task_rcd &rs, char **err_msg);

//delete task info by id.
int delete_update_task_info(char *uid, char **err_msg);

int update_task_finish_by_uid(char *uid, time_t t, char **err_msg);

int get_task_status_by_uuid(char *uuid, int *status, char **err_msg);

//get task info by uid.
int get_task_by_uid(struct task_rcd &rs, char *uid, char **err_msg);

//get topology list only with source and target.
int get_task_by_uid(struct task_rcd &rs, char *uid, char **err_msg);

//get topology detail with topo from "source" to "target" 
int get_topo_list(list<struct topo_rcd*> &rs_list, char **err_msg);

//save topology info.
int save_topo_info(struct topo_rcd &rs, char **err_msg);

//update topology info.
int update_topo_info(struct topo_rcd &rs, char **err_msg);

//get multi file receiver by task_id
int get_topo_info(char *source, char *target, struct topo_rcd &rs, char **err_msg);

int get_task_status(int task_id, char **err_msg);

//get task status by task id.
int get_task_file_receiver(int task_id, int file_id, char **receiver_list, char **err_msg);

//get percentage of file uploaded by file id(db primary key).
int get_file_slice_no(uint32_t file_id, char *name, uint32_t *slice_no, char **err_msg);

//get last data transfer rate from db.
int get_last_task_data_rate(char **err_msg);

#endif
