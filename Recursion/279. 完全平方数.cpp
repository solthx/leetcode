/*
    问题描述：
        给定正整数 n，找到若干个完全平方数（比如 1, 4, 9, 16, ...）
        使得它们的和等于 n。你需要让组成和的完全平方数的个数最少。
        示例 1:

        输入: n = 12
        输出: 3 
        解释: 12 = 4 + 4 + 4.
        示例 2:

        输入: n = 13
        输出: 2
        解释: 13 = 4 + 9.

    问题分析：
        动态规划，
        dp[i]表示i的最少完全平方数
        
        1. O(N^2)的Dp，超时。。
            dp初始化为INT_MAX
            dp[0] = 0 ， dp[1]=1
            for  i : 1->n 
                if ( 是平方数 )
                    dp[i]=1；
                else 
                    for j : 1->i
                        if ( dp[j]<INT_MAX && dp[i-j]<INT_MAX )
                                dp[i] = min(dp[i],dp[j]+dp[i-j]);
        
        2. 对情况1进行优化，
           显然在里面的那个循环做了太多的无用操作，
           反向Dp不行，可以换个思路，试试正向的Dp ,
           每个数都一定可以分出一个 平方数+另外一个数
           而平方数是1，它的存在一定是最小的，
           所以只要让dp[另外一个数]最小就行了，
           这样就有了下面的递推
            for (int i = 0; i <= n; ++i) 
                for (int j = 1; i + j * j <= n; ++j) 
                    dp[i + j * j] = min(dp[i + j * j], dp[i] + 1);
            
        3. 进一步优化，
            百度后知道了一个数学定理：
                任何数都可以由4个平方数组成。
            因此，dp[i]的取值范围为 1-4，
            并且如果n%4==0， 那么dp[n]==dp[n/4]
            可以用来缩小n
 */

class Solution {
public:
    int numSquares(int n) {
        while (n % 4 == 0) n /= 4;
        int dp[n+1];
        for ( int i=0; i<=n; ++i ) dp[i]=INT_MAX;
        dp[0] = 0;
        for ( int i=0; i<=n; ++i ){
            for ( int j=1; i + j*j<=n ; ++j )
                dp[i+j*j] = min(dp[i]+1, dp[i+j*j]);
        }
        return dp[n];
    }
};