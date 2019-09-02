/*
    问题描述:
        给定一个按照升序排列的整数数组 nums，和一个目标值 target。找出给定目标值在数组中的开始位置和结束位置。
        你的算法时间复杂度必须是 O(log n) 级别。
        如果数组中不存在目标值，返回 [-1, -1]。

        示例 1:
            输入: nums = [5,7,7,8,8,10], target = 8
            输出: [3,4]

        示例 2:
            输入: nums = [5,7,7,8,8,10], target = 6
            输出: [-1,-1]

    问题分析:
        二分查找，
        要注意处理 元素不存在的情况，
        对于这种题，一次a不过就等于没做出来了.
*/



class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int mid, l=0, r=nums.size()-1;
        while( l<=r ){
            mid = (l+r)/2;
            if ( nums[mid]<=target ) l = mid+1;
            else r = mid-1;
        }
        int lo=0, hi=nums.size()-1;
        while( lo<=hi ){
            mid = (lo+hi)/2;
            if ( nums[mid]<target ) lo = mid+1;
            else hi = mid-1;
        }
        if ( lo<=l-1 )
            return { lo,l-1 };
        return {-1,-1};
    }
};