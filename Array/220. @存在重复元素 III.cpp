/*
	题目描述：
		给一个数组，看是否存在i和j使得：
			i和j的差绝对值小于等于k
			nums[i]和nums[j]的差的绝对值小于等于t

	解决思路：
		|i-j|<=k  ： 
			维护一个窗口大小为k
			
		|i-j|<=k && |nums[i]-nums[j]|<=t
		=> 在大小为k的窗口中， 存在|nums[i]-nums[j]|<=t
		=> 设i为遍历游标，找到首个比nums[i]大的值a，
		看|nums[i]-a|<=t是否满足（因为区间内的每一个值都可以是nums[j]）
		只要存在就满足要求。
		
*/

class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        if (t<0 || k<=0) return false;
        if ( nums.size()<=1 ) return false;
        //超时解法O(N*k)
        // for ( int i=0; i<nums.size(); ++i ){
        //     for ( int j=max(i-k,0); j<i; ++j ){
        //         if ( abs((long)nums[i]-(long)nums[j])<=(long)t ) return true;
        //     }
        // }
        
        //O(N*logK)
        //维护一个有K个节点的平衡二叉树
        //找比nums[i]小的最大值和比nums[i]大的最小值
        set<long> s; //维护一个大小为k的窗口
        set<long> :: iterator it;
        int i=0,mi;
        for ( int i=0; i<nums.size(); ++i ){
            // 窗口保证了i与j之间的差最大为k
            // 只要在窗口中找到了有元素落在了[nums[i]-t,nums[i]+t] 这个区间上
            // 那么就返回true
            // 注意，这里的思路就是：
            // 找到首个大于nums[i]-t的值，然后看这个值与nums[i]具体差多少！
            it = s.lower_bound((long)nums[i]-(long)t);
            if ( it!=s.end() && abs((long)*it - (long)nums[i])<=t ) return true;
            s.insert(nums[i]);
            if ( s.size()>k ) s.erase(nums[i-k]); 
        }
        return false;
    }
};