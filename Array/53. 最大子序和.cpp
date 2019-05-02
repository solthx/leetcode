/*
	问题描述：
		给定一个整数数组 nums ，找到一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。

		示例:

		输入: [-2,1,-3,4,-1,2,1,-5,4],
		输出: 6
		解释: 连续子数组 [4,-1,2,1] 的和最大，为 6。
		
	问题解析：
		方法一：
			动态规划. dp[i]表示以第i个元素为结尾的最大和，找出最大的那个，很简单，不多说了。

		方法二：
			分而治之。
			本题可以说是分而治之的一个典型例题！
			将数组分而治之，会有三种情况：
				假设数组 nums[left, right] 存在最大区间，mid = (left + right) /2
				情况1： 最大值在 nums[left, mid]里
				情况2： 最大值在 nums[mid + 1, right]里
				情况3： 最大值横跨三个部分，即nums[left, mid -1]的最大值加上nums[mid + 1, right]的最大值，再加上mid为最终的值。
*/


class Solution1 {
public:
    int maxSubArray(vector<int>& nums) {
        int cur=0,res=0;
        vector<int> dp( nums.size() , 0 ); // dp[i]表示以第i个元素为结尾的最大和
        res = dp[0] = nums[0];
        for ( int i=1; i<nums.size(); ++i ){
            dp[i] = max( dp[i-1]+nums[i] , nums[i] );
            res = max(res , dp[i]);
        }
        return res;
    }
};


class Solution2 {
public:
    int maxSubArray(vector<int>& nums) {
        //分治解法：
        return divide( nums,0,nums.size()-1, INT_MIN );
    }
    
    int divide(vector<int> & nums, int l,int r,int dmax){
        // 边界返回
        if ( l>=r ) return nums[l];
        int mid = (l+r)/2;
        //情况一
        int left_max = divide(nums,l,mid,dmax);
        //情况二
        int right_max = divide(nums,mid+1,r,dmax);
        int cur=0,mid_max=0,lm=0,rm=0;
        //去最大
        dmax = max(dmax,left_max);
        dmax = max(dmax,right_max);
        
        //情况三：以nums[mid-1]为结尾的的最大值，和以nums[mid+1]为首的最大值，再加上nums[mid]，就是中间情况
        for ( int i=mid-1; i>=0; --i ){
            cur+= nums[i];
            lm = max(lm,cur);
        }
        cur=0;
        for (int i=mid+1; i<nums.size(); ++i){
            cur+=nums[i];
            rm = max(rm,cur);
        }
        mid_max = lm+nums[mid]+rm;
        //返回三种情况的最大情况
        return max(dmax,mid_max);
    }
};