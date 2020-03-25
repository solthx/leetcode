/*
    问题描述：
        「快乐前缀」是在原字符串中既是 非空 前缀也是后缀（不包括原字符串自身）的字符串。

        给你一个字符串 s，请你返回它的 最长快乐前缀。

        如果不存在满足题意的前缀，则返回一个空字符串。

        示例 1：

        输入：s = "level"
        输出："l"
        解释：不包括 s 自己，一共有 4 个前缀（"l", "le", "lev", "leve"）和 4 个后缀（"l", "el", "vel", "evel"）。最长的既是前缀也是后缀的字符串是 "l" 。
        示例 2：

        输入：s = "ababab"
        输出："abab"
        解释："abab" 是最长的既是前缀也是后缀的字符串。题目允许前后缀在原字符串中重叠。
        示例 3：

        输入：s = "leetcodeleet"
        输出："leet"
        示例 4：

        输入：s = "a"
        输出：""
        

        提示：

        1 <= s.length <= 10^5
        s 只含有小写英文字母
    
    问题分析:
        想要在常数时间内判断两个字符串是否相同，肯定是要对字符串做预处理的。

        方法一：滚动哈希
            滚动哈希用于在O(1)的时间内判断两个字符串是否相等。

            滚动哈希是将字符串编码成一个哈希数组，具体方法可以参考 #1316那题，
            链接：https://github.com/solthx/leetcode/blob/master/String/1316.%20%E4%B8%8D%E5%90%8C%E7%9A%84%E5%BE%AA%E7%8E%AF%E5%AD%90%E5%AD%97%E7%AC%A6%E4%B8%B2.md

            当我们能够用O(1)的时间判断两个字符串是否相等的时候，这题就能做啦～
        
        方法二: KMP
            构建成的kmp数组，
                a1 a2 a3 ... ai ... an

            如果存在一个字符串既是前缀，又是后缀的话，那么一定满足：
                a1 == a-k+1
                a2 == a-k+2
                ........
                ak == an
            
            因为next数组保存的是： 最长公共前缀
            因此， 如果真的存在的“快乐前缀”的话，
            那么构建的next数组一定满足：

                  next[a-k+1] == 1
                  next[a-k+2] == 2
                  ...............
                  next[a-k+1] == k

            因此，答案信息就保存在next[n]里面。
*/


// 方法一： 字符串滚动哈希，  写成了一个板子的形式。
# define ull unsigned long long 
# define BASE 37
class Solution {
public:
    // 记录哈希code，下标从1开始
    ull hs[100100]={0};
    ull offset[100100]={0};
    
    // 初始化，s是字符串
    void init(string s){
        offset[0]=1;
        for(int i=1; i<=s.size(); ++i){
            hs[i] = hs[i-1]*BASE + (s[i-1]-'a');
            offset[i] = offset[i-1]*BASE;
        }
    }    
    
    // 获取区间[l,r]的哈希编码, 哈希编码相同则表示字符串相同
    ull get_code(int l, int r){
        int len = r-l+1;
        return hs[r]-hs[l-1]*offset[len];
    }
    
    string longestPrefix(string s) {
        int n = s.size();
        init(s);
        for(int i=2; i<=s.size(); ++i){
            int len = n-i+1;
            //[0,len] [i,n]
            if ( get_code(1,len) == get_code(i,n) )
                return s.substr(i-1);
        }
        return "";
    }
};

// 方法二：kmp
class Solution2 {
public:
    string longestPrefix(string s) {
        int n = s.size();
        vector<int> idx = get_next(s);
        int d = idx.back();
        if (d<=0) return "";
        return s.substr(n-d);
    }

    // 尽管理解也不是很难
    // 但还是要考前背一背，喝前摇一摇
    vector<int> get_next( string pat ){
        int n=pat.size();
        vector<int> next(n+1,0);
        int i=0, j=-1;
        next[0] = -1;
        while( i<pat.size() ){
            if ( j<0 || pat[i]==pat[j] ){
                next[++i] = ++j;
            }else j=next[j];
        }
        return next;
    }
};

