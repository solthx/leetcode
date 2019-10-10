/*
    问题描述:
        给定一个有 n 个整数的数组，你需要找到满足以下条件的三元组 (i, j, k) ：
        0 < i, i + 1 < j, j + 1 < k < n - 1
        子数组 (0, i - 1)，(i + 1, j - 1)，(j + 1, k - 1)，(k + 1, n - 1) 的和应该相等。
        这里我们定义子数组 (L, R) 表示原数组从索引为L的元素开始至索引为R的元素。

        示例:

        输入: [1,2,1,2,1,2,1]
        输出: True
        解释:
        i = 1, j = 3, k = 5. 
        sum(0, i - 1) = sum(0, 0) = 1
        sum(i + 1, j - 1) = sum(2, 2) = 1
        sum(j + 1, k - 1) = sum(4, 4) = 1
        sum(k + 1, n - 1) = sum(6, 6) = 1
         
        注意:

        1 <= n <= 2000。
        给定数组中的元素会在 [-1,000,000, 1,000,000] 范围内。

    问题分析:
        目标是找i, j, k，
        暴力遍历每一个j， 分成了两个区间，
        然后看左区间是否能分成两个等值数组和，
        再看右区间能不能分成等值数组和，
        如果上面两个都可以，那就看左右两边的 等值数组和是否相等，
        上面三个都满足就返回true 
        复杂度为O(N^2)
*/

class Solution {
public:
    bool splitArray(vector<int>& nums) {
        int n = nums.size();
        int predix[2010]={0};
        int suffix[2010]={0};
        if ( n<7 ) return false;
        for ( int i=1; i<=n; ++i ){
            predix[i] = predix[i-1] + nums[i-1];
            suffix[n-i+1] = suffix[n-i+2] + nums[n-i]; 
        }
        for ( int i=1; i<n; ++i ){
            unordered_set<int> mp;
            for ( int j=2; j<=i-2; ++j )
                if ( predix[j-1] == ( predix[i-1]-predix[j] ) )
                    mp.insert( predix[j-1] );
            for ( int j=i+1; j<n; ++j )
                if ( suffix[j+1] == (suffix[i+1]-suffix[j]) && mp.count(suffix[j+1])>0 )
                    return true;
        }
        return false;
    }

};