/*
    问题描述:
        给出一个字符串 s 和一个整数 k，请你帮忙判断这个字符串是不是一个「K 回文」。
        所谓「K 回文」：如果可以通过从字符串中删去最多 k 个字符将其转换为回文，那么这个字符串就是一个「K 回文」。
        示例：

        输入：s = "abcdeca", k = 2
        输出：true
        解释：删除字符 “b” 和 “e”。
         

        提示：

        1 <= s.length <= 1000
        s 中只含有小写英文字母
        1 <= k <= s.length

    问题分析:
        动态规划, 先求最长回文子序列长度len , 然后返回 n-len<=k

        dp[i][j] 表示区间[i,j]的最长回文长度.

        转移公式:
            if ( s[i]==s[j] )
                dp[i][j] = dp[i+1][j-1] + 2
            else dp[i][j] = max( dp[i][j-1], dp[i+1][j] )
*/

class Solution {
public:
    bool isValidPalindrome(string s, int k) {
        int n = s.size();
        vector<vector<int>> dp( n+1, vector<int>(n+1,0) );
        for ( int len=1; len<=n; ++len )
            for ( int i=1; i+len-1<=n; ++i ){
                if ( len==1 ){
                    dp[i][i] = 1;
                    continue;
                }
                int j = i+len-1;
                if ( s[i-1]==s[j-1] ) dp[i][j] = dp[i+1][j-1] + 2;
                else dp[i][j] = max( dp[i][j-1], dp[i+1][j] );
            }
        return n-dp[1][n]<=k;
    }
};