/*
	问题描述：
		返回给定的数组中是否存在这样三个数i,j,k：
			Return true if there exists i, j, k 
			such that arr[i] < arr[j] < arr[k] given 0 ≤ i < j < k ≤ n-1 else return false.
			
	问题分析：
		方法一：
			一直维护一个长度为2的递增序列(m1<m2)，一旦发现比
		m2大的数，立刻返回true（那就变成三个了）。
		
		方法二：
                left[i]记录前i个数中的最小值
                right[i]记录后i个数中的最大值
                然后再遍历一遍，找有没有left[i-1]<nums[i]<right[n-i-1]

*/


class Solution1 {
public:
    bool increasingTriplet(vector<int>& nums) {
        /*
            方法一：
                一直维护一个长度为2的递增序列(m1<m2)，一旦发现比
            m2大的数，立刻返回true（那就变成三个了）。
		*/
            int m1=INT_MAX, m2 = INT_MAX;
            for ( int e:nums ){
                if ( e<m1 ) m1=e;
                else if ( e>m1 && e<m2 ) m2= e;
                else if ( e>m2 ) return true;
            }
            return false;
        
    }
};

class Solution2 {
public:
    bool increasingTriplet(vector<int>& nums) {
        /*
            方法二：
                left[i]记录前i个数中的最小值
                right[i]记录后i个数中的最大值
                然后再遍历一遍，找有没有left[i-1]<nums[i]<right[n-i-1]
        */
        int n = nums.size();
        if ( n<3 ) return false;
        vector<int> left(n,INT_MAX);
        vector<int> right(n,0);
        int maxi=0,mini=nums[0];
        for ( int i=0; i<n; ++i ){
            mini = min( mini, nums[i] );
            left[i] = mini;
            maxi = max( maxi, nums[n-i-1] );
            right[i] = maxi;
        }
        for ( int i=1; i<n-1; i++ ){
            if ( left[i-1]<nums[i] && nums[i]<right[n-i-1] )
                return true;
        }
        return false;
    }
};