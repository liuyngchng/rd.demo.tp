#ifndef _COMMON_H_
#define _COMMON_H_
#include "const.h"
#include <string>
using namespace std;

/**
 * get filename from file full path.
**/
void get_file_name(const char path[], char name[]);

/**
 * get file path from file full path.
**/
int get_file_path(char path[], char name[]);

/**
 * get file size in byte from file full path.
 */
int get_file_size(const char path[]);

/**
 * convert a integer to a char array.
 */
void itoa (int n, char s[]);

/**
 * get ip string from a ip port string like IP:port
 */
char *get_ip(std::string ip_port);

/**
 * get port int value from a ip port string like IP:port
 */
int get_port(std::string ip_port);

/**
 * get port string value from a ip port string like IP:port
 */
char *get_port_str(std::string ip_port);

/**
 * get local ip addr from network interface card.
 */
int get_local_ip(char *nic, char *ip);

/**
 * split a string in 'source' by separator 'search', save in 'result'.
 */
int split_str(char *source, char *search, char result[][32]);

#endif
