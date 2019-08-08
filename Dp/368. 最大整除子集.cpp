/*
    问题描述:
        给出一个由无重复的正整数组成的集合，找出其中最大的整除子集，
        子集中任意一对 (Si，Sj) 都要满足：Si % Sj = 0 或 Sj % Si = 0。
        如果有多个目标子集，返回其中任何一个均可。

        示例 1:
        输入: [1,2,3]
        输出: [1,2] (当然, [1,3] 也正确)
        
        示例 2:
        输入: [1,2,4,8]
        输出: [1,2,4,8]

    问题分析:
        先排序,保证i之前的元素都比第i个元素小
        
        dp[i]保存了 dp[i]记录了最大整除子集的元素个数，且集合里的最大元素是nums[i]
        
        记录个数是为了找最大个数, 当扫描到nums[i]的时候，找出所有能被nums[i]整除的
        dp[0~i-1]的最大值，然后加上当前元素. （ nums[i]能整除nums[j]，
        那么以nums[j]为最大值的 这种最大整除子集里的所有元素也都能被nums[i]整除) 
    
        path[i] 记录了 在nums里所有能被nums[i]整除的数中 ，最大整除子集最大的那个index
        这个index也就是当初更新dp[i]时选择的那个index

        记录path是为了, 本题并不是让求最大子集个数，而是返回这个子集，所以需要path[i]来记录
 */

class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        int n=nums.size();
        if ( n<=0 ) return {};
        int idx=-1, maxi=-1;
        sort(nums.begin(),nums.end());
        
        vector<int> dp(n,1);  // dp[i]记录了最大整除子集的元素个数，且集合里的最大元素是nums[i]
        vector<int> path(n);  // path记录了 在nums里所有能被nums[i]整除的数中 ，最大整除子集最大的那个index
        
        for ( int i=0; i<nums.size(); ++i ){
            int cur_maxi=-1, cur_idx=-1;
            for ( int j=i-1; j>=0; --j ){
                // 向前找所有能被nums[i]整除的最大整除子集中最大个数的那个
                if ( nums[j]!=0 && nums[i]%nums[j]==0 && dp[j]>cur_maxi ){
                    cur_maxi = dp[j];
                    cur_idx = j;
                }
            }
            
            // 用最大的那个更新
            // 并记录path 用于后面找到这个子集
            path[i] = cur_idx;
            if ( cur_idx!=-1 )
                dp[i]+=dp[cur_idx];
            
            dp[i]++;
            if ( dp[i]>maxi ){
                maxi = dp[i];
                idx = i;
            }
        }
        vector<int> res;
        while( idx>=0 ){
            res.push_back(nums[idx]);
            idx = path[idx];
        }
        return vector<int>(res.rbegin(),res.rend());
    }
};