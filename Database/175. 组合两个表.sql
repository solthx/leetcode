/*
    问题描述:
        表1: Person
            +-------------+---------+
            | 列名         | 类型     |
            +-------------+---------+
            | PersonId    | int     |
            | FirstName   | varchar |
            | LastName    | varchar |
            +-------------+---------+
            PersonId 是上表主键
        
        表2: Address
            +-------------+---------+
            | 列名         | 类型    |
            +-------------+---------+
            | AddressId   | int     |
            | PersonId    | int     |
            | City        | varchar |
            | State       | varchar |
            +-------------+---------+
        AddressId 是上表主键
        
        编写一个 SQL 查询，满足条件：无论 person 是否有地址信息，都需要基于上述两表提供 person 的以下信息：
        
        FirstName, LastName, City, State

    问题分析：
        inner join on expr:
            表的等值连接，expr为连接表与表之间的表达式(例如a.personId=b.presonId)
        left join on expr:
            左连接, 以本题为例，把左表中的所有员工的信息和右表进行连接，若某个员工的信息未在右表里出现过，那就用null来填充
        right join on expr:
            右连接，类似左连接
        
        ps: 尽量使用join on， 让表的条件表达式出现在from中而不是where中
*/

select FirstName, LastName, City, State 
from Person left join Address on Person.PersonId = Address.PersonId
