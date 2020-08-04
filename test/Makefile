all: _md5test _file_path_test _timestamp_test _db_test _sqlite_test

CC=g++
CFLAGS=-g -Wall
BUILD_CFLAGS= -I../lib -I../src 
LINK_FLAG=-L../lib

_sqlite_test:sqlite_test.o 
	$(CC) $(BUILD_CFLAGS) ${LINK_FLAG} -o $@ $< -lsqlite3 -ldl -lpthread
_db_test:db_test.o db.o common.o
	$(CC) $(BUILD_CFLAGS) $(LINK_FLAG) -o $@ db_test.o db.o common.o -llog4c -lsqlite3 -ldl -lpthread

_timestamp_test:timestamp.o
	$(CC) ${CFLAGS} ${BUILD_CFLAGS} -o $@ $< timestamp_test.cc

_file_path_test:file_path_test.cc
	$(CC) ${CFLAGS} ${BUILD_CFLAGS} -o $@  file_path_test.cc ../src/common.cc

_md5test:md5test.o md5.o common.o
	$(CC) ${CFLAGS} ${BUILD_CFLAGS} -o $@ md5test.o md5.o common.o 
common.o:
	$(CC) $(BUILD_CFLAGS) $(CFLAGS) -o $@ -c ../src/common.cc
md5.o: 
	$(CC) -o $@ -c ../src/md5.cc
md5test.o:
	$(CC) $(BUILD_CFLAGS) $(CFLAGS) -o $@ -c md5test.cc
db_test.o:
	$(CC) $(BUILD_CFLAGS) $(CFLAGS) -o $@ -c db_test.cc
db.o:
	$(CC) $(BUILD_CFLAGS) $(CFLAGS) -o $@ -c ../src/db.cc
timestamp.o:
	$(CC) $(BUILD_CFLAGS) $(CFLAGS)  -o $@ -c ../src/timestamp.cc
sqlite_test.o:
	$(CC) $(BUILD_CFLAGS) $(CFLAGS)  -o $@ -c sqlite_test.cc
clean:
	rm -fr _* *.o *.a
