/*
    问题描述:
        实现一个基本的计算器来计算一个简单的字符串表达式的值。
        字符串表达式可以包含左括号 ( ，右括号 )，加号 + ，减号 -，非负整数和空格  。
        
        示例 1:
            输入: "1 + 1"
            输出: 2
        示例 2:
            输入: " 2-1 + 2 "
            输出: 3
        示例 3:
            输入: "(1+(4+5+2)-3)+(6+8)"
            输出: 23
        说明：
            你可以假设所给定的表达式都是有效的。
            请不要使用内置的库函数 eval。

    问题分析:
        方法一: 
            先中缀转后缀，然后再求值
            中缀转后缀的思路:
                从左到右遍历中缀表达式:
                    1. 遇到数字: 
                        直接加入到后缀表达式的一部分中
                        数字不一定是一个位的哦，记得判断!
                    2. 遇到符号: 
                        判断当前符号和栈顶符号的优先级，
                        if 当前符号是')' or 当前符号优先级 > 栈顶符号优先级 :
                            则栈顶元素一次出栈并加入到后缀表达式中. 然后当前符号进栈
                遍历完之后，把栈里的所有符号都加入到后缀表达式中
            计算后缀表达式就不多说了..
        

        方法一可以说是中缀表达式求值的通杀法了，
        另一个通杀法在 #772 也就是 #227+#224
        下面来看方法二和方法三  
        
        因为本题只有+和-，所以难点在括号的处理上.
        我们希望先计算括号内的表达式，
        所以可以用两个方法来实现. 
        要知道的是，后缀表达式是遇到符号，进行出栈判断，
        而处理中缀表达式，是遇到数字，进行出栈判断！！！！！
            
        方法二:
            一个方法是，引入一个优先级,
            栈中的元素为一个 pair< 符号，优先级 >
            每遇到一个'(' , 优先级加1，
            每遇到一个')' , 优先级减1
            所以，优先级最高的符号，就是最里层的括号了
            所以，我们优先计算优先级高的符号
            
            两个栈，st用于存pair<char,int> ，digit用于存操作数

            例如:  1 - ( 2 - 3 ) + 1 
                  ^                  遇到1，    1加入digit栈, st栈空, 无操作
                    ^                遇到'-',   {'-', 0} 入栈
                      ^              遇到'(',   优先级+1 (变为1)
                        ^            遇到2,     2加入digit栈, 当前优先级(1)>栈顶优先级(0),无操作
                          ^          遇到'-',   {'-', 1} 入栈
                            ^        遇到3,     当前优先级>=栈顶优先级, 可以进行操作:
                                        1. {'-', 1} 出栈
                                        2. digit出栈一个数 b
                                        3. 当前数为 a
                                        4. 计算b-a，压入digit中
                              ^     遇到')' ，  优先级-1 (变为0)
                                ^   遇到'+',    {'+', 0} 入栈
                                  ^ 遇到1 ，    优先级>=栈顶优先级, 同上
            最后计算完st和digit中剩下的，最后digit里会只剩下一个元素，这个元素就是结果.

        方法三:
            另外一个实现“优先计算括号里的表达式”的方法就是, 
            用一个栈保存一个  pair< 计算到目前位置的结果, 当前位置的前一个操作符 >
            维护两个变量：
                一个是从 “开头或上一次压栈” 之后的计算结果 res
                另一个是当前数字的前一个操作符 pre

            每当遇到'(', 就说明要计算括号里的表达式了，所以把当前的计算状态保存起来，
            而当前的计算状态就是上面维护的那两个变量，res和pre, 然后打包成pair存到栈中
            然后初始化res和pre， 开始继续计算括号里的表达式 ( 初始res=0, pre='+'， 相当于进行+0操作，不影响结果 )
            
            每当遇到')', 就说明括号里的表达式计算完了，可以把当前的res和之前保存的res进行计算了，操作符就是pair里的那个操作符
            其实就是把括号里的表达式抽象成一个数了。

            下面来看个例子:
                1 - ( 2 - 3 ) + 1 
                ^                 1,    res= 0+1 = 1
                  ^               -,    pre='-'
                    ^             (,    压入{1,'-'}, 初始化res=0, pre='+'
                      ^           2,    res = 0+2 = 2
                        ^         -,    pre = '-'
                          ^       3,    res = 2-3 = -1
                            ^     ),    res = pre_res - res = 1 - (-1) = 2
                              ^   +,    pre = '+'
                                ^ 1,    res = res + 1 = 3
                                    最后结果为3 
*/

