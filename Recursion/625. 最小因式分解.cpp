/*
    问题描述:
        给定一个正整数 a，找出最小的正整数 b 使得 b 的所有数位相乘恰好等于 a。
        如果不存在这样的结果或者结果不是 32 位有符号整数，返回 0。

        样例 1

        输入：
            48 
        输出：
            68

        样例 2

        输入：
            15
        输出：
            35

    问题分析:
        注意，结果超过32位的情况。
*/

class Solution {
public:
    int smallestFactorization(int a) {
        vector<int> res;
        bool canDivide = helper(res,a);
        if ( !canDivide ) return 0;
        return f(res);
    }
    
    bool helper( vector<int>& res, int a ){
        int i;
        if ( a<10 ){
            res.push_back(a);
            return true;
        }
        for ( i=9; i>1; --i )
            if ( a%i==0 ){
                res.push_back( i );
                return helper( res, a/i );
            }
        return false;
    } 
    
    int f( vector<int>& res ){
        sort(res.begin(), res.end());
        long i = 0; 
        for (auto e:res){
            i = i*10 + e;
            if ( i>INT_MAX ) return 0;
        }
        return i;
    }
    
};