/*
	题目描述：
		给定一个正整数，返回它在 Excel 表中相对应的列名称。

		例如，

			1 -> A
			2 -> B
			3 -> C
			...
			26 -> Z
			27 -> AA
			28 -> AB 
			...
		示例 1:

		输入: 1
		输出: "A"
		示例 2:

		输入: 28
		输出: "AB"
		示例 3:

		输入: 701
		输出: "ZY"
		
	题目分析:
		有点像转26进制? 从1开始的，但对数取mod的时候，从0开始比较好做，
		因此对每个数进行取mod操作和整除操作的时候，都先对n减一	
*/

class Solution {
public:
    string convertToTitle(int n) {
        string res="";
        while( n ){
            n--;
            res =  (char)((n%26)+'A') + res ;
            n/=26;
        }
        return res;
    }
};

class Solution {
public:
    int titleToNumber(string s) {
        int res=0;
        for ( auto e:s )
            res = res*26 + (e-'A'+1) ;
        return res;
    }
};