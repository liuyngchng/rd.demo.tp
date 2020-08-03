#ifndef _STACK_UTIL_H_
#define _STACK_UTIL_H_
#include "const.h"
#include <tp.h>
using namespace std;


/**
 * send buf content limited by t_len to i_sockfd. 
 **/
int snd_buf(UDTSOCKET i_sockfd, char* buf, size_t t_len);

/**
 * receive stream from i_sockfd to buf limited by t_len
 */
int rcv_buf(UDTSOCKET i_sockfd, char* buf, size_t t_len);

/**
 * save file content from stream represented by sockfd with stream length as size
 * to file name file_name.
**/
int save_f(const char path[], const int size, UDTSOCKET sockfd);

/**
 * send file stream to sockfd
 */
int snd_f(const char path[], UDTSOCKET sockfd);

#endif
