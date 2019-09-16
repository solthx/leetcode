/*
    问题描述:
        编写一个 SQL 查询，获取 Employee 表中第二高的薪水（Salary） 。
        +----+--------+
        | Id | Salary |
        +----+--------+
        | 1  | 100    |
        | 2  | 200    |
        | 3  | 300    |
        +----+--------+
        例如上述 Employee 表，SQL查询应该返回 200 作为第二高的薪水。如果不存在第二高的薪水，那么查询应返回 null。
        +---------------------+
        | SecondHighestSalary |
        +---------------------+
        | 200                 |
        +---------------------+

    问题分析:
        1.ifnull(expr1, expr2):
            表示    if (expr1!=null):
                        choose expr1
                    else
                        choose expr2
        2. limit n offset m: (等价于 limit n,m)
            无视前m条记录，从第m+1条记录开始选取n条记录
        
        3. ordered by xxx desc/asc

        补充:
            4. isnull(expr):
                if ( expr!=null ) return 0
                else return 1
*/
select ifnull(
    (
        select distinct Salary 
        from Employee
        order by Salary desc
        limit 1,1
    ), null ) as SecondHighestSalary