#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;
int main()
{
	char conf_file[12] = "peer.config";
	ifstream in(conf_file);
	string line;
	if (!in) {
		cout << "error" << endl;
	} else {
		cout << "OK" << endl;;
	}
	while (getline(in, line)) {
		char c = ':';
		char s[20];
		strcpy(s, line.c_str());
		char *p = strchr(s, c);
		p++;
		cout << "peer.config info=" << line << ", c=" << p << endl;
		const char *a = line.c_str();
		char b[20] = {0};
		for (int i = 0; i < strlen(a); i++) {
			if (a[i] == c)
				break;
			else
				b[i] = a[i];
		}
		cout << b << endl;
	}

}
