/*
    问题描述:
        有台奇怪的打印机有以下两个特殊要求：
        打印机每次只能打印同一个字符序列。
        每次可以在任意起始和结束位置打印新字符，并且会覆盖掉原来已有的字符。
        给定一个只包含小写英文字母的字符串，你的任务是计算这个打印机打印它需要的最少次数。

        示例 1:
            输入: "aaabbb"
            输出: 2
            解释: 首先打印 "aaa" 然后打印 "bbb"。

        示例 2:
            输入: "aba"
            输出: 2
            解释: 首先打印 "aaa" 然后在第二个位置打印 "b" 覆盖掉原来的字符 'a'。
        
        提示: 输入字符串的长度不会超过 100。

    问题分析:
        本题很明显使用区间dp来做.. 难点主要在于状态转移的推导... 

        dp[i][j]保存了 在打印区间[i,j]的字符，需要的最少次数.

        这题推了一个小时..不停的debug 最后发现着力点错了.. 
        
        看了题解才恍然大雾的。。 

        二刷的时候重新推把.. 看完题解以后是理解了..但也没难度了.. 因为难度主要在于独立思考推导的过程..

        建议二刷.. 这道题的重要性不在于ac，而在于独立思考的并ac掉的这个过程

        给个提示吧: 从简单的例子入手，着手分析..



        答案:

            dp[i][j] = min( dp[i+1][j], dp[i][j-1] ) + 1;

            for k from i to j:
                if s[i]==s[k]:
                    dp[i][j] = min( dp[i][j], dp[i+1][k-1] + dp[k][j] );

        参考文章: https://www.cnblogs.com/grandyang/p/8319913.html
        

*/


class Solution {
public:
    int strangePrinter(string s) {
        // O(N^3)试试
        if ( s.size()==0 ) return 0;
        int dp[101][101]={0}; // dp[i][j]记录了打印s[i:j]所需要的最少次数
        int n = s.size();
        for ( int i=0; i<n; ++i )
            dp[i][i] = 1;
        for ( int len = 2; len<=n; ++len ){
            for ( int i=0; i<=n-len; ++i ){
                int j = i+len-1;
                if ( len==2 ){
                    dp[i][j] = 1 + (s[i]!=s[j]);
                    continue;
                }
                dp[i][j] = min( dp[i+1][j], dp[i][j-1] )+1;
                for ( int k=i+1; k<=j; ++k ){
                    if ( s[k]==s[i] ){
                        dp[i][j] = min( dp[i][j], dp[i+1][k-1]+dp[k][j] );
                    }
                }
            }
        }
        return dp[0][n-1];
    }
};