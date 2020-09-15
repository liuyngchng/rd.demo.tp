all:sqlite3 libsqlite3.a libsqlite3.so
CC=gcc
CFLAGS=-g -fPIC -Wall
LIB=../lib
sqlite3:shell.o sqlite3.o
	$(CC) $(CFLAGS) -o $@ shell.c sqlite3.o -lpthread -ldl
libsqlite3.so:sqlite3.o
	$(CC) -shared -o $@ $^ -lpthread -ldl
libsqlite3.a:sqlite3.o
	ar crs libsqlite3.a sqlite3.o 
	cp libsqlite3.a sqlite3.h ${LIB} 
sqlite3.o:
	tar -zxf sqlite3.c.tar.gz
	$(CC) $(CFLAGS) -o $@  -c sqlite3.c
shell.o:shell.c
	$(CC) $(CFLAGS) -o $@ -c $^
clean:
	rm -fr *.a *.o libsqlite3 sqlite3.c sqlite3
