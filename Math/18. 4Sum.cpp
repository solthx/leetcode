/*
    问题描述：
        给定一个包含 n 个整数的数组 nums 和一个目标值 target，判断 nums 中是否存在四个元素 a，b，c 和 d ，使得 a + b + c + d 的值与 target 相等？找出所有满足条件且不重复的四元组。

        注意：

        答案中不可以包含重复的四元组。

        示例：

        给定数组 nums = [1, 0, -1, 0, -2, 2]，和 target = 0。

        满足要求的四元组集合为：
        [
            [-1,  0, 0, 1],
            [-2, -1, 1, 2],
            [-2,  0, 0, 2]
        ]
    
    问题分析：
        在3Sum的基础上，在加一层循环。
        要注意，在排序后，过滤相同元素的时候，一定要是在自己的循环内比较
        例如：
            for ( int i=0; i<nums.size(); ++i ){
                ...
                if ( i-1>=0 && nums[i]==nums[i-1] ) continue;
                for ( int j = i+1; j<nums.size(); ++j ){
                    ==========注意==========
                    if ( j-1>i && nums[j]==nums[j-1] ) continue;
                    ======这里要在自己的循环内判断，也就是前一项一定是j能取到的！！！======
                    ======也可以理解成j-1必须存在，而j从i+1开始取，也就是j-1>=i+1  ，即j-1>i
                    .....
                    .....
                }
                ...
            }
 */
 
 class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> res;
        sort( nums.begin(), nums.end() );
        int t1,t2,l,r;
        for ( int i=0; i<nums.size(); ++i ){
            t1 = target - nums[i];
            if ( i-1>=0 && nums[i]==nums[i-1] ) continue;
            for ( int j = i+1; j<nums.size(); ++j ){
                if ( j-1!=i && nums[j]==nums[j-1] ) continue;
                t2 = t1 - nums[j];
                l = j+1;
                r = nums.size()-1;
                while( l<r ){
                    if ( nums[l]+nums[r] < t2 ){
                        ++l;
                    }else if ( nums[l]+nums[r] > t2 ){
                        --r;
                    }else{
                        res.push_back({nums[i],nums[j],nums[l],nums[r]});
                        while( l-1!=j && l<r && nums[l]==nums[l-1] ) ++l;
                        while( l<r && nums[r]==nums[r-1] ) --r;
                        ++l;
                        --r;                        
                    }
                }
            }
        }
        return res;
    }
};