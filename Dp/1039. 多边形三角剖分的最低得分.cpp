/*
    问题描述:
        https://leetcode-cn.com/problems/minimum-score-triangulation-of-polygon/

    问题分析:
        dfs做超时... 知道肯定是dp或记忆化.. 但一直选不对状态保存 T_T

        看了题解才恍然大雾.. 原来是区间dp..
        dp[i][j]表示第i个点到第j个点之间所有的点组成的多边形所得到的值的和的最小值

        状态更新：
            先初始化:
                dp全初始化为INT_MAX
                dp[i][i] == dp[i][i+1] == 0
                dp[i][i+2] == A[i]*A[i+1]*A[i+2]

            状态更新:
            for len from 3 to n:
                for i from 0 , and i+len<n :
                    j = i+len;
                    for k from i+1 to j-1:
                        dp[i][j] = min( dp[i][j], dp[i][k]+dp[k][j]+A[i]*A[j]*A[k] );
           
*/

class Solution {
public:
    int minScoreTriangulation(vector<int>& A) {
        int n = A.size(), j;
        vector<vector<int>> dp( n+2, vector<int>(n+2, INT_MAX));
        for (int i=0; i<=n; ++i  ){
            dp[i][i+1] = 0;
            dp[i][i] = 0;
        }
        
        for ( int i=0; i<=n-3; ++i )
            dp[i][i+2] = A[i]*A[i+1]*A[i+2];
        
        for ( int len=3; len<n; ++len ){
            for ( int i=0; i+len<n; ++i ){
                j = i+len;
                for ( int k=i+1; k<j; ++k ){
                    dp[i][j] = min( dp[i][j], dp[i][k]+dp[k][j]+A[i]*A[j]*A[k] );
                }
            }
        }
        
        return dp[0][n-1];
    }
};