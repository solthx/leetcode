/*
	题目描述：
		给定一个含有 n 个正整数的数组和一个正整数 s ，找出该数组中满足其和 ≥ s 的长度最小的连续子数组。如果不存在符合条件的连续子数组，返回 0。

		示例: 

		输入: s = 7, nums = [2,3,1,2,4,3]
		输出: 2
		解释: 子数组 [4,3] 是该条件下的长度最小的连续子数组。

		
	方法一：
		解决方法受“#325 最长子序列之和为k” 那道题的启发，
		既然要求 sum{l,r} >= s,
		先设sum[i]为前i个元素的和，
		然后找 sum[i]-sum[j] >= s
		即 找 sum[j] <= sum[i] - s
		基本方法和#325类似， 只不过是找最小长度，比较简单就不赘述了。
		
	方法二:
		虫取法，其实就是two pointer, 两个指针维护一个区间(l,r)，使得这个区间的和(sum)
		大于等于s，然后找出最短的那个。
			步骤：
				1. 移动r，直到sum{l,r}>=s
				2. 更新长度
				3. 移动l, 直到sum{l,r}<s 
				4. 更新长度(记得l要减一，因为当前的l是首个不满足的条件，要回退一下)
				5. 返回最大长度。
*/


class Solution1 {
public:
	//	O(NlogN)
    int minSubArrayLen(int s, vector<int>& nums) {
        map<int,int> m;  // (sum[i] : i)
        set<int> st;    // 用来找首个小于等于
        set<int> :: iterator it;
        vector<int> sums(nums.size(),0);
        int acc=0,res=INT_MAX; 
        for ( int i=0; i<nums.size(); ++i ){
            if ( nums[i]>=s ) return 1;  //单个元素大于s，直接返回了
            acc += nums[i];
            sums[i] = acc;
            if ( sums[i]>=s ) res = min(res,i+1);  //sum[i]>=s的情况，更新最值res
            // sum[i] - x >=s
            // x <= sum[i]-s
            it = st.lower_bound(sums[i]-s);   //找到首个大于等于sum[i]-s的元素
            while( it!=st.begin() && (*it)>sums[i]-s ) it--; //向前移，找到最后一个小于等于sum[i]-s的元素（map内部有序）
            if ( it!=st.begin() && m.count((*it)) )  //如果找到了，更新res
                res = min( res, i- m[(*it)]);
            m[sums[i]] = i;
            st.insert(sums[i]);
            
        }
        return res==INT_MAX?0:res;
    }  
	
};


class Solution2 {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
		//O(N)
        int l=0,r=0,sum=0,res=INT_MAX;
        while( r<nums.size() ){
			//步骤一：移动r，直到sum{l,r}>=s
            while( r<nums.size() && sum<s  ){
                sum += nums[r++];
            }
            //步骤二：更新长度
			if ( sum>=s )
                res = min(res,r-l);
            //步骤三：移动l, 直到sum{l,r}<s
			while( l<r && sum>=s ){
                sum -= nums[l++];
            }
            //步骤四：更新长度(记得l要减一，因为当前的l是首个不满足的条件，要回退一下)
			if ( l>0 && sum+nums[l-1]>=s )
                res = min(res,r-l+1);
        }
		//步骤五：返回最大长度。
        return res==INT_MAX?0:res;
    }
};

