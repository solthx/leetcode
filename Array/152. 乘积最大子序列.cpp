/*
	题目描述：
		给定一个整数数组 nums ，找出一个序列中乘积最大的连续子序列（该序列至少包含一个数）。

		示例 1:
		输入: [2,3,-2,4]
		输出: 6
		解释: 子数组 [2,3] 有最大乘积 6。

		示例 2:
		输入: [-2,0,-1]
		输出: 0
		解释: 结果不能为 2, 因为 [-2,-1] 不是子数组。

	题目分析：
		既然要求连续，那就要让dp记录下以第i个元素为结尾的subarray的最大乘积，
		因为如果当前元素是负数，有可能前面的一个最小乘积乘上一个负数会变成最大乘积，
		所以也记录一下最小乘积
		
		maxi[i]记录以第i个元素为结尾的最大乘积
		mini[i]记录以第i个元素为结尾的最小乘积
	
		状态转移公式：
			maxi[i] = max( maxi[i-1] * nums[i] , nums[i], mini[i-1]*nums[i] )
			mini[i] = min( maxi[i-1] * nums[i] , nums[i], mini[i-1]*nums[i] )
		
		最后再返回最大的maxi
*/


class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        if ( !n ) return 0;
        int ma,mi;
        int res = nums[0];
        vector<int> maxi(n+1,1);
        vector<int> mini(n+1,1);
        for ( int i=1; i<=n; ++i ){
            ma = maxi[i-1] * nums[i-1];
            mi = mini[i-1]* nums[i-1];
            maxi[i] = max(max(ma,mi),nums[i-1]);
            mini[i] = min(min(ma,mi),nums[i-1]);
            res = max(res,maxi[i]);
        }
        return res;
    }
};