/*
	题目描述：
		找出字符串中的第一个唯一字符 （这不是题目名吗
		
	题目分析：
		打表。。水题
*/

class Solution {
public:
    int firstUniqChar(string s) {
        int cnt[26]={0};
        for ( int i=0; i<s.size(); ++i )
            cnt[s[i]-'a']++;
        for ( int i=0; i<s.size(); ++i )
            if ( cnt[s[i]-'a']==1 )
                return i;
        return -1;
    }
};