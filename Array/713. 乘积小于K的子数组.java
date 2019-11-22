/*
    问题描述:
        给定一个正整数数组 nums。
        找出该数组内乘积小于 k 的连续的子数组的个数。

        示例 1:

        输入: nums = [10,5,2,6], k = 100
        输出: 8
        解释: 8个乘积小于100的子数组分别为: [10], [5], [2], [6], [10,5], [5,2], [2,6], [5,2,6]。
        需要注意的是 [10,5,2] 并不是乘积小于100的子数组。
        说明:

        0 < nums.length <= 50000
        0 < nums[i] < 1000
        0 <= k < 10^6

    问题分析:
        看到子数组:
            1. 滑动窗口(双指针)
            2. hashmap + 前缀和（可能取mod
            3. 分治、归并
            4. dp
        
        本题算是滑动窗口+dp思想了（尽管没用dp

        维护一个窗口， 
        
        在位置i上，计算出以第i个位置为结尾的最大乘积小于k的窗口，计算以第i个元素为结尾时，子数组的个数.  （当从左向右扫描的时候，尽量还是以第i个数为结尾，而不是以第i个数为开始。。
        
        然后把每一个位置上的个数都加起来就是结果了。
        
        

*/

class Solution {
    public int numSubarrayProductLessThanK(int[] nums, int k) {
        int res = 0, prod = 1, left = 0;
        if (k < 1)
            return 0;
        for (int right = 0; right < nums.length; ++right) {
            prod *= nums[right];
            while (left <= right && prod >= k)
                prod /= nums[left++];
            res += (right - left + 1);
        }
        return res;
    }
}