#include "common.h"
int main()
{
	char a[] ="/data/t/bc/d/abc.txt";
	printf("%s\n", a);
	char name[124] = {0};
	get_file_name(a, name);
	printf("%s\n", name);
	int i = get_file_path(a,name);
	printf("%d,%s\n", i, a);
	return 0;
}
