/**
 * agent used by client to send and receive file.
 */
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
#include "stack_util.h"
#include "md5.h"
#include "log4c.h"
#include "db.h"

#define _PATH_	"/data/cli/"			//client download defalt path

using namespace std;

// get file name from full path.
void get_file_name(const char path[], char file_name[]);

// write file stream named file(file full path) to sockfd 
int snd_f(const char path[], UDTSOCKET sockfd); 

// read file stream from sockfd sockfd and write to file named file
int save_f(const char path[], const int size, UDTSOCKET sockfd); 

int get_file_md5(const char *path, char *md5);

void byte_to_hexstr( const unsigned char* source, char* dest, int source_len);

//perf monitor
static void* monitor(void* s);

// init socket.
UDTSOCKET init(char *ip, int& port);

static char *peer_ip;

static log4c_category_t* mycat = NULL;

static bool open_data_flow = false;

static double mbpsSendRate = 0.0L;

static double mbpsBandwidth;

static double msRTT;

static double pktSntLossRate;

static void log_init()
{
	log4c_init();
	mycat = log4c_category_get("tp.cli.agt");
}
/**
 * send file to peer.
 */
int send_file(char *path, char *ip, int& port)
{
	log_init();
	UDTSOCKET sockfd = init(ip, port);	
	char cmd[CMD_SIZE] = "put", file_name[F_NAME_SIZE] = {0}, file_size[FILE_SIZE] = {0};
	log4c_category_log(mycat, LOG4C_PRIORITY_INFO,
        "send file=%s, at %d in %s ",
        path, __LINE__, __FILE__);
	snd_buf(sockfd, cmd, CMD_SIZE);					//send cmd to peer
	int i_f_size = 0;
	get_file_name(path, file_name);
	snd_buf(sockfd, file_name, F_NAME_SIZE);		//send file name to peer
	log4c_category_log(mycat, LOG4C_PRIORITY_INFO,
        "snd f_name=%s, at %d in %s ",file_name, __LINE__, __FILE__);
	i_f_size = get_file_size(path);
	if (i_f_size <=0) {
		log4c_category_log(mycat, LOG4C_PRIORITY_ERROR,
    	    "file_size=%s, file size error, at %d in %s ",
        	file_size, __LINE__, __FILE__);
		return -1;
	}
	itoa(i_f_size, file_size);
	snd_buf(sockfd, file_size, FILE_SIZE);			//send file size to peer
	log4c_category_log(mycat, LOG4C_PRIORITY_INFO,
        "snd f_size=%s, at %d in %s ",file_size, __LINE__, __FILE__);
	char md5[33] = {0};
	log4c_category_log(mycat, LOG4C_PRIORITY_INFO,
        "start caculate md5 of %s, at %d in %s ",
        path, __LINE__, __FILE__);
	get_file_md5(path, md5);
	snd_buf(sockfd, md5, 32);						//send file md5
	log4c_category_log(mycat, LOG4C_PRIORITY_INFO,
        "snd f_md5=%s, at %d in %s ",md5, __LINE__, __FILE__);
    char sig[4] = {0};
    rcv_buf(sockfd, sig, 3);
	log4c_category_log(mycat, LOG4C_PRIORITY_INFO,
        "rcvd sig=%s, at %d in %s ",
        sig, __LINE__, __FILE__);
    if (strcmp(sig, "dup") == 0) {
        char fin_sig[] = "fin";
        snd_buf(sockfd, fin_sig, 3);
	    log4c_category_log(mycat, LOG4C_PRIORITY_INFO,
            "snd sig=%s, at %d in %s ",
            fin_sig, __LINE__, __FILE__);
       UDT::close(sockfd);
       return 0;
    } else if(strcmp(sig, "new") == 0) {
		log4c_category_log(mycat, LOG4C_PRIORITY_INFO,
        	"snding %s, at %d in %s ",
        	path, __LINE__, __FILE__);
		// send the file
		fstream ifs(path, ios::in | ios::binary);
   		ifs.seekg(0, ios::end);
   		int64_t size = ifs.tellg();
   		ifs.seekg(0, ios::beg);
		int64_t offset = 0, send_size = 0;
		open_data_flow = true;
		if (UDT::ERROR == (send_size = UDT::sendfile(sockfd, ifs, offset, size))) {
			log4c_category_log(mycat, LOG4C_PRIORITY_ERROR,
    		"snd err,msg= %s, at %d in %s ",
			UDT::getlasterror().getErrorMessage(), __LINE__, __FILE__);
			return -1;
   		}
		open_data_flow = false;
		log4c_category_log(mycat, LOG4C_PRIORITY_INFO,
    		"snd finish, snd size = %ld,  at %d in %s ",
    		send_size, __LINE__, __FILE__);
		char fin_sig[4] = {0};
		rcv_buf(sockfd, fin_sig, 3);
		log4c_category_log(mycat, LOG4C_PRIORITY_INFO,
    		"rcvd peer signal, %s,  at %d in %s ",
    		fin_sig, __LINE__, __FILE__);
		ifs.close();
	}
	UDT::close(sockfd);
	return 0;
}

