#include "sqlite3.h" 
#include <cstdio>
#include <cstring>
#include <assert.h>  
#pragma comment(lib, "sqlite3.lib")  
typedef struct per
{
    char *name;
    int age;
    char *sex;
} per;
per a[] = {
    "David",22,"man",
    "Eve",28,"man",
    "Frand",21,"woman"
};
// 这个函数可以用来打印出每行的信息  
static int callback(void *NotUsed, int argc, char **argv, char **azColName){  
    int i;  
    for(i=0; i<argc; i++){  
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");  
    }  
    printf("\n");  
    return 0;  
}  
int main()  
{  
    sqlite3 *pdb;  
    char *zErrMsg;  
    sqlite3_stmt *pstmt;  
    const char *pzTail;  
    const unsigned char *pTmp;
    int age;
    int nCol;
    // 打开数据库连接   
    int nRet = sqlite3_open("e:\\db\\people.db",&pdb);  
    assert(SQLITE_OK == nRet);  
    // 创建表  
    const char *sql = "CREATE TABLE IF NOT EXISTS person(name VARCHAR(128),"  
        "age INTEGER,"  
        "sex VARCHAR(7)"  
        ");";  
    nRet = sqlite3_exec(pdb,sql,NULL,NULL,&zErrMsg);  
    if (nRet != SQLITE_OK)  
    {  
        printf("%s\n",zErrMsg);  
        sqlite3_close(pdb);  
        return 1;  
    }
    sql = "DELETE  FROM person;";
    nRet = sqlite3_exec(pdb,sql,NULL,NULL,&zErrMsg);  
    if (nRet != SQLITE_OK)  
    {  
        printf("%s\n",zErrMsg);  
        sqlite3_close(pdb);  
        return 1;  
    }
    // 使用sqlite3_exec() 插入数据  
    sql = "INSERT INTO person(name,age,sex) VALUES(\"Alice\",15,\"woman\");";  
    nRet = sqlite3_exec(pdb,sql,NULL,NULL,&zErrMsg);  
    assert(SQLITE_OK == nRet);  // 为了简单，这里不打印zErrMsg的值  
    sql = "INSERT INTO person(name,age,sex) VALUES(\"Bob\",18,\"man\");";  
    nRet = sqlite3_exec(pdb,sql,NULL,NULL,&zErrMsg);  
    assert(SQLITE_OK == nRet);  // 为了简单，这里不打印zErrMsg的值  
    sql = "INSERT INTO person(name,age,sex) VALUES(\"Charli\",11,\"man\");";  
    nRet = sqlite3_exec(pdb,sql,NULL,NULL,&zErrMsg);  
    assert(SQLITE_OK == nRet);  // 为了简单，这里不打印zErrMsg的值  
    // 使用sqlite3_exec() 查询数据  
    printf("=====query by sqlite3_exec()=====\n");
    sql = "SELECT name,age,sex FROM person;";  
    nRet = sqlite3_exec(pdb,sql,callback,NULL,&zErrMsg);  
    assert(SQLITE_OK == nRet);  
    // 使用sqlite3_prepare_v2(), sqlite3_bind_...() 插入数据
    sql = "INSERT INTO person(name,age,sex) VALUES(?,?,?);";
    nRet = sqlite3_prepare_v2(pdb,sql,strlen(sql),&pstmt,&pzTail);
    assert(SQLITE_OK == nRet);  
    int i;
    for (i=0;i<sizeof(a)/sizeof(per);i++)
    {
        nCol = 1;
        sqlite3_bind_text(pstmt,nCol++,a[i].name,strlen(a[i].name),NULL);
        sqlite3_bind_int(pstmt,nCol++,a[i].age);
        sqlite3_bind_text(pstmt,nCol++,a[i].sex,strlen(a[i].sex),NULL);
        sqlite3_step(pstmt);
        sqlite3_reset(pstmt);
    }
    sqlite3_finalize(pstmt);
    // 使用sqlite3_prepare_v2(), sqlite3_column_...() 查询数据
    printf("====== query by sqlite3_prepare_v2()======\n");
    sql = "SELECT name,age,sex FROM person;";
    nRet = sqlite3_prepare_v2(pdb,sql,strlen(sql),&pstmt,&pzTail);
    assert(SQLITE_OK == nRet);  
    while(sqlite3_step(pstmt) == SQLITE_ROW)
    {
        nCol = 0;
        pTmp = sqlite3_column_text(pstmt,nCol++);
        printf("%s|",pTmp);
        age = sqlite3_column_int(pstmt,nCol++);
        printf("%d|",age);
        pTmp = sqlite3_column_text(pstmt,nCol++);
        printf("%s\n",pTmp);
    }
    sqlite3_finalize(pstmt);
    sqlite3_close(pdb);  
    return 0; 
}
