#ifndef _TASK_RCD_H_
#define _TASK_RCD_H_
#include "db.h"

using namespace std;

namespace soci
{
    template<>
    struct type_conversion<task_rcd>
    {
        typedef values base_type;

        static void from_base(values const & v, indicator /* ind */, task_rcd &t)
        {
            t.id = v.get<int>("id");
            t.app_id = v.get<int>("app_id");
            t.data_size = v.get<int>("data_size");
            string uid = v.get<string>("uid");
            t.uid = const_cast<char*>(uid.c_str());
            string target = v.get<string>("target");
            t.target = const_cast<char*>(target.c_str());
            t.zone = v.get<int>("zone");
            string create_time = v.get<string>("create_time");
            t.create_time = const_cast<char*>(create_time.c_str());
            string update_time = v.get<string>("update_time");
            t.update_time = const_cast<char*>(update_time.c_str());
            string interrupt_time = v.get<string>("interrupt_time");
            t.interrupt_time = const_cast<char*>(interrupt_time.c_str());
            string restart_time = v.get<string>("restart_time");
            t.restart_time = const_cast<char*>(restart_time.c_str());
            string cancel_time = v.get<string>("cancel_time");
            t.cancel_time = const_cast<char*>(cancel_time.c_str());
            t.file_id = v.get<int>("file_id");
            t.priority = v.get<int>("priority");
            t.progress = v.get<int>("progress");
            string op_uid = v.get<string>("op_uid");
            t.op_uid = const_cast<char*>(op_uid.c_str());
            t.op_type = v.get<int>("op_type");
            t.status = v.get<int>("status");
            t.del = v.get<int>("del");
        }

        static void to_base(const task_rcd &t, values &v, indicator & ind)
        {
            v.set("id", t.id);
            v.set("app_id", t.app_id);
            v.set("data_size", t.data_size);
            string uid = t.uid;
            v.set("uid", uid);
            string target = t.target;
            v.set("target", target);
            v.set("zone", t.zone);
            string create_time = t.create_time;
            v.set("create_time", create_time);
            string update_time = t.update_time;
            v.set("update_time", update_time);
            string interrupt_time = t.interrupt_time;
            v.set("interrupt_time", interrupt_time);
            string restart_time = t.restart_time;
            v.set("restart_time", restart_time);
            string cancel_time = t.cancel_time;
            v.set("cancel_time", cancel_time);
            v.set("file_id", t.file_id);
            v.set("priority", t.priority);
            v.set("progress", t.progress);
            string op_uid  =  t.op_uid;
            v.set("op_uid", op_uid);
            v.set("op_type", t.op_type);
            v.set("status", t.status);
            v.set("del", t.del);
        }
    };  
}
#endif
