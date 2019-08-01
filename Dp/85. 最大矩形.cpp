/*
    问题描述：
        给定一个仅包含 0 和 1 的二维二进制矩阵，找出只包含 1 的最大矩形，并返回其面积。
        示例:
        输入:
        [
            ["1","0","1","0","0"],
            ["1","0","1","1","1"],
            ["1","1","1","1","1"],
            ["1","0","0","1","0"]
        ]
        输出: 6

    问题分析：
        方法一：
            leetcode 84. Largest Rectangle in Histogram (直方图中最大的矩形)的变种，
            dp[i][j]记录了以matrix[i][j]为起点，向上的连续的1的个数，当作84题中的直方图的高度
            然后像84题那样，计算每一行的最大矩形，
            最终取每行最大中的最大。

        方法二：
            dp[i][j]记录了matrix[i][j](包括自身的)左边连续的1的个数，作为矩形的长
            然后向上直到遇到 dp[r][j]==0， 矩形的长取当前遇到的每一行的长的最小值，
            矩形的高就是从扫描的起始位置(i,j)到(r,j)的距离
            
            res = max( min(dp[t][j])*(i-t+1) )  t的范围是(r,i]
 */

class Solution1 {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        if ( matrix.size()==0 || matrix[0].size()==0 ) return 0;
        int n = matrix.size(), m=matrix[0].size();
        vector<vector<int>> dp(n, vector<int>(m,0));
        for ( int i=0; i<n; ++i )
            for ( int j=0; j<m; ++j ){
                if ( i>0 ){
                    if ( matrix[i][j]=='1' )
                        dp[i][j] = dp[i-1][j] + 1;
                    else 
                        dp[i][j] = 0;
                }else dp[i][j] = (matrix[i][j]=='1')?1:0;
            }
        int res = 0;
        for ( int i=0; i<n; ++i ){
            res = max(res, helper( dp[i] ));
        }
        return res;
    }
    
    int helper( vector<int> & nums ){
        int res=0;
        for ( int i=0; i<nums.size(); ++i ){
            //cout<<i<<endl;
            if ( i<nums.size()-1 && nums[i]>nums[i+1] || i==nums.size()-1 ){
                int j=i, mi=nums[i];
                while( j>=0 ){
                    mi = min(mi, nums[j]);
                    res = max(res, mi*(i-j+1));    
                    --j;
                }
            }
        }
        return res;
    }
    
};


class Solution2 {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        if ( matrix.size()==0 || matrix[0].size()==0 ) return 0;
        int n = matrix.size(), m=matrix[0].size(), res=0;
        vector<vector<int>> dp(n, vector<int>(m,0));
        for ( int i=0; i<n; ++i )
            for ( int j=0; j<m; ++j ){
                if ( j>0 )
                    dp[i][j] = matrix[i][j]=='1'?dp[i][j-1] + 1:0;
                else if ( j==0 )
                    dp[i][j] = matrix[i][j]=='1'?1:0;
                
                int r=i, mi=dp[i][j];
                while( r>=0 && dp[r][j]>0 ){
                    mi = min(mi, dp[r][j]);
                    res = max( res, mi*(i-r+1) );
                    --r;
                }
            }
        return res;
    }
};