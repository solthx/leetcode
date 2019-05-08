/*
	题目描述：
		给定一个无重复元素的有序整数数组，返回数组区间范围的汇总。

		示例 1:
		输入: [0,1,2,4,5,7]
		输出: ["0->2","4->5","7"]
		解释: 0,1,2 可组成一个连续的区间; 4,5 可组成一个连续的区间。
		
		示例 2:
		输入: [0,2,3,4,6,8,9]
		输出: ["0","2->4","6","8->9"]
		解释: 2,3,4 可组成一个连续的区间; 8,9 可组成一个连续的区间。
		
	题目分析：
		正常遍历就行：
			伪代码：
				for i from 1 to N:
					如果第i个元素和前一个元素不连续:
						如果已经存在连续段：加一个 "->" + nums[i-1]
						不存在连续段，不用加(加了就会变成"a->a")
					
						
*/

class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        vector<string> res;
        if ( nums.size()<1 ) return res;
        string elem = to_string(nums[0]);
        int i,idx=0;
        for ( i=1; i<nums.size(); ++i ){
            if ( nums[i]>1+nums[i-1] ){
				//存在连续段
                if ( idx<i-1 )
                    elem = elem + "->" + to_string(nums[i-1]);
                res.push_back(elem);
                elem = to_string(nums[i]);
				//记录开始位置，用来确保是否存在连续段
                idx = i;
            }
        }
		//最后一次也来个判断
        if ( idx<i-1 )
            elem = elem + "->" + to_string(nums.back());
        res.push_back(elem);
        return res;
    }
};