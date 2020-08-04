all:sqlite3 libsqlite3.a
CC=gcc
CFLAGS=-g -Wall
LIB=../lib
sqlite3:shell.o sqlite3.o
	$(CC) shell.c sqlite3.o -lpthread -ldl -o sqlite3
libsqlite3.a:sqlite3.o
	ar crs libsqlite3.a sqlite3.o 
	cp libsqlite3.a sqlite3.h ${LIB} 
sqlite3.o:
	tar -zxf sqlite3.c.tar.gz
	$(CC) -o sqlite3.o  -c sqlite3.c
shell.o:shell.c
	$(CC) -o shell.o -c shell.c
clean:
	rm -fr *.a *.o libsqlite3 sqlite3.c sqlite3
