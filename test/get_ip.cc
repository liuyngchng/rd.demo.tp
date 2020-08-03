#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <net/if.h>
#include <sys/ioctl.h>

#define _NIC_ "enp2s0"

/**
 * get ip addr by network interface card name.
 */
inline void get_ip(char *nic, char *ip)
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
		printf("socket error\n");
		return;
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
}

int main()
{
	char nic[10] = _NIC_;
	char ip[20] = {0};
	get_ip(nic, ip);
	printf("%s\n", ip);

}
