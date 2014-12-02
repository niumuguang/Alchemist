#根据 固定列 倒序查看
#Select UpdateTime from FutureDB.i1501;
#select ＊ from FutureDB.i1501 order by idnew_table desc limit 0,1;
Use FutureDB;
select * from FutureDB.i1501 order by idnew_table desc;