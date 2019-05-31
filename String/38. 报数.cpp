/*
	问题描述：
		报数序列是一个整数序列，按照其中的整数的顺序进行报数，得到下一个数。其前五项如下：

		1.     1
		2.     11
		3.     21
		4.     1211
		5.     111221
		1 被读作  "one 1"  ("一个一") , 即 11。
		11 被读作 "two 1s" ("两个一"）, 即 21。
		21 被读作 "one 2",  "one 1" （"一个二" ,  "一个一") , 即 1211。

		给定一个正整数 n（1 ≤ n ≤ 30），输出报数序列的第 n 项。

		注意：整数顺序将表示为一个字符串。

		 

		示例 1:

		输入: 1
		输出: "1"
		示例 2:

		输入: 4
		输出: "1211"
	
	题目分析：
		字符串模拟，正常模拟就行了，水题
		不过需要注意的是，数字字符比数字大一个'0' 记得减掉
*/

class Solution {
public:
    string countAndSay(int n) {
        if ( n<=1 ) return "1";
        n--;
        string s = "1";
        int i,cnt,elem,j;
        while( n-- ){
            string x = "";
            i=0;
            while( i<s.size() ){
                j = i+1;
                cnt = 1;
                elem = s[i]-'0';
                while( j<s.size() && s[i]==s[j] ){
                    ++j;
                    ++cnt;
                }
                x = x + (to_string(cnt)+to_string(elem));
                i = j;
            }
            s = x;
        }
        return s;
    }
};