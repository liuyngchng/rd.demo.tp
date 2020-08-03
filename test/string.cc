#include <string.h>
#include <iostream>
#include <stdlib.h> 
#include <stdio.h>

using namespace std;

void change_str( char *s)
{
	string a = s;
	cout << "a=" << s << endl;
	string b = a + " changed";
	cout << "b=" << b << endl;
}

int main()
{
	// convert string to char *
	string s1 = "abcdefg";
	char *data;
	int len = s1.length();
	data = (char *)malloc((len+1)*sizeof(char));
	s1.copy(data, len, 0);
	cout << data << endl;

	// convert char * to string
	string s;
	char *p ="hello who are you?";
	change_str(p);
	s = p;
	string s2 = s + " where are you?";
	cout << s2 << endl;
//	printf("%s", s);
}
