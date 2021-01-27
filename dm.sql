--- connect server ---
disql username/psword@dbhost:port
create table t(a int,b int,c int);
insert into t values(1,2,3);
insert into t values(11,22,33);
commit;
quit;

--- 查看表定义 ---
CALL SP_TABLEDEF('schema', 'tableName');

--- DM7查看数据库版本 ---
select * from v$version;

-- 查看所有表空间（schema）---
select name from v$tablespace;

-- 查看所有表空间物理文件 --
select * from v$datafile;

-- 执行sql脚本 --
SQL> start /a/b/c.sql

-- 编辑SQL脚本 --
SQL> edit /a/b/c.sql

