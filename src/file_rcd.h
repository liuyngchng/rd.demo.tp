#include "db.h"

using namespace std;

namespace soci
{
    template<>
    struct type_conversion<file_rcd>
    {   
        typedef values base_type;

        static void from_base(values const & v, indicator /* ind */, file_rcd &f)
        {
            f.id = v.get<int>("id");
            f.app_id = v.get<int>("app_id");
            f.file_id = v.get<int>("file_id");
            string name = v.get<string>("name");
            strcpy(f.name, name.c_str());
            string md5 = v.get<string>("md5");
            strcpy(f.md5, md5.c_str());
            f.size = v.get<int>("size");
            string path = v.get<string>("path");
            strcpy(f.path, path.c_str());
            f.slice_size = v.get<int>("slice_size");
            f.slice_total = v.get<int>("slice_total");
            f.slice_snd = v.get<int>("slice_snd");
            string create_time = v.get<string>("create_time");
            strcpy(f.create_time, create_time.c_str()):
            string update_time = v.get<string>("update_time");
            strcpy(f.update_time, update_time);
            f.del = v.get<int>("del");
        }

        static void to_base(const file_rcd &f, values &v, indicator & ind)
        {
            v.set("id", f.id);
            v.set("app_id", f.app_id);
            v.set("file_id", f.file_id);
            string name = f.name;
            v.set("name", name);
            string md5 = f.md5;
            v.set("md5", md5);
            string size = f.size;
            v.set("size", size);
            string path  =  f.path;
            v.set("path", path);
            v.set("slice_size", f.slice_size);
            v.set("slice_total", slice_total);
            v.set("slice_snd", slice_snd);
            string create_time = f.create_time;
            v.set("create_time", create_time);
            string update_time = f.update_time;
            v.set("update_time", update_time);
            v.set("del", f.del);
        }
    };  
}
