/*
    问题描述:
        给定一个只包含三种字符的字符串：（ ，） 和 *，写一个函数来检验这个字符串是否为有效字符串。有效字符串具有如下规则：
        任何左括号 ( 必须有相应的右括号 )。
        任何右括号 ) 必须有相应的左括号 ( 。
        左括号 ( 必须在对应的右括号之前 )。
        * 可以被视为单个右括号 ) ，或单个左括号 ( ，或一个空字符串。
        一个空字符串也被视为有效字符串。
        
        示例 1:
            输入: "()"
            输出: True
        
        示例 2:
            输入: "(*)"
            输出: True
        
        示例 3:
            输入: "(*))"
            输出: True
        
        注意:
            字符串大小将在 [1，100] 范围内。

    问题分析：
        方法一:
            O(N)
            从左往右扫描，
            用栈1来保存左括号的坐标，
            用栈2来保存*的坐标，
            每当遇到')'， 就优先从栈1 弹出左括号和其匹配，
            若栈1 为空，就找'*'栈2去匹配，
            如果栈2也为空， 说明局部不可能匹配成功，返回false

            扫描结束后，如果栈1 不空，
            就继续弹出，看能否和栈2的‘*’进行配对，

            这个时候，就要对坐标进行比较了，

            因为是从左往右扫描入栈的， 栈顶是靠右的，

            所以，栈1的栈顶就是最右的'('的坐标， 栈2的栈顶就是最右的'*'
            
            如果'*'不在'('的右边，那么就返回false， 肯定不成立

            如果剩余的(都和‘*’ 匹配成功了， 那么就返回true

        方法二：
            动态规划 O(N^3)
            区间dp:
            dp[i][j]表示区间[i,j]是否 是合法的.

            区间dp的状态更新:
                dp[i][j] = dp[i][m] && dp[m+1][j];
*/

class Solution1 {
public:
    bool checkValidString(string s) {
        stack<int> l,r,star;
        for ( int i=0; i<s.size(); ++i )
            if ( s[i]=='(' ) l.push(i);
            else if ( s[i]=='*' ) star.push(i);
            else{
                if ( l.size()>0 ) l.pop();
                else if ( star.size()>0 ) star.pop();
                else return false;
            }
        while( l.size()>0 && star.size()>0 && l.top()<star.top() ){
            l.pop(); star.pop();
        }
        return l.size()==0;
    }
};


class Solution2 {
public:
    bool checkValidString(string s) {
        int n = s.size();
        vector<vector<bool>> dp( n+3, vector<bool>(n+3, true) );
        for ( int i=1; i<=n; ++i )
            if ( s[i-1]!='*' ) dp[i][i] = false;
        for ( int len=1; len<=n; ++len ){
            for ( int i=1; i<=n; ++i ){
                if ( i+len-1>n )continue;
                int j = i+len-1;
                dp[i][j] = ( (s[i-1]=='('||s[i-1]=='*') && (s[j-1]==')'||s[j-1]=='*') && dp[i+1][j-1]  ); 
                for ( int m=i+1; m<j && !dp[i][j]; ++m )
                    dp[i][j] = dp[i][m] && dp[m+1][j];
            }
        }
        return dp[1][n];
    }
};