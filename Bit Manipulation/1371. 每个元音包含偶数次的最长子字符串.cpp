/*
    问题描述:
        给你一个字符串 s ，请你返回满足以下条件的最长子字符串的长度：
        每个元音字母，即 'a'，'e'，'i'，'o'，'u' ，在子字符串中都恰好出现了偶数次。

    问题分析：
        对于这种，“恰好出现了偶数次”，“恰好出现了奇数次” 的 关键字，如果能够用位运算进行压缩的话，可以考虑抑或来做。

        位运算 + 异或(^)的性质 => 恰好出现了偶数次

        state的1~5位，用于表示'a'，'e'，'i'，'o'，'u' 是出现了奇数次还是偶数次。
        

        state_i记录[0,i]的'a'，'e'，'i'，'o'，'u' 是出现了奇数次还是偶数次。

        如果state_i == state_j i<j
        
        那么(i,j]这一段一定是满足'a'，'e'，'i'，'o'，'u' 是出现了偶数次!
*/

class Solution {
public:
    int findTheLongestSubstring(string s) {
        vector<int> mp(128, -2);
        mp[0] = -1;
        int res=0, state = 0;
        for(int i=0; i<s.size(); ++i){
            if ( s[i]=='a' ) state ^= (1<<0);
            else if ( s[i]=='e' ) state ^= (1<<1);
            else if ( s[i]=='i' ) state ^= (1<<2);
            else if ( s[i]=='o' ) state ^= (1<<3);
            else if ( s[i]=='u' ) state ^= (1<<4);
            if (mp[state]<-1) mp[state]=i;
            if ( mp[state]>=-1 )
                res = max(res, i-mp[state]);
        }
        return res;
    }
};