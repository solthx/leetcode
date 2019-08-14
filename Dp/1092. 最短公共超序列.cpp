/*
    问题描述:
        给出两个字符串 str1 和 str2，返回同时以 str1 和 str2 作为子序列的最短字符串。如果答案不止一个，则可以返回满足条件的任意一个答案。
        （如果从字符串 T 中删除一些字符（也可能不删除，并且选出的这些字符可以位于 T 中的 任意位置），可以得到字符串 S，那么 S 就是 T 的子序列）

        示例：
        输入：str1 = "abac", str2 = "cab"
        输出："cabac"
        解释：
        str1 = "abac" 是 "cabac" 的一个子串，因为我们可以删去 "cabac" 的第一个 "c"得到 "abac"。 
        str2 = "cab" 是 "cabac" 的一个子串，因为我们可以删去 "cabac" 末尾的 "ac" 得到 "cab"。
        最终我们给出的答案是满足上述属性的最短字符串。

        提示：
            1 <= str1.length, str2.length <= 1000
            str1 和 str2 都由小写英文字母组成。

    问题分析:
        这题一开始看错了。。以为是构造最短公共超子串， 但其实是子序列！！
        难度一下就不一样了。

        思路是: 
            1. 求出最长公共子序列
            2. 构造公共子序列
            3. 根据公共子序列，来构造最短公共超序列
        
        第一步和第二步如果改成用string来做的话，会TLE。。
        
        1. 先求出第一步的dp数组
        2. 第二步第三步一起做了, 正向做了结果TLE，反向做会快很多
           
            初始 i=str1.size()-1,  j=str2.size()-1

            string res;

            2.1 如果 str1[i]==str2[j] 说明这个字符是公共字符:
                    res =  str1[i] + res;
                    --i; --j;
            2.2 如果 dp[i-1][j]==dp[i][j] 说明str1[i]这个字符是str1有的但str2没有的
                    res =   str1[i] + res;
                    --i;
            2.3 如果 dp[i][j-1]==dp[i][j] 说明str2[j]这个字符是str1有的但str2没有的
                    res = str2[j] + res;
                    --j;
            2.4 如果 i<=0  说明str2剩下的都是str1没有的
                    res = str2.substr(0,j) + res;
            2.5 如果 j<=0  说明str1剩下的都是str2没有的
                    res = str1.substr(0,i) + res;

        完成上面的逻辑，就构成的res就是最短公共超序列
*/

class Solution {
public:
    string shortestCommonSupersequence(string str1, string str2) {
        // str1比str2长
        if ( str1.size()<str2.size() ) return shortestCommonSupersequence(str2, str1);
        int n = str1.size(), m=str2.size();
        vector<vector<int>> dp( n+1, vector<int>(m+1, 0) );
        for ( int i=1; i<=n; ++i ){
            for ( int j=1; j<=m; ++j )
                if ( str1[i-1]==str2[j-1] )
                    dp[i][j] = dp[i-1][j-1] + 1;
                else
                    dp[i][j] = max( dp[i-1][j], dp[i][j-1] );
            
        }
        string res;
        int i = n, j=m;
        while( i>0 && j>0 ){
            if ( str1[i-1]==str2[j-1] ){
                res = str1[i-1] + res;
                --i;--j;
            }else if ( dp[i][j-1]==dp[i][j] ){
                while( j>0 && dp[i][j-1]==dp[i][j] )
                    res = str2[--j] + res;
                
            }
            else if ( dp[i-1][j]==dp[i][j] )
                while( i>0 && dp[i-1][j]==dp[i][j] )
                    res = str1[--i] + res;
        }
        if ( i>0 ){
            res = str1.substr(0,i) + res;
        }else if ( j>0 )
            res = str2.substr(0,j) + res;
        return res;
    }
};