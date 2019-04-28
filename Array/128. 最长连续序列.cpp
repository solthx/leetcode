/*
	题目描述：
		给定一个未排序的整数数组，找出最长连续序列的长度。
		
		示例:

		输入: [100, 4, 200, 1, 3, 2]
		输出: 4
		解释: 最长连续序列是 [1, 2, 3, 4]。它的长度为 4。

	题目解析：
		方法一：
			简单粗暴，先排序后判断
			
		方法二：	
			1. 用哈希表存储每个端点值对应连续区间的长度
			2. 若数已在哈希表中：跳过不做处理
			3. 若是新数加入：
				3.1 取出其左右相邻数已有的连续区间长度 left 和 right
				3.2 计算当前数的区间长度为：cur_length = left + right + 1
				3.3 根据 cur_length 更新最大长度 max_length 的值
				3.4 更新区间两端点的长度值
				
		方法三:
			用set（这不还是O(NlogN)
            把数组里的每个值丢入set，
            然后重新遍历原数组，对于每个元素，删完左区间，再删右区间，
            每删一个都给计数器加一，最后得到区间长度
            然后取最大长度
*/


class Solution1 {
public:
    int longestConsecutive(vector<int>& nums) {
        /*
            先排序，再判断，O(NlogN)
        */
		if( nums.size()<1 ) return 0;
        sort(nums.begin(),nums.end());
        
        int res = 1,cnt=1;
        for ( int i=1; i<nums.size(); ++i ){
            
            if ( nums[i]==nums[i-1]+1 ) cnt++;
            else if ( nums[i]==nums[i-1] ) continue;
            else{
                
                res = max(res,cnt);
                cnt = 1;
            }
        }
        
        return max(res,cnt);
};

class Solution2 {
public:
    int longestConsecutive(vector<int>& nums) {
        
        /*
            方法二：
                1. 用哈希表存储每个端点值对应连续区间的长度
                2. 若数已在哈希表中：跳过不做处理
                3. 若是新数加入：
                    3.1 取出其左右相邻数已有的连续区间长度 left 和 right
                    3.2 计算当前数的区间长度为：cur_length = left + right + 1
                    3.3 根据 cur_length 更新最大长度 max_length 的值
                    3.4 更新区间两端点的长度值
        */
        if( nums.size()<1 ) return 0;
        unordered_map<int,int> m;
        int res = 0,left_bound,right_bound;
        for ( int i=0; i<nums.size(); ++i ){
            if ( !m.count(nums[i]) ){
                m[nums[i]] = 1;          
                if ( m.count(nums[i]-1) ){
                    m[nums[i]] += m[nums[i]-1];
                }
                if ( m.count(nums[i]+1) ){
                    m[nums[i]] += m[nums[i]+1];
                }
                //更新
                if ( m.count(nums[i]-1) ){
                    left_bound = nums[i]-m[nums[i]-1];
                    m[left_bound] = m[nums[i]];
                }
                if ( m.count(nums[i]+1) ){
                    right_bound = nums[i]+m[nums[i]+1];
                    m[right_bound] = m[nums[i]];
                }
            }
            res = max(res,m[nums[i]]);            
        }
        return res;
     
};


class Solution3 {
public:
    int longestConsecutive(vector<int>& nums) {
        /*
            方法三：用set（这不还是O(NlogN)
            把数组里的每个值丢入set，
            然后重新遍历原数组，对于每个元素，删完左区间，再删右区间，
            每删一个都给计数器加一，最后得到区间长度
            然后取最大长度
            
        */
        unordered_set<int> s;
        int res=0,cnt=0,point;
        if( nums.size()<1 ) return 0;
        for ( int e:nums ) s.insert(e);
        for ( int e:nums ){
            cnt=0;
            point = e;
            while( s.erase(point) ){ 
                cnt++;
                point--;
            }
            point = e+1;
            while( s.erase(point) ){
                cnt++;
                point++;
            }
            res = max(res,cnt);
        }
        return res;
    }
};