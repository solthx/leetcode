/*
    问题分析:
        如果字符串中的所有字符都相同，那么这个字符串是单字符重复的字符串。
        给你一个字符串 text，你只能交换其中两个字符一次或者什么都不做，然后得到一些单字符重复的子串。返回其中最长的子串的长度。

        示例 1：
        输入：text = "ababa"
        输出：3

        示例 2：
        输入：text = "aaabaaa"
        输出：6
        
        示例 3：
        输入：text = "aaabbaaa"
        输出：4

        示例 4：
        输入：text = "aaaaa"
        输出：5

        示例 5：
        输入：text = "abcdef"
        输出：1

    问题分析:
        分为四种情况:
            aabaabbb 间隔为1 ，两侧没有可补充的连续字符(这里连续字符是a)
            aabaabba 间隔为1 ， 两侧存在可补充的连续字符
            aaabbbb  间隔大于1， 且两侧不存在可补充的连续字符
            aaabba   间隔大于1，且两侧存在可补充的连续字符

        难点就在逻辑实现上（其实也不难

        就题论题，只要在逻辑上是正确的，且能实现的，就直接做。。

 */

class Solution {
public:
    int maxRepOpt1(string text) {
        if ( text.size()<=1 ) return text.size();
        if ( text.size()==2 ) return 1+text[0]==text[1];
        int n = text.size();
        bool flag=false;
        int res=1;
        int i=1;
        while( i<n ){
            // 过滤左相同
            while( i<n && text[i]==text[i-1] ) ++i;
            if (i<n) flag=true;
            if ( i+1<n && text[i-1]==text[i+1] ){
                // 间隔等于1
                // aabaa 和 aababaa 的情况 
                int cnt = 0;
                char c = text[i-1];
                int l = i-1, r=i+1;
                while( l>=0 && text[l]==c ){
                    --l;
                    ++cnt;
                }
                while( r<n && text[r]==c ){
                    ++r;
                    ++cnt;
                }
                while( l>=0 && text[l]!=c ){
                    --l;
                }
                while( r<n && text[r]!=c ){
                    ++r;
                }
                // 存在补充的连续元素
                if ( l>=0 || r<n ) cnt++;
                res = max(res, cnt);
            }else if ( i+1<n && text[i-1]!=text[i+1] ){
                // 间隔大于1 
                // aaabbccd 和 aaabba的情况
                int cnt=0;
                char c = text[i-1];
                int l = i-1, r=i;
                while( l>=0 && text[l]==c ){
                    ++cnt;
                    --l;
                }
                
                while( l>=0 && text[l]!=c ){
                    --l;
                }
                while( r<n && text[r]!=c ){
                    ++r;
                }
                //存在连续区间外的连续元素
                if ( l>=0 ||r<n ) cnt++;
                res = max(res, cnt);
            }
            ++i;
        }
        return flag?res:text.size();
    }
};