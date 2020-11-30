#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <assert.h>
#include <string.h>
#include "mq.h"

enum connection_type {
    CONN_TCP,
    CONN_UNIX,
    CONN_FD,
    CONN_SSL
};

struct config {
    enum connection_type type;

    struct {
        const char *host;
        int port;
        struct timeval timeout;
    } tcp;

    struct {
        const char *path;
    } unix_sock;

    struct {
        const char *host;
        int port;
        const char *ca_cert;
        const char *cert;
        const char *key;
    } ssl;
};

static redisContext *c;

/**
 * disconnect redis
 */
int disconnect(redisContext *c, int keep_fd) {
    redisReply *reply;
    /* Make sure we're on DB 9. */
    reply = (redisReply *)redisCommand(c,"SELECT 9");
    assert(reply != NULL);
    freeReplyObject(reply);
    reply = (redisReply *)redisCommand(c,"FLUSHDB");
    assert(reply != NULL);
    freeReplyObject(reply);

    /* Free the context as well, but keep the fd if requested. */
    if (keep_fd)
        return redisFreeKeepFd(c);
    redisFree(c);
    return -1;
}

/**
 * init redis db connection.
 */
int init1(char *ip, int port) {
    if(NULL != c) {
        return 0;
    }
	printf("connect host:%s, port:%d, type:%d\n", ip, port, CONN_TCP);
	c = redisConnect(ip, port);
    if (c == NULL) {
        printf("Connection error: can't allocate redis context\n");
        exit(1);
    } else if (c->err) {
        printf("Connection error: %s\n", c->errstr);
        redisFree(c);
        exit(1);
    } else {
        printf("connected\n");
    }
    return 0;
}

/**
 * init redis db connection.
 */
redisContext* init() {
    printf("init.\n");    
	struct config cfg = {
        .tcp = {
            .host = "127.0.0.1",
            .port = 6379 
        }
    };
	cfg.type = CONN_TCP;
	printf("host:%s, port:%d, type:%d\n", cfg.tcp.host, cfg.tcp.port, cfg.type);
	redisContext *c = redisConnect(cfg.tcp.host, cfg.tcp.port);
    if (c == NULL) {
        printf("Connection error: can't allocate redis context\n");
        exit(1);
    } else if (c->err) {
        printf("Connection error: %s\n", c->errstr);
        redisFree(c);
        exit(1);
    } else {
        printf("connected\n");
    }
    return c;
}

/**
 * populate cmd with key and elmt as "cmd key elmt".
 */
char * populate_cmd(char* cmd, char* key, char* elmt) {
    char splt[] = " ";
    const int sum_len = strlen(cmd) + strlen(splt)+ strlen(key) + strlen(splt) + strlen(elmt) + 1;
    char* cmd_exe = (char*)malloc(sum_len);
    bzero(cmd_exe, sizeof(cmd_exe));
    strcat(cmd_exe, cmd);
    strcat(cmd_exe, splt);
    strcat(cmd_exe, key);
    strcat(cmd_exe, splt);
    strcat(cmd_exe, elmt);
    printf("cmd=%s\n", cmd_exe);
    return cmd_exe;
}

/**
 * run redis cmd: LPUSH key elmt
 */
void lpush(char* key, char* elmt) {
    redisReply *r;
    char cmd[] = "LPUSH";
    char * cmd_exe = populate_cmd(cmd, key, elmt);
    r = (redisReply *)redisCommand(c, cmd_exe);
    printf("type=%d,integer=%lld,dval=%lf,len=%ld,str=%s,vtype=%s,elements=%ld\n", 
        r->type,r->integer,r->dval,r->len,r->str,r->vtype,r->elements);
    free(cmd_exe);
}

/**
 * convert a integer to a char array.
 */
void itoa (int n, char s[])
{
    int i, sign;
    if ((sign = n) < 0)
        n=-n;
    i = 0;
    do {
        s[i++] = n%10 + '0';
    } while ((n/=10) > 0); 
    if(sign < 0)
        s[i++] = '-';
    s[i] ='\0';
    int l = strlen(s);
    for(int j=0; j < l/2; j++) {
        char t = s[j];
        s[j] = s[l-1-j];
        s[l-1-j] = t;
    }   
}

/**
 * run redis cmd: LTRIM key start stop, "start" index start from 0.
 */
void ltrim(char* key, int start, int stop) {
    redisReply *r;
    char cmd[] = "LTRIM ";
    char start_c[32] = {0};
    itoa(start, start_c);
    char stop_c[32] = {0};
    itoa(stop, stop_c);
    const int sum_len = strlen(start_c) + strlen(stop_c) + 2;
    char ss[sum_len];
    bzero(ss, sizeof(ss));
    strcat(ss, start_c);
    strcat(ss, " ");
    strcat(ss, stop_c);
    char * cmd_exe = populate_cmd(cmd, key, ss);
    r = (redisReply *)redisCommand(c, cmd_exe);
    printf("type=%d,integer=%lld,dval=%lf,len=%ld,str=%s,vtype=%s,elements=%ld\n", 
        r->type,r->integer,r->dval,r->len,r->str,r->vtype,r->elements);
    free(cmd_exe);
}

/**
 * trim list name "key" reserve element from "start" to "stop".
 * "start" index start from 0.
 */
void trim(char* key, int start, int stop) {
    ltrim(key, start, stop);
}

/**
 * run redis cmd: RPOP key
 */
char* rpop(char* key) {
    redisReply *r;
    char cmd[] = "RPOP";
    char * cmd_exe = populate_cmd(cmd, key, "");
    r = (redisReply *)redisCommand(c, cmd_exe);
    printf("type=%d,integer=%lld,dval=%lf,len=%ld,str=%s,vtype=%s,elements=%ld\n", 
        r->type,r->integer,r->dval,r->len,r->str,r->vtype,r->elements);
    free(cmd_exe);
    return r->str;
    // if (strcmp(r->str, "(null)") == 0) {
    //     return NULL;
    // } else {
    //     return r->str;
    // }
}

/**
 * run redis cmd: LLEN key
 */
int llen(char* key) {
    redisReply *r;
    char cmd[] = "LLEN";
    char * cmd_exe = populate_cmd(cmd, key, "");
    r = (redisReply *)redisCommand(c, cmd_exe);
    printf("type=%d,integer=%lld,dval=%lf,len=%ld,str=%s,vtype=%s,elements=%ld\n", 
        r->type,r->integer,r->dval,r->len,r->str,r->vtype,r->elements);
    free(cmd_exe);
    return r->integer;
}

/**
 * push elememt elmt to the head of a list named "key".
 */
void push(char* key, char* elmt) {
    lpush(key, elmt);
}

/**
 * pop element from the bottom of a list named "key".
 */
char* pop(char* key) {
    return rpop(key);
}

/**
 * get the element number in list name "key".
 */
int get_len(char* key) {
    return llen(key);
}

/**
 * for test purpose only.
 */ 
int main() {
    char ip[] = "127.0.0.1";
    int port = 6379;
    init1(ip, port);
    char key[] = "data";
    char elmt[] = "elementtest";
	lpush(key, elmt);
    // char* value = rpop(key);
    // printf("elmt = %s\n", value);
    // long long len = llen(key);
    // printf("len=%lld\n", len);
    // ltrim(key, 0, 6);
    // printf("disconnected\n");
}
