/*
    问题描述：
        有 n 个气球，编号为0 到 n-1，每个气球上都标有一个数字，这些数字存在数组 nums 中。
        现在要求你戳破所有的气球。每当你戳破一个气球 i 时，你可以获得 nums[left] * nums[i] * nums[right] 个硬币。 这里的 left 和 right 代表和 i 相邻的两个气球的序号。
        注意当你戳破了气球 i 后，气球 left 和气球 right 就变成了相邻的气球。
        
        求所能获得硬币的最大数量。
        说明:
        你可以假设 nums[-1] = nums[n] = 1，但注意它们不是真实存在的所以并不能被戳破。
        0 ≤ n ≤ 500, 0 ≤ nums[i] ≤ 100

        示例:
        输入: [3,1,5,8]
        输出: 167 
        解释: nums = [3,1,5,8] --> [3,5,8] -->   [3,8]   -->  [8]  --> []
             coins =  3*1*5      +  3*5*8    +  1*3*8      + 1*8*1   = 167

    问题分析：
        有点类似石子合并那题，很明显是用区间Dp，
        在推状态转移公式的时候，要注意气球戳破后就没了，再更新的时候不要选错位置！
        
        dp[i][j]表示在区间[i,j]中能获得的最大硬币数量。

        状态转移公式：
            dp[i][j] = max( dp[i][j], coins[i-1]*coins[k]*coins[j+1] + dp[i][k-1] + dp[k+1][j] )
                                           戳破第k个气球后得到的硬币数  +  区间[i,k-1]得到的最大硬币数 + 区间[k+1,j]得到的最大硬币数
 
        注意边界。
 */

 class Solution {
public:
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        if ( n<=0 ) return n;
        int dp[n+1][n+1]; // 区间[i,j]中最大付钱数;
        int j, left, right; 
        memset(dp,0,sizeof(dp));
        for ( int len=1; len<=nums.size(); ++len ){
            for ( int i=0; i+len<=nums.size(); ++i ){
                // 计算dp[i][i+len]
                j = i+len-1;
                for ( int k=i; k<=j; ++k ){
                    left = (i>0)?nums[i-1]:1;
                    right = (j<nums.size()-1)?nums[j+1]:1;
                    if ( k>0 && k<nums.size()-1 )
                        dp[i][j] = max(dp[i][j], left*nums[k]*right+dp[i][k-1]+dp[k+1][j]);
                    else if ( k==0 )
                        dp[i][j] = max(dp[i][j], left*nums[k]*right+dp[k+1][j]);
                    else if ( k==nums.size()-1 )
                        dp[i][j] = max(dp[i][j], left*nums[k]*right+dp[i][k-1]);    
                }
            }
        }
        return dp[0][nums.size()-1];
    }
};