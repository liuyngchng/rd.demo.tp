#ifndef _TOPO_RCD_H_
#define _TOPO_RCD_H_
#include "db.h"

using namespace std;

namespace soci
{
    template<>
    struct type_conversion<topo_rcd>
    {   
        typedef values base_type;

        static void from_base(values const & v, indicator /* ind */, topo_rcd &t)
        {
            t.id = v.get<int>("id");
            string source = v.get<string>("source");
            t.source = const_cast<char*>(source.c_str());
            string target = v.get<string>("target");
            t.target = const_cast<char*>(target.c_str());
            t.loss = v.get<int>("loss");
            t.is_connected = v.get<int>("is_connected");
            t.available_bw = v.get<int>("available_bw");
            t.capacity_bw = v.get<int>("capacity_bw");
            t.latency = v.get<int>("latency");
            t.type = v.get<int>("type");
            string create_time = v.get<string>("create_time");
            t.create_time = const_cast<char*>(create_time.c_str());
            string update_time = v.get<string>("update_time");
            t.update_time = const_cast<char*>(update_time.c_str());
            t.del = v.get<int>("del");
        }

        static void to_base(const topo_rcd &t, values &v, indicator & ind)
        {
            v.set("id", t.id);
            string source = t.source;
            v.set("source", source);
            string target = t.target;
            v.set("target", target);
            v.set("loss", t.loss);
            v.set("is_connected", t.is_connected);
            v.set("available_bw", t.available_bw);
            v.set("capacity_bw", t.capacity_bw);
            v.set("latency", t.latency);
            v.set("type", t.type);
            string create_time = t.create_time;
            v.set("create_time", create_time);
            string update_time = t.update_time;
            v.set("update_time", update_time);
            v.set("del", t.del);
        }
    };  
}
#endif
