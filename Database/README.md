# 扫盲
## 1. ifnull(expr1, expr2):
表示
```sql
if (expr1!=null):
        choose expr1
    else
        choose expr2
```
## 2. limit n offset m: (等价于 limit n,m)
无视前m条记录，从第m+1条记录开始选取n条记录
        
## 3. ordered by xxx desc/asc

## 4. isnull(expr):
```sql
if ( expr!=null ) 
    return 0
else 
    return 1
```

## 5. inner join on expr:

表的等值连接，expr为连接表与表之间的表达式(例如a.personId=b.presonId)

## 6. left join on expr:

左连接, 以本题为例，把左表中的所有员工的信息和右表进行连接，若某个员工的信息未在右表里出现过，那就用null来填充

## 7. right join on expr:

右连接，类似左连接

ps: 尽量使用join on， 让表的条件表达式出现在from中而不是where中

## 8. 注释:
```sql
-- hehe
/* hehe */
```

## 9. order by xx 
```sql
order by col1 desc , col2 asc ; -- 优先按col1降序排序，col1相等的话，就按照col2升序排序

order by 1 desc , 2 asc ; -- 优先按第一个属性降序排序，第一个属性的值相等的话，就按照第二个属性升序
```

## 10. like
```sql
-- 1. 匹配以a开头并以a结尾的
where xx like 'a%a';
-- ps: 单个的 '%' 不会匹配到null

-- 2. 匹配以a开头并以a结尾的长度为3的
where xx like 'a_a';
-- ps: _和%一样，只不过_是匹配一个任意字符

-- 3. [AB]% 匹配以A或B为开头的 ，跟正则表达式里的[]类似
where xx like '[AB]%'

-- 4. [^AB]% 匹配不以 A或B为开头的 ，跟正则表达式里的^类似， 取反
where xx like '[^AB]%'
```

## 11. 广播？
有点像python里的广播， 对列的操作就会变成对结果集的操作
```sql
-- 对查询结果的两边加上括号
select concat('(',name,')') as name from account;
/*结果:
+-------+
| name  |
+-------+
| (aaa) |
| (bbb) |
| (ccc) |
| (ddd) |
| (eee) |
| (fff) |
+-------+
*/

-- 根据已有的列的查询结果，来构造新的列的值
-- 新增一个money*2的列
select money , money*2 as doubled from account;
/* 结果:
+-------+---------+
| money | doubled |
+-------+---------+
|  1000 |    2000 |
|  1000 |    2000 |
|  1000 |    2000 |
|  1500 |    3000 |
|   900 |    1800 |
|   900 |    1800 |
+-------+---------+
*/

```