class Solution2 {
public:
    // 引入优先级 来优先处理括号里的表达式
    int calculate(string s) {
        stack<pair<char,int>> st;
        stack<int> digit;
        int p=0;
        int res=0;
        for ( int i=0; i<s.size(); ++i ){
            if ( s[i]=='+' || s[i]=='-' ){
                // 是符号
                // 计算所有栈顶元素的优先级>=当前优先级的 （就是优先计算括号里的和同一层的
                while( !st.empty() && st.top().second >= p ){
                    char op = st.top().first; st.pop();
                    int a = digit.top(); digit.pop();
                    int b = digit.top(); digit.pop();
                    if (  op=='+' )
                        digit.push(b+a);
                    else digit.push(b-a);
                }
                st.push({s[i],p});
            }else if ( s[i]=='(' ) ++p;  //优先级+1
            else if ( s[i]==')' ) --p;   //优先级-1
            else if ( s[i]>='0' && s[i]<='9' ){  //遇到数字开始处理
                int j = i;
                while( j<s.size() && s[j]>='0' && s[j]<='9' ) ++j;
                digit.push( stoi(s.substr(i, j-i) ));
                i = j-1;
            }
        }
        // 把剩余的操作符和剩余的操作数计算完
        while( st.size()>0 ){
            char op = st.top().first; st.pop();
            int a = digit.top(); digit.pop();
            int b = digit.top(); digit.pop();
            if (  op=='+' )
                digit.push(b+a);
            else digit.push(b-a);
        }
        return digit.top();
    }
};

class Solution3 {
public:
    // 遇到括号后保存当前计算状态 和 把括号里的表达式看作为一个数 的思想
    int calculate(string s) {
        stack<pair<int, int>> st;
        int res = 0;
        int sig=1;
        for ( int i=0; i<s.size(); ++i ){
            if ( s[i]=='+' ) sig=1;
            else if ( s[i]=='-' ) sig=-1;
            else if ( s[i]=='(' ){
                st.push({res,sig});
                res=0;
                sig=1;
            }else if ( s[i]==')' ){
                int op = st.top().second;
                int pre_res = st.top().first; st.pop();
                res = pre_res + op*res; 
            }else if ( s[i]<='9' && s[i]>='0' ){
                int j=i;
                while( j<s.size() && s[j]>='0' && s[j]<='9' ) ++j;
                res += sig * stoi( s.substr(i,j-i) );
                i = j-1;
            }
        }
        return res;
    }
};

class Solution1 {
public:
    int calculate(string s) {
        // 中缀转后缀，然后用栈计算
        // 写的有点shit... 下次再重写一遍把.. 
        stack<char> sig;
        string e="";
        vector<string> suffix;
        string bs="";
        int i=0;
        while ( i<s.size() ){
            if ( s[i]==' ' ){
                ++i;
            }else if ( s[i]>='0' && s[i]<='9' ){
                // 是数字就直接加入了
                string d="";
                while( i<s.size() && s[i]>='0' && s[i]<='9' ){
                    d += s[i];
                    ++i;
                }
                // 遇到数字，就直接加入到后缀表达式结果中
                suffix.push_back(d);
                // 如果符号栈的栈顶 存在, 那么就入栈 ('('相当于一个表达式的开头)
                if ( sig.size()>0 && sig.top()!='(' ){
                    suffix.push_back(e+sig.top()) ;
                    sig.pop();
                }
            }else if ( s[i]=='+' || s[i]=='-' || s[i]=='(' ){
                // 遇到符号直接入栈
                sig.push(s[i]);
                ++i;
            }else if ( s[i]==')' ){
                while( sig.top()!='(' ){
                    suffix.push_back(e+sig.top());
                    sig.pop();
                }   
                if ( sig.size()>0 ){
                    sig.pop();
                }
                ++i;
                if ( sig.size()>0 ){
                    suffix.push_back(e+sig.top()); sig.pop();
                }
            }
        }
        // suffix为后缀
        while( sig.size()>0 ){
            suffix.push_back(e+sig.top());
            sig.pop();
        }
        return helper( suffix );
    }
    
    int helper( vector<string> bs ){
        stack<int> s; 
        int i=0;
        for ( auto & c:bs ){
            //cout<<c<<endl;
            if ( c=="+" || c=="-" ){
                int a=s.top(); s.pop();
                int b=s.top(); s.pop();
                if ( c=="+" )
                    s.push(a+b);
                else s.push(b-a);
            }else{
                s.push(stoi(c));
            }
        }
        return s.top();
    }
    
};