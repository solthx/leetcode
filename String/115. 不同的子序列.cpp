/*
    问题描述：
        给定一个字符串 S 和一个字符串 T，计算在 S 的子序列中 T 出现的个数。
        一个字符串的一个子序列是指，通过删除一些（也可以不删除）字符且不干扰剩余字符相对位置所组成的新字符串。（
        例如，"ACE" 是 "ABCDE" 的一个子序列，而 "AEC" 不是）

        示例 1:
        输入: S = "babgbag", T = "bag"
        输出: 5
        babgbag
        ^^ ^
        babgbag
        ^^    ^
        babgbag
        ^    ^^
        babgbag
        ^  ^^
        babgbag
            ^^^
    问题分析：
        DFS会超时，因为有许多重复的计算，故使用动态规划来保存状态，空间换时间。

        dp[i][j]表示 “s的前i个字符中 包含了 t的前j个字符 的个数”
        最终输出dp[s.size()][t.size()]就是结果

        状态转移：
            //状态转移怎么来的，用上面的例子，画一画就知道了，不是很难。
            if ( s[i] == t[j] )
                dp[i][j] = dp[i-1][j-1] + dp[i-1][j];
            else 
                dp[i][j] = dp[i-1][j]; 
 */

 class Solution {
public:
    int numDistinct(string s, string t) {
        int lens=s.size(), lent=t.size();
        if ( lens<lent ) return 0;
        long long dp[lens+1][lent+1]; //dp[i][j]是s前i个元素中有t前j个字符的情况个数
        
        // 全初始化为0
        memset(dp,0,sizeof(dp));
        
        // 把dp[i][1]的情况做好
        for ( int i=0; i<lens; ++i )
            if ( s[i]==t[0] )
                dp[i+1][1] = dp[i][1] + 1;
            else dp[i+1][1] = dp[i][1];
        
        // 更新得到dp[i][j]
        dp[0][0] = 1;
        for ( int j=2; j<=lent; ++j ){
            // 要求i>=j 
            // 每次从dp[j][j]开始，因为i<j的时候，不考虑
            // 处理第一个情况
            dp[j][j] =  ((dp[j-2][j-2]) * (s[j-1]==t[j-1]));
            for ( int i=j; i<=s.size(); ++i ){
                if ( s[i-1]==t[j-1] )
                    dp[i][j] = dp[i-1][j]+dp[i-1][j-1];
                else dp[i][j] = dp[i-1][j];
            }    
        }
        return dp[lens][lent];
    }
};

// 简洁版
