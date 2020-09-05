/**
 * gcc -I/usr/local/mysql/include  -L/usr/local/mysql/lib -lmysqlclient -o mysql mysql.c
 */
#include <stdlib.h>
#include <stdio.h>
#include <mysql.h>
int main() 
{
	MYSQL *conn_ptr;
	MYSQL_RES *res_ptr;  
    MYSQL_ROW sqlrow;  
    MYSQL_FIELD *fd;  
    int res, i, j; 
	conn_ptr = mysql_init(NULL);
	if (!conn_ptr) {
		printf("mysql_init failed\n");
		return EXIT_FAILURE;
	}
	// ip=localhost, username=root, psword=0000, db=test, port=3306
	conn_ptr = mysql_real_connect(conn_ptr, "localhost", "root", "0000", "test", 3306, NULL, 0);
	if (conn_ptr) {
		printf("Connection success\n");
		int res = mysql_query(conn_ptr, "select id,name,address from a");
		if (res) {
			printf("SELECT error:%s\n", mysql_error(conn_ptr));
		} else {
			res_ptr = mysql_store_result(conn_ptr);
			if (res_ptr) {
				printf("%lu Rows\n", (unsigned long)mysql_num_rows(res_ptr));
				j = mysql_num_fields(res_ptr);
				while ((sqlrow = mysql_fetch_row(res_ptr))) {
					for(i = 0; i < j; i++)		   
						printf("%s\t", sqlrow[i]);	
					printf("\n");
				}
				if (mysql_errno(conn_ptr)) {
					fprintf(stderr, "Retrive error:s\n", mysql_error(conn_ptr));				 
				}
			}
			mysql_free_result(res_ptr);
		}
	} else {
		printf("Connection failed\n");
	}
	mysql_close(conn_ptr);
	return EXIT_SUCCESS;
}
