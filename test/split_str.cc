#include <string.h>
#include <stdio.h>
int split_str(char *source, char *search, char result[][32])
{
	char *token;
	token = strtok(source, search);
	printf("%s\n", token);
	int i=0;
	while (NULL != token) {
		token = strtok(NULL, search);
		if (NULL == token)
			break;
		strcpy(result[i], token);
		i++;
	}
	return i;
}

int main()
{
	char result[5][32] = {{0}};
	char line[] = "LINE TO BE SEPARATED";
	char *search = " ";
	int c = split_str(line, search, result);
	for (int i =0; i < c; i ++){
		printf("%s\n", result[i]);
	} 
}
