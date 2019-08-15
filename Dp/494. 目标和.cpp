/*
    问题描述:
        给定一个非负整数数组，a1, a2, ..., an, 和一个目标数，S。现在你有两个符号 + 和 -。对于数组中的任意一个整数，你都可以从 + 或 -中选择一个符号添加在前面。
        返回可以使最终数组和为目标数 S 的所有添加符号的方法数。
        
        示例 1:
            输入: nums: [1, 1, 1, 1, 1], S: 3
            输出: 5
        解释: 
            -1+1+1+1+1 = 3
            +1-1+1+1+1 = 3
            +1+1-1+1+1 = 3
            +1+1+1-1+1 = 3
            +1+1+1+1-1 = 3

            一共有5种方法让最终目标和为3。
            注意:
                数组的长度不会超过20，并且数组中的值全为正数。
                初始的数组的和不会超过1000。
                保证返回的最终结果为32位整数。

    问题分析:
        方法一:
            数组大小才20， 2^20 也就是10^6 , 暴力dfs也可以过去

        方法二:
            进一步加速，就是dfs+记忆化，保存一下中间状态。
            记忆化的精髓就是保存中间的状态，
            但这个状态该怎么选择呢? 
            一般是选能够保存的，且能够独一无二的表示出当前情况的，且这种情况会在dfs的过程中多次遇到的

            所以本题的状态选择:
                memo[idx][cur]就是“在第idx的位置时，此刻的和为cur，在这一开始状态下，走到最后一个位置所组成的所有和中，和为target”的个数


        方法三:
            我们可以把方法二转换成迭代的形式，
            状态选择:
                dp[i][j] 是到第i个位置元素为止，和为j的元素个数
                但是，和有可能是负数， 所以dp[i]是一个map<int,int>
                


            状态更新，通过上一个来更新下一个的方式，来进行更新:
                for i from 0 to n-1:
                    for auto e:dp:   //第i个位置处有多少个由前面i-1个元素得到 所有和的情况 ，并用来更新下一个位置。 这一思想和#403 青蛙过河一样
                        dp[i+1][ e.first + nums[i] ] += dp[i][e.second];
                        dp[i+1][ e.first - nums[i] ] += dp[i][e.second]; 
                return dp[n][target]

        方法四:
            这个方法可牛坏了。。
            sums{P} - sums{N} = targte
            sums{P} - sums{N} + sums{P} + sums{N} = target +sums{P} + sums{N}
            2* sums{P} = target + sums{nums}
            sums{P} = (target + sums{nums}) / 2

            因此问题就变成了，在nums中找出和为 (target + sums{nums}) / 2 的子集个数

            这就变成了01背包问题。。
            dp[i][j]表示 前i个元素和为j的个数 ( 这里跟方法三的dp一样，但不同的是，这里我们的和一定是正值，所以可以不用map，复杂度从log变成常数 )
             
            for ( int i=1; i<=nums.size(); ++i ){
                for ( int j=target; j>=0; --j ){
                    // 第j个元素不放入子集
                    dp[i][j] += dp[i-1][j];
                    // 第j个元素放入子集
                    if ( j>=nums[i-1] )
                        dp[i][j] += (dp[i-1][j-nums[i-1]]);
                }
            }

            ps：
                可以用滚动数组把空间优化到O(N)
                for ( int i=1; i<=nums.size(); ++i ){
                    for ( int j = target; j>=nums[i-1]; --j )
                        dp[j] += dp[j-nums[i-1]];
                }
*/


// dfs 1896ms
class Solution1 {
public:
    int findTargetSumWays(vector<int>& nums, int S) {
        int res=0;
        dfs( res, 0,nums, S );
        return res;
    }
    void dfs( int & res , int idx, vector<int>& nums, long long S ){
        if ( idx >= nums.size() ){
            if ( S==0 )
                ++res;
            return ;
        }
        dfs( res, idx+1, nums, S-nums[idx] );
        dfs( res, idx+1, nums, S+nums[idx] );
    }
};

// dfs+记忆化 44ms
class Solution2 {
public:
    int findTargetSumWays(vector<int>& nums, int S) {
        int n=nums.size();
        vector<vector<int>> memo(n+1, vector<int>(2002,-1));  
        // memo[idx][sum] 指 在idx位置，且和为sum，到最后一个位置后能得到和为S的个数
        return dfs( 0, nums, (long long)S+1000, memo, 1000 );
    }
    int dfs( int idx, vector<int>& nums, long long S,vector<vector<int>> & memo, int cur ){
        if ( memo[idx][cur]>=0 ) return memo[idx][cur];
        if ( idx>=nums.size()  ){
            if ( cur==S ) 
                return 1;
            return 0;
        }
        int cnt=0;
        cnt += dfs( idx+1, nums, S, memo, cur+nums[idx] );
        cnt += dfs( idx+1, nums, S, memo, cur-nums[idx] );
        memo[idx][cur] = cnt;
        return memo[idx][cur];
    }
};

// dp+map 216ms 因为用到map，所以复杂度上升了。。
class Solution3 {
public:
    int findTargetSumWays(vector<int>& nums, int S) {
        vector<unordered_map<int, int>> dp(nums.size()+1); 
        // dp[i][j] 表示前i个数和为j的个数
        dp[0][0] = 1;
        for ( int i=0; i<nums.size(); ++i ){
            for ( auto a:dp[i] ){
                dp[i+1][a.first+nums[i]] += a.second;
                dp[i+1][a.first-nums[i]] += a.second;
            }
        }
        return dp[nums.size()][S];
    }
};

// dp 转化成01背包问题 二维16ms 滚动数组优化到8ms
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int S) {
        // sums{P} - sums{N} = targte
        // sums{P} - sums{N} + sums{P} + sums{N} = target +sums{P} + sums{N}
        // 2* sums{P} = target + sums{nums}
        // sums{P} = (target + sums{nums}) / 2
        int acc=0;
        for ( auto e:nums ) acc+=e;
        long target = ((long)S+acc);
        if ( target%2==1 || acc<S ) return 0;
        target/=2;
        // dp[i][j]是前i个元素中，和为j的个数
        /*vector<vector<int>> dp( nums.size()+1, vector<int>(target+1,0 ) );
        dp[0][0] = 1;
        for ( int i=1; i<=nums.size(); ++i ){
            for ( int j=target; j>=0; --j ){
                dp[i][j] += dp[i-1][j];
                if ( j>=nums[i-1] )
                    dp[i][j] += (dp[i-1][j-nums[i-1]]);
            }
        }
        return dp[nums.size()][target];*/
        vector<int> dp( target+1,0 );
        dp[0] = 1;
        for ( int i=1; i<=nums.size(); ++i ){
            for ( int j = target; j>=nums[i-1]; --j )
                dp[j] += dp[j-nums[i-1]];
        }
        return dp[target];
    }
};