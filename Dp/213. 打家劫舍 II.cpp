/*
    问题分析：
        土匪打劫，数组中的元素为该房屋的财富数，
        不能连续打劫相邻的两个房屋，
        所有房屋是环状( 若打劫了最后一个屋子，那么第一个屋子就不能打劫 )
        问最多能打劫多少财富

    问题分析:
        分两种情况，
        一种是打劫第一户人家，一种是不打劫第一户人家，
        最后返回上面两种情况的最大值。
 */

class Solution1 {
public:
    int rob(vector<int>& nums) {
        if (nums.size()==0) return 0;
        if ( nums.size()==1 ) return nums[0];
        int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(2,0));
        //dp[i][0]表示不偷第i个房屋
        //dp[i][1]表示偷第i个房屋
        int res1,res2;
        //第一个必偷
        dp[0][1] = nums[0];
        dp[0][0] = INT_MIN;
        for ( int i=1; i<n; ++i ){
            dp[i][0] = max( dp[i-1][0], dp[i-1][1] );
            dp[i][1] = max( dp[i][0], dp[i-1][0]+nums[i] );
        }
        res1 = dp[n-1][0];
        //第一个不偷
        dp[0][1] = INT_MIN;
        dp[0][0] = 0;
        for ( int i=1; i<n; ++i ){
            dp[i][0] = max( dp[i-1][0], dp[i-1][1] );
            dp[i][1] = max( dp[i][0], dp[i-1][0]+nums[i] );
        }
        res2 = dp[n-1][1];
        return max(res1, res2); 
    }
};

// 空间优化到O(1)
class Solution2 {
public:
    int rob(vector<int>& nums) {
        if ( nums.size()==0 ) return 0;
        if ( nums.size()==1 ) return nums[0];
        int res1,res2;
        //不打劫第一户
        int da=nums[1], buda=0, pre_da=nums[1], pre_buda=0;
        for ( int i=2; i<nums.size(); ++i ){
            buda = max( pre_buda, pre_da );
            da = max( buda, pre_buda+nums[i] );
            pre_buda = buda;
            pre_da = da;
        }
        res1 = max( pre_da, pre_buda );
        
        da=nums[0], buda=0, pre_da=nums[0], pre_buda=0;
        for ( int i=1; i<nums.size()-1; ++i ){
            buda = max( pre_buda, pre_da );
            da = max( buda, pre_buda+nums[i] );
            pre_buda = buda;
            pre_da = da;
        }
        res2 = max( pre_da, pre_buda );
        return max(res1, res2);
        
    }
};
