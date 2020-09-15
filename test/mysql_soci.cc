/*
g++ -g -Wall -o _mysql_soci mysql_soci.cc -I../lib/soci/include/ -I /usr/local/mysql/include -I/usr/include/mysql -L../lib/soci/ -L/usr/local/mysql/lib -lsoci_mysql -lsoci_core -lmysqlclient -ldl
create table person(`id` int null, `first_name` varchar(32) null, `last_name` varchar(32) null, `gender` varchar(32) null);
*/

#include "soci/soci.h"
#include "soci/mysql/soci-mysql.h"
#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <exception>
#include <unistd.h>
#include <assert.h>
   
using namespace std;
using namespace soci;

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

            // p.gender will be set to the default value "unknown"
            // when the column is null:
            p.gender = v.get<std::string>("gender", "unknown");
    
            // alternatively, the indicator can be tested directly:
            // if (v.indicator("GENDER") == i_null)
            // {   
            //     p.gender = "unknown";
            // }
            // else
            // {   
            //     p.gender = v.get<std::string>("GENDER");
            // }
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

   
int main() 
{
	//multithread
	const size_t poolSize = 10; 
	connection_pool pool(poolSize);

	for (size_t i = 0; i != poolSize; ++i) {
    	session & sql = pool.at(i);
    	//sql.open("postgresql://dbname=mydb");
		sql.open(mysql,"service=test user=root password=0000");
	}
	cout << "db pool constructed." << endl;
	//return 0;
	session sql(pool);
	cout << "db connected!!"<<endl;

	cout <<"rowset collection demo" << endl;
	rowset<row> rs = (sql.prepare << "select id, name, value from a");
	// iteration through the resultset:
	for (rowset<row>::const_iterator it = rs.begin(); it != rs.end(); ++it) {
    	row const& row = *it;
    // dynamic data extraction from each row:
    	cout << "id: " << row.get<int>(0) << "\t|"
			 << "name: " << row.get<string>(1) << "\t|"
			 << "value: " << row.get<string>(2) << endl;
	}	
	cout << "basic result demo" << endl;
	int id = 1;
	string name;
	string value;
	sql << "select name, value from test.a where id =" << id, into(name), into(value);
	cout << "name:" << name << ", value:" << value << endl;

	cout << "use demo" << endl;
	int id1 = 110;
	string name1 = "my name1";
	string value1 = "my value1";
	sql << "insert into a (id, name, value) values (:id, :name, :value)", use(id1), use(name1), use(value1); 

	cout << "object relation mapping demo" << endl;
	Person p;
	p.id = 1;
	p.lastName = "Smith";
	p.firstName = "Pat";
	sql << "insert into person(id, first_name, last_name) "
		"values(:id, :first_name, :last_name)", use(p);
	Person p1; 
	sql << "select * from person", into(p1);
	assert(p1.id == 1); 
	assert(p1.firstName + p.lastName == "PatSmith");
	assert(p1.gender == "unknown");
	cout << "assert is OK" << endl;
	
	p.firstName = "Patricia";
	sql << "update person set first_name = :first_name "
        "where id = :id", use(p);

} 
