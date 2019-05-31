/*
	题目描述：
		给你两个字符串 S 和 T, 判断他们是否只差一步编辑。
		编辑操作为：删除，插入，替换一个字符

		样例
		例1:

		输入: s = "aDb", t = "adb" 
		输出: true
		例2:

		输入: s = "ab", t = "ab" 
		输出: false
		解释:
		s=t ,所以他们不相差一次编辑的距离

	问题分析：
		字符串模拟，分类讨论就行。。
*/

class Solution {
public:
    /**
     * @param s: a string
     * @param t: a string
     * @return: true if they are both one edit distance apart or false
     */
    bool isOneEditDistance(string &s, string &t) {
        // write your code here
        if ( s.size()>t.size() )
            return isOneEditDistance(t,s);
        if ( t.size()-s.size()>1 ) return false;
        int j,i=0;
        // 删除（插入的情况可以变成删除）
        if ( t.size()-s.size()==1 ){
            while( i<s.size() && s[i]==t[i] ) i++;
            //
            j = i + 1; //删除当前元素
            while( i<s.size() && s[i]==t[j] ){
                i++;
                j++;
            }
            return j==t.size();
        }else{
            //替换的情况
            while( i<s.size() && s[i]==t[i] ) i++;
            if ( i<s.size() )
                t[i] = s[i];
            else return false; // 相等则距离为0 不符合
            while( i<s.size() && s[i]==t[i] ) i++;
            return i==s.size();
        }
        return false;
    }
};

