/*
	问题描述：
		给你一个没有排序的数组，请将原数组就地重新排列满足如下性质

		nums[0] <= nums[1] >= nums[2] <= nums[3]....
		Example
		样例 1:

		输入: [3, 5, 2, 1, 6, 4]
		输出: [1, 6, 2, 5, 3, 4]
		解释: 这个问题可能有多种答案, [2, 6, 1, 5, 3, 4] 同样可以.
		样例 2:

		输入: [1, 2, 3, 4]
		输出: [2, 1, 4, 3]

	问题分析：
		方法一：
			O(NlogN) 先排序，再交换
		
		方法二：
			O(N)，找规律可以发现
			nums[0] <= nums[1] >= nums[2] <= nums[3]....
			i是奇数的时候， nums[i] >= nums[i-1]
			i是偶数的时候， nums[i] <= nums[i-1]
			
			然后就可以写程序了，不满足的就交换
*/

class Solution1 {
public:
    /*
     * @param nums: A list of integers
     * @return: nothing
     */
    void wiggleSort(vector<int> &nums) {
        // write your code here
        if ( nums.size()<2 ) return ;
        sort(nums.begin(),nums.end(),cmp);
        for ( int i=0; i<nums.size()-1; i+= 2 )
            swap(nums[i],nums[i+1]);
    }
    static bool cmp(int a,int b){
        return a>b;
    }
};

class Solution2 {
public:
    /*
     * @param nums: A list of integers
     * @return: nothing
     */
    void wiggleSort(vector<int> &nums) {
        // write your code here
        for ( int i=1; i<nums.size(); i++ ){
            if ( (i%2==0 && nums[i]>nums[i-1]) || (i%2==1 && nums[i]<nums[i-1] ) )
                swap(nums[i],nums[i-1]);
        }
    }
};