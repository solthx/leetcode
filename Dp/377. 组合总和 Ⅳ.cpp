/*
    问题描述：
        给定一个由正整数组成且不存在重复数字的数组，找出和为给定目标正整数的组合的个数。
        示例:
            nums = [1, 2, 3]
            target = 4
        所有可能的组合为：
            (1, 1, 1, 1)
            (1, 1, 2)
            (1, 2, 1)
            (1, 3)
            (2, 1, 1)
            (2, 2)
            (3, 1)

    问题分析：
        完全背包问题，
        dp[i]为和为i的组合个数
        状态转移公式
        i递增取是每个元素能取无限次
        i递减取是每个元素只能取一次
        dp[i] = dp[i] + dp[i-nums[j]];

        优化：
            可以先对nums进行排序，当遇到i-nums[j]<0的时候直接break就行了（nums递增,后面的肯定也都小于0

        遗留问题：
            本题使用unsigned int以外的类型都挂了。。（long long居然也挂了，不知道为什么
 */

 class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        unsigned int dp[target+1];
        memset(dp,0,sizeof(dp));
        //vector<unsigned int> dp(target+1, 0);
        dp[0] = 1;
        sort( nums.begin(),nums.end() );
        for ( int i=1; i<=target; ++i){
            for ( int j=0; j<nums.size(); ++j ){
                if ( nums[j]<=i )
                    dp[i] += dp[i-nums[j]];
                else break;
            }
        }
        return dp[target];
    }
};