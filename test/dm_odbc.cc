//#include <windows.h>
#include <stdio.h>
#include <sql.h>
#include <sqltypes.h>
#include <sqlext.h>
/* 检测返回代码是否为成功标志,当为成功标志返回 TRUE,否则返回 FALSE */
#define RC_SUCCESSFUL(rc) ((rc) == SQL_SUCCESS || (rc) == SQL_SUCCESS_WITH_INFO)
/* 检测返回代码是否为失败标志,当为失败标志返回 TRUE,否则返回 FALSE */
#define RC_NOTSUCCESSFUL(rc) (!(RC_SUCCESSFUL(rc)))
HENV 		henv; 		/* 环境句柄 */
HDBC 		hdbc; 		/* 连接句柄 */
HSTMT		hsmt;		/* 语句句柄 */
SQLRETURN	sret; 		/* 返回代码 */
char szpersonid[11];	/*人员编号*/
long cbpersonid=0;
char szname[51];		/*人员姓名*/
long cbname=0;
char szphone[26];		/*联系电话*/
long cbphone=0;
int main(void)
{
	/* 申请一个环境句柄 */
	SQLAllocHandle(SQL_HANDLE_ENV, NULL, &henv);
	/* 设置环境句柄的 ODBC 版本 */
	SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
	/* 申请一个连接句柄*/
	SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);
	SQLConnect(hdbc, (SQLCHAR *)"DM", SQL_NTS, (SQLCHAR *)"SYSDBA", SQL_NTS, (SQLCHAR*)"SYSDBA", SQL_NTS);
	/* 申请一个语句句柄*/
	SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hsmt);
	/* 立即执行查询人员信息表的语句*/
	SQLExecDirect(hsmt, (SQLCHAR *)"SELECT * FROM sysdba.t;", SQL_NTS);
	/* 绑定数据缓冲区*/
	SQLBindCol(hsmt, 1, SQL_C_CHAR, szpersonid, sizeof(szpersonid), &cbpersonid);
	SQLBindCol(hsmt, 2, SQL_C_CHAR, szname, sizeof(szname), &cbname);
	SQLBindCol(hsmt, 3, SQL_C_CHAR, szphone, sizeof(szphone), &cbphone);
	/* 取得数据并且打印数据 */
	printf("人员编号 人员姓名 联系电话\n");
	for (;;) {
		sret = SQLFetchScroll(hsmt, SQL_FETCH_NEXT, 0);
		if (sret == SQL_NO_DATA_FOUND)
			break;
		printf("%s %s %s\n", szpersonid, szname, szphone);
	}
	/* 释放语句句柄 */
	SQLFreeHandle(SQL_HANDLE_STMT, hsmt);
	/* 断开与数据源之间的连接*/
	SQLDisconnect(hdbc);
	/* 释放连接句柄*/
	SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
	/* 释放环境句柄*/
	SQLFreeHandle(SQL_HANDLE_ENV, henv);
	return 0;
}
