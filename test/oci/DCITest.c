/******************************/
/* DCI编程实例 */
/******************************/

#ifdef WIN32
#include <windows.h>
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include "DCI.h"

/* 声明句柄 */
OCIEnv		*envhp;		/* 环境句柄 */
OCISvcCtx	*svchp;		/* 服务环境句柄 */
OCIServer	*srvhp;		/* 服务器句柄 */
OCISession	*authp;		/* 会话句柄 */
OCIStmt		*stmthp;	/* 语句句柄 */
OCIDescribe *dschp;		/* 描述句柄 */

OCIError	*errhp;		/* 错误句柄 */
OCIDefine	*defhp[10]; /* 定义句柄 */
OCIBind		*bidhp[10]; /* 绑定句柄 */

sb2			ind[3];		/* 指示符变量 */

/* 绑定select结果集的参数 */
text szpersonid[11];	/* 存储personid列 */
text szsex[2];			/* 存储sex列 */
text szname[51];		/* 存储name列 */
text szemail[51];		/* 存储mail列 */
text szphone[26];		/* 存储phone列 */
text szid[10];			/*	*/
char sql[256];			/* 存储执行的sql语句*/

int main(int argc, char *argv[])
{
	char strServerName[50];	//连接串：192.168.49.36:5236/XXJH
	char strUserName[50];	//用户名
	char strPassword[50];	//密码
	text errbuf[100];
	int retValue = 0;		//返回值

	/* 设置服务器，用户名和密码 */
	strcpy(strServerName,"192.168.49.36:5236/XXJH");
	strcpy(strUserName,"XXJH");
	strcpy(strPassword,"123456789");
	
	/* 初始化OCI应用环境*/
	OCIInitialize(OCI_DEFAULT, NULL, NULL, NULL, NULL);
	/* 初始化环境句柄 */
	OCIEnvInit(&envhp, OCI_DEFAULT,0, 0);
	/* 分配句柄 */
	OCIHandleAlloc(envhp, (dvoid**)&svchp, OCI_HTYPE_SVCCTX,	0,	0);		/* 服务器环境句柄 */
	OCIHandleAlloc(envhp, (dvoid**)&srvhp, OCI_HTYPE_SERVER,	0,	0);		/* 服务器句柄 */
	OCIHandleAlloc(envhp, (dvoid**)&authp, OCI_HTYPE_SESSION,	0,	0);		/* 会话句柄 */
	OCIHandleAlloc(envhp, (dvoid**)&errhp, OCI_HTYPE_ERROR,		0,	0);		/* 错误句柄 */
	OCIHandleAlloc(envhp, (dvoid**)&dschp, OCI_HTYPE_DESCRIBE,	0,	0);		/* 描述符句柄 */
	
	/* 连接服务器 */
	retValue = OCIServerAttach(srvhp, errhp,(text *)strServerName, 
		(sb4)strlen(strServerName),OCI_DEFAULT);
	
	/* 设置用户名和密码 */
	retValue = OCIAttrSet(authp,OCI_HTYPE_SESSION,(text *)strUserName,
		(ub4)strlen(strUserName),OCI_ATTR_USERNAME,errhp);
	retValue = OCIAttrSet(authp,OCI_HTYPE_SESSION,(text *)strPassword,
		(ub4)strlen(strPassword), OCI_ATTR_PASSWORD,errhp);
	
	/* 设置服务器环境句柄属性 */
	retValue = OCIAttrSet ((dvoid*)svchp, (ub4) OCI_HTYPE_SVCCTX, 
		(dvoid*)srvhp, (ub4) 0, OCI_ATTR_SERVER, errhp);
	retValue = OCIAttrSet(svchp, OCI_HTYPE_SVCCTX,(dvoid*)authp,
		0, OCI_ATTR_SESSION, errhp);
	
	/* 创建并开始一个用户会话 */
	retValue = OCISessionBegin (svchp, errhp, authp,OCI_CRED_RDBMS,OCI_DEFAULT);
	retValue = OCIHandleAlloc(envhp, (dvoid**)&stmthp,OCI_HTYPE_STMT, 0, 0); /* 语句句柄 */

	/******************************/
	/* 查询person表 */
	/******************************/
	strcpy(sql, "select \"sex\",\"name\",\"email\",\"phone\",\"personid\" from \"XXJH\".\"person\";");
	
	/* 准备SQL语句 */
	retValue = OCIStmtPrepare(stmthp, errhp,(text *)sql, strlen(sql),OCI_NTV_SYNTAX, OCI_DEFAULT);
	
	/* 绑定输出列 */
	retValue = OCIDefineByPos (stmthp,&defhp[0],errhp, 1,(ub1*)szpersonid,
		sizeof(szpersonid),SQLT_STR,&ind[0], 0, 0, OCI_DEFAULT);
	retValue = OCIDefineByPos (stmthp,&defhp[1],errhp, 2,(ub1*)szname,
		sizeof(szname),SQLT_STR,&ind[1], 0, 0, OCI_DEFAULT);
	retValue = OCIDefineByPos (stmthp,&defhp[2],errhp, 3,(ub1*)szphone,
		sizeof(szphone),SQLT_STR,&ind[2], 0, 0, OCI_DEFAULT);
	
	/* 执行SQL语句 */
	retValue = OCIStmtExecute(svchp, stmthp,errhp, (ub4)0, 0, NULL, NULL, OCI_DEFAULT);
	if (retValue != 0)
	{
		retValue = OCIErrorGet(errhp, 1, NULL, &retValue, (OraText *)errbuf, sizeof(errbuf), OCI_HTYPE_ERROR);
		printf("%s\n",errbuf);
	}
	printf("%-10s%-10s%-10s\n", "PERSONID", "NAME", "PHONE");
	while((OCIStmtFetch(stmthp, errhp,1,OCI_FETCH_NEXT,OCI_DEFAULT)) != OCI_NO_DATA)
	{
		printf("%-10s",		szpersonid);
		printf("%-10s",		szname);
		printf("%-10s\n",	szphone);
	}

	/******************************/
	/* 向person表插入一条数据 */
	/******************************/
	memset(sql, 0, sizeof(sql));
// 	insert into "XXJH"."person"("sex", "name", "email", "phone", "personid") 
// 		VALUES('1','2','3','4','5');
/*	strcpy(sql, "insert into \"XXJH\".\"person\"(\"sex\", \"name\", \"email\", \"phone\", \"personid\") values(:sex,:name,:email,:phone,:id)");*/
	strcpy(sql, "insert into \"XXJH\".\"person\"(\"sex\", \"name\", \"email\", \"phone\") values(:sex,:name,:email,:phone)");
	
	/* 准备SQL语句 */
	retValue = OCIStmtPrepare(stmthp, errhp,(text *)sql, strlen(sql),OCI_NTV_SYNTAX, OCI_DEFAULT);
	
	/* 设置输入参数 */
	memset(szsex, 0, sizeof(szsex));
	strcpy((char *)szsex,		"M");
	memset(szname, 0, sizeof(szname));
	strcpy((char *)szname,		"张三");
	memset(szemail, 0, sizeof(szemail));
	strcpy((char *)szemail,		"zhangsan@dameng.com");
	memset(szphone, 0, sizeof(szphone));
	strcpy((char *)szphone,		"027-87588000");
	memset(szid, 0, sizeof(szid));
	strcpy((char *)szid,		"1");
	
	/* 绑定输入列 */
	retValue = OCIBindByName (stmthp, &bidhp[0], errhp, (OraText *)":sex", 4, szsex, strlen((char*)szsex), 
		SQLT_AFC, NULL, NULL, NULL, 0, NULL, 0);
	retValue = OCIBindByName (stmthp, &bidhp[1], errhp, (OraText *)":name", 5, szname, strlen((char*)szname), 
		SQLT_AFC, NULL, NULL, NULL, 0, NULL, 0);
	retValue = OCIBindByName (stmthp, &bidhp[2], errhp, (OraText *)":email", 6, szemail, strlen((char*)szemail), 
		SQLT_AFC, NULL, NULL, NULL, 0, NULL, 0);
	retValue = OCIBindByName (stmthp, &bidhp[3], errhp, (OraText *)":phone", 6, szphone, strlen((char*)szphone), 
		SQLT_AFC, NULL, NULL, NULL, 0, NULL, 0);
// 	OCIBindByName (stmthp, &bidhp[4], errhp, (OraText *)":id", 6, szid, strlen((char*)szid), 
// 		SQLT_AFC, NULL, NULL, NULL, 0, NULL, 0);
	
	/* 执行SQL语句 */
	retValue = OCIStmtExecute(svchp, stmthp, errhp, (ub4)1, (ub4) 0, (CONST OCISnapshot*) 0, (OCISnapshot*) 0, 
		(ub4) OCI_DEFAULT);
	if (retValue != 0)
	{
		OCIErrorGet(errhp, 1, NULL, &retValue, (OraText *)errbuf, sizeof(errbuf), OCI_HTYPE_ERROR);
		printf("%s\n",errbuf);
	}

	/* 提交到数据库 */
	OCITransCommit(svchp, errhp, OCI_DEFAULT);
	
	/******************************/
	/* 更新person表 */
	/******************************/
	memset(sql, 0, sizeof(sql));
	strcpy(sql, "update \"XXJH\".\"person\" set \"sex\"='M',\"name\"='Liuhuan',\"email\"='liujian@mail',\"phone\"='13636396811' WHERE \"personid\"='5'");

	/* 准备SQL语句 */
	retValue = OCIStmtPrepare(stmthp, errhp,(text *)sql, strlen(sql),OCI_NTV_SYNTAX, OCI_DEFAULT);
	/* 执行SQL语句 */
	retValue = OCIStmtExecute(svchp, stmthp, errhp, (ub4)1, (ub4) 0, (CONST OCISnapshot*) 0, (OCISnapshot*) 0, 
		(ub4) OCI_DEFAULT);
	if (retValue != 0)
	{
		OCIErrorGet(errhp, 1, NULL, &retValue, (OraText *)errbuf, sizeof(errbuf), OCI_HTYPE_ERROR);
		printf("%s\n",errbuf);
	}

	/* 提交到数据库 */
	OCITransCommit(svchp, errhp, OCI_DEFAULT);

	/************************************************************************/
	/* 删除person表的ID为1的数据，首先要在数据库中存在这条记录 */
	/************************************************************************/
	memset(sql, 0, sizeof(sql));
	strcpy(sql, "delete from \"XXJH\".\"person\" WHERE \"personid\" =:1");

	/* 准备SQL语句 */
	retValue = OCIStmtPrepare(stmthp, errhp,(text *)sql, strlen(sql),OCI_NTV_SYNTAX, OCI_DEFAULT);
	
	/* 绑定输入参数 */
	memset(szpersonid, 0, sizeof(szpersonid));
	strcpy((char *)szpersonid, "5");
	retValue = OCIBindByPos(stmthp, &bidhp[0], errhp, 1, szpersonid, strlen((char*)szpersonid), 
		SQLT_AFC, NULL, NULL, NULL, 0, NULL, 0);
	
	/* 执行SQL语句 */
	retValue = OCIStmtExecute(svchp, stmthp, errhp, (ub4)1, (ub4) 0, (CONST OCISnapshot*) 0, (OCISnapshot*) 0, 
		(ub4) OCI_DEFAULT);
	if (retValue != 0)
	{
		retValue = OCIErrorGet(errhp, 1, NULL, &retValue, (OraText *)errbuf, sizeof(errbuf), OCI_HTYPE_ERROR);
		printf("%s\n",errbuf);
	}

	/* 提交到数据库 */
	OCITransCommit(svchp, errhp, OCI_DEFAULT);
	
	//结束会话
	OCISessionEnd(svchp, errhp, authp, (ub4) 0);
	//断开与数据库的连接
	OCIServerDetach(srvhp, errhp, OCI_DEFAULT);
	//释放OCI句柄
	OCIHandleFree((dvoid*)dschp, OCI_HTYPE_DESCRIBE);
	OCIHandleFree((dvoid*)stmthp, OCI_HTYPE_STMT );
	OCIHandleFree((dvoid*)errhp, OCI_HTYPE_ERROR);
	OCIHandleFree((dvoid*)authp, OCI_HTYPE_SESSION );
	OCIHandleFree((dvoid*)svchp, OCI_HTYPE_SVCCTX);
	OCIHandleFree((dvoid*)srvhp, OCI_HTYPE_SERVER);


#ifdef WIN32
 Sleep(10000);
#endif	

#if  defined(__aarch64__) || defined(__x86_64__)
	sleep(10000);
#endif

	return 0;
}
