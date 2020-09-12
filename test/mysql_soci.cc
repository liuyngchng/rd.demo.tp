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
	string sql_str = "select count(*) from test.a";
	//string sql_str = "insert into cf1 (id, field_0) values (00, 'asd')";
	//sql << sql_str;
	rowset<row> rs = (sql.prepare << "select id, name, value from test.a");

	// iteration through the resultset:
	for (rowset<row>::const_iterator it = rs.begin(); it != rs.end(); ++it) {
    	row const& row = *it;
    // dynamic data extraction from each row:
    	cout << "id: " << row.get<int>(0) << "\t|"
			 << "name: " << row.get<string>(1) << "\t|"
			 << "value: " << row.get<string>(2) << endl;
}
} 
