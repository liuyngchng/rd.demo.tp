--- connect server ---
disql SYSDBA/SYSDBA@localhost:5236
create table t(a int,b int,c int);
insert into t values(1,2,3);
insert into t values(11,22,33);
commit;
quit;

--- 查看表定义 ---
CALL SP_TABLEDEF('SYSDBA', 'tableName');


