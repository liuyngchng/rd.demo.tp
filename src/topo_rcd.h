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
            f.id = v.get<int>("id");
            string source = v.get<string>("source");
            t.source = source.c_str();
            string target = v.get<string>("target");
            t.target, target.c_str();
            t.loss = v.get<float>("loss");
            t.is_connected = v.get<bool>("is_connected");
            t.available_bw = v.get<int>("available_bw");
            t.capacity_bw = v.get<int>("capacity_bw");
            t.lantency = v.get<int>("lantency");
            t.type = v.get<int>("type");
            string create_time = v.get<string>("create_time");
            t.create_time = create_time.c_str():
            string update_time = v.get<string>("update_time");
            t.update_time = update_time;
            f.del = v.get<int>("del");
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
            string create_time = f.create_time;
            v.set("create_time", create_time);
            string update_time = f.update_time;
            v.set("update_time", update_time);
            v.set("del", f.del);
        }
    };  
}
