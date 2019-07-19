/*
    问题描述：
        给定一个整数 n，返回 n! 结果尾数中零的数量。

        示例 1:

        输入: 3
        输出: 0
        解释: 3! = 6, 尾数中没有零。

    问题分析：
        即看公倍数为5，25，125， 。。的个数
        一个5将提供一个0，
        25提供2个0， （5*5）
        125提供3个0 （5*5*5）

        5，25， 125，。。。遍历所以情况，
        看n里有多少个
 */
 class Solution {
public:
    int trailingZeroes(int n) {
        int res=0;
        int t=1, m,mi=1;
        for ( long long t=5; t<=n; t*=5 ){
            res += (n/t ) ; //mi=幂
        }
        return res;
    }
};