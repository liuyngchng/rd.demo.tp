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


-- 查看表空间物理文件的名称及大小 --
select t.name tablespace_name,t.id file_id,d.path file_name,d.total_size*sf_get_page_size()/1024/1024||'m' total_space from v$tablespace t, v$datafile d where t.id=d.group_id;

-- 查看数据库实例信息 --
select name inst_name from v$instance;

-- 确定高负载的 SQL(慢查询) --
select * from v$long_exec_sqls;


select owner, table_name, tablespace_name from dba_tables where owner = 'sysdba';

-- 查询当前用户下所有的表名--
select NAME from sysobjects where "SUBTYPE='SCH');

-- 有开源的客户端工具可以连DM ?--
-- 基于JDBC的工具就可以，比如：SQuirrel SQL、DbVisualizer --

