/*
    题目描述：
        给定一个字符串 s，将 s 分割成一些子串，使每个子串都是回文串。

        返回符合要求的最少分割次数。

        示例:

        输入: "aab"
        输出: 1
        解释: 进行一次分割就可将 s 分割成 ["aa","b"] 这样两个回文子串。

    题目分析：
        一开始没想到用dp做。。看了题解才恍然大悟。。
        1. dp[i]代表前i的字符中，使得每个子串是回文串的最小分割次数
        2. 状态转移方程：
            到第i个字符时，
                j定义域为[0,i-1]，
                if:
                    j==0 && s[j]==s[i] && s[j+1,i-1]是回文
                then:
                    dp[i] = 0
                if:
                    j>0 && s[j]==s[i] && s[j+1,i-1]是回文
                then:
                    dp[i] = dp[j-1] + 1
            你应该看得懂了。。
 */


 class Solution {
public:
    int minCut(string s) {
        if ( s.size()<=1 )
            return 0;
        //dp[i] 为前i个中最少回文个数
        int len = s.size();
        int dp[len]; //dp[i]代表前i的字符中，使得每个子串是回文串的最小分割次数
        bool pal[len][len]; //pal[i][j]==true 表示s[i,j]是回文
        /*
            pal进行单独初始化， 也可以融进下面的循环中
            for ( int i=0; i<len; ++i ){
                pal[i][i] = true;
                for ( int j=0; j<len; ++j ){
                    if ( j<i && s[j]==s[i] && ( i-j<2 || pal[j+1][i-1]==true)  ){
                        pal[j][i] = true;
                    }
                    else if (i!=j) pal[j][i] = false;
                }
            }
        */
        
        dp[0] = 0;
        pal[0][0] = true;
        // 开始遍历
        for ( int i=1; i<len; ++i ){
            pal[i][i] = true;
            dp[i] = dp[i-1] + 1; //最坏的情况，就是和之前任何一个都组不成新回文
            for ( int j=0; j<i; ++j ){
                if ( s[j]==s[i] && ( i-j<2 || pal[j+1][i-1]==true)  ){
                    // 满足这个条件。pal[j][i]就是true
                    pal[j][i] = true;
                    if ( j==0 ) dp[i] = 0;
                    else dp[i] = min(dp[i], dp[j-1] + 1);
                }else pal[j][i] = false;
            }    
        }
        return dp[len-1];
    }
};