/*
    问题描述：
        给定一个仅包含数字 0-9 的字符串和一个目标值，
        在数字之间添加二元运算符（不是一元）+、- 或 * ，返回所有能够得到目标值的表达式。
        输入: num = "232", target = 8
        输出: ["2*3+2", "2+3*2"]

        输入: num = "105", target = 5
        输出: ["1*0+5","10-5"]

        输入: num = "00", target = 0
        输出: ["0+0", "0-0", "0*0"]

        输入: num = "3456237490", target = 9191
        输出: []

    问题分析：
        本题的难点就是数字的长度没有限制（如示例2），
        并且还要记录当前计算结果的表达式，
        因此分治使用起来就比较麻烦，
        
        因为要实时记录当前计算结果的表达式，
        而dfs一般可以满足这种要求，

        但如果使用dfs遇到的麻烦就是：
            处理比较靠后的优先级比较高的乘法时会出问题，
            例如 2+3*2 应该是 8 
            但dfs就会算成 2+3 = 5， 5*2=10，
        
        因此解决这个问题，就可以用dfs，它就变成水题了。

        一个解决思路是：
            pre是前一个操作数，
            cur是当前计算结果
            tmp是当前的操作数

            维护两个变量，pre和cur，遍历当前所有取数情况，得到tmp


        对于加法的更新 (减法就是tmp是负数) ：
            当前       下一个
            tmp   ->   pre   
         cur + tmp ->   cur
        
        对于乘法的更新比较秀，
            当前              下一个
           tmp*pre      ->    pre
        cur-pre+pre*tmp ->    cur

        对于前一个是加减法，上面的式子还好理解(对于加减法不用管pre)，
        对于前一个是乘法的情况，技巧性就比较强了。。

        首先声明一点，pre这个变量存在的意义就是为了帮助解决乘法的情况，
        cur-pre+pre*tmp对cur的更新， 解决了前一种情况是加减的情况

        如果前一种情况是乘法，
        那对pre的更新显然就要好好选取，来满足cur-pre+pre*tmp这个对cur的更新。。

        之所以选tmp*pre，是因为：
            （在当前为乘法的情况中）
            当前的cur == 前一个tmp * 前一个pre
            对cur的更新 ： 当前cur * 当前tmp => 前一个tmp * 前一个pre * tmp --(1)

            若当前的pre == 前一个tmp * 前一个pre

            那么 cur-pre+pre*tmp == 0 + 前一个tmp * 前一个pre * tmp == (1) 
            因此，只要对使用tmp*pre来更新下一次的pre， 就可以使乘法也满足这个情况。。

        PS:
            在真正面试的时候，如果遇到这题，如果不能想到这种巧妙的更新技巧，
        也可以再加一个变量来记录前一个操作是什么，然后根据前一个操作情况来选取当前操作情况
        这种方法二刷的时候再加把。。
 */



class Solution {
private:
    vector<string> res;
public:
    vector<string> addOperators(string num, int target) {
        helper(  num, target, 0, 0, "");  
        return res;
    }
    
    void helper( string num, int target, long pre, long cur, string str ){
        if ( num=="" && target==cur ){
            res.push_back(str);
            return ;
        }
        for ( int len=1; len<=num.size(); ++len ){
            string st_tmp = num.substr(0,len);
            if ( st_tmp[0]=='0' && st_tmp.size()>1 ) return;
            long tmp = stoll(st_tmp);
            //加
            if ( str.size()>0 ){
                helper( num.substr(len), target, tmp, cur+tmp, str + "+" +st_tmp);
                helper( num.substr(len), target, -1*tmp, cur-tmp, str + "-" +st_tmp );
                helper( num.substr(len), target, pre*tmp, cur-pre + pre*tmp, str + "*" +st_tmp );
            }else helper(num.substr(len), target, tmp, tmp, st_tmp);
        }
    }
    
};