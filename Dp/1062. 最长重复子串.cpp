/*
    问题描述:
        给定字符串 S，找出最长重复子串的长度。如果不存在重复子串就返回 0。
            
            示例 1：
            输入："abcd"
            输出：0
            解释：没有重复子串。
            
            示例 2：
            输入："abbaba"
            输出：2
            解释：最长的重复子串为 "ab" 和 "ba"，每个出现 2 次。
            
            示例 3：
            输入："aabcaabdaab"
            输出：3
            解释：最长的重复子串为 "aab"，出现 3 次。
            
            示例 4：
            输入："aaaaa"
            输出：4
            解释：最长的重复子串为 "aaaa"，出现 2 次。
             
            提示：
                字符串 S 仅包含从 'a' 到 'z' 的小写英文字母。
                1 <= S.length <= 1500

    问题分析：
        因为是找最长重复的子串，也就是在同一个串的不同位置找到两个相同的子串，
        所以可以用二维dp来做
        dp[i][j]保存  满足"分别以s[i]和s[j]结尾，且i!=j，且这个子串相同" 这样子的
        子串的最长长度.

        状态转移：
            if ( s[i]==s[j] )
                dp[i][j] = dp[i-1][j-1] + 1
        
        ps:
            两个字符串，重复，等等类似这种 遍历一遍不能解决问题的字符串问题，
            可以考虑二维dp来做。
*/
class Solution {
public:
    int longestRepeatingSubstring(string S) {
        int n = S.size();
        int res= 0;
        vector<vector<int>> dp(n+1, vector<int>(n+1,0));
        for ( int i=1; i<=n; ++i )
            for ( int j=i+1; j<=n; ++j )
                if ( S[i-1]==S[j-1] ){
                    dp[i][j] = dp[i-1][j-1] + 1;
                    res = max( res, dp[i][j] );
                }
        return res;
    }
};