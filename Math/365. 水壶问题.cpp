/*
    问题描述：
        有两个容量分别为 x升 和 y升 的水壶以及无限多的水。请判断能否通过使用这两个水壶，从而可以得到恰好 z升 的水？

        如果可以，最后请用以上水壶中的一或两个来盛放取得的 z升 水。

        你允许：

        装满任意一个水壶
        清空任意一个水壶
        从一个水壶向另外一个水壶倒水，直到装满或者倒空
        示例 1: (From the famous "Die Hard" example)

        输入: x = 3, y = 5, z = 4
        输出: True
        示例 2:

        输入: x = 2, y = 6, z = 5
        输出: False

    问题分析：
        抽象成数学语言就是，看是否存在m和n，使得 m*x + b*y = z 。
        这里提一下裴蜀定理：
            对于任意给定的a,b, 
            当且仅当m是 gcd(a,b)的倍数（ 即 m%gcd(a,b)==0 ）
            那么必定存在无数组x,y
            使得 a*x + b*y = m
        所以，应用到这一题来就是看 z是不是gcd(x,y)的倍数
        同时本题还要要求x+y<=z


        ps: 辗转相除，温习一下。。
 */
class Solution {
public:
    bool canMeasureWater(int x, int y, int z) {
        return z==0 || y+x>=z && z%gcd(x,y)==0;
    }

    int gcd(int x, int y){
        return y==0? x: gcd(y, x%y);
    }
};
