all: _md5test _file_path_test _timestamp_test _db_test

CC=g++
CFLAGS=-g -Wall
BUILD_CFLAGS= -I../lib -I../src -L../lib

_db_test:db_test.o db.o common.o
	$(CC) $(BUILD_CFLAGS) -o _db_test db_test.o db.o common.o ../log4c/obj/*.o ../lib/sqlite3.o -ldl -lpthread

_timestamp_test:timestamp.o
	$(CC) ${CFLAGS} ${BUILD_CFLAGS} -o _timestamp_test timestamp.o timestamp_test.cc

_file_path_test:file_path_test.cc
	$(CC) ${CFLAGS} ${BUILD_CFLAGS} -o _file_path_test  file_path_test.cc ../src/common.cc

_md5test:md5test.o md5.o common.o
	$(CC) ${CFLAGS} ${BUILD_CFLAGS} -o _md5test md5test.o md5.o common.o 
common.o:
	$(CC) $(BUILD_CFLAGS) $(CFLAGS) -o common.o -c ../src/common.cc
md5.o: 
	$(CC) -o md5.o -c ../src/md5.cc
md5test.o: 
	$(CC) $(BUILD_CFLAGS) $(CFLAGS) -o md5test.o -c md5test.cc
db_test.o:
	$(CC) $(BUILD_CFLAGS) $(CFLAGS) -o db_test.o -c db_test.cc
db.o:
	$(CC) $(BUILD_CFLAGS) $(CFLAGS) -o db.o -c ../src/db.cc
timestamp.o:
	$(CC) $(BUILD_CFLAGS) $(CFLAGS)  -o timestamp.o -c ../src/timestamp.cc
clean:
	rm -fr _* *.o *.a


