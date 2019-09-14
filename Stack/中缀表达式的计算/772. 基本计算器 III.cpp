/*
    问题描述:
        实现一个基本的计算器来计算简单的表达式字符串。

        表达式字符串可以包含左括号 ( 和右括号 )，加号 + 和减号 -，非负 整数和空格 。

        表达式字符串只包含非负整数， +, -, *, / 操作符，左括号 ( ，右括号 )和空格 。整数除法需要向下截断。

        你可以假定给定的字符串总是有效的。所有的中间结果的范围为 [-2147483648, 2147483647]。

        一些例子：
            "1 + 1" = 2
            " 6-4 / 2 " = 4
            "2*(5+5*2)/3+(6/2+8)" = 21
            "(2+6* 3+5- (3*14/7+2)*5)+3"=-12
        注：不要 使用内置库函数 eval。

    问题分析:
        解决该方法的思路，就是#224解决括号的思路，加上#227解决+，-，*，/的思路，
        #224中优先计算括号的思路， 就是当遇到'('的时候， 保存的状态不再是<res, pre>
        即 <到当前位置为止计算的结果, 前一个操作符> 这个状态， 
        这里保存的状态是 <到当前位置为止的buffer， pre> ， 这里的buffer保存了到当前位置为止，优先计算'-','*','/'得到的 待累加 数组
        
        当遇到')'的时候， 我们根据 '(' 前一个操作符，来完成具体该做什么操作.

        举个例子:
        1 + 2 * ( 5 + 5 ) / 2 
        ^                    1,     buff = {1}
          ^                  +,     pre = +
            ^                2,     buff = {1,2}
              ^              *,     pre = *
                ^            (,     状态压栈，保存状态<{1,2}, '*'>, 初始化buff, pre
                  ^          5，    buff = {5}
                   ^         +,     pre = +   
                     ^       5,     buff = {5,5}
                       ^     ),     括号内的计算结果为5+5=10, 
                                    前一个状态为<{1,2}, '*'>, 
                                    前一个操作符为'*'
                                    把括号内的表达式看成一个数，那么这个数就是表达式的计算结果，这里就是10
                                    当前buff重新更新为{1,2}，
                                    且pre=='*' , 当前值为10
                                    buff = {1,2*10} = {1,20}
                          ^  /,     pre=/
                           ^ 2,     buff = {1,20/2} = {1,10}
        最终结果为 accumulate(buff) = 11

        该操作和思想就是#227 +#224 只不过在保存状态这一个地方不一样.
*/

class Solution {
public:
    int calculate(string s) {
        int res=0;
        char pre = '+';
        vector<long> buff;
        stack<pair<vector<long>,char>> st;
        for ( int i=0; i<s.size(); ++i ){
            if ( s[i]==' ' ) continue;
            else if ( s[i]>='0' && s[i]<='9' ){
                // 是数字
                long num=0;
                while( i<s.size() && s[i]>='0' && s[i]<='9' )
                    num = num*10 + (s[i++]-'0');
                --i;
                // 得到操作数num
                // 看前一个符号是什么
                if ( pre=='-' ) buff.push_back(-num);
                else if ( pre=='*' ){
                    int t=buff.back(); buff.pop_back();
                    buff.push_back( t*num );
                }else if ( pre =='/' ){
                    int t=buff.back(); buff.pop_back();
                    buff.push_back( t/num );    
                }else buff.push_back( num );
            }else if ( s[i]=='(' ){
                // 把前面的总和 和 前一个符号记录下来
                st.push({buff,pre});
                buff.clear();  //初始化buff
                pre = '+'; // 初始化pre
            }else if ( s[i]==')' ){
                // sums为括号内的计算结果
                int num = accumulate( buff.begin(), buff.end(),0 );
                buff = st.top().first;
                pre = st.top().second; st.pop();
                if ( pre=='-' ) buff.push_back(-num);
                else if ( pre=='*' ){
                    int t=buff.back(); buff.pop_back();
                    buff.push_back( t*num );
                }else if ( pre =='/' ){
                    int t=buff.back(); buff.pop_back();
                    buff.push_back( t/num );    
                }else buff.push_back( num );
            }else if ( s[i]=='+' || s[i]=='-' || s[i]=='*' || s[i]=='/' ){
                pre = s[i];
            }
        }
        return  accumulate( buff.begin(), buff.end(),0 );
    }
};