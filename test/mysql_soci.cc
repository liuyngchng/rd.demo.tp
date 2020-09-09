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
   
int main() {
	session sql(mysql,"service=mysql user=root password=0000");
	cout << "has connected!!"<<endl;
	string sql_str = "select count(*) from test.a";
	//string sql_str = "insert into cf1 (id, field_0) values (00, 'asd')";
	sql << sql_str;
} 
