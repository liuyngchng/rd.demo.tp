A demo for tp
# 1. stack
```
mkdir obj
make os=OSX             //on Mac OS
```

# 2. sqlite-amalgamation-3081101.zip

## 2.1 编译静态库

```
gcc -c sqlite3.c -lpthread -ldl -o sqlite3.o

ar -r libsqlite3.a sqlite3.o
```
将列出的各个目标文件一起打包成一个静态库libsqlite3.a

## 2.2  编译命令行管理工具
```
gcc shell.c sqlite3.c -lpthread -ldl -o sqlite3
```

## 2.3 编译动态链接库

```
gcc sqlite3.c -lpthread -ldl -fPIC -shared -o libsqlite3.so
```


- -fPIC：表示编译为位置独立的代码，不用此选项的话编译后的代码是位置相关的，动态载入时是通过代码拷贝的方式来满足不同进程的需要， 这样，N个进程就就需要N个动态库的拷贝，不能达到真正代码段共享的目的。

- -shared：表示生成一个共享目标文件(动态链接库)。它可以和其他目标文件连接产生可执行文件。

- -lpthread系统库用于支持线程操作。

- -dl系统库用于支持动态装载


# 3. log4c

```
tar -zxf log4c-1.2.4.tar.gz
cd log4c-1.2.4
rm doc tests examples
```
修改 Makefile.x, configure, 将以下两行
```
SUBDIRS = config src ${DOC_SUBDIR} ${TEST_SUBDIR} examples
DIST_SUBDIRS = config src doc tests examples
```
中的 doc tests exampls 删除
```
mkdir build
cd build
../configure --without-expat
cd ..
autoreconf -ivf 
cd build
make
cd log4c-1.2.4/build/src/log4c/.libs
mkdir obj
cp liblog4c.a obj
cd obj
ar -x liblog4c.a
```

# 2. env for dynamic lib  

```
# add dynamic link library path for runtime
LD_LIBRARY_PATH=/a/b/c:$LD_LIBRARY_PATH

# add dynamic link library path for compile time
LIBRARY_PATH=$LD_LIBRARY_PATH:$LIBRARY_PATH

# add include header file path 
CPLUS_INCLUDE_PATH=/a/b/c:$CPLUS_INCLUDE_PATH

C_INCLUDE_PATH=$CPLUS_INCLUDE_PATH

export LD_LIBRARY_PATH;
export LIBRARY_PATH;
export CPLUS_INCLUDE_PATH;
export C_INCLUDE_PATH;
```
# 3. use sqlite with c in ubuntu

```
apt-get install sqlite sqlite3
```
sqlite3，就是安装编译之后的sqlite3，不能用于开发。  
检查数据库安装结果：  
```
sqlite3 test.db
.database
.exit
```
安装Sqlite3编译需要的工具包  
```
apt-get install libsqlite3-dev
```
这时候便可以使用#include<sqlite3.h>在头文件导入  

sqlitebrowser - GUI editor for SQLite databases

```
int sqlite3_exec(
  sqlite3\*,                     /* An open database */
  const char *sql,              /* SQL to be executed */
  sqlite_callback,              /* Callback function */
  void *,                       /* 1st argument to callback function */
  char **errmsg                 /* Error msg written here */
);
```

# 4. LT code 

LT codes  
Conference Paper in Foundations of Computer Science, 1975., 16th Annual Symposium on · January 2002  
DOI: 10.1109/SFCS.2002.1181950 ·  
Source: DBLP

Author: Michael Luby , from Digital Fountain, Inc.   
luby@digitalfountain.com  
卢比变换码（LT码，英文：Luby transform codes, LT codes）  
是第一个最接近完善的抹除码(erasure correcting codes)的实用涌泉码(fountain codes），  
由Michael Luby在1998年发明并于2002年发表。

#5. dm db
```
https://blog.csdn.net/cddchina/article/details/80733303?utm_medium=distribute.pc_relevant_bbs_down.none-task--2~all~sobaiduend~default-1.nonecase&depth_1-utm_source=distribute.pc_relevant_bbs_down.none-task--2~all~sobaiduend~default-1.nonecase
```

# 6. SOCI
https://www.jianshu.com/p/66ac4e90c602
