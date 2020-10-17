# 1. Dameng DB
## 1.1 setup dm db
```
cd dameng_x86
./DMInstall.bin
cd /home/rd/Desktop/DMDBMS

```
add path for cmd
```
sudo vim /etc/profile
PATH=/home/rd/dmdbms/bin:$PATH
export PATH
source /etc/profile
```
start DmServiceDMSERVER, to run
```
DmServiceDMSERVER start
```
test you dm server
```
disql SYSDBA/SYSDBA@localhost:5236
create table t(a int,b int,c int);
insert into t values(1,2,3);
insert into t values(11,22,33);
commit;
quit
```

## 1.2 setup unixODBC

```
tar -zxf unixODBC-2.3.9.tar.gz
cd unixODBC-2.3.9/
./configure
make
sudo make install
```
add so to lib path
```
sudo vim /etc/profile
LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH
sudo ldconfig
```
then, run
```
odbcinst -j
```
you can see
```
unixODBC 2.3.9
DRIVERS............: /usr/local/etc/odbcinst.ini
SYSTEM DATA SOURCES: /usr/local/etc/odbc.ini
FILE DATA SOURCES..: /usr/local/etc/ODBCDataSources
USER DATA SOURCES..: /home/rd/.odbc.ini
SQLULEN Size.......: 8
SQLLEN Size........: 8
SQLSETPOSIROW Size.: 8
```
## 1.3 config odbc

sudo vim /user/local/etc/odbcinst.ini,
content as following
```
[DM7 ODBC DRIVER]
Description = ODBC DRIVER FOR DM7
Driver		= /home/rd/dmdbms/bin/libdodbc.so
Setup		= /lib/libdmOdbcSetup.so
```
sudo vim /usr/local/etc/odbc.ini,
content as following
```
[dm]
Description = DM ODBC DSN
Driver		= DM7 ODBC DRIVER
SERVER		= localhost
UID			= SYSDBA
PWD			= SYSDBA
TCP_PORT 	= 5236
```
## 1.4 config LD_LIBRARY_PATH
add dm libdodbc.so to LD_LIBRARY_PATH
sudo vim /etc/profile
```
LD_LIBRARY_PATH=/home/rd/dmdbms/bin:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH
```
and run
```
sudo ldconfig
```
now test your odbc config, run
 ```
 isql -v dm
 ```
you can see
```
+---------------------------------------+
| Connected!                            |
|                                       |
| sql-statement                         |
| help [tablename]                      |
| quit                                  |
|                                       |
+---------------------------------------+
```
if you see
`Can't open lib '/home/rd/dmdbms/bin/libdodbc.so' : file not found`,
but the so file really exit, that is because of LD_LIBRARY_PATH config
for dmdb lib and odbc lib is not valid or haven't be activated.
check and fix the problem,you can run
```
ldd theSoCalledMissedSoFile.so
```
to check what's wrong.

# 2. DM DB case sensitive  
# 2.1 对于表名、字段名而言  
在设置为大小写敏感的库中进行查询的时候，可能经常会遇到无效的表名或列名的问题，  
下面针对这种情况进行说明。  
# 2.2 如果使用DM管理工具图形界面建表的话建议表名和字段名都使用大写
因为使用图形界面建表相当于使用语句建表的时候加了双引号的，会固定住大小写。  
如果写成小写，那么就是小写了，在查询的时候也需要加双引号，否则就有可能报无效的表名或列名的问题，比较麻烦；
# 2.3 如果使用脚本建表的话，如果表名和字段名没有加双引号的话都会被系统自动转换成大写  
如：create table test(a int)；系统会自动把表名test，字段名a转换成大写，处理方式与Oracle数据库一致  
所以针对大小写敏感的库，在使用建表脚本或者通过查询脚本进行查询的时候建议统一不要写双引号，  
让系统统一自动都转化为大写；
## 2.4 以上两点主要针对大小写敏感的库而言，大小写不敏感的库则不存在上述问题。  
基于以上两点，在初始化数据库的过程中就可以对字符串比较大小写敏感这个参数做出合理的选择了。
