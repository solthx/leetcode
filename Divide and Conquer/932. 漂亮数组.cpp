/*
    问题描述：
        对于某些固定的 N，如果数组 A 是整数 1, 2, ..., N 组成的排列，使得：
        对于每个 i < j，都不存在 k 满足 i < k < j 使得 A[k] * 2 = A[i] + A[j]。
        那么数组 A 是漂亮数组。

        给定 N，返回任意漂亮数组 A（保证存在一个）。

        示例 1：

        输入：4
        输出：[2,1,4,3]
        示例 2：

        输入：5
        输出：[3,1,2,5,4]
         

        提示：

        1 <= N <= 1000


    问题分析：
        考察数学+分治:
            性质1:
                a+c = 2*b
            =>  (a*2) + (c*2) = 2*(2*b)
            =>  (a-k) + (c-k) = 2*(b-k)

            性质2:
                我们目的是破坏 a+c = 2*b 
                也就是说，a+c 只要满足是奇数就可以了。
                所以，我们把奇数放到左边， 偶数放到右边，这样就保证了两边的和一定为奇数 即:a+c一定为奇数

                然后对于区间[i,j], 只要[i,k]满足条件， [k,j]满足条件，然后奇偶分离以下，[i,j]就一定也满足条件

            举个例子:
                N=6
                
                1 2 3 4 5 6 
            =>  1 3 5 | 2 4 6
            
            =>  [1 2 3]*2-1  | [1 2 3]*2
            =>  [1 3 2]*2-1  | [1 3 2]*2
            =>   1 5 3 2 6 4  == 最终结果  
*/

class Solution {
public:
    vector<int> beautifulArray(int N) {
        if ( N==0 ) return {};
        if ( N==1 ) return {1};
        if ( N==2 ) return {1,2};
        vector<int> res;
        for ( auto p: beautifulArray((N+1)/2) )
            res.push_back( 2*p-1 );
        for ( auto p: beautifulArray((N)/2) )
            res.push_back( 2*p );
        return res;
    }
};