/**
 * get file from peer.
 */
int get_file(char* file_name, char *ip, int& port)
{
	log_init();
	UDTSOCKET sockfd = init(ip, port);	
	char cmd[CMD_SIZE] = "get", file_size[FILE_SIZE] = {0}, file_md5[33] = {0};
	log4c_category_log(mycat, LOG4C_PRIORITY_INFO,
       	"get file=%s, at %d in %s ",
       	file_name, __LINE__, __FILE__);
	snd_buf(sockfd, cmd, CMD_SIZE);				// send cmd to server
	int i_f_size = 0;
	snd_buf(sockfd, file_name, F_NAME_SIZE);		// send file name to server
	string path = _PATH_;
	path += file_name;
	const char *p = path.c_str();
	//cout << "downloading " << p << endl;
	rcv_buf(sockfd, file_size, FILE_SIZE);		// receive file size
	log4c_category_log(mycat, LOG4C_PRIORITY_INFO,
       	"rcvd file_size=%s, at %d in %s ",
       	file_size, __LINE__, __FILE__);
	rcv_buf(sockfd, file_md5, 32);				// receive file md5
	log4c_category_log(mycat, LOG4C_PRIORITY_INFO,
       	"rcvd file_md5=%s, at %d in %s ",
       	file_md5, __LINE__, __FILE__);
	i_f_size = atoi(file_size);
	
	open_data_flow = true;
	//receive file
	fstream ofs(p, ios::out | ios::binary | ios::trunc);
	int64_t rcv_size;
	int64_t offset = 0;
	log4c_category_log(mycat, LOG4C_PRIORITY_INFO,
       	"rcving %s,size=%d at %d in %s ",
       	file_name, i_f_size, __LINE__, __FILE__);
	if (UDT::ERROR == (rcv_size = UDT::recvfile(sockfd, ofs, offset, i_f_size))){
		log4c_category_log(mycat, LOG4C_PRIORITY_ERROR,
       	"rcv err,msg=%s at %d in %s ",
      	UDT::getlasterror().getErrorMessage(), __LINE__, __FILE__);
      	return -1;
   	}
	open_data_flow = false;
	char fin_sig[] = "fin";
	snd_buf(sockfd, fin_sig, 3);
	log4c_category_log(mycat, LOG4C_PRIORITY_INFO,
    	"get success, rcv_size=%ld, at %d in %s ",
    	rcv_size, __LINE__, __FILE__); 
	close(sockfd);
	return 0;
}

/**
 * init socket connection.
 */
UDTSOCKET init(char *ip, int& port)
{
	log_init();
	peer_ip = ip;
	struct sockaddr_in sock_addr;
	sock_addr.sin_family = AF_INET;
	sock_addr.sin_port = htons(port);
	inet_pton(AF_INET, ip, &sock_addr.sin_addr);
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
	//pthread_t t;
	//pthread_create(&t, NULL, monitor, &sockfd);
//	pthread_detach(t);
	return sockfd;
}

