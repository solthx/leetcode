/*
    问题描述:
        给你一个非空的字符串 s 和一个整数 k，你要将这个字符串中的字母进行重新排列，使得重排后的字符串中相同字母的位置间隔距离至少为 k。
        所有输入的字符串都由小写字母组成，如果找不到距离至少为 k 的重排结果，请返回一个空字符串 ""。
        
        示例 1：
            输入: s = "aabbcc", k = 3
            输出: "abcabc" 
            解释: 相同的字母在新的字符串中间隔至少 3 个单位距离。
        
        示例 2:
            输入: s = "aaabc", k = 3
            输出: "" 
            解释: 没有办法找到可能的重排结果。
        
        示例 3:
            输入: s = "aaadbbcc", k = 2
            输出: "abacabcd"
            解释: 相同的字母在新的字符串中间隔至少 2 个单位距离。

    问题分析:
        用hashmap来记录每个字符出现次数，然后打包成pair，以出现次数为比较的值，存入一个最大堆中,
        然后按照滑动窗口的想法，窗口大小为min( k, len ), len为剩下待存入 string res的字符个数,
        
        这里有个坑，就是在写堆的compare函数的时候，不仅仅要按出现次数排序，当出现次数相等时，也要对字符排序，
        这样才能保证在两个窗口之间，相同的元素的间隔保持在k

        例如aabbc,k=2
        如果不按字符排序, 那么:
                        第一个窗口k  ab
                        第二个窗口k  ba //因为此时 a和b和c的剩余可以用的次数都是1
                        这样拼起来就是 abba 显然不对, 错因就是，对于相同的频率，第一个窗口优先选了a，而第二个优先选了b, 所以也要对字符排序！
*/

class Solution {
public:
    string rearrangeString(string s, int k) {
        int n = s.size();
        if ( !k || s.size()==1 ) return s;
        auto cmp = [](pair<char,int>&a, pair<char,int>& b){
            if ( a.second!=b.second )
                return a.second<b.second;
            // 别忘对字符排序
            return a.first>b.first;
        };
        priority_queue<pair<char,int>, vector<pair<char,int>>, decltype(cmp)> q(cmp);
        pair<char, int> tmp;
        unordered_map<char,int> mp; 
        string res="";
        for ( auto c:s )
          ++mp[c];
        for ( auto e:mp ){
          q.push(e);
        }
        while( q.size()>0 ){
            //len为窗口大小
            int len = min( k, n ); 
            vector<pair<char, int>> p;
            for ( int i=0; i<len; ++i ){
                if ( q.size()==0 ) return "";
                tmp = q.top();
                q.pop();
                res += tmp.first;
                if ( --tmp.second>0 ) p.push_back(tmp);
                // n为剩余需要装入res中的字符
                --n;
            }
            for ( auto &e:p ) q.push(e);
        }
        return res;
    }
};