# 扫盲
1. ifnull(expr1, expr2):
表示
```sql
if (expr1!=null):
        choose expr1
    else
        choose expr2
```
2. limit n offset m: (等价于 limit n,m)
无视前m条记录，从第m+1条记录开始选取n条记录
        
3. ordered by xxx desc/asc

4. isnull(expr):
```sql
if ( expr!=null ) 
    return 0
else 
    return 1
```

5. inner join on expr:

表的等值连接，expr为连接表与表之间的表达式(例如a.personId=b.presonId)

6. left join on expr:

左连接, 以本题为例，把左表中的所有员工的信息和右表进行连接，若某个员工的信息未在右表里出现过，那就用null来填充

7. right join on expr:

右连接，类似左连接

ps: 尽量使用join on， 让表的条件表达式出现在from中而不是where中

8. 