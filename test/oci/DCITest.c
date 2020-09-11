/******************************/
/* DCI���ʵ�� */
/******************************/

#ifdef WIN32
#include <windows.h>
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include "DCI.h"

/* ������� */
OCIEnv		*envhp;		/* ������� */
OCISvcCtx	*svchp;		/* ���񻷾���� */
OCIServer	*srvhp;		/* ��������� */
OCISession	*authp;		/* �Ự��� */
OCIStmt		*stmthp;	/* ����� */
OCIDescribe *dschp;		/* ������� */

OCIError	*errhp;		/* ������ */
OCIDefine	*defhp[10]; /* ������ */
OCIBind		*bidhp[10]; /* �󶨾�� */

sb2			ind[3];		/* ָʾ������ */

/* ��select������Ĳ��� */
text szpersonid[11];	/* �洢personid�� */
text szsex[2];			/* �洢sex�� */
text szname[51];		/* �洢name�� */
text szemail[51];		/* �洢mail�� */
text szphone[26];		/* �洢phone�� */
text szid[10];			/*	*/
char sql[256];			/* �洢ִ�е�sql���*/

int main(int argc, char *argv[])
{
	char strServerName[50];	//���Ӵ���192.168.49.36:5236/XXJH
	char strUserName[50];	//�û���
	char strPassword[50];	//����
	text errbuf[100];
	int retValue = 0;		//����ֵ

	/* ���÷��������û��������� */
	strcpy(strServerName,"192.168.49.36:5236/XXJH");
	strcpy(strUserName,"XXJH");
	strcpy(strPassword,"123456789");
	
	/* ��ʼ��OCIӦ�û���*/
	OCIInitialize(OCI_DEFAULT, NULL, NULL, NULL, NULL);
	/* ��ʼ��������� */
	OCIEnvInit(&envhp, OCI_DEFAULT,0, 0);
	/* ������ */
	OCIHandleAlloc(envhp, (dvoid**)&svchp, OCI_HTYPE_SVCCTX,	0,	0);		/* ������������� */
	OCIHandleAlloc(envhp, (dvoid**)&srvhp, OCI_HTYPE_SERVER,	0,	0);		/* ��������� */
	OCIHandleAlloc(envhp, (dvoid**)&authp, OCI_HTYPE_SESSION,	0,	0);		/* �Ự��� */
	OCIHandleAlloc(envhp, (dvoid**)&errhp, OCI_HTYPE_ERROR,		0,	0);		/* ������ */
	OCIHandleAlloc(envhp, (dvoid**)&dschp, OCI_HTYPE_DESCRIBE,	0,	0);		/* ��������� */
	
	/* ���ӷ����� */
	retValue = OCIServerAttach(srvhp, errhp,(text *)strServerName, 
		(sb4)strlen(strServerName),OCI_DEFAULT);
	
	/* �����û��������� */
	retValue = OCIAttrSet(authp,OCI_HTYPE_SESSION,(text *)strUserName,
		(ub4)strlen(strUserName),OCI_ATTR_USERNAME,errhp);
	retValue = OCIAttrSet(authp,OCI_HTYPE_SESSION,(text *)strPassword,
		(ub4)strlen(strPassword), OCI_ATTR_PASSWORD,errhp);
	
	/* ���÷���������������� */
	retValue = OCIAttrSet ((dvoid*)svchp, (ub4) OCI_HTYPE_SVCCTX, 
		(dvoid*)srvhp, (ub4) 0, OCI_ATTR_SERVER, errhp);
	retValue = OCIAttrSet(svchp, OCI_HTYPE_SVCCTX,(dvoid*)authp,
		0, OCI_ATTR_SESSION, errhp);
	
	/* ��������ʼһ���û��Ự */
	retValue = OCISessionBegin (svchp, errhp, authp,OCI_CRED_RDBMS,OCI_DEFAULT);
	retValue = OCIHandleAlloc(envhp, (dvoid**)&stmthp,OCI_HTYPE_STMT, 0, 0); /* ����� */

	/******************************/
	/* ��ѯperson�� */
	/******************************/
	strcpy(sql, "select \"sex\",\"name\",\"email\",\"phone\",\"personid\" from \"XXJH\".\"person\";");
	
	/* ׼��SQL��� */
	retValue = OCIStmtPrepare(stmthp, errhp,(text *)sql, strlen(sql),OCI_NTV_SYNTAX, OCI_DEFAULT);
	
	/* ������� */
	retValue = OCIDefineByPos (stmthp,&defhp[0],errhp, 1,(ub1*)szpersonid,
		sizeof(szpersonid),SQLT_STR,&ind[0], 0, 0, OCI_DEFAULT);
	retValue = OCIDefineByPos (stmthp,&defhp[1],errhp, 2,(ub1*)szname,
		sizeof(szname),SQLT_STR,&ind[1], 0, 0, OCI_DEFAULT);
	retValue = OCIDefineByPos (stmthp,&defhp[2],errhp, 3,(ub1*)szphone,
		sizeof(szphone),SQLT_STR,&ind[2], 0, 0, OCI_DEFAULT);
	
	/* ִ��SQL��� */
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
	/* ��person�����һ������ */
	/******************************/
	memset(sql, 0, sizeof(sql));
// 	insert into "XXJH"."person"("sex", "name", "email", "phone", "personid") 
// 		VALUES('1','2','3','4','5');
/*	strcpy(sql, "insert into \"XXJH\".\"person\"(\"sex\", \"name\", \"email\", \"phone\", \"personid\") values(:sex,:name,:email,:phone,:id)");*/
	strcpy(sql, "insert into \"XXJH\".\"person\"(\"sex\", \"name\", \"email\", \"phone\") values(:sex,:name,:email,:phone)");
	
	/* ׼��SQL��� */
	retValue = OCIStmtPrepare(stmthp, errhp,(text *)sql, strlen(sql),OCI_NTV_SYNTAX, OCI_DEFAULT);
	
	/* ����������� */
	memset(szsex, 0, sizeof(szsex));
	strcpy((char *)szsex,		"M");
	memset(szname, 0, sizeof(szname));
	strcpy((char *)szname,		"����");
	memset(szemail, 0, sizeof(szemail));
	strcpy((char *)szemail,		"zhangsan@dameng.com");
	memset(szphone, 0, sizeof(szphone));
	strcpy((char *)szphone,		"027-87588000");
	memset(szid, 0, sizeof(szid));
	strcpy((char *)szid,		"1");
	
	/* �������� */
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
	
	/* ִ��SQL��� */
	retValue = OCIStmtExecute(svchp, stmthp, errhp, (ub4)1, (ub4) 0, (CONST OCISnapshot*) 0, (OCISnapshot*) 0, 
		(ub4) OCI_DEFAULT);
	if (retValue != 0)
	{
		OCIErrorGet(errhp, 1, NULL, &retValue, (OraText *)errbuf, sizeof(errbuf), OCI_HTYPE_ERROR);
		printf("%s\n",errbuf);
	}

	/* �ύ�����ݿ� */
	OCITransCommit(svchp, errhp, OCI_DEFAULT);
	
	/******************************/
	/* ����person�� */
	/******************************/
	memset(sql, 0, sizeof(sql));
	strcpy(sql, "update \"XXJH\".\"person\" set \"sex\"='M',\"name\"='Liuhuan',\"email\"='liujian@mail',\"phone\"='13636396811' WHERE \"personid\"='5'");

	/* ׼��SQL��� */
	retValue = OCIStmtPrepare(stmthp, errhp,(text *)sql, strlen(sql),OCI_NTV_SYNTAX, OCI_DEFAULT);
	/* ִ��SQL��� */
	retValue = OCIStmtExecute(svchp, stmthp, errhp, (ub4)1, (ub4) 0, (CONST OCISnapshot*) 0, (OCISnapshot*) 0, 
		(ub4) OCI_DEFAULT);
	if (retValue != 0)
	{
		OCIErrorGet(errhp, 1, NULL, &retValue, (OraText *)errbuf, sizeof(errbuf), OCI_HTYPE_ERROR);
		printf("%s\n",errbuf);
	}

	/* �ύ�����ݿ� */
	OCITransCommit(svchp, errhp, OCI_DEFAULT);

	/************************************************************************/
	/* ɾ��person���IDΪ1�����ݣ�����Ҫ�����ݿ��д���������¼ */
	/************************************************************************/
	memset(sql, 0, sizeof(sql));
	strcpy(sql, "delete from \"XXJH\".\"person\" WHERE \"personid\" =:1");

	/* ׼��SQL��� */
	retValue = OCIStmtPrepare(stmthp, errhp,(text *)sql, strlen(sql),OCI_NTV_SYNTAX, OCI_DEFAULT);
	
	/* ��������� */
	memset(szpersonid, 0, sizeof(szpersonid));
	strcpy((char *)szpersonid, "5");
	retValue = OCIBindByPos(stmthp, &bidhp[0], errhp, 1, szpersonid, strlen((char*)szpersonid), 
		SQLT_AFC, NULL, NULL, NULL, 0, NULL, 0);
	
	/* ִ��SQL��� */
	retValue = OCIStmtExecute(svchp, stmthp, errhp, (ub4)1, (ub4) 0, (CONST OCISnapshot*) 0, (OCISnapshot*) 0, 
		(ub4) OCI_DEFAULT);
	if (retValue != 0)
	{
		retValue = OCIErrorGet(errhp, 1, NULL, &retValue, (OraText *)errbuf, sizeof(errbuf), OCI_HTYPE_ERROR);
		printf("%s\n",errbuf);
	}

	/* �ύ�����ݿ� */
	OCITransCommit(svchp, errhp, OCI_DEFAULT);
	
	//�����Ự
	OCISessionEnd(svchp, errhp, authp, (ub4) 0);
	//�Ͽ������ݿ������
	OCIServerDetach(srvhp, errhp, OCI_DEFAULT);
	//�ͷ�OCI���
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
