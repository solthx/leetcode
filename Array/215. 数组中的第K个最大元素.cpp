/*
	题目描述：
		在未排序的数组中找到第 k 个最大的元素。请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。
		
		示例 1:
		输入: [3,2,1,5,6,4] 和 k = 2
		输出: 5
		
		示例 2:
		输入: [3,2,3,1,2,4,5,5,6] 和 k = 4
		输出: 4

	问题分析：
		方法一：
			先使用快排思想，每次选一个key(在本题中，每次选第一个击败35%，每次选中间那个击败99.5%)
			把这个key给定位到它应该在的次序位置i，用二分的方法，直到到i==k为止。
			
			Kth_element( nums, k, low, high )的解释：
				返回 i 在区间 [low,high] 中，第k小的元素
				
				每次把key = nums[(low+high)/2]归位 ， 假设归位的位置是 j 
				再求出key在当前区间中的rank (rank = j - low + 1)
				
				二分判断：
					如果rank==k 直接返回结果
					如果rank>k 说明结果在左区间[low,j-1]排第 k
					如果rank<k 说明结果在右区间[j+1,high]排第 k-rank

			都从1开始计
			
			
	
		方法二：
			排序，取第k个元素。	
		
		
*/




class Solution1 {
public:
    int findKthLargest(vector<int>& nums, int k) {
        return Kth_element(nums,nums.size()-k+1,0,nums.size()-1);
    }
		
	/*
		Kth_element( nums, k, low, high )的解释：
			返回 i 在区间 [low,high] 中，第k小的元素
			
			每次把key = nums[(low+high)/2]归位 ， 假设归位的位置是 j 
			再求出key在当前区间中的rank (rank = j - low + 1)
			
			二分判断：
				如果rank==k 直接返回结果
				如果rank>k 说明结果在左区间[low,j-1]排第 k
				如果rank<k 说明结果在右区间[j+1,high]排第 k-rank
	*/	
    int Kth_element(vector<int>& nums, int k,int lo,int hi){
        swap(nums[lo],nums[(lo+hi)/2]);
        int key = nums[lo];
        int rank;
        int l=lo,r = hi;
        while( l<r ){
            while( l<r && nums[r]>=key ) r--;
            if ( l<r ) swap(nums[l++],nums[r]);
            while( l<r && nums[l]<=key ) l++;
            if ( l<r ) swap(nums[l],nums[r--]);
        } 
        nums[l] = key;
        rank = l-lo+1;
        if ( rank == k ) return key;
        else if ( rank<k ) return Kth_element(nums, k-rank, l+1,hi);
        else return Kth_element(nums, k, lo, l-1);
    }
};


class Solution2 {
public:
    int findKthLargest(vector<int>& nums, int k) {
        sort(nums.begin(),nums.end());
        return nums[nums.size()-k];
    }
};