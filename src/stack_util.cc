/**
 * some common structure and function used in client and server.
 **/
#include <sys/types.h>
#include <tp.h>
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
#include "stack_util.h"
#include <iomanip>

using namespace std;

/**
 * send buf content limited by t_len to i_sockfd. 
 **/
int snd_buf(UDTSOCKET i_sockfd, char* buf, size_t t_len)
{ 
	int i_this_snd;
	unsigned int i_snd = 0;
	if (t_len == 0)
		return 0;
	while (i_snd < t_len) {
		i_this_snd = UDT::send(i_sockfd, buf, t_len - i_snd, 0);
		if (i_this_snd == UDT::ERROR)
			return i_snd;
		i_snd += i_this_snd;
		buf += i_this_snd;
	}
	return t_len;
} 

/**
 * receive stream from i_sockfd to buf limited by t_len
 */
int rcv_buf(UDTSOCKET i_sockfd, char* buf, size_t t_len)
{
	int i_this_rd;
	unsigned int i_rd = 0;
	if (t_len == 0)
		return 0;
	while (i_rd < t_len) {
		i_this_rd = UDT::recv(i_sockfd, buf, t_len - i_rd, 0);
		if (i_this_rd == UDT::ERROR)
			return i_rd;
		i_rd += i_this_rd;
		buf += i_this_rd;
	}
	return t_len;
}

/**
 * save file content from stream represented by sockfd
 * to file name file_name.
**/
int save_f(const char path[], const int size, UDTSOCKET sockfd)
{
	FILE* fp;
	if ((fp = fopen(path, "a")) == NULL) {
		cout << "cannot open file: " << path << endl;
		return -1;
	}
	int rd_l;
	char *buf = new char[BUF_SIZE];
	int _1MB = 1024 * 1024;
	long sz_mb = size/_1MB;
	int sum_l = 0;
	while(sum_l < size) {
		rd_l = UDT::recv(sockfd, buf, sizeof(buf), 0);
		if (rd_l == UDT::ERROR) {
			cout << "recv err:" << UDT::getlasterror().getErrorMessage() << endl;
			break;
		}
		sum_l += rd_l;
		if (rd_l > 0)
			fwrite(buf, sizeof(char), rd_l, fp);
		if (size > 0)
			cout << "recved " << fixed << setprecision(1)
				 << (float)sum_l/size * 100 << "%" 
				 << "(" << sum_l/_1MB << "MB/"<< sz_mb << "MB)" 
				 << endl;
	}
	fseek(fp, 0, SEEK_END);
	long pos = ftell(fp);
	cout << "t_f_size=" << pos << "; t_f=" << path << endl;
	rewind(fp);
	fclose(fp);
	return 0;
}

/**
 * send file stream to sockfd
 */
int snd_f(const char path[], UDTSOCKET sockfd)
{
	FILE* fp;
	if ((fp = fopen(path,"rb")) == NULL) {
		cout << "cannot open file: " << path << endl;
		return -1;
	}
	fseek(fp, 0, SEEK_END);
	long size = ftell(fp);
	cout << "s_f_size=" << size << "; s_f=" << path << endl;
	rewind(fp);
	int l = 0;
	int sum_l = 0;
	char buf[BUF_SIZE] = {0};
	int _1MB = 1024 * 1024;
	long sz_mb = size/_1MB;
	while (!feof(fp)) {
		l = fread(buf, sizeof(char), sizeof(buf), fp);
		sum_l += l;
		int w_l = UDT::send(sockfd, buf, l, 0);
		if (w_l == UDT::ERROR) {
			cout << "send file failed " << path << ", error:" 
				 << UDT::getlasterror().getErrorMessage() << endl;
			close(sockfd);
			return -1;
		}
		cout << "sent " << fixed << setprecision(1) 
			 << (float)sum_l/size * 100 << "%" 
			 << "(" << sum_l/_1MB << "MB/" << sz_mb << "MB)"
			 << endl;
	}
	cout << "upload size " << sum_l << endl;
	fclose(fp);
	return 0;

}

