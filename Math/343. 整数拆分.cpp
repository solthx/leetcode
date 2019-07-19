/*
    问题描述：
        给定一个正整数 n，将其拆分为至少两个正整数的和，并使这些整数的乘积最大化。 返回你可以获得的最大乘积。

        示例 1:

        输入: 2
        输出: 1
        解释: 2 = 1 + 1, 1 × 1 = 1。

    问题分析：
        Dp， dp[i]表示i分解后的最大乘积
        需要注意的是，
        状态转移公式为：
             dp[t] = max(dp[t],  max(j,dp[j]) * max(t-j,dp[t-j]));
        因为dp[2] = 1 * 1
        dp[i]有可能会小于i
        故在i和dp[i]中取最大
 */

class Solution {
public:
    int integerBreak(int n) {
        //dp[i]表示i分解后的最大乘积
        int dp[n+10];
        memset(dp,0,sizeof(dp));
        dp[0] = 0;
        dp[1] = dp[2] = 1;
        dp[3] = 2;
        if ( n<3 ) return dp[n];
        for ( int t=4; t<=n; ++t ){
            for ( int j=2; j<=t/2; ++j ){
                dp[t] = max(dp[t], max(j,dp[j])*max(t-j,dp[t-j]));
            }
        } 
        return dp[n];
    }
};