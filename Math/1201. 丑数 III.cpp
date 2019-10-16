/*
    问题描述:
        请你帮忙设计一个程序，用来找出第 n 个丑数。
        丑数是可以被 a 或 b 或 c 整除的 正整数。

        示例 1：

        输入：n = 3, a = 2, b = 3, c = 5
        输出：4
        解释：丑数序列为 2, 3, 4, 5, 6, 8, 9, 10... 其中第 3 个是 4。
        示例 2：

        输入：n = 4, a = 2, b = 3, c = 4
        输出：6
        解释：丑数序列为 2, 3, 4, 6, 8, 9, 12... 其中第 4 个是 6。
        示例 3：

        输入：n = 5, a = 2, b = 11, c = 13
        输出：10
        解释：丑数序列为 2, 4, 6, 8, 10, 11, 12, 13... 其中第 5 个是 10。
        示例 4：

        输入：n = 1000000000, a = 2, b = 217983653, c = 336916467
        输出：1999999984
         

        提示：

        1 <= n, a, b, c <= 10^9
        1 <= a * b * c <= 10^18
        本题结果在 [1, 2 * 10^9] 的范围内

    问题分析:
        这题感觉好难...一点都不medium...

        hint里的提示是, 用二分来做.

        f(x)返回小于x的所有丑数， 然后开始二分逼近..

        然后问题就变成了，如何计算小于x的丑数个数..
        
        给定一个k , 计算所有小于等于k ，且能被a或b或c整除的个数

        先来看这个情况:
            1. 给定一个k， 所有小于等于k, 且能被a整除的个数为 k/a 个
            2. 给定一个k, 所有小于等于k， 且能被b整除的个数为 k/b 个
        所以， 给定一个k, 所有小于等于k， 且能被a整除 或 能被b整除的个数为 k/a + k/b - k/lcm(a,b) 个 (lcm(a,b),为a和b的最小公倍数)

        这其实就是容斥原理的应用，

        同理可以应用到被 a, b, c 整除的情况， 即 
            k/a + k/b + k/c - k/lcm(a,b) - k/lcm(a,c) - k/lcm(b,c) + k/lcm(a,b,c)
        就是 “所有小于等于k ，且能被a或b或c整除的个数”

        ps: 对于lcm的实现，可以接触gcd来做， 即 a*b/gcd(a,b) = lcm(a,b)
        pps: lcm(a,b,c) = lcm( lcm(a,b), c )
        ppps: 这里的二分是一个逼近的过程，即 如果cnt是答案，
        那么在一段区间里， 小于等于k且能被a或b或c整除的个数 都会是cnt， 我们要找最小的那个 ! 
        因此，并不是找到就结束了， 而是要逼近到左边界
*/

class Solution {
public:
    int nthUglyNumber(int n, int a, int b, int c) {
         int l = 1, r = 2 * 1e9, mid;
         // 二分逼近
        while( l<=r ){
            mid = l + (r-l)/2;
            int cnt = f( mid,a,b,c );
            if ( cnt>=n ) r = mid-1; //逼近左边界
            else if ( cnt<n ) l = mid +1 ;
        }
        return l;
    }
    
    // f(x)返回小于x的所有丑数
    int f(int k, int a, int b, int c){
        return k/a + k/b + k/c - k/lcm(a,b) - k/lcm(b,c)- k/lcm(a,c) + k/lcm(lcm(a,b),c);
    }
    
    long long lcm( int a, int b ){
        return (long long)a*b / (long long)gcd(a,b);
    }

    int gcd(int a, int b){
        return a==0?b: gcd(b%a, a);
    }
};