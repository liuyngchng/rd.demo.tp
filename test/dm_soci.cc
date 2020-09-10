/**
 * export ODBCINI=/etc/odbc.ini
 * export ODBCSYSINI=/etc 
 * odbcinst -j
 */
#include "soci/soci.h"
#include "soci/odbc/soci-odbc.h"
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
	connection_parameters parameters("odbc", "DSN=dm");
	parameters.set_option(odbc_option_driver_complete, "0" /* SQL_DRIVER_NOPROMPT */);
	session sql(odbc, "filedsn=/etc/odbc.ini");
	cout << "has connected!!"<<endl;
	rowset<row> rs = (sql.prepare << "select a, b, c from sysdba.t");

	// iteration through the resultset:
	for (rowset<row>::const_iterator it = rs.begin(); it != rs.end(); ++it) {
    	row const& row = *it;
    // dynamic data extraction from each row:
    	cout << "a: " << row.get<string>(0) << "\t|"
			 << "b: " << row.get<string>(1) << "\t|"
			 << "c: " << row.get<string>(2) << endl;
}
} 
