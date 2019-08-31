/*
    问题描述:
        假设按照升序排序的数组在预先未知的某个点上进行了旋转。
        ( 例如，数组 [0,1,2,4,5,6,7] 可能变为 [4,5,6,7,0,1,2] )。
        搜索一个给定的目标值，如果数组中存在这个目标值，则返回它的索引，否则返回 -1 。
        你可以假设数组中不存在重复的元素。
        你的算法时间复杂度必须是 O(log n) 级别。
        
        示例 1:
            输入: nums = [4,5,6,7,0,1,2], target = 0
            输出: 4
        
        示例 2:
            输入: nums = [4,5,6,7,0,1,2], target = 3
            输出: -1

    问题分析:
        1. nums[mid] > nums[r]:
            说明 [l,mid]升序有序
        2. nums[mid] < nums[r]:
            说明 [mid,r]升序有序
        3. nums[mid] == nums[r]:
            1 1 3 1 ,  1 1 3 1 1 1 故无法判断,
            解决方法是：把第三种情况变成上面两种情况，
            即: while( r>mid && nums[mid]==nums[r] ) --r;
*/

class Solution {
public:
    bool search(vector<int>& nums, int target) {
        // 10:08
        // nums[mid]>nums[r]，说明[l,mid]是升序
        // nums[mid]<nums[r]，说明[mid,r]是升序
        return find( nums, target, 0, nums.size()-1 );
    }
    
    bool find( vector<int>& nums, int target, int l, int r ){
        if ( l>r ) return false;
        int mid = (l+r)/2;
        if ( l==r ) return nums[l]==target;
        if ( nums[mid]==target ) return true;
        while( r>mid && nums[mid]==nums[r] ) r--;
        if ( r>mid ){
            if ( nums[mid]<nums[r] ){
                if ( nums[mid]<=target && target<=nums[r] )
                    return binary_search( nums, target, mid, r );
                return find( nums, target, l, mid-1 );
            }else if ( nums[mid]>nums[r] ){
                if ( nums[l]<=target && target<=nums[mid] )
                    return binary_search( nums, target, l, mid);
                return find( nums, target, mid+1, r );
            }
        }
        return find( nums, target, l, mid-1 );
    }
    
    bool binary_search( vector<int>& nums, int target, int l, int r ){
        int mid;
        while( l<=r ){
            mid = (l+r)/2;
            if ( nums[mid]<target ) l = mid + 1;
            else if ( nums[mid]>target ) r= mid-1;
            else return true;
        }
        return false;
    }
};