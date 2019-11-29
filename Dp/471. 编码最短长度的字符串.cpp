/*
    问题描述:
        给定一个 非空 字符串，将其编码为具有最短长度的字符串。
        编码规则是：k[encoded_string]，其中在方括号 encoded_string 中的内容重复 k 次。
        
        注：
            k 为正整数且编码后的字符串不能为空或有额外的空格。
            你可以假定输入的字符串只包含小写的英文字母。字符串长度不超过 160。
            如果编码的过程不能使字符串缩短，则不要对其进行编码。如果有多种编码方式，返回任意一种即可。
         

        示例 1：
            输入： "aaa"
            输出： "aaa"
            解释： 无法将其编码为更短的字符串，因此不进行编码。
         

        示例 2：
            输入： "aaaaa"
            输出： "5[a]"
            解释： "5[a]" 比 "aaaaa" 短 1 个字符。
         

        示例 3：
            输入： "aaaaaaaaaa"
            输出： "10[a]"
            解释： "a9[a]" 或 "9[a]a" 都是合法的编码，和 "10[a]" 一样长度都为 5。
         

        示例 4：
            输入： "aabcaabcd"
            输出： "2[aabc]d"
            解释： "aabc" 出现两次，因此一种答案可以是 "2[aabc]d"。
         

        示例 5：
            输入： "abbbabbbcabbbabbbc"
            输出： "2[2[abbb]c]"
            解释： "abbbabbbc" 出现两次，但是 "abbbabbbc" 可以编码为 "2[abbb]c"，因此一种答案可以是 "2[2[abbb]c]"。
         
    问题分析：
        这是一道很棒的区间dp的题目； 

        在解决本题之前，先来看这样一个问题：
        
        问题一:
            给一个字符串s, 判断s是否由多个字符串重复组成.
                例如: 
                    s = "abcabc"
                    s就是由"abc"重复组成
                
                    s = "abcde"
                    s就不是由多个字符串重复组成
            
                如果一个字符串是由多个字符串重复组成的话，

                那么一定存在一个 字符串前缀 == 字符串后缀 

                例如 "abcabc" ，那么前缀就是“abc”,后缀也是"abc"
                “abababab”， 那么前缀就是“ab” ， 后缀就是“ab”
        
        问题二:
            在问题一的基础上，如果s是由多个字符串重复组成的话，
            那么找出最短的那个字符串，即重复出现次数最多的那个字符串.

            例如 s = "abababab", 应该返回ab而不是abab

            一个简单的解决方法就是:
                在字符串 s+s 中 从第二个字符开始匹配s ，得到位置idx

                如果idx < s.size() 就说明一定存在问题一里的那个前缀后缀，
                那么就说明s里一定存在重复的字符串。

                然后这里还用了点小贪心，就是匹配到的最小idx( idx不等于0 )，那个位置之前的字符串就都是 那个最短的重复字符串.

                举个例子：
                    s = "abababab"

                    sps = s + s = "abababababababab"
                    
                    在sps里面匹配abababab, 最小的匹配位置idx为2，
                    因此，2之前的字符串，即sps.substr(0,2) 就是最短的重复字符串了. 

        看完上面的两个问题以后，就知道该怎么求一个字符串内的最多重复出现的字符串了，

        接下来就好办了， 直接用区间dp

        因为题目要返回字符串，所以dp[i][j]用来保存区间[i,j]内能编码成的最短字符串.
        最终返回dp[0][n-1]就行了.

        状态转移：
            字符串变的更短无非是两种情况：
                1. 字符串重新编码, 即： aaaaa->5[a]
                2. dp[i][j].size() > dp[i][k].size() + dp[k+1][j].size()
            
            然后就好办了：
                第一种情况:
                    得到[i,j]的时候，先看能不能对str[i,j]这段字符串进行重新编码 （利用上面的方法）
                
                第二种情况:
                    更简单了，直接再来一个循环， k属于[i,j] ，遍历每一个情况，来update
                    
                    if ( dp[i][k].size()+dp[k+1][j].size()<dp[i][j].size() )
                        dp[i][j] = dp[i][k] + dp[k+1][j]; 
            ps：
                还有一个优化就是: 如果第一个情况发生了，那么第二种情况一定不会发生update. 因此，一旦进入了第一种情况进行更新，那么直接continue就行了.    

        呀～ 真是道好题！ 
*/

class Solution {
public:
    string encode(string s) {
        int n=s.size();
        if ( n<=1 ) return s;
        vector<vector<string>> dp( 200, vector<string>(200, "") );
        for ( int len=1; len<=n; ++len ){
            for ( int i=0; i<=n-len; ++i ){
                if ( len==1 ){ 
                    dp[i][i] = s[i];
                    continue;
                }
                int j = i+len-1;
                dp[i][j] = s.substr(i,len);
                string pre = dp[i][j];
                int pos = (pre+pre).find( pre,1 );
                if ( pos<pre.size() ){
                    string after_encode = to_string((pre.size()/pos))+"["+dp[i][i+pos-1]+"]";
                    if ( after_encode.size()<dp[i][j].size() )
                        dp[i][j] = after_encode; 
                    continue;
                }
                for ( int k=i; k<=j; ++k ){
                    if ( dp[i][k].size()+dp[k+1][j].size()<dp[i][j].size() )
                        dp[i][j] = dp[i][k] + dp[k+1][j];    
                }
            }
        }
        return dp[0][n-1];
    }
};

