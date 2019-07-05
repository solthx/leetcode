/*
    题目描述：
       找到给定字符串（由小写字符组成）中的最长子串 T ， 要求 T 中的每一字符出现次数都不少于 k 。输出 T 的长度。
        
        示例 1:
        输入:
        s = "aaabb", k = 3
        输出:
        3
        最长子串为 "aaa" ，其中 'a' 重复了 3 次。
        
        示例 2:
        输入:
        s = "ababbc", k = 2
        输出:
        5
        最长子串为 "ababb" ，其中 'a' 重复了 2 次， 'b' 重复了 3 次。

    问题分析：
        首先遍历S，得到一个非法/合法数组book, 出现次数小于k次的直接判死刑了。。
        
        递归返回情况： 所有元素的出现次数都大于等于k次
        再次遍历S，当遇到非法字符的时候（出现次数小于k次的字符），就以非法字符的位置作为分割点
        递归的判断两边的情况，来找出最长的合法串。

        例如： 
            ababca k=2
            在c处分成了 abab和a 
            最长为4

            abcabcab k=3
            在c成分成了 ab ab ab
            不存在

            子串通过调用当前函数来判断
 */

 class Solution {
public:
    int longestSubstring(string s, int k) {
        if ( k<=1 ) return s.size();
        bool book[128]={false};  // 判断合法/非法数组
        int cnt[128]={0};   
        int tmp[128]={0};
        int pd=0;   //用来记录非法字符个数
        bool flag=false; //用来记录是否存在合法字符
        for ( auto c:s ){
            if ( cnt[c]==0 ) pd++; //cnt[c]为0，说明首次出现，非法字符个数+1
            if ( ++cnt[c] == k ) { //cnt[c]到达k说明字符c合法，非法字符数-1 
                flag=true;
                book[c] = true;
                pd--;
            }
        }
        //非法字符数为0，且存在合法字符，则返回当前长度
        //就是所有元素的出现次数都大于等于k次
        if ( pd==0 ) return  flag?s.size():0;
        int left=0, right=0, res=0;
        int mini=s.size();
        // 维护一个window， left和right就是被非法字符分割得到的子串
        while( right<s.size() ){
            //得到下一个window（子串）
            while( left<s.size() && !book[s[left]] )
                ++left;
            right = left;
            while( right<s.size() && book[s[right]] ){
                ++right;
            }
            //更新最长
            res = max( res, longestSubstring( s.substr(left, right-left) ,k ));
            //更新左边界
            left = right;
        }
        return res;
    }
    
};