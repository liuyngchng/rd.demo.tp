/**
 * ping used to sniffer network.
 */
#include "ping.h"
#include "stack_util.h"

using namespace std;

UDTSOCKET init(char *path, int port);

static log4c_category_t* mycat = NULL;

static void log_init()
{
	log4c_init();
	mycat = log4c_category_get("tp.peer.ping");
}
/**
 * send file to peer.
 */
int ping(char* path, int port)
{
	log_init();
	UDTSOCKET sockfd = init(path, port);
	if (sockfd < 0 )
		return sockfd;
	char cmd[CMD_SIZE] = "pin";
	log4c_category_log(mycat, LOG4C_PRIORITY_DEBUG,
        "snd sig=%s, at %d in %s ",
        cmd, __LINE__, __FILE__);
	snd_buf(sockfd, cmd, CMD_SIZE);					//send cmd to peer
    char sig[4] = {0};
    rcv_buf(sockfd, sig, 3);
	log4c_category_log(mycat, LOG4C_PRIORITY_DEBUG,
        "rcvd sig=%s, at %d in %s ",
        sig, __LINE__, __FILE__);
	UDT::close(sockfd);
	return 0;
}

/*
 * init socket connection.
 */
UDTSOCKET init(char *path, int port)
{
	log_init();
	struct sockaddr_in sock_addr;
	sock_addr.sin_family = AF_INET;
	sock_addr.sin_port = htons(port);
	inet_pton(AF_INET, path, &sock_addr.sin_addr);
	UDTSOCKET sockfd = UDT::socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		log4c_category_log(mycat, LOG4C_PRIORITY_ERROR,
       		"create socket fail, at %d in %s ",
       		__LINE__, __FILE__);
		return -1;
	}
	if (UDT::ERROR == UDT::connect(sockfd, (struct sockaddr*)&sock_addr, sizeof(sock_addr))) {
		log4c_category_log(mycat, LOG4C_PRIORITY_ERROR,
       		"connect error, %s, at %d in %s ",
			UDT::getlasterror().getErrorMessage(),
       		__LINE__, __FILE__);
		return -1;
	}
	return sockfd;
}

