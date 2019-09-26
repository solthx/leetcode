/*
    问题描述:
        给定一个字符串，你的任务是计算这个字符串中有多少个回文子串。

        具有不同开始位置或结束位置的子串，即使是由相同的字符组成，也会被计为是不同的子串。

        示例 1:

        输入: "abc"
        输出: 3
        解释: 三个回文子串: "a", "b", "c".
        示例 2:

        输入: "aaa"
        输出: 6
        说明: 6个回文子串: "a", "a", "a", "aa", "aa", "aaa".
        注意:

        输入的字符串长度不会超过1000。

    问题分析:
        方法一：Dp
            dp[i][j]保存了 字符串s[i:j]中的回文子串的数量
            isPal[i][j]记录了 字符串[i:j]是否为回文串

            状态转移公式为：
                dp[i][j] = dp[i+1][j] + dp[i][j-1] - dp[i+1][j-1] 
                if  s[i]==s[j] && isPal[i+1][j-1] == true  :
                    dp[i][j]++
            
            这里解释一下上面的转移公式,
            
            dp[i][j] = [i,j-1]的回文个数 + [i+1,j]的回文个数 - [i+1, j-1]的回文个数
            
            此时dp[i][j]只是 区间[i,j]中，长为[1,len-1]的回文个数( len = j-i+1 )
            而如果 s[i]==s[j]，那么区间[i,j]中，长为len的回文个数为1， 
            
            因此dp[i][j]++

        方法二:
            中心扩散法:
                aba 的回文个数为 b , aba ， 2个
                abba 的回文个数为  bb, abba， 2个

                可以看出，这种回文个数是 从中心向两边扩散的次数
*/

class Solution2 {
public:
    int countSubstrings(string s) {
        int res = 0, n=s.size();
        for ( int i=0; i<n; ++i ){
            int l = i , r = i;
            while( l>=0 && r<n && s[l--]==s[r++] ) ++res;
            l=i; r = i+1;
            while( l>=0 && r<n && s[l--]==s[r++] ) ++res;
        }
        return res;
    }
};


class Solution1 {
public:
    int countSubstrings(string s) {
        // dp[i][j]表示这个区间内的回文子串数
        if ( s.size()<=1 ) return s.size();
        int n=s.size();
        vector<vector<bool>> isPal(n+3, vector<bool>(n+3,false));
        vector<vector<int>> dp( n+3, vector<int>(n+3, 0) );
        for ( int len=1; len<=n; ++len ){
            for ( int i=0; i<n; ++i ){
                int j = i+len-1;
                if ( j<n ){
                    if ( i!=j && s[i]==s[j] ){
                        if ( len>2 ){
                            dp[i][j] = dp[i][j-1] + dp[i+1][j] - dp[i+1][j-1]+ (isPal[i+1][j-1]) ;
                            isPal[i][j] =  isPal[i+1][j-1] ;
                        }else{
                            dp[i][j] = 3;
                            isPal[i][j] = true;
                        }
                    }else if ( i==j ){
                        dp[i][j] = 1;
                        isPal[i][j] = true;
                    }else dp[i][j] = dp[i][j-1] + dp[i+1][j] - dp[i+1][j-1];
                }
            }
        }
        return dp[0][n-1];
    }
};