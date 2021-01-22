all:_server _client libagent.a 

CC=g++
CFLAGS=-g -fPIC -Wall 
INC_FLAG= -I../lib -I. -I../lib/soci/include 
L_FLAG= -L../lib -L../lib/soci 
DIR= $(shell pwd)
BIN=../bin
LIB=../lib
LOG4C=../log4c
L_DIR=$(LOG4C)
L_LIB=$(L_DIR)/build/src/log4c/.libs
SQLITE=$(DIR)/../sqlite3
STACK=../stack


C_BIN=test -d $(BIN) || mkdir -p $(BIN)

OBJS=common.o stack_util.o agent.o ping.o md5.o timestamp.o scheduler.o db_soci.o

_server:server.o $(OBJS) _stack _log4c _sqlite
	$(C_BIN)
	$(CC) $(INC_FLAG) $(L_FLAG) $(CFLAGS) -o $@ $< $(OBJS) -llog4c -lsqlite3 -ltp -lsoci_core -lsoci_odbc -lpthread -ldl 
	cp _server $(BIN)/server
_client:client.o $(OBJS) _stack _log4c _sqlite
	$(C_BIN)
	$(CC) $(INC_FLAG) $(L_FLAG) $(CFLAGS) -o $@ $< $(OBJS) -llog4c -lsqlite3 -ltp -lsoci_core -lsoci_odbc -lpthread -ldl
	cp _client $(BIN)/client
_stack:$(LIB)/libtp.a
	test -e $<
	touch _stack
_log4c:$(L_LIB)/liblog4c.a
	test -e $<
	cp $< $(LIB)
	touch _log4c
_sqlite:$(LIB)/libsqlite3.a
	test -e $<	
	touch _sqlite
libagent.a:agent.o db.o common.o $(STACK)/*.o 
	ar crs libagent.a $^ 
%.o:%.cc %.h 
	$(CC) $(CFLAGS) $(INC_FLAG) $< -c -o $@
clean:
	rm -fr _* *.a *.o $(BIN)/server $(BIN)/client
