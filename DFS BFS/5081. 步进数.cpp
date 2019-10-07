/*
    问题描述:
        如果一个整数上的每一位数字与其相邻位上的数字的绝对差都是 1，那么这个数就是一个「步进数」。
        例如，321 是一个步进数，而 421 不是。
        给你两个整数，low 和 high，请你找出在 [low, high] 范围内的所有步进数，并返回 排序后 的结果。

        示例：

        输入：low = 0, high = 21
        输出：[0,1,2,3,4,5,6,7,8,9,10,12,21]
         

        提示：

        0 <= low <= high <= 2 * 10^9

    问题分析:
        个人认为，本题dfs的一个难点就是，只要确定下一位就行了，不用在两端确定，
        例如:

        12的转移应该是:
            23 -> 232
            23 -> 234
        
        而不是:
            23 -> 232
            23 -> 234
            23 -> 123  
            23 -> 323

        我们可以设一个起始数，然后根据这个起始数来产生下一个数
        例如起始数为3,

        3->32->321
           32->323->..
        3->34->343->..
           34->345->..

        因此，23->123 的情况是多此一举， 因为123会由起始数为1的来产生.

        因此，我们只需要关心根据当前数产生的下一个数，然后“起始数”为[1,9]

        ps： 在生成下一位的时候，记得过滤:
            1. 当前数>high 返回
            2. 最后一位数是1 和 9的情况
*/

class Solution {
public:
    vector<int> countSteppingNumbers(int low, int high) {
        vector<int> res;
        if ( low==0 ) res.push_back(0);
        for ( int i=1; i<=9; ++i )
            dfs( res, i, low, high );
        sort( res.begin(), res.end() );
        return res;
    }
    
    void dfs( vector<int>& res, long d, int low, int high  ){
        if ( d>high ) return ; // 超出范围返回
        if ( d>=low && d<=high ) res.push_back( d );
        int last = d%10;
        if ( last>0 ) dfs( res, d*10+last-1, low, high ); // 最后一位的区间要在[0,9]
        if ( last<9 ) dfs( res, d*10+last+1, low, high );
    }
};