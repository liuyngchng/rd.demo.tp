/**
 * a file server, user need to input command like
 * get test.txt or put test.txt
 */
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <string>
#include <fstream>
#include <iostream>
#include "tp.h"
#include "common.h"
#include "stack_util.h"
#include "log4c.h"
#include "timestamp.h"
#include "db.h"
#include "ping.h"
#include "scheduler.h"
#include "server.h"

using namespace std;

void get_file_name(const char path[], char name[]);

//perf monitor
static void* monitor(void* s);

static log4c_category_t* mycat = NULL;

static int _PORT_;

static bool ping_flag;					// 0: no ping , 1: ping peer

static char *peer_ip;

static bool open_data_flow = false;

static double mbpsSendRate = 0.0L;

static double mbpsBandwidth;

static double msRTT;

static double pktSntLossRate;

static void log_init()
{
	log4c_init();
	mycat = log4c_category_get("tp.srv");
}


int init_srv(UDTSOCKET *psockfd)
{
	if (((*psockfd) = UDT::socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		log4c_category_log(mycat, LOG4C_PRIORITY_ERROR,
			"socket error at %d in %s ",
			__LINE__, __FILE__);
		return -1;
	}
	log4c_category_log(mycat, LOG4C_PRIORITY_INFO,
		"socket ok at %d in %s ",
		__LINE__, __FILE__);
	struct sockaddr_in my_addr;
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(_PORT_);
	my_addr.sin_addr.s_addr = INADDR_ANY;
	bzero(&(my_addr.sin_zero), sizeof(my_addr.sin_zero));
	if ((UDT::bind(*psockfd, (struct sockaddr*)&my_addr, 
			sizeof(struct sockaddr))) == UDT::ERROR) {
		log4c_category_log(mycat, LOG4C_PRIORITY_ERROR,
			"bind error, %s, at %d in %s ",
			UDT::getlasterror().getErrorMessage(),
			__LINE__, __FILE__);
		return -2;
	}
	log4c_category_log(mycat, LOG4C_PRIORITY_INFO,
		"bind OK, at %d in %s ",
		__LINE__, __FILE__);

	setsockopt(*psockfd, SOL_SOCKET, SO_REUSEADDR, 
		(char*)&my_addr, sizeof(my_addr)); 

	if (UDT::listen(*psockfd, _BACL_LOG_) == -1) {
		log4c_category_log(mycat, LOG4C_PRIORITY_ERROR,
			"listen error, at %d in %s ",
			__LINE__, __FILE__);
		return -3;
	}
	log4c_category_log(mycat, LOG4C_PRIORITY_INFO,
		"listen %d, at %d in %s ",
		_PORT_, __LINE__, __FILE__);
	return 0;	
}

/**
 * receive file stream from fd(peer).
 */
int rcv_f(UDTSOCKET fd)
{
	char file_name[F_NAME_SIZE] = {0};					//file_name buffer 
	char file_size[FILE_SIZE] = {0};
	char file_md5[33] = {0};							//file md5 buffer
	rcv_buf(fd, file_name, F_NAME_SIZE);				//receive file name 
	rcv_buf(fd, file_size, FILE_SIZE);					//receive file size
	log4c_category_log(mycat, LOG4C_PRIORITY_INFO,
		"rcvd file_size=%s, at %d in %s ",
		file_size,__LINE__, __FILE__);
	rcv_buf(fd, file_md5, 32);						//receive file md5
	log4c_category_log(mycat, LOG4C_PRIORITY_INFO,
		"rcvd file_md5=%s, at %d in %s ",
		file_md5,__LINE__, __FILE__);
	char name[F_NAME_SIZE] = {0};
	get_file_name(file_name, name);
	struct file_rcd rst;
	bool is_exist;
	try {
		is_exist = get_file_by_md5_name(file_md5, name,  rst);			// check whether file exist by md5 and name.
		if (!is_exist) {
			is_exist = get_file_by_md5(file_md5,  rst);								// check whether file exist by md5.
		}
	} catch (int e) {
		log4c_category_log(mycat, LOG4C_PRIORITY_ERROR,
			"err=%d, at %d in %s ", e,__LINE__, __FILE__);
		return e;
	}
	if (is_exist && (access(rst.path, 0)) != 0) {										// check file whether exist in file system.
		is_exist = false;
		delete_file_by_md5(file_md5);
		log4c_category_log(mycat, LOG4C_PRIORITY_DEBUG,
			"file can't be found with db info for md5=%s,path=%s, delete file info in db, at %d in %s ", 
			rst.md5, rst.path, __LINE__, __FILE__);
	}
	if (is_exist) {
		log4c_category_log(mycat, LOG4C_PRIORITY_INFO,
			"file %s exist, at %d in %s ", rst.path, __LINE__, __FILE__);
		if (strcmp(rst.name, name) == 0) {
			log4c_category_log(mycat, LOG4C_PRIORITY_DEBUG,
				"dup file name %s found in db, at %d in %s ", rst.name ,__LINE__, __FILE__);
		} else {
			log4c_category_log(mycat, LOG4C_PRIORITY_INFO,
				"save new file name %s in db, at %d in %s ",name ,__LINE__, __FILE__);
			strcpy(rst.name, name);
			save_file_info(rst);
		}
		char dup_sig[] = "dup";								//duplicate file.
		snd_buf(fd, dup_sig, strlen(dup_sig));
		log4c_category_log(mycat, LOG4C_PRIORITY_INFO,
			"snd sig %s, at %d in %s ",dup_sig ,__LINE__, __FILE__);
		char fin_sig[4] = {0};								// finish signal
		rcv_buf(fd, fin_sig, 3);
		log4c_category_log(mycat, LOG4C_PRIORITY_INFO,
			"rcv sig %s, at %d in %s ",fin_sig ,__LINE__, __FILE__);
		UDT::close(fd);
		return 0;
	}
	string path = _PATH_;
	char t[17] = {0};
	get_time(t);
	string timestamp = t;
	path += timestamp + "_" + name;
	const char *p = path.c_str();
	log4c_category_log(mycat, LOG4C_PRIORITY_INFO,
		"new file, at %d in %s ",__LINE__, __FILE__);
	struct file_rcd rs;
	strcpy(rs.name, name);
	strcpy(rs.md5, file_md5);
	strcpy(rs.path, p);
	int i_f_size = atoi(file_size);
	rs.size = i_f_size;
	save_file_info(rs);
	log4c_category_log(mycat, LOG4C_PRIORITY_INFO,
		"file info saved in db, at %d in %s ",__LINE__, __FILE__);
	char new_sig[] = "new";
	snd_buf(fd, new_sig, strlen(new_sig));
	log4c_category_log(mycat, LOG4C_PRIORITY_INFO,
		"snd sig %s, at %d in %s ", new_sig ,__LINE__, __FILE__);
	log4c_category_log(mycat, LOG4C_PRIORITY_INFO,
		"rcving file %s, save to path %s, size=%s, at %d in %s ",
		file_name, _PATH_, file_size, __LINE__, __FILE__);
	//receive file
	fstream ofs(p, ios::out | ios::binary | ios::trunc);
	int64_t recvsize;
	int64_t offset = 0;
	open_data_flow = true;
	if (UDT::ERROR == (recvsize = UDT::recvfile(fd, ofs, offset, i_f_size))) {
		log4c_category_log(mycat, LOG4C_PRIORITY_ERROR,
			"rcv err, msg=%s, at %d in %s ",
		UDT::getlasterror().getErrorMessage(), __LINE__, __FILE__);
		return -1;
	}
	//if (save_f(p, i_f_size, acceptfd) == 0)			//receive stream and save to file
	log4c_category_log(mycat, LOG4C_PRIORITY_INFO,
		"saved file %s, at %d in %s ",
		p, __LINE__, __FILE__);
	ofs.close();
	char fin_sig[] = "fin";								// finish signal
	snd_buf(fd, fin_sig, strlen(fin_sig));
	UDT::close(fd);
	return 0;
}

/*
 * send file stream to fd(peer).
 */
int snd_f(UDTSOCKET fd)
{
	char file_name[F_NAME_SIZE] = {0};					  //file_name from client 
	char file_size[FILE_SIZE] = {0};
	char file_md5[33] = {0};							//file md5 from client
	rcv_buf(fd, file_name, F_NAME_SIZE);		//receive file name
	string path = _PATH_;
	path += file_name;
	int i_f_size = get_file_size(path.c_str());
	itoa(i_f_size, file_size);
	snd_buf(fd, file_size, FILE_SIZE);		//send file size
	log4c_category_log(mycat, LOG4C_PRIORITY_INFO,
		"snd file_size=%s, at %d in %s ",
		file_size, __LINE__, __FILE__);
	snd_buf(fd, file_md5, 32);				//send file md5
	log4c_category_log(mycat, LOG4C_PRIORITY_INFO,
		"snding %s, at %d in %s ",
		file_name, __LINE__, __FILE__);
	// send the file
	fstream ifs(path.c_str(), ios::in | ios::binary);
	ifs.seekg(0, ios::end);
	int64_t size = ifs.tellg();
	ifs.seekg(0, ios::beg);
	int64_t offset = 0;
	open_data_flow = true;
	if (UDT::ERROR == UDT::sendfile(fd, ifs, offset, size)) {
		log4c_category_log(mycat, LOG4C_PRIORITY_ERROR,
			"snd err, msg=%s, at %d in %s ",
			UDT::getlasterror().getErrorMessage(), __LINE__, __FILE__);
		return -1;
	}
	//if (snd_f(path.c_str(), acceptfd) ==0)			// write file content to stream
	log4c_category_log(mycat, LOG4C_PRIORITY_INFO,
		"sent finish,%s/%s, at %d in %s ",
		_PATH_, file_name, __LINE__, __FILE__);
	char fin_sig[4] = {0};
	rcv_buf(fd, fin_sig, 3);
	log4c_category_log(mycat, LOG4C_PRIORITY_INFO,
		"rcvd peer signal %s, at %d in %s ",
		fin_sig, __LINE__, __FILE__);
	ifs.close();
	UDT::close(fd);
	return 0;
}
/*
 * send a pong sig to fd(peer) as response to ping.
 */
int pong(UDTSOCKET fd)
{
	char sig[4] = "pon";
	snd_buf(fd, sig, 3);		//send sig pong 
	log4c_category_log(mycat, LOG4C_PRIORITY_DEBUG,
		"snd sig=%s, at %d in %s ",
		sig, __LINE__, __FILE__);
	UDT::close(fd);
	return 0;
}

void* run(void* sockfd)
{
	UDTSOCKET fd = *(UDTSOCKET*)sockfd;	
	char cmd[CMD_SIZE] = {0};							//save cmd：get || put 
	rcv_buf(fd, cmd, CMD_SIZE);					//receive cmd
	log4c_category_log(mycat, LOG4C_PRIORITY_INFO,
		"rcvd cmd=%s, at %d in %s ",
		cmd, __LINE__, __FILE__);
	if (strcmp(cmd, "put") == 0) {
		rcv_f(fd);
	} else if (strcmp(cmd, "get") == 0) {
		snd_f(fd);	
	} else if (strcmp(cmd, "pin") == 0) {
		pong(fd);
	} else {
		log4c_category_log(mycat, LOG4C_PRIORITY_ERROR,
			"illegal op, at %d in %s ",
			__LINE__, __FILE__);
	}
	UDT::close(fd);
	return NULL;
}

void do_ping(void *data)
{
	char *p_ip_port = (char *)data;
    struct timeval tv;
    tv.tv_sec = 5;
    tv.tv_usec = 0;
	char *ip = get_ip(p_ip_port);
	int port =atoi(get_port_str(p_ip_port));
	int ret = ping(ip, port);
	char my_ip[20] = {0};
	char nic[10] = _NIC_;
	get_local_ip(nic, my_ip);
	int c = get_peer_info(my_ip, ip);
	if (c>0) {
		update_peer_info(my_ip, ip, ret == 0 ? 1 : 0);
	} else {
		insert_peer_info(my_ip, ip, ret == 0 ? 1 : 0);
	}
	log4c_category_log(mycat, LOG4C_PRIORITY_DEBUG,
		"ping(%s, %d) ret=%d, at %d in %s ",
		ip, port, ret, __LINE__, __FILE__);
    schedule(tv, do_ping, data);
}

int schedule_ping(const char *ip_port)
{
    struct timeval tv;
    struct timeval timeout;
    init_scheduler ();
    tv.tv_sec = _PING_INTERVAL_;
    tv.tv_usec = 0;
	string ip_s = get_ip(ip_port);
	string port_s = get_port_str(ip_port);
	string ip_port_str = ip_s + ":" + port_s;
	const char *p_ip_port = ip_port_str.c_str();
    schedule(tv, do_ping, const_cast<char*>(p_ip_port));
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;
    while (1) {
        select(0, NULL, NULL, NULL, &timeout);
    }
    return 0;
}

/**
 * ping peer when online, offline, lost
 */
void* ping_peer(void* param)
{
	char conf_file[20] = "config/peer.config";
	ifstream in(conf_file);
	string line;
	if (!in) {
		log4c_category_log(mycat, LOG4C_PRIORITY_ERROR,
			"error, can't open file %s,  at %d in %s",
			conf_file, __LINE__, __FILE__);
		return NULL;
	}
	while (getline(in, line)) {
		log4c_category_log(mycat, LOG4C_PRIORITY_INFO,
			"peer.config info=%s, at %d in %s",
			line.c_str(), __LINE__, __FILE__);
		schedule_ping(line.c_str());			
	}
	return NULL;
}

int main(int argc, char** argv){
	if (argc < 3) {
		cerr <<"pls input listening port and ping flag" << endl;
		return 1;
	}
	_PORT_ = atoi(argv[1]);
	ping_flag = atoi(argv[2]);
	UDTSOCKET sockfd;
	log_init();
	int i = init_srv(&sockfd);
	if (i < 0) {
		log4c_category_log(mycat, LOG4C_PRIORITY_INFO,
			"init error, %d, at %d in %s ",
			i, __LINE__, __FILE__);
		return i;
	}
	if(ping_flag) {
		pthread_t t;
		pthread_create(&t, NULL, &ping_peer, NULL);
		pthread_detach(t);
	}
	struct sockaddr_in csock;
	int sin_size;
	while (1) {
		UDTSOCKET acceptfd = UDT::accept(sockfd, (struct sockaddr*)&csock, &sin_size);
		if (acceptfd < 0) {
			close(sockfd);
			log4c_category_log(mycat, LOG4C_PRIORITY_ERROR,
				"accept failed, at %d in %s ",
				__LINE__, __FILE__);
			return -4;
		}
		log4c_category_log(mycat, LOG4C_PRIORITY_INFO,
			"conn from %s:%d, at %d in %s ",
			inet_ntoa(csock.sin_addr), ntohs(csock.sin_port), 
			__LINE__, __FILE__);
		peer_ip = inet_ntoa(csock.sin_addr);
		pthread_t t;
		pthread_create(&t, NULL, &run, &acceptfd);
		pthread_detach(t);
		
		pthread_t t1;
    	pthread_create(&t1, NULL, monitor, &acceptfd);
	}
	UDT::close(sockfd);
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

