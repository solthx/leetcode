/*
	问题描述：
		给定一个只包含两种字符的字符串：+和-，
		你和你的小伙伴轮流翻转"++"变成"--"。
		当一个人无法采取行动时游戏结束，另一个人将是赢家。

		编写一个函数判断是否能够保证先手胜利。

		样例1
		输入: s = "++++"
		输出: true
		解释:
		先手可以通过翻转中间的"++"使字符串变成"+--+"来保证胜利。.
		
		样例2
		输入: s = "+++++"
		输出: false 
		解释:
		先手赢不了啊，后手都有应对的方法
		"+++--" --> "+----"
		"++--+" --> "----+"
		
	问题分析：
		这类博弈问题都是双方尽力去选，
		只要当前选手选了 当前可选情况中的某一个情况，使得后面的选手必输，那么当前就可以必胜！

		分治的想法，
		canWin()==true 是返回先手能赢
		!canWin()==true 是返回先手会输
		然后，a是先手，b是后手，那么a反转完之后可以看作是b变成了先手，
		就这么递归的做下去。。。
		伪代码：
			if( s翻转成了t && !canWin(t) )
				当前先手可以稳赢
			
	
	踩坑记录：
		C++中容器的size()返回的是无符号整数，也就是0-1 = unsigned_int_maximun
		substr( pos, len)
		从pos位置，截取长度为len的字符串，pos从0开始
		substr(pos)
		从pos位置，截取从pos到最后一个元素的字符串。
*/
class Solution {
public:
    /**
     * @param s: the given string
     * @return: if the starting player can guarantee a win
     */
    bool canWin(string s) {
        // write your code here
        for ( int i=0; i<(int)s.size()-1; ++i ){
          //  cout<<i<<endl;
            if ( s[i]=='+' && s[i+1]=='+' && !canWin(s.substr(0,i) + "--" + s.substr(i+2)) ) {
                return true;
            }
        }
        return false;
    }
};