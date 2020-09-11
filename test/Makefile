all: _md5test _dm_odbc _file_path_test _timestamp_test _db_test _sqlite_test _mysql _mysql_soci

CC=g++
CFLAGS=-g -Wall
BUILD_CFLAGS= -I../lib -I../src 
LINK_FLAG=-L../lib

_mysql_soci:mysql_soci.cc
	$(CC) ${CFLAGS} -o $@ $< -I../lib/soci/include/ -I/usr/include/mysql -L../lib/soci/ -L/usr/lib/x86_64-linux-gnu -lsoci_mysql -lsoci_core -lmysqlclient -ldl 
_sqlite_test:sqlite_test.o 
	$(CC) $(BUILD_CFLAGS) ${LINK_FLAG} -o $@ $< -lsqlite3 -ldl -lpthread
_db_test:db_test.o db.o common.o
	$(CC) $(BUILD_CFLAGS) $(LINK_FLAG) -o $@ $^ -llog4c -lsqlite3 -ldl -lpthread
_dm_odbc:dm_odbc.o
	$(CC) -o $@ $^ -L/usr/lib -lodbc
_mysql:mysql.o
	$(CC) -I/usr/local/mysql/include -I/usr/include/mysql  -L/usr/local/mysql/lib -L/usr/lib/x86_64-linux-gnu -o $@ $< -lmysqlclient
_timestamp_test:timestamp.o
	$(CC) ${CFLAGS} ${BUILD_CFLAGS} -o $@ $< timestamp_test.cc

_file_path_test:file_path_test.cc
	$(CC) ${CFLAGS} ${BUILD_CFLAGS} -o $@  $< ../src/common.cc

_md5test:md5test.o md5.o common.o
	$(CC) ${CFLAGS} ${BUILD_CFLAGS} -o $@ $^ 
common.o:
	$(CC) $(BUILD_CFLAGS) $(CFLAGS) -o $@ -c ../src/common.cc
md5.o: 
	$(CC) -o $@ -c ../src/md5.cc
md5test.o:md5test.cc
	$(CC) $(BUILD_CFLAGS) $(CFLAGS) -o $@ -c $^
db_test.o:db_test.cc
	$(CC) $(BUILD_CFLAGS) $(CFLAGS) -o $@ -c $<
dm_odbc.o:dm_odbc.cc
	$(CC) $(CFLAGS)  -L/usr/lib -lodbc -c $^
db.o:
	$(CC) $(BUILD_CFLAGS) $(CFLAGS) -o $@ -c ../src/db.cc
mysql.o:mysql.c
	$(CC) -I/usr/local/mysql/include -I/usr/include/mysql -o $@ -c $<
timestamp.o:
	$(CC) $(BUILD_CFLAGS) $(CFLAGS)  -o $@ -c ../src/timestamp.cc
sqlite_test.o:sqlite_test.cc
	$(CC) $(BUILD_CFLAGS) $(CFLAGS)  -o $@ -c $^
clean:
	rm -fr _* *.o *.a
