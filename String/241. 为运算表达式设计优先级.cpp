/*
    问题描述：
        给定一个含有数字和运算符的字符串，为表达式添加括号，改变其运算优先级以求出不同的结果。你需要给出所有可能的组合的结果。有效的运算符号包含 +, - 以及 * 。

        示例 1:

        输入: "2-1-1"
        输出: [0, 2]
        解释: 
        ((2-1)-1) = 0 
        (2-(1-1)) = 2

    问题分析：
        每遇到一个符号就递归的计算符号两边所有的计算结果情况（用vector保存） ，
        然后根据符号对两边的数进行相应操作，
        再将结果保存到res中， 
        然后对每一个符号都进行这种操作，
        最终返回res。
 */

 class Solution {
public:
    vector<int> diffWaysToCompute(string input) {
        vector<int> res,left,right;
        int i=0;
        if ( input.size()<1 ) 
            return res;
        bool flag=false;  //是否要继续下去，是否还存在符号（+，-，*）
        if ( input[0]=='-' ) //第一个数是负数
            ++i;
        for(  ; i<input.size(); ++i ){
            if ( !isDigit(input[i]) ){ //对每一个符号都进行这种“计算“两边得到整体”的操作”
                flag=true;   // 还要继续下去，还存在符号
                left = diffWaysToCompute(input.substr(0,i)); //计算左边的所有结果
                right = diffWaysToCompute(input.substr(i+1)); // 计算右边的所有结果
                for ( int a=0; a<left.size(); ++a )  // 计算这个符号所得到的所有结果
                    for ( int b=0; b<right.size(); ++b )
                        res.push_back( cal(left[a],right[b],input[i] ) );
            }
        }
        if ( !flag ) 
            return { atoi(input.c_str()) }; //string转int
        return res;
    }
    
    
    bool isDigit( char c ){
        return c>='0' && c<='9';
    }
    
    int cal( int a, int b, char c ){
        if ( c=='+' )
            return a+b;
        else if ( c=='-' )
            return a-b;
        else if ( c=='*' )
            return a*b;
        else return '#';
    }
};