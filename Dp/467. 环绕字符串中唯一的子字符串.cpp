/*
    问题描述:   
        把字符串 s 看作是“abcdefghijklmnopqrstuvwxyz”的无限环绕字符串，所以 s 看起来是这样的："...zabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcd....". 
        现在我们有了另一个字符串 p 。你需要的是找出 s 中有多少个唯一的 p 的非空子串，尤其是当你的输入是字符串 p ，你需要输出字符串 s 中 p 的不同的非空子串的数目。 
        注意: p 仅由小写的英文字母组成，p 的大小可能超过 10000。

        示例 1:
            输入: "a"
            输出: 1
            解释: 字符串 S 中只有一个"a"子字符。
         
        示例 2:
            输入: "cac"
            输出: 2
            解释: 字符串 S 中的字符串“cac”只有两个子串“a”、“c”。.
         
        示例 3:
            输入: "zab"
            输出: 6
            解释: 在字符串 S 中有六个子串“z”、“a”、“b”、“za”、“ab”、“zab”。.

    问题分析：
        题目其实就是想让我们求所有  “不重复的 连续字典序的所有子串个数” 
        例如 abcdeeef
            abcd和ef就是连续字典序，
            abcd-> a,b,c,d,ab,ac,ad,abc,abd,abcd
                -> {a},{ab,b},{abc,bc,c},{abcd,bcd,cd,d}
            
            ef-> e,f,ef
              -> {e},{f,ef}

        所以，我们只要将以p的第i个位置的字母为结尾的连续字典序个数加起来，就是 我们想要的连续字典序的所有子串个数

        但是 cac -> {c},{a},{c}
            会有重复的c，去重方法就是，不再以p的第i个位置的字母为结尾的连续字典序个数，
            而是变成以字母p[i]为结尾的连续字典序个数，设其为 cnt[ p[i]-'a' ]

            在多次更新cnt[ p[i] - 'a' ]的时候， 我们取最大的那个。

        状态:
            dp[i] 以p中第i个位置的元素为结尾的，字典序个数。
            
            if ( p[i]-p[i-1]==1 || p[i]=='a' && p[i-1]=='z )
                p[i] = p[i-1]+1
            else p[i] = 1 

            cnt[ p[i] - 'a' ] 为以 字母p[i]为结尾的 连续字典序个数
            
            cnt[ p[i] - 'a' ] = max( cnt[ p[i] - 'a' ], dp[i] )
*/
class Solution {
public:
    int findSubstringInWraproundString(string p) {
        int n = p.size();
        if ( !n ) return 0;
        vector<int> dp( n, 0 );
        vector<int> cnt( 26,0 );
        for ( int i=0; i<n; ++i ){
            if ( i>0 && (p[i]==p[i-1]+1 || (p[i]=='a' && p[i-1]=='z') ) )
                dp[i] = dp[i-1] + 1;        
            else dp[i] = 1;
            cnt[p[i]-'a'] = max( cnt[p[i]-'a'], dp[i] );
        }
        //对cnt求和
        return accumulate(cnt.begin(), cnt.end(),0);
    }
    
};