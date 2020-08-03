#ifndef _PING_H_
#define _PING_H_
#include <arpa/inet.h>
#include "tp.h"
#include "log4c.h"
#include "const.h"
#include "common.h"

int ping(char* path, int port);

#endif
