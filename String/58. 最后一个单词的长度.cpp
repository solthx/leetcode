/*
	问题描述：
		返回字符串中最后一个单词的长度
		
	题目分析：
		从后向前遍历就是。。记得过滤空格。。水题
*/

class Solution {
public:
    int lengthOfLastWord(string s) {
        int cnt=0,i=s.size()-1;
        while( i>=0 && s[i]==' ' )
            --i;
        while( i>=0 && s[i]!=' ' ){
            i--;
            cnt++;
        }
        return cnt;
    }
};