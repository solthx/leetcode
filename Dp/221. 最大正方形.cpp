/*
    问题描述：
        给一个01矩阵，找出该矩阵里的最大全1正方形。
    
    问题分析：
        暴力找出和为n*n的长为n的最大正方形， O(M*N*M*N)直接TLE

        看了题解以后，
        dp[i][j]保存了以坐标(i,j)为右下角的正方形的最大边长。

        在更新dp[i][j]的时候，
        如果matrix[i][j]是1，我们就会去找以matrix(i-1,j-1)为右下角的最大正方形，
        假设这个边长为m， 然后我们会去看 以当前位置向上和向左是否是连续的m个1，
        如果都满足的话，那么当前的最大正方形长就为m+1。

        dp[i-1][j-1]记录了以matrix(i-1,j-1)为右下角的最大正方形的长度
        dp[i-1][j]提供了(i,j)上方连续1的个数
        dp[i][j-1]提供了(i,j)左方连续1的个数
        当前最大正方形的边长，就是上面三个数的最小值加一。

        if ( matrix[i][j]==1 )
            dp[i][j] = min(dp[i-1][j-1], dp[i-1][j], dp[i][j-1]) + 1;
        else 
            dp[i][j] = 0;
 */

 class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        if ( matrix.size()<=0 ) return 0;
        int n = matrix.size(), m = matrix[0].size(); 
        vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
        int res=0;
        for ( int i=1; i<=n; ++i ){
            for ( int j=1; j<=m; ++j ){
                if ( matrix[i-1][j-1]=='1')
                    dp[i][j] = min(min(dp[i-1][j-1],dp[i-1][j]),dp[i][j-1])+1;
                res = max(res, dp[i][j]);
            }
        }
        return res*res;
    }
};