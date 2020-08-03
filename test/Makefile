all: md5test file_path_test timestamp_test db_test

CC=g++
CFLAGS=-g -Wall
BUILD_CFLAGS= -I../lib -I../src -L../lib
LOG4C=log4c-1.2.4

db_test:db_test.o db.o common.o
	$(CC) $(BUILD_CFLAGS) -o ../bin/db_test ../obj/db_test.o ../obj/db.o ../obj/common.o ../src/${LOG4C}/obj/*.o ../lib/sqlite3.o -ldl -lpthread

timestamp_test:timestamp.o
	$(CC) ${CFLAGS} ${BUILD_CFLAGS} -o ../bin/timestamp_test ../obj/timestamp.o timestamp_test.cc

file_path_test:file_path_test.cc
	$(CC) ${CFLAGS} ${BUILD_CFLAGS} -o ../bin/file_path_test  file_path_test.cc ../src/common.cc

md5test:md5test.o md5.o common.o
	$(CC) ${CFLAGS} ${BUILD_CFLAGS} -o ../bin/md5test ../obj/md5test.o ../obj/md5.o ../obj/common.o 
common.o:
	$(CC) $(BUILD_CFLAGS) $(CFLAGS) -o ../obj/common.o -c ../src/common.cc
md5.o: 
	$(CC) -o ../obj/md5.o -c ../src/md5.cc
md5test.o: 
	$(CC) $(BUILD_CFLAGS) $(CFLAGS) -o ../obj/md5test.o -c md5test.cc
db_test.o:
	$(CC) $(BUILD_CFLAGS) $(CFLAGS) -o ../obj/db_test.o -c db_test.cc
db.o:
	$(CC) $(BUILD_CFLAGS) $(CFLAGS) -o ../obj/db.o -c ../src/db.cc
timestamp.o:
	$(CC) $(BUILD_CFLAGS) $(CFLAGS)  -o ../obj/timestamp.o -c ../src/timestamp.cc
clean:
	rm ../bin/* ../obj/*.o ../obj/*.a


