/*
    问题描述：
        土匪打劫，数组中的元素为该房屋的财富数，
        不能连续打劫相邻的两个房屋，
        问最多能打劫多少财富。

    问题分析：
        dp[i][0]表示不偷第i个房屋
        dp[i][1]表示偷第i个房屋
        状态转移:
        dp[i][0] = max( dp[i-1][0], dp[i-1][1] );
        dp[i][1] = max( dp[i][0], dp[i-1][0]+nums[i] );

        每次只用到四个变量，空间优化到O(1)
        da: 在当前位置打劫
        buda: 在当前位置不打劫
        pre_da: 在前一个位置打劫
        pre_buda: 在前一个位置不打劫 

        状态:
            buda = max( pre_buda, pre_da );
            da = max( buda, pre_buda+nums[i] );
            pre_buda = buda;
            pre_da = da;

 */

class Solution1 {
public:
    int rob(vector<int>& nums) {
        if (nums.size()==0) return 0;
        int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(2,0));
        //dp[i][0]表示不偷第i个房屋
        //dp[i][1]表示偷第i个房屋
        dp[0][1] = nums[0];
        for ( int i=1; i<n; ++i ){
            dp[i][0] = max( dp[i-1][0], dp[i-1][1] );
            dp[i][1] = max( dp[i][0], dp[i-1][0]+nums[i] );
        }
        return max(dp[n-1][0], dp[n-1][1]);
    }
};

class Solution2 {
public:
    int rob(vector<int>& nums) {
        if ( nums.size()==0 ) return 0;
        int da=nums[0], buda=0, pre_da=nums[0], pre_buda=0;
        // da: 在当前位置打劫
        // buda: 在当前位置不打劫
        // pre_da: 在前一个位置打劫
        // pre_buda: 在前一个位置不打劫 
        for ( int i=1; i<nums.size(); ++i ){
            buda = max( pre_buda, pre_da );
            da = max( buda, pre_buda+nums[i] );
            pre_buda = buda;
            pre_da = da;
        }
        return max(da,buda);
    }
};