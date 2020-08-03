#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include "log4c.h"
#include "client.h"

using namespace std;

int send_file(char* file);

int get_file(char* file_name);

static log4c_category_t* mycat = NULL;

static char *_IP_;

static int _PORT_;

static void log_init()
{
	log4c_init();
	mycat = log4c_category_get("tp.cli");
}

int main(int argc, char** argv){
	if (argc < 3) {
        cerr <<"pls input server IP and port" << endl;
        return 1;
    }
    _IP_ = argv[1];
    _PORT_ = atoi(argv[2]);
	cout << "server:" << _IP_ << ":" << _PORT_ << endl; 
	log_init();
	while(1) {
		char cmd[CMD_SIZE] = {0}, file[FILE_SIZE] = {0};
		cout << "input your cmd:" << endl;
		cin >> cmd >> file;
		log4c_category_log(mycat, LOG4C_PRIORITY_INFO,
      		"cmd=%s, file=%s at %d in %s ",
      		cmd, file, __LINE__, __FILE__); 
		if (strcmp(cmd, "put") == 0) {
			send_file(file, _IP_, _PORT_);
		} else if (strcmp(cmd, "get") == 0) {					//download a file from server	
			get_file(file, _IP_, _PORT_);
		} else {
			log4c_category_log(mycat, LOG4C_PRIORITY_ERROR,
      			"illegal op, at %d in %s ",
      			__LINE__, __FILE__); 
		}
	}
	return 0;
}
