/*
    问题描述:
        整数可以被看作是其因子的乘积。
        例如：
        8 = 2 x 2 x 2;
        = 2 x 4.
        请实现一个函数，该函数接收一个整数 n 并返回该整数所有的因子组合。

        注意：
        你可以假定 n 为永远为正数。
        因子必须大于 1 并且小于 n。

        示例 1：
        输入: 1
        输出: []
        示例 2：
        输入: 37
        输出: []

        示例 3：
        输入: 12
        输出:
        [
        [2, 6],
        [2, 2, 3],
        [3, 4]
        ]
    问题分析：
        第一：所有的因子都是从2开始。
        第二：由题目可知，n的因子不能包括它本身，所以cur的size必须大于1（等于1的时候只包含他本身，不符合要求），
        第三：为了剔除重复元素，新添加的元素必须大于等于tmp中的最后一个元素 例如当n=32的时候 tmp中 2 2 2 4 
        这个时候还差一个因子2 但是2不能添加进 cur，因为2小于tmp中的最后一个元素4.如果添加进去会和2 2 2 2 4这个集合一样。

 */


class Solution {
public:
    vector<vector<int>> getFactors(int n) {
        vector<vector<int>> res;
        vector<int> cur;
        if ( n>2 )
            helper( res, 2, n, cur );
        return res;
        
    }
    
    void helper( vector<vector<int>> & res,int start, int n, vector<int>& cur ){
        if ( n<2 ) return ;

        for ( int i=start; i<=sqrt(n); ++i ){
            if ( n%i==0 ){
                cur.push_back(i);
                cur.push_back((n/i));
                res.push_back(cur);
                cur.pop_back();
                helper( res, i, n/i, cur );
                cur.pop_back();
            }
        }
    }
    
    vector<int> sorted( vector<int> & s)
    {
        vector<int> res = vector<int>(s.begin(),s.end());
        sort(res.begin(),res.end());
        return res;
    }
    
};