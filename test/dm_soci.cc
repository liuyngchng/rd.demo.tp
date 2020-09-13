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
   
using namespace std;
using namespace soci;
   
int main() 
{
	connection_parameters parameters("odbc", "DSN=dm");
	parameters.set_option(odbc_option_driver_complete, "0" /* SQL_DRIVER_NOPROMPT */);
    session sql(parameters);
	//session sql(odbc, "filedsn=../config/test-mssql.dsn");
	cout << "db connected!!"<<endl;
	rowset<row> rs = (sql.prepare << "select a, b, c from sysdba.t");

	// iteration through the resultset:
	for (rowset<row>::const_iterator it = rs.begin(); it != rs.end(); ++it) {
    	const row& row = *it;
    // dynamic data extraction from each row:
    	cout << "a: " << row.get<int>(0) << "\t|";  //get type must match with db.
		cout << "b: " << row.get<int>(1) << "\t|";
		cout << "c: " << row.get<int>(2) << endl;
    }
}
