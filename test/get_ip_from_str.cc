#include <iostream>
#include <string.h>
#include <stdlib.h>

using namespace std;

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
	cout << "a=" << ip_port << endl;
	char c = ':';
    static char s[20] = {0};
    strcpy(s, ip_port.c_str());
    char *p = strchr(s, c);
    p++;
	cout << "b=" << p << endl;
	return p;
}

int get_port(string ip_port)
{
	return atoi(get_port_str(ip_port));
}


int main()
{
	char ip[20] = "127.0.0.1:9002";
	char *port = get_port_str(ip);
	cout << port << endl;
}
