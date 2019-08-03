/*
    问题分析:
        一条包含字母 A-Z 的消息通过以下方式进行了编码：
        'A' -> 1
        'B' -> 2
        ...
        'Z' -> 26
        给定一个只包含数字的非空字符串，请计算解码方法的总数。

        示例 1:
        输入: "12"
        输出: 2
        解释: 它可以解码为 "AB"（1 2）或者 "L"（12）。

    问题分析：
        本题是属于看完题目后秒有思路，然后在细节上坑人的题目。

        dp[i]表示前i个字符编码方法的总数。
        
        状态转移的时候主要讨论当前数字字符和前一个数字字符。

            前一个数字字符  当前数字字符
                为0           不为0
                为0             为0
               不为0          不为0
               不为0            为0
        讨论这四种情况就行了，状态转移很好写，也很好理解，就不多赘述了。
 */

 class Solution {
public:
    int numDecodings(string s) {
        if ( s.size()==0 || s[0]=='0' ) return 0;
        int n=s.size(), two;
        vector<int> dp(n+1, 0);
        dp[0] = dp[1] = 1;
        
        for ( int i=2; i<=n; ++i ){
            if ( s[i-1]!='0' ){
                // 当前字符不是0
                if( s[i-2]!='0' ){
                    // 当前字符不是0， 前一个字符不是0
                    two = stoi(s.substr(i-2,2));
                    if ( two>0 && two<27 )
                        dp[i] = dp[i-1] + dp[i-2];
                    else dp[i] = dp[i-1];
                }else{
                    // 当前字符不是0， 前一个字符是0
                    dp[i] = dp[i-1];
                }
            }else{
                // 当前字符是0
                if ( s[i-2]!='0' ){
                    // 前一个字符不是0
                    if ( s[i-2]>'2' ) return 0;
                    else dp[i] = dp[i-2];
                }else return 0;
            }
        }
        return dp[n];
    }
};