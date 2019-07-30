/*
    问题描述：
        给定三个字符串 s1, s2, s3, 验证 s3 是否是由 s1 和 s2 交错组成的。

        示例 1:

        输入: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
        输出: true
        示例 2:

        输入: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc"
        输出: false

    问题分析：
        dp[i][j] 记录了 s1的前i个字符和s2的前j能否交错组成s3的前i+j个字符

        状态转移公式:
            如果第i+j个字符和s1的第i个字符一样:
                dp[i][j] = dp[i-1][j];
            如果第i+j个字符和s2的第j个字符一样:
                dp[i][j] = dp[i][j-1];
            如果第i+j个字符既不..又不..:
                dp[i][j] = false
        
        状态转移公式：
            dp[i][j] = ( s3[i+j]==s1[i] && dp[i-1][j] ) || ( s3[i+j]==s2[j] && dp[i][j-1] ) 

        本题初始化也是个难点！ 
        按照题目要求来调整初始数组。
 */

 class Solution {
public:
    bool isInterleave(string &s1, string &s2, string &s3) {
        int n = s1.size(), m=s2.size();
        if ( n+m!=s3.size() ) return false;
        vector<vector<bool>> dp(n+1, vector<bool>(m+1, false));
        //dp[i][j] 表示 s1的前i个 和s2的前j个 是否能够交错组成s3的前i+j个
        dp[0][0] = true;
        for ( int i=1; i<=n; i++ )
            if ( s1[i-1]==s3[i-1] ) dp[i][0] = dp[i-1][0];
        for ( int i=1; i<=m; i++ )
            if ( s2[i-1]==s3[i-1] ) dp[0][i] = dp[0][i-1];
        for ( int i=1; i<=n; ++i )
            for ( int j=1; j<=m; ++j ){
                dp[i][j] = ( s3[i+j-1]==s1[i-1] && dp[i-1][j] ) || (s3[i+j-1]==s2[j-1] && dp[i][j-1] );
            }
        return dp[n][m];
    }
};