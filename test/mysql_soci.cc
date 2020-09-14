/*
g++ -g -Wall -o _mysql_soci mysql_soci.cc -I../lib/soci/include/ -I /usr/local/mysql/include -I/usr/include/mysql -L../lib/soci/ -L/usr/local/mysql/lib -lsoci_mysql -lsoci_core -lmysqlclient -ldl
*/
#include "soci/soci.h"
#include "soci/mysql/soci-mysql.h"
#include<iostream>
#include<istream>
#include<ostream>
#include<string>
#include<exception>
#include<unistd.h>
   
using namespace std;
using namespace soci;
   
int main() 
{
	session sql(mysql,"service=mysql user=root password=0000");
	cout << "db connected!!"<<endl;

	cout <<"rowset collection demo" << endl;
	rowset<row> rs = (sql.prepare << "select id, name, value from test.a");
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
	int id1 = 10;
	string name1 = "my name1";
	string value1 = "my value1";
	sql << "insert into test.a (id, name, value) values (:id, :name, :value)", use(id1), use(name1), use(value1); 
} 
