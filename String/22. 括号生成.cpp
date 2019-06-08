/*
	问题描述：
		给出 n 代表生成括号的对数，请你写出一个函数，使其能够生成所有可能的并且有效的括号组合。

		例如，给出 n = 3，生成结果为：

		[
		  "((()))",
		  "(()())",
		  "(())()",
		  "()(())",
		  "()()()"
		]

	问题分析：
		回溯+剪枝 ， 
		让每一个位置都选是'('或是')'
		遍历所有情况，然后l和r的两个变量控制左括号数量和右括号数量
		保证左括号数一定要大于等于右括号数(即l>=r)
		然后n代表还能够加的左括号数
		这样，当n==0, l==r的时候，就是返回的情况
		(回溯情况:  (l<r) or (n<0) )
*/

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        string s="";
        helper( n, 0, 0, s, res, 0 );
        return res;
    }
    
    void helper( int n, int l, int r, string s, vector<string>& res,int i ){
        if ( n<0 ) return; 
        if ( n==0 && l==r ){
            res.push_back(s);
            return ;
        }
        if ( r>l ) return ; 
        helper( n-1, l+1, r, s+'(', res, i+1 );
        helper( n, l, r+1, s+')', res, i+1 );
    }
};