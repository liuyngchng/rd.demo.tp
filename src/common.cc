/**
 * some common structure and function used in client and server.
 **/
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include "common.h"
#include <iomanip>

/**
 * get filename from file full path
**/
void get_file_name(const char path[], char name[])
{
	int j = strlen(path)-1;
	int i = j;
	for ( ; i >= 0 ; i--) {
		if (path[i] == '/' || path[i] == '\\')
			break;
		else
			name[j-i] = path[i];
	}
	j = strlen(name)-1;
	for (i = 0; i <= j/2; i++) {
		char temp = name[i];
		name[i] = name[j-i];
		name[j-i] = temp;
	}
	name[j+2] = '\0';
}

/**
 * get file path from file full path
**/
int get_file_path(char path[], char name[])
{
	get_file_name(path, name);
	path[strlen(path) - strlen(name)]='\0';
	return strlen(path);
}

int get_file_size(const char path[])
{
	FILE* fp;
	if ((fp = fopen(path,"rb")) == NULL) {
		printf("can't open file: %s, at %d of %s\n", path, __LINE__, __FILE__);
		return -1;
	}
	fseek(fp, 0, SEEK_END);
	long pos = ftell(fp);
	rewind(fp);
	fclose(fp);
	return (int)pos;
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

char *get_ip(string ip_port)
{
	char c = ':';
    char s[20];
    strcpy(s, ip_port.c_str());
    char *p = strchr(s, c);
    p++;
    const char *a = ip_port.c_str();
    static char ip[20] = {0};
    for (unsigned int i = 0; i < strlen(a); i++) {
        if (a[i] == c)
            break;
        ip[i] = a[i];
    }
	return ip;
}

char *get_port_str(string ip_port)
{
	char c = ':';
    static char s[20] = {0};
    strcpy(s, ip_port.c_str());
    char *p = strchr(s, c);
    p++;
	return p;
}

int get_port(string ip_port)
{
	return atoi(get_port_str(ip_port));
}

int get_local_ip(char *nic, char *ip)
{
	int i = 0;
	int sockfd;
	struct ifconf ifc;
	char buf[1024] = {0};
	char ipbuf[20] = {0};
	struct ifreq *ifr;
	ifc.ifc_len = 1024;
	ifc.ifc_buf = buf;
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) <0) {
		printf("socket error, at %d of %s\n", __LINE__, __FILE__);
		return -1;
	}
	ioctl(sockfd, SIOCGIFCONF, &ifc);
	ifr = (struct ifreq*)buf;
	for (i = (ifc.ifc_len/sizeof(struct ifreq)); i > 0; i--) {
		if (strcmp(ifr-> ifr_name, nic) == 0) {
			inet_ntop(AF_INET, &((struct sockaddr_in *)&ifr->ifr_addr) -> sin_addr, ipbuf, 20);
			strcpy(ip, ipbuf);	
		} else {
			ifr = ifr + 1;
		}
	}
	return 0;
}

int split_str(char *source, char *search, char result[][32])
{
    char *token;
    token = strtok(source, search);
	if (NULL !=token) {
		strcpy(result[0], token);	
	}
    int i=1;
    while (NULL != token) {
        token = strtok(NULL, search);
        if (NULL == token)
            break;
        strcpy(result[i], token);
        i++;
    }
    return i;
}
