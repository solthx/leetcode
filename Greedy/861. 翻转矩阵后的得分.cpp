/*
    问题描述:
        有一个二维矩阵 A 其中每个元素的值为 0 或 1 。
        移动是指选择任一行或列，并转换该行或列中的每一个值：将所有 0 都更改为 1，将所有 1 都更改为 0。
        在做出任意次数的移动后，将该矩阵的每一行都按照二进制数来解释，矩阵的得分就是这些数字的总和。
        返回尽可能高的分数。

        示例：

        输入：[[0,0,1,1],[1,0,1,0],[1,1,0,0]]
        输出：39
        解释：
        转换为 [[1,1,1,1],[1,0,0,1],[1,1,1,1]]
        0b1111 + 0b1001 + 0b1111 = 15 + 9 + 15 = 39
         

        提示：

        1 <= A.length <= 20
        1 <= A[0].length <= 20
        A[i][j] 是 0 或 1

    问题分析:
        因为这里的二进制是从行来看的，

        因此，行的重要性比较高。。

        从每一行来看，只有两种情况， 翻转or不翻转，

        而 1000>0111

        所以，取高位为1的那一个情况。

        这样，就保证了，每一行都是当前局部最大的。。

        然后再翻转列， 除了第一列之外（因为第一列已经都是1了）

        后面的每一列， 也是分为2种情况， 我们取数字1个数比较多的情况，

        因为在同一列的话，代表的权重都一样大，所以当然是1越多越好了！！

        这样做两次贪心， 最后得出的值就是答案。
*/

class Solution {
public:
    int matrixScore(vector<vector<int>>& A) {
        int res =0 ;
        if ( A.size()==0 || A[0].size()==0 ) return 0;
        // 扫描行
        for ( int i=0; i<A.size(); ++i )
            if ( A[i][0]==0 )
                for (auto &e:A[i])
                    e = (e+1)%2;
        // 扫描列
        for ( int i=0; i<A[0].size(); ++i ){
            int zero=0; //0的个数
            for ( int j=0; j<A.size(); ++j )
                zero += (A[j][i]==0);
            if ( zero>A.size()-zero )
                for ( int j=0; j<A.size(); ++j )
                    A[j][i] = (A[j][i]+1)%2; 
        }
        // 进行求和
        for ( auto line:A )
            res += helper(line);
        return res;
    }
    
    int helper( vector<int> line){
        int res=0;
        for ( auto d:line )
            res = res*2 + d;
        return res;
    }
};