/*
 *convert a unsigned char array to a  hex char array
*/
void byte_to_hexstr( const unsigned char* source, char* dest, int source_len)
{
    short i;
    unsigned char high_byte, low_byte;
    for (i = 0; i < source_len; i++)
    {
        high_byte = source[i] >> 4;
        low_byte = source[i] & 0x0f ;
        high_byte += 0x30;
        if (high_byte > 0x39)               // A ~ F
            dest[i*2] = high_byte + 0x07 + 0x20;
        else
            dest[i*2] = high_byte;          // 0 ~ 9
        low_byte += 0x30;
        if (low_byte > 0x39)
            dest[i*2 + 1] = low_byte + 0x07 + 0x20;
        else
            dest[i*2 + 1] = low_byte;
    }
}


/**
 * get md5 value from a file with file path as 'path'
 */
int get_file_md5(const char *path, char *md5)
{
	log_init();
    md5_state_t ms;
    md5_init(&ms);
    FILE *file;
    if ((file = fopen (path, "rb")) == NULL) {
        cout << path << "can't be opened" << endl;
		log4c_category_log(mycat, LOG4C_PRIORITY_ERROR,
       		"file %s can't be opened, at %d in %s ",
			path, __LINE__, __FILE__);
        return -1;
    }
    md5_byte_t buffer[1024*1024] = {0}, digest[16] = {0};
    int len = 0;
    while ((len = fread(buffer, 1, 1024*1024, file)))
        md5_append(&ms, buffer, len);
    md5_finish(&ms, digest);
    byte_to_hexstr(digest, md5, sizeof(digest));
	return 0;
}

static void* monitor(void* s)
{
	UDTSOCKET u = *(UDTSOCKET*)s;
   	UDT::TRACEINFO perf;
   	while (true) {
      	sleep(1);
		if(!open_data_flow)
			continue;
      	if (UDT::ERROR == UDT::perfmon(u, &perf)) {
	  		log4c_category_log(mycat, LOG4C_PRIORITY_DEBUG,
	       		"perfMon error,%s, at %d in %s ",
        		UDT::getlasterror().getErrorMessage(), __LINE__, __FILE__);
         	break;
      	}
	  	log4c_category_log(mycat, LOG4C_PRIORITY_DEBUG,
	       	"sndRate=%lfMbps,bandwidth=%lfMbps, RTT=%lfms," 
		   	"pktSent=%ld,pktSndLoss=%d, at %d in %s",
		   	perf.mbpsSendRate, perf.mbpsBandwidth, perf.msRTT, 
		   	perf.pktSent, perf.pktSndLoss, __LINE__, __FILE__);
		if (perf.mbpsSendRate > mbpsSendRate) 
			mbpsSendRate = perf.mbpsSendRate;
		if (perf.mbpsBandwidth > mbpsBandwidth)
			mbpsBandwidth = perf.mbpsBandwidth;
		if (perf.msRTT > msRTT)
			msRTT = perf.msRTT;
		if (perf.pktSent > 0 && (perf.pktSndLoss *100)/perf.pktSent > pktSntLossRate)
			pktSntLossRate = (perf.pktSndLoss *100)/perf.pktSent;
		char ip[32] = {0};
		char nic[16] = "enp3s0";
		get_local_ip(nic, ip);
		log4c_category_log(mycat, LOG4C_PRIORITY_DEBUG,
           	"from=%s, to=%s, r=%lfMbps,bw=%lfMbps, rtt=%lfms, pktls=%lf%%, at %d in %s",
         	ip, peer_ip, mbpsSendRate, mbpsBandwidth, msRTT, pktSntLossRate, __LINE__,  __FILE__ );
		struct topo_rcd topo;
		topo.source = ip;
		topo.target = peer_ip;
		topo.loss = pktSntLossRate;
		topo.is_connected = 1;
		topo.available_bw = mbpsSendRate;
		topo.capacity_bw = mbpsBandwidth;
		topo.latency = msRTT;
		topo.type= 1;	
		save_topo_info(topo);
   }
   return NULL;
}

