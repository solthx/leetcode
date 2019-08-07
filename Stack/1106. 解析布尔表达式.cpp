/*
    问题描述:
        给你一个以字符串形式表述的 布尔表达式（boolean） expression，返回该式的运算结果。
        有效的表达式需遵循以下约定：
        "t"，运算结果为 True
        "f"，运算结果为 False
        "!(expr)"，运算过程为对内部表达式 expr 进行逻辑 非的运算（NOT）
        "&(expr1,expr2,...)"，运算过程为对 2 个或以上内部表达式 expr1, expr2, ... 进行逻辑 与的运算（AND）
        "|(expr1,expr2,...)"，运算过程为对 2 个或以上内部表达式 expr1, expr2, ... 进行逻辑 或的运算（OR）

        输入：expression = "!(f)"
        输出：true

        输入：expression = "|(&(t,f,t),!(t))"
        输出：false

    问题分析：
        见到这种求表达式的，一般都是分治，或者用栈来解决。。
        本题使用两个栈，
        sign保存操作，
        digit保存t/f和括号        

        i从0开始扫描expression，
        遇到't' or 'f' or '('，入栈digit
        遇到'&' or '|' or '!'，入栈sign
        遇到')'，开始进行操作，
        ! 是 pop出一个bool字符，然后把'('也pop出来，
        取反之后在push回digit栈

        '&'和'|'差不多， 都是不停pop出栈和当前bool进行对应操作，
        直到栈空或遇到(, 再停下来。。 然后把'(' pop出去，在把结果bool给push回去

        整体来说不难。。就是实现的时候要高度集中。。不然一个bug能de半天..
 */
class Solution {
public:
    bool parseBoolExpr(string expr) {
        char cur;
        int i=0;
        stack<char> sign;
        stack<char> digit;
        while( i<expr.size() ){
            if ( expr[i]=='|' || expr[i]=='&' || expr[i]=='!' ) sign.push(expr[i]);
            else if ( expr[i]=='t' ) digit.push(expr[i]);
            else if ( expr[i]=='f' ) digit.push(expr[i]);
            else if ( expr[i]==')' ){
                if ( sign.size()>0 && digit.size()>0 ){
                    cur = digit.top(); digit.pop(); 
                    if ( sign.top()=='!' ){
                        if ( digit.top()=='(' ) 
                            digit.pop();
                        digit.push(Rev(cur)); // 取反
                    }else if ( sign.top() =='&' ){
                        while( !digit.empty() && digit.top()!='(' ){
                            cur = And(cur,digit.top());
                            digit.pop();
                        }
                        if ( !digit.empty() && digit.top()=='(' )
                            digit.pop();
                        digit.push(cur);
                    }else if ( sign.top()=='|'  ){
                        while( !digit.empty() && digit.top()!='(' ){
                            cur = Or(cur, digit.top());
                            digit.pop();
                        }
                        if ( !digit.empty() && digit.top()=='(' )
                            digit.pop();
                        digit.push(cur); 
                    }
                    sign.pop();
                }
            }else if ( expr[i]=='(' ) digit.push(expr[i]);
            ++i;
        }
        return digit.top()=='t'?true:false;
    }
    
    char And( char a, char b ){
        return a=='t' && b=='t' ? 't' : 'f';
    }
    
    char Or(char a, char b){
        return a=='t'|| b=='t'?'t':'f';
    }
    
    char Rev(char a){
        return a=='t'?'f':'t';
    }
    
};
