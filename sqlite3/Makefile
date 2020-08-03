all:shell libsqlite3
CC=gcc
CFLAGS=-g -Wall
LIB=../lib
shell:shell.c sqlite3.o
	$(CC) shell.c sqlite3.o -lpthread -ldl -o sqlite3
	touch shell
libsqlite3:sqlite3.o
	cp sqlite3.o ${LIB} 
	cp sqlite3.h ${LIB}
	touch libsqlite3
sqlite3.o:sc
	$(CC) -c sqlite3.c -lpthread -ldl -o sqlite3.o
sc:sqlite3.h
	tar -zxf sqlite3.c.tar.gz
	touch sc
clean:
	rm -fr *.o sc libsqlite3 shell sqlite3.c sqlite3
