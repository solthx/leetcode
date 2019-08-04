/*
    问题描述:
        给定一个字符串 (s) 和一个字符模式 (p) ，实现一个支持 '?' 和 '*' 的通配符匹配。
        '?' 可以匹配任何单个字符。
        '*' 可以匹配任意字符串（包括空字符串）。
        两个字符串完全匹配才算匹配成功。

        说明:

        s 可能为空，且只包含从 a-z 的小写字母。
        p 可能为空，且只包含从 a-z 的小写字母，以及字符 ? 和 *。

        输入:
            s = "acdcb"
            p = "a*c?b"
        输出: 
            false

        输入:
            s = "acdcab"
            p = "ac?*b"
        输出: 
            true

    问题分析:
        类似 10.Regular Expression Matching 正则表达式匹配
        搞定了那题，这题基本也没什么难度。。
        同样的，dp[i][j]表示s的前i个字符能否被p的前j个字符匹配成功。

        状态转移为:
            if ( s[i-1]==p[j-1] || p[j-1]=='?' )
                dp[i][j] = dp[i-1][j-1];
            else if ( p[j-1]=='*' )
                dp[i][j] = (dp[i-1][j]||dp[i-1][j-1]||dp[i][j-1]);
            else dp[i][j] = false; 

        理解完第10题，这题的状态转移式也好理解了。。
        即考虑了 当前为p[j]是'*'，且dp[i][j]为真  的所有情况
 */

 class Solution {
public:
    bool isMatch(string s, string p) {
        int n = s.size(), m= p.size(); 
        if ( !n && !m ) return true;
        vector<vector<bool>> dp(n+1, vector<bool>(m+1,false) );
        dp[0][0] = true;
        for ( int j=1; j<=m; ++j )
            if ( p[j-1]=='*' ) dp[0][j] = dp[0][j-1];
        for ( int i=1; i<=n; ++i )
            for ( int j=1; j<=m; ++j ){
                if ( s[i-1]==p[j-1] || p[j-1]=='?' )
                    dp[i][j] = dp[i-1][j-1];
                else if ( p[j-1]=='*' )
                    dp[i][j] = (dp[i-1][j]||dp[i-1][j-1]||dp[i][j-1]);
                else dp[i][j] = false;
            }
        return dp[n][m];
    }
};