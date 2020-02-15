/*
    问题描述:
        部门表 Department：

    +---------------+---------+
    | Column Name   | Type    |
    +---------------+---------+
    | id            | int     |
    | revenue       | int     |
    | month         | varchar |
    +---------------+---------+
    (id, month) 是表的联合主键。
    这个表格有关于每个部门每月收入的信息。
    月份（month）可以取下列值 ["Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"]。
     

    编写一个 SQL 查询来重新格式化表，使得新的表中有一个部门 id 列和一些对应 每个月 的收入（revenue）列。

    查询结果格式如下面的示例所示：

        Department 表：
        +------+---------+-------+
        | id   | revenue | month |
        +------+---------+-------+
        | 1    | 8000    | Jan   |
        | 2    | 9000    | Jan   |
        | 3    | 10000   | Feb   |
        | 1    | 7000    | Feb   |
        | 1    | 6000    | Mar   |
        +------+---------+-------+

    查询得到的结果表：
        +------+-------------+-------------+-------------+-----+-------------+
        | id   | Jan_Revenue | Feb_Revenue | Mar_Revenue | ... | Dec_Revenue |
        +------+-------------+-------------+-------------+-----+-------------+
        | 1    | 8000        | 7000        | 6000        | ... | null        |
        | 2    | 9000        | null        | null        | ... | null        |
        | 3    | null        | 10000       | null        | ... | null        |
        +------+-------------+-------------+-------------+-----+-------------+

        注意，结果表有 13 列 (1个部门 id 列 + 12个月份的收入列)。
    
    问题分析:
        mysql没pivot函数只能用if来转换做(虽然有我也8会。。)
        
        本题收获:
            1. if (expr1, res1, res2) 
                    语意等价于: expr1 ? res1 : res2 
            2. 在属性上加` , 字符串是''，别搞混了

            select if ( `month`='Jan', revenue, null )
            from Department;
            
            就是 返回 month属性为Jan 的 元组
            因为如果if里匹配到多条的话，是个元祖集，不指定的话，就是返回第一条元组！

            因此，在本题中，需要用一个聚合函数来操作，只要这个集合里存在非空revenue，那么就返回非空，
            所以可以用sum或者max来做
*/

select id, 
max(if(`month`='Jan',revenue,null)) as Jan_Revenue,
max(if(`month`='Feb',revenue,null)) as Feb_Revenue,
max(if(`month`='Mar',revenue,null)) as Mar_Revenue,
max(if(`month`='Apr',revenue,null)) as Apr_Revenue,
max(if(`month`='May',revenue,null)) as May_Revenue,
max(if(`month`='Jun',revenue,null)) as Jun_Revenue,
max(if(`month`='Jul',revenue,null)) as Jul_Revenue,
max(if(`month`='Aug',revenue,null)) as Aug_Revenue,
max(if(`month`='Sep',revenue,null)) as Sep_Revenue,
max(if(`month`='Oct',revenue,null)) as Oct_Revenue,
max(if(`month`='Nov',revenue,null)) as Nov_Revenue,
max(if(`month`='Dec',revenue,null)) as Dec_Revenue
from Department
group by id;