# 1. Dameng DB
## 1.1 setup dm db
```
cd dameng_x86
./DMInstall.bin
cd /home/rd/Desktop/DMDBMS

```
open `DM Service Viewer` as   /home/rd/dmdbms/tool/dmservice.sh
start DmServiceDMSERVER
add path for cmd
```
sudo vim /etc/profile
PATH=/home/rd/dmdbms/bin:$PATH
export PATH
source /etc/profile
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
make install
```
run
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
```
add libodbc.so to LD_LIBRARY_PATH
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
but the so file really exit, that is because LD_LIBRARY_PATH config
for dm lib and odbc lib is not valid or haven't be activated.
check and fix the problem,you canb run
```
ldd theSoCalledMissedSoFile.so
```
