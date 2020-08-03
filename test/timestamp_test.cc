#include "timestamp.h"
#include <iostream>
using namespace std;
int main()
{
	//cout << "" << endl;
	char time[20] = {0};
	get_time(time);
	cout << time << endl;
	char ft[32] = {0};
	get_format_time(ft);
	cout << ft << endl;
}
