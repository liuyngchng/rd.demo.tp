/**
 * export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/rd/workspace/soci/build/lib
 * export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/rd/dmdbms/bin/
 * odbcinst -j
 */
#include "soci/soci.h"
#include "soci/odbc/soci-odbc.h"
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
	connection_parameters parameters("odbc", "DSN=dm");
	parameters.set_option(odbc_option_driver_complete, "0" /* SQL_DRIVER_NOPROMPT */);
	//multithread
    const size_t poolSize = 10;
    connection_pool pool(poolSize);

    for (size_t i = 0; i != poolSize; ++i) {
        session & sql = pool.at(i);
        sql.open(parameters);
    }
	cout << "db pool constructed." << endl;
	//return 0;
    //session sql(parameters);
	//session sql(odbc, "filedsn=../config/test-mssql.dsn");
	//cout << "db connected!!"<<endl;
	session sql(pool);
	rowset<row> rs = (sql.prepare << "select a, b, c from sysdba.t");

	// iteration through the resultset:
	for (rowset<row>::const_iterator it = rs.begin(); it != rs.end(); ++it) {
    	const row& row = *it;
    // dynamic data extraction from each row:
    	cout << "a: " << row.get<int>(0) << "\t|";  //get type must match with db.
		cout << "b: " << row.get<int>(1) << "\t|";
		cout << "c: " << row.get<int>(2) << endl;
    }

	cout << "object relation mapping demo" << endl;
    Person p;
    p.id = 1;
    p.lastName = "Smith";
    p.firstName = "Pat";
    sql << "insert into person(id, first_name, last_name) "
        "values(:id, :first_name, :last_name)", use(p);
	cout << "insert OK" << endl;	
	Person p1;
    sql << "select id, first_name, last_name from person limit 1", into(p1);
    assert(p1.id == 1);
    assert(p1.firstName + p.lastName == "PatSmith");
    assert(p1.gender == "unknown");
    cout << "assert is OK" << endl;

	p.firstName = "Patricia";
    sql << "update person set first_name = :first_name "
        "where id = :id", use(p);

}
