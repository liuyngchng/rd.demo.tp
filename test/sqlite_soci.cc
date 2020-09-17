/*
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/rd/workspace/soci/build/lib
g++ -g -Wall -o _sqlite_soci sqlite_soci.cc -I../lib/soci/include/ -I../lib -L../lib/soci/ -lsoci_core -ldl
./_sqlite_soci
*/
#include "soci/soci.h"
#include "soci/sqlite3/soci-sqlite3.h"
#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <exception>
#include <unistd.h>
#include <assert.h>
#include "person.h"
   
using namespace std;
using namespace soci;

int main()
{
    //multithread
    const size_t poolSize = 10; 
    connection_pool pool(poolSize);

    for (size_t i = 0; i != poolSize; ++i) {
        session & sql = pool.at(i);
        sql.open("sqlite3", "db=test.db timeout=2 shared_cache=true");
    }   
    cout << "db pool constructed." << endl;
    session sql(pool);
	sql << "create table if not exists t(a int ,b int ,c int);";
    sql << "delete from t;";
	sql << "insert into t values (1, 2,3);";
	sql << "insert into t values (1, 2, 3);";
	rowset<row> rs = (sql.prepare << "select a, b, c from t");
	// iteration through the resultset:
    for (rowset<row>::const_iterator it = rs.begin(); it != rs.end(); ++it) {
        const row& row = *it;
    // dynamic data extraction from each row:
        cout << "a: " << row.get<int>(0) << "\t|";  //get type must match with db.
        cout << "b: " << row.get<int>(1) << "\t|";
        cout << "c: " << row.get<int>(2) << endl;
    }

	int count;
	sql << "select count(*) from file_info", into(count);
	cout << count << endl;
	
	sql << "create table if not exists person(id int ,first_name varchar(32), last_name varchar(32), gender char(10));";
	sql << "delete from person;";
    cout << "object relation mapping demo" << endl;
    Person p;
    p.id = 1;
    p.lastName = "Smith";
    p.firstName = "Pat";
    sql << "insert into person(id, first_name, last_name) "
        "values(:id, :first_name, :last_name)", use(p);
    cout << "insert OK" << endl;    
    Person p1; 
    sql << "select id, first_name, last_name,gender from person limit 1", into(p1);
    assert(p1.id == 1); 
    assert(p1.firstName + p.lastName == "PatSmith");
    assert(p1.gender == "unknown");
    cout << "assert is OK" << endl;

    p.firstName = "Patricia";
    sql << "update person set first_name = :first_name "
        "where id = :id", use(p);
}
