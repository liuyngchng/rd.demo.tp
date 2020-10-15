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
#include "person.h"

using namespace std;
using namespace soci;

/**
 * db pool size.
 */
static const size_t pool_size = 10;

/**
 * db pool.
 */
static connection_pool pool(pool_size);

/**
 * database init flag, 
 * true: db inited, 
 * false: not inited.
 */
static bool is_db_inited = false;

/**
 * init db pool, to be compatible with sqlite, the argument sqlite3 is reserved
 * but not be used in function.
 */
void init_db(sqlite3 **db) 
{
	if (is_db_inited) {
		return;
	}
	connection_parameters parameters("odbc", "DSN=dm");
    parameters.set_option(odbc_option_driver_complete, "0" /* SQL_DRIVER_NOPROMPT */);
	for (size_t i = 0; i != pool_size; ++i) {
        session & sql = pool.at(i);
        sql.open(parameters);
    }
	is_db_inited = true;
    cout << "db pool constructed." << endl;
}


/**
 * save file info in rs to database.
 */
bool save_file_info(struct file_rcd &rs)
{
	init_db(NULL);
	session sql(pool);
	sql << "insert into 'file_info'(app_id, name, md5, size, "
         "slice_size, slice_total,slice_snd, path)"
        "values(:app_id, :name, :md5,:size, :slice_size, slice_total, slice_snd, path)", use(p);
    cout << "insert OK" << endl;	
}
