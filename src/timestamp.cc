#include <sys/time.h>
#include <string>
#include <stdio.h>

static void get_time(int *iv)
{
    struct timeval tv;
    struct timezone tz;
    gettimeofday(&tv, &tz);
    struct tm *t = localtime(&tv.tv_sec);
	int year = 1900 + t->tm_year;
	iv[0] = year;
	iv[1] = t->tm_mon +1;
	iv[2] = t->tm_mday;
	iv[3] = t->tm_hour;
	iv[4] = t->tm_min;
	iv[5] = t->tm_sec;
	iv[6] = (int)(tv.tv_usec/1000);
}

void get_time( char *time)
{
	int iv[7] = {0};
	get_time(iv);
	sprintf(time, "%d%02d%02d%02d%02d%02d%03d", iv[0], iv[1], iv[2], iv[3], iv[4], iv[5], iv[6]);
}

void get_format_time(char *time)
{
	int iv[7] = {0};
	get_time(iv);
	sprintf(time, "%04d-%02d-%02d %02d:%02d:%02d.%03d", iv[0], iv[1], iv[2], iv[3], iv[4], iv[5], iv[6]);
}

