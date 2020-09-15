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
   
using namespace std;
using namespace soci;

int main()
{
	session sql("sqlite3", "db=test.db timeout=2 shared_cache=true");
	int count;
	sql << "select count(*) from file_info", into(count);
	cout << count << endl;
}
