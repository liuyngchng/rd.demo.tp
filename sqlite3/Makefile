all:_shell _libsqlite3
CC=gcc
CFLAGS=-g -Wall
LIB=../lib
_shell:shell.c sqlite3.o
	$(CC) shell.c sqlite3.o -lpthread -ldl -o _sqlite3
	touch _shell
_libsqlite3:sqlite3.o
	cp sqlite3.o ${LIB} 
	cp sqlite3.h ${LIB}
	touch _libsqlite3
sqlite3.o:_sc
	$(CC) -c sqlite3.c -lpthread -ldl -o sqlite3.o
	rm -fr sqlite3.c
_sc:sqlite3.h
	tar -zxf sqlite3.c.tar.gz
	touch _sc
clean:
	rm -fr _* *.o sc libsqlite3 shell sqlite3.c sqlite3
