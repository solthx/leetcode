/*
    问题描述：
        给定一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c ，使得 a + b + c = 0 ？找出所有满足条件且不重复的三元组。

        注意：答案中不可以包含重复的三元组。

        例如, 给定数组 nums = [-1, 0, 1, 2, -1, -4]，

        满足要求的三元组集合为：
        [
        [-1, 0, 1],
        [-1, -1, 2]
        ]

    问题分析：
        利用twoSum的基础上再来个twoSum,
        要注意的点是，过滤重复的元素，
        对于排序过的数，利用：
        for ( .. ; ..  ; ++i)
            if( i-1存在 && nums[i]==nums[i-1] )
                continue；
        来过滤掉重复的元素判断，
        这个方法在之前也遇到过。。这里再记一下。。
        
        当遇到nums[i]+nums[j]==target的时候，
        也可以利用这个方法同时过滤掉相同元素来更新i和j

 */

 class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int i=0,j=nums.size()-1, target;
        sort(nums.begin(),nums.end());
        vector<vector<int>> res;
        for( int k=0; k<nums.size(); ++k  ){
            if ( k>0 && nums[k]==nums[k-1] ) continue;
            target = nums[k] * -1;
            i=k+1; j=nums.size()-1;
            while(  i<j ){
                if ( nums[i]+nums[j]>target ) --j;
                else if ( nums[i]+nums[j]<target ) ++i;
                else{
                    res.push_back({ nums[i],nums[j],nums[k] });
                    while( i<j && nums[i]==nums[i+1] ) ++i;
                    while( i<j && nums[j]==nums[j-1] ) --j;
                    ++i;
                    --j;
                }
            }
        }
        return res;
    }
};