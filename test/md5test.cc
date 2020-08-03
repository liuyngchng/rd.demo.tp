#include "../src/md5.h"
//#include "trans.h"
#include <fstream>
#include <iostream>

using namespace std;

/* Prints a message digest in hexadecimal.
 */
static void md5_print (unsigned char digest[16])
{
	for (int i = 0; i < 16; i++)
		printf("%02x", digest[i]);
	printf("\n");
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


int main(int argc, char* argv[])
{
	if(argc < 2) {
		cout << "pls input file name" << endl;
	}
	md5_state_t ms;
	md5_init(&ms);
	FILE *file;
	char *filename = argv[1]; //[] = "../server.cc";
	if ((file = fopen (filename, "rb")) == NULL) {
		cout << filename << "can't be opened" << endl;
		return -1;
	}
	md5_byte_t buffer[1024*1024] = {0}, digest[16] = {0};
	int len = 0;
	while ((len = fread(buffer, 1, 1024*1024, file)))
		md5_append(&ms, buffer, len);
	md5_finish(&ms, digest);   	
	//md5_print(digest);
	char dest[33] = {0};
	byte_to_hexstr(digest, dest, sizeof(digest));
	//cout << sizeof(dest) << endl;
	//printf("%s\n", dest);
	cout << dest << endl;	
	return 0;
}
