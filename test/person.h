using namespace std;

struct Person
{
    int id; 
    string firstName;
    string lastName;
    string gender;
};

namespace soci
{
    template<>
    struct type_conversion<Person>
    {   
        typedef values base_type;

        static void from_base(values const & v, indicator /* ind */, Person & p)
        {
            p.id = v.get<int>("id");
            p.firstName = v.get<std::string>("first_name");
            p.lastName = v.get<std::string>("last_name");
            p.gender = v.get<std::string>("gender", "unknown");
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
