/*
	问题描述：
		给定一个数组 nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧。你只可以看到在滑动窗口 k 内的数字。滑动窗口每次只向右移动一位。

		返回滑动窗口最大值。

		示例:

		输入: nums = [1,3,-1,-3,5,3,6,7], 和 k = 3
		输出: [3,3,5,5,6,7] 
		解释: 

		  滑动窗口的位置                最大值
		---------------               -----
		[1  3  -1] -3  5  3  6  7       3
		 1 [3  -1  -3] 5  3  6  7       3
		 1  3 [-1  -3  5] 3  6  7       5
		 1  3  -1 [-3  5  3] 6  7       5
		 1  3  -1  -3 [5  3  6] 7       6
		 1  3  -1  -3  5 [3  6  7]      7
		注意：

		你可以假设 k 总是有效的，1 ≤ k ≤ 输入数组的大小，且输入数组不为空。
	
	问题分析：
		方法一：
			每次记录最大值与其index， 移动游标，
			若新加进来的值比最大值大，则更新最大值和最大游标，
			若删除的那个元素是最大值，那么重新在区间内找最大值
			这里重新找的办法是暴力。。
			所以算法复杂度:
				最差是O(N*K),降序的情况
				最好是O(N),非降序
			
		方法二：
			为了优化找出最小值的那个流程，我们可以维护一个栈，
			每来一个元素，当前仅当栈顶元素大于当前元素，或栈空，
			才把当前元素入栈，如果不满足，就一直pop，把栈pop到满足为止
*/

class Solution1 {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> res;
        int i,cur,j=0;
        if ( nums.size()<1 || k<=0 ) return res;
        if ( k>nums.size() ) k=nums.size(); 
		//pair<index，maximum>
        pair<int,int> maxi;
        maxi.first=0;
        maxi.second = nums[0];
        for ( i=1; i<k ; ++i ){
            if ( nums[i]>maxi.second ){
                maxi.first = i;
                maxi.second = nums[i];
			//最大值取最新的那个
            }else if (nums[i]==maxi.second)
                maxi.first = i;
        }
        res.push_back(maxi.second);
        for ( ; i<nums.size(); ++i,j++ ){
			//更新最大值
            if ( nums[i]>maxi.second ){
                maxi.first = i;
                maxi.second = nums[i];
            }else if ( nums[i]==maxi.second ){
                maxi.first = i;
            }else{ //当前不是最大值，就可能会删除最大值！
                if( j==maxi.first ){
					//暴力重新找最大值
                    maxi.first = j+1;
                    maxi.second = nums[j+1];
                    for ( int t=j+2; t<=i; ++t ){
                        if ( nums[t]>maxi.second ){
                            maxi.first = t;
                            maxi.second = nums[t];
                        }
                    }
                }
            }
            res.push_back(maxi.second);
        }
        return res;        
    }
};

//============================Solution2================================


class MQueue{
    public:
        void push(int x){
            while( !q.empty() && q.back()<x )
                q.pop_back();
            q.push_back(x);
        }
    
        void pop(){
            if ( !q.empty() )
                q.pop_front();
        }
        
        int get_max(){
            return q.front();
        }
    private:
        deque<int> q;
};
class Solution2 {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> res;
        int i,cur,j=0;
        if ( nums.size()<1 || k<=0 ) return res;
        if ( k>nums.size() ) k=nums.size(); 
        MQueue q;
		//前k个
        for ( i=0; i<k; ++i ){
            q.push(nums[i]);
        }
        res.push_back(q.get_max());
        for ( ; i<nums.size(); ++i ){
			//删除的时候，才pop
            if ( nums[i-k]==q.get_max())
                q.pop();
            q.push(nums[i]);
            res.push_back(q.get_max());
        }
        return res;
    }
};