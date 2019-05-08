/*
	题目描述：	
		给定长度为 n 的整数数组 nums，其中 n > 1，返回输出数组 output ，其中 output[i] 等于 nums 中除 nums[i] 之外其余各元素的乘积。

		示例:

		输入: [1,2,3,4]
		输出: [24,12,8,6]
		说明: 请不要使用除法，且在 O(n) 时间复杂度内完成此题。

		进阶：
		你可以在常数空间复杂度内完成这个题目吗？（ 出于对空间复杂度分析的目的，输出数组不被视为额外空间。）
		
	题目分析：
		一	开始看错题了，以为是所有情况的乘积除去nums中的元素， 但并不是那样
			而是除去nums[i]的其他所有元素的乘积。。
			这一下就简单多了。。
			如果不让用除法的话：
				le[i]表示[0,i]这个区间内元素的乘积，
				ri[i]表示[i,n)这个区间内的元素的乘积
				res[i] = le[i-1]*ri[i+1]
				为了方便处理边界情况，le和ri从1开始记，第0号元素和第n+1号元素都是1（乘了和没乘一样
		
			关于进阶：
				不要再使用le和ri了，数据一直保存在res里，
				第一趟的时候，res[i]就计算1~i-1的乘积
				然后再反着来一遍，计算[i+1,n)的乘积，在乘给res[i]
				效果是一样的。
*/

class Solution1 {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        //空间复杂度O(N)
        int n=nums.size();
        vector<int> res;
        vector<int> le(n+1,1);
        vector<int> ri(n+2,1);
        for ( int i=0; i<n; ++i ){
            le[i+1] = nums[i]*le[i];
            ri[n-i] =  nums[n-i-1] * ri[n-i+1]; 
        }
        for ( int i=1; i<=n; ++i ){
            res.push_back(le[i-1]*ri[i+1]);
        }
        return res;
    }
    
};


class Solution2 {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        //空间复杂度O(1)
        /*
			思想和上面一样，只是一直都用res来保存
		*/
		int n=nums.size();
        vector<int> res(n,1);
        int cur=1;
        for ( int i=1; i<n; ++i ){
           cur *= nums[i-1];
            res[i] = cur;
        }
        cur = 1;
        for ( int i=n-2; i>=0; --i ){
            cur *= nums[i+1];    
            res[i] *= cur;
        }
        return res;
    }
    
};