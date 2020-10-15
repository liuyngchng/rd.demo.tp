using namespace std;

struct file_info 
{
	int     app_id;
    int     file_id;
    string  name;
    string  md5;
	// file size
    int     size;
	// file path
    string  path;
	// unit:MB, file slice size 
    int     slice_size;  
	// total slice cout
    int     slice_total;
	// numbers of slices have been sent
    int     slice_snd;
	// format: YYYY-mm-DD HH:MM:ss SSS
    string  create_time;
    string  update_time;
	// logic delete flag , 0:not delete, 1:deleted
    int     del; 
};

namespace soci
{
    template<>
    struct type_conversion<Person>
    {   
        typedef values base_type;

        static void from_base(values const & v, indicator /* ind */, file_rcd &f)
        {
            f.app_id = v.get<int>("app_id");
            f.file_id = v.get<std::string>("file_id");
            f.name = v.get<std::string>("name");
            f.md5 = v.get<std::string>("md5", "unknown");
			
        }

        static void to_base(const Person & p, values & v, indicator & ind)
        {
            v.set("id", p.id);
            v.set("first_name", p.firstName);
            v.set("last_name", p.lastName);
            v.set("gender", p.gender, p.gender.empty() ? i_null : i_ok);
            ind = i_ok;
        }
    };  
}
