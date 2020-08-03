#ifndef _AGENT_H_
#define _AGENT_H_
#include <sys/types.h>
#include <tp.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <string>
#include <iostream>
#include <fstream>
#include "common.h"
#include "md5.h"

#define CB 0;		//appType
#define DB 1;
#define SS 2;
/**
 * send file to server.
 */
int send_file(char* path, char *ip, int& port);

/**
 * get file from server.
 */
int get_file(char* file_name, char *ip, int& port);
#endif
