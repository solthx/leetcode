/*
    问题描述：
        给定一个整数数组 nums ，你可以对它进行一些操作。
        每次操作中，选择任意一个 nums[i] ，删除它并获得 nums[i] 的点数。之后，你必须删除每个等于 nums[i] - 1 或 nums[i] + 1 的元素。
        开始你拥有 0 个点数。返回你能通过这些操作获得的最大点数。

        示例 1:

        输入: nums = [3, 4, 2]
        输出: 6
        解释: 
        删除 4 来获得 4 个点数，因此 3 也被删除。
        之后，删除 2 来获得 2 个点数。总共获得 6 个点数。
        示例 2:

        输入: nums = [2, 2, 3, 3, 3, 4]
        输出: 9
        解释: 
        删除 3 来获得 3 个点数，接着要删除两个 2 和 4 。
        之后，再次删除 3 获得 3 个点数，再次删除 3 获得 3 个点数。
        总共获得 9 个点数。
        注意:

        nums的长度最大为20000。
        每个整数nums[i]的大小都在[1, 10000]范围内。

    问题分析:
        状态保存错了。。导致公式推的太复杂。。
        看了题解才恍然大雾。。应该把值作为状态保存，而不是下标

        这道题转换一下就是， 相邻的值不能选，然后求能得到的最大的和，
        解决方法和打家劫舍那题思想一样，
        
        最后，可以用滚动数组 把空间优化到常数.

*/

class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
        // dp一开始建错了
        // 应该从值入手！！
        if ( nums.empty() ) return 0;
        int mx=*max_element(nums.begin(),nums.end());
        vector<int> sums(mx+1,0);
        //int sums[10001]={0};
        for ( auto e:nums )
            sums[e] += e;
        //vector<vector<int>> dp( 10010, vector(2,0) );
        int tmp, take = 0, nottake = 0;
        int res = 0;
        for ( int i=1; i<=mx; ++i ){
            // dp[i][0] = max( dp[i-1][0], dp[i-1][1] );
            // dp[i][1] = sums[i] + dp[i-1][0];
            //  res = max( dp[i][0], dp[i][1] );
            tmp = take;
            take = sums[i] + nottake;
            nottake = max( nottake, tmp );
        }
        return max( take, nottake );
    }
};