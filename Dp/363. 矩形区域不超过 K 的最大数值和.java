/*
    问题描述：
        给定一个非空二维矩阵 matrix 和一个整数 k，找到这个矩阵内部不大于 k 的最大矩形和。
        示例:

        输入: matrix = [[1,0,1],[0,-2,3]], k = 2
        输出: 2 
        解释: 矩形区域 [[0, 1], [-2, 3]] 的数值和是 2，且 2 是不超过 k 的最大数字（k = 2）。

    问题分析：
        方法一：暴力解法，O(M^2*N^2)
            1. 求矩形的面积时，往往需要对角两个点的坐标，但如果这样保存会很占空间
            可以类比一维数组里的任意区间和那样，通过相减来得到某个区间上的坐标。
            这里用类似的方法，dp[i][j]表示以[0,0]为一个角，[i,j]为另一个角的矩阵面积，
            然后一步一步的判断

            加入matrix[i][j]的元素：
                1. dp[i][j] =   dp[i-1][j] + dp[i][j-1] + matrix[i][j] - dp[i-1][j-1] //减去加了两次重合区域
                2. 计算内部所有不是以[0,0]为一个角的其他面积：
                for r from 0 to i (exclude i):
                    for c from 0 to j (exclude j)： 
                        spare = dp[i][j] - dp[r][j] - dp[i][c] + dp[r][c]; //减了两次，加回来 
        
        方法二：
            https://github.com/solthx/leetcode/blob/master/Matrix/363.%20%E7%9F%A9%E5%BD%A2%E5%8C%BA%E5%9F%9F%E4%B8%8D%E8%B6%85%E8%BF%87%20K%20%E7%9A%84%E6%9C%80%E5%A4%A7%E6%95%B0%E5%80%BC%E5%92%8C.cpp
 */

class Solution {
    public int maxSumSubmatrix(int[][] matrix, int k) {
        int row = matrix.length, col = matrix[0].length;
        int[][] sum = new int[row + 1][col + 1];
        int nxt_sum = 0;
        // 更新sum
        // 暴力，复杂度为O(N*M*N*M)
        int res = Integer.MIN_VALUE, cur;
        for (int i = 1; i <= row; ++i) {
            for (int j = 1; j <= col; ++j) {
                sum[i][j] = matrix[i - 1][j - 1] + sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
                for (int r = 0; r < i; ++r)
                    for (int c = 0; c < j; ++c) {
                        cur = sum[i][j] - sum[i][c] - sum[r][j] + sum[r][c];
                        if (cur <= k && cur > res) {
                            res = cur;
                            if (res == k)
                                return k;
                        }
                    }
            }
        }
        /*
         * int [][] A = new int[row+1][col+1]; for ( int i=0; i<row; ++i ){ for ( int
         * j=0; j<col; ++j ) if ( j>0 ){ A[i][j] = A[i][j-1] + matrix[i][j]; }else{
         * A[i][j] = matrix[i][j]; } } int cur = 0, rowsum=0, res=Integer.MIN_VALUE; for
         * ( int l=0; l<col; ++l ) for ( int r=l; r<col; ++r ){ rowsum = 0; for ( int
         * i=0; i<row; ++i ){ TreeSet<Integer> ts = new TreeSet<Integer>(); rowsum +=
         * (A[i][r] - A[i][l] + matrix[i][l]); // sum[0,i]->a , sum[0,j]->b , j>i, //
         * 找满足 b-a<=k, a>=b-k // 且 b-a最大，即a最小，即最小的，且满足a>=b-k的a Integer a =
         * ts.ceiling(rowsum - k); if ( a!=null ) res = Math.max(rowsum - a, res);
         * ts.add(rowsum); } }
         */
        return res;
    }
}
