/*
	问题描述：
		给定一个只包含 '(' 和 ')' 的字符串，找出最长的包含有效括号的子串的长度。

		示例 1:

		输入: "(()"
		输出: 2
		解释: 最长有效括号子串为 "()"
		示例 2:

		输入: ")()())"
		输出: 4
		解释: 最长有效括号子串为 "()()"

	问题分析：
		方法一： 使用栈来记录元素下标:

			使用栈记录每一个'('的下标，start记录有效开始位置
			当遇到')'的时候，若此时:
				1. 栈为空，说明)数量多余(数量，此位置之前都没用了，更新start
				2. 栈不空:
					先pop出一个元素
					2.1 : 若栈空，则res取 max(res, i-start+1) （"()()()" 类似这种情况）
					2.2 ：若栈不空，则res取 max(res, i-stack.top() ) （"(()()" 类似这种情况）
			返回res

		方法二：动态规划:
			
			dp[i]记录了以第i个元素为结尾的最长有效括号序列个数， 
			如果当前括号是')' ， 并且第 i-1 - dp[i-1] 个元素是'('
			
			那么dp[i] = dp[i-1]+2  // 好好体会，挺好理解
			
			最后不要忘记dp[i] += dp[i-dp[i]]  // 例如()()()情况
			
*/

class Solution1 {
public:
    int longestValidParentheses(string s) {
        stack<int> st;
        int start = 0, res=0;
        for ( int i=0; i<s.size(); ++i ){
            if ( s[i]=='(' )
                st.push(i);
            else if ( s[i]==')' ){
                if ( st.size()<=0  )
                    start = i+1;
                else{
                    st.pop();
                    if ( st.size()==0 ){
                        res = max(res, i-start+1);
                    }
                    else{
                        res = max(res, i-st.top());
                    }
                }
            }
        }
        return res;
    }
};


class Solution2 {
public:
    int longestValidParentheses(string s) {
        s = ')' + s;
        int n = s.size(),res=0; 
        vector<int> dp(n,0);
        for ( int i=1; i<n; ++i ){
            if ( s[i]==')' && s[i-1-dp[i-1]]=='(' )
                dp[i] = dp[i-1] + 2;
            dp[i] += ( dp[i-dp[i]] );
            res = max(res,dp[i]);
        }
        return res;
    }
};






