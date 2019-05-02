/*
	问题描述：
		给一个数组nums和目标值k，找到数组中最长的子数组，使其中的元素和为k。如果没有，则返回0。
		样例1
		
		输入: nums = [1, -1, 5, -2, 3], k = 3
		输出: 4
		解释:
		子数组[1, -1, 5, -2]的和为3，且长度最大 
		
	题目分析：
		sum[i] 为nums的前i个元素的和 
		unordered_map的内容是： {sum[i] : i } 
		
		用HashMap, Key指i及之前元素的总和，value指当前index。
		
		对于每个i，不仅检查当前sum，也要检查(currentSum - previousSum)来看看是否与k相等。对map.containsKey(sum - k) 的理解是一个重点：
		
		举例说明：
		
			K=3
			
			Index : 0,1,2,3,4,5....
			
			Value : 2,0,2,1,1,1....
			
			Sum: 2,2,4,5,6,7
			
			Sum-K: 4
			
			map.containsKey(sum - k) : The index is 2
			
			从index0~2的总和是4了，从0~5的总和是7了，那么从3~5的总和是不是就是我们想要的3？
			
			3~5的size怎么计算呢？ ===>> i - map.get(sum - k)在这个例子里就是5-2
		
*/ 

class Solution {
public:
    /**
     * @param nums: an array
     * @param k: a target value
     * @return: the maximum length of a subarray that sums to k
     */
    int maxSubArrayLen(vector<int> &nums, int k) {
        if ( nums.size()<1 ) return 0;
        unordered_map<int,int> m;
        vector<int> sum(nums.size(),0);
        unordered_map<int,int> :: iterator it;
        //m[sum] = index;
        int idx;
        int res=0;
        sum[0]=nums[0];
        m[sum[0]] = 0;
        if ( sum[0]==k ) res = 1;
        for ( int i=1; i<nums.size(); ++i ){
            sum[i] = sum[i-1] + nums[i];
            //因为要求最长的，所以当sum相同时，我们取i最小的那个，这样减出的距离更大！
			//因此，只有当m里没有当前sum的时候，我们才将其插入 
            if ( m.count(sum[i])==0 )
                m[sum[i]] = i;
            if ( sum[i]==k ) res = i+1;
        }
        
        for ( int i=0; i<nums.size(); ++i ){
            // sum[i] - x = k 
            // x = sum[i]-k
            it = m.find(sum[i]-k);
            if ( it!=m.end() && (*it).second<=i ){
                res = max(res, i-(*it).second);
            }
        }
        return res;
    }
};

/*                      map
  idx  0  1  2  3  4  (value)
  val  1 -1  5 -2  3  
  sum  1  0  5  3  6  (key)
*/


// 空间优化
 
