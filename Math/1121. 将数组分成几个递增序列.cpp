/*
    问题描述:
        给你一个 非递减 的正整数数组 nums 和整数 K，判断该数组是否可以被分成一个或几个 长度至少 为 K 的 不相交的递增子序列。
        
        示例 1：
        输入：nums = [1,2,2,3,3,4,4], K = 3
        输出：true
        解释：
        该数组可以分成两个子序列 [1,2,3,4] 和 [2,3,4]，每个子序列的长度都至少是 3。
        
        示例 2：
        输入：nums = [5,6,6,7,8], K = 3
        输出：false
        解释：
        没有办法根据条件来划分数组。

    问题分析:
        相同元素肯定是不能在同一个数组里的，
        所以最大相同元素个数 就是分出来的最少序列个数，
        然后  最少序列个数 * 序列最少元素个数(K) <= nums.size() 的话，就成立，
        否则就不成立。 
 */
class Solution {
public:
    bool canDivideIntoSubsequences(vector<int>& nums, int K) {
        // maxi 为最大连续元素个数
        int i=0, maxi=1,cnt;
        while( i<nums.size() ){
            while( i<nums.size()-1 && nums[i]!=nums[i+1] ) ++i;
            cnt=1;
            while( i<nums.size()-1 && nums[i]==nums[i+1] ){
                ++cnt;
                ++i;
            }
            ++i;
            if ( maxi<cnt ) maxi = cnt;
        }
        return maxi*K<=nums.size();
    }
};