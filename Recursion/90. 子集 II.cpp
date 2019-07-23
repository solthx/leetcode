/*
    问题描述：
        给定一个可能包含重复元素的整数数组 nums，返回该数组所有可能的子集（幂集）。
        说明：解集不能包含重复的子集。
        示例:
        输入: [1,2,2]
        输出:
        [
            [2],
            [1],
            [1,2,2],
            [2,2],
            [1,2],
            []
        ]

    问题分析：
        比较简单的一题，这里记录一下如何过滤重复情况，
        要记住这种过滤思想，
        在进行dfs的时候，
        一般是处理当前的情况，然后下一个子问题的处理方式和当前处理方式相同，只不过是参数不同，
        但是，当处理当前情况的时候，可能会有许多重复的情况，
        举个例子，在处理当前情况的时候往往会碰到for循环，
        在for循环中，遍历没一个元素来作为处理当前情况的核心，
        但可能会存在重复元素，因此，这个时候只要判断若下一个元素和当前元素相同，就视为相同情况，
        直接过滤掉就行了。。
        
        要记住的不是这个特例，而是引申出的过滤相同情况的思想。
 */

 class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        //set<vector<int> > sets;
        vector<vector<int>> res;
        res.push_back({});
        sort(nums.begin(),nums.end());
        vector<int> v;
        helper(res, 0, nums, v);
        return res;
    }
    
    void helper( vector<vector<int>> & res, int start, vector<int> & nums, vector<int> & cur){
        for ( int i=start; i<nums.size(); ++i ){
            cur.push_back(nums[i]);
            /*if ( sets.count(cur)==0 ){
                sets.insert(cur);
                res.push_back(cur);
            }*/
            res.push_back(cur);
            helper(res, i+1, nums, cur);
            cur.pop_back();
            // 过滤相同情况
            while( i+1<nums.size() && nums[i+1] == nums[i] ) ++i;
        }
    }
};