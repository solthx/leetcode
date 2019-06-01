/*
	题目描述：
		一个镜像数字是指一个数字旋转180度以后和原来一样(倒着看)。例如，数字"69"，"88"，和"818"都是镜像数字。
		写下一个函数来判断是否这个数字是镜像的。数字用字符串来表示。

		样例
		样例1:

		输入 : "69" 
		输出 : true
		样例 2:

		输入 : "68" 
		输出 : false
		
	题目分析:
		两个指针向中间逼近，一旦发现不是mirror就返回false
		注意！奇数个字符的情况，中间的那个也要判断！		
*/

class Solution {
public:
    /**
     * @param num: a string
     * @return: true if a number is strobogrammatic or false
     */
    bool isStrobogrammatic(string &num) {
        // write your code here
        int i=0,j=num.size()-1;
        if ( num.size()<1 ) return true;
        while( i<=j ){
            if ( is_mirror(num[i],num[j]) ){
                i++;
                j--;
            }else return false;
        }
        return true;
    }
    
    bool is_mirror(char a, char b){
        if ( a=='9'&&b=='6' || a=='6' && b=='9' ) return true;
        else if ( a==b ){
            if ( a=='1' || a=='8' || a=='0' ) return true;
        }
        return false;
    }
};