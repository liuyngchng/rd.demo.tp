all:_server _client libagent.a 

CC=g++
CFLAGS=-g -fPIC -Wall 
BUILD_CFLAGS= -I../lib -I. 
DIR= $(shell pwd)
BIN=../bin
LIB=../lib
LOG4C=../log4c
L_DIR=${LOG4C}
L_OBJ=${L_DIR}/obj
L_BUILD=${L_DIR}/build/src
SQLITE=${DIR}/../sqlite3
STACK=../stack

# _stack _log4c _sqlite
ELF_OBJ=${OBJS} ${STACK}/*.o ${L_OBJ}/*.o ${LIB}/sqlite3.o

C_BIN=test -d ${BIN} || mkdir -p ${BIN}
C_L_OBJ=test -d ${L_OBJ} || mkdir -p ${L_OBJ}

OBJS=common.o stack_util.o agent.o ping.o db.o md5.o timestamp.o scheduler.o

_server:server.o ${OBJS} _stack _log4c _sqlite
	${C_BIN}
	$(CC) $(BUILD_CFLAGS) $(CFLAGS) -o _server server.o ${ELF_OBJ}  -lpthread -ldl 
	cp _server ${BIN}/server
_client:client.o ${OBJS} _stack _log4c _sqlite
	${C_BIN}
	$(CC) $(BUILD_CFLAGS) $(CFLAGS) -o _client client.o ${ELF_OBJ} -lpthread -ldl
	cp _client ${BIN}/client
_stack:${STACK}/libudt.a
	test -e ${STACK}/libudt.a
	touch _stack
_log4c:${L_BUILD}/log4c/*.o
	${C_L_OBJ}
	#cp ${LOG4C}/src/log4c.h ../lib
	#cp ${LOG4C}/src/log4c/*.h ../lib/log4c
	cp ${L_BUILD}/log4c/*.o  ${L_OBJ}
	cp ${L_BUILD}/sd/*.o  ${L_OBJ}
	touch _log4c
	cd ${DIR}
_sqlite:${SQLITE}/sqlite3.o
	cp ${SQLITE}/sqlite3.o ${LIB}
	${C_BIN}
	cp ${SQLITE}/_sqlite3 ${BIN}/sqlite3
	touch _sqlite
libagent.a:agent.o db.o common.o 
	ar crs libagent.a agent.o common.o db.o ${STACK}/*.o 
	cp libagent.a ${LIB}
%.o:%.cc %.h 
	$(CC) $(CFLAGS) ${BUILD_CFLAGS} $< -c -o $@
clean:
	rm -fr _* *.a *.o ${BIN} 
