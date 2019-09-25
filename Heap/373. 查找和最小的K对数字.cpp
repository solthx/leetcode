/*
    问题描述:
        给定两个以升序排列的整形数组 nums1 和 nums2, 以及一个整数 k。

        定义一对值 (u,v)，其中第一个元素来自 nums1，第二个元素来自 nums2。

        找到和最小的 k 对数字 (u1,v1), (u2,v2) ... (uk,vk)。

        示例 1:

        输入: nums1 = [1,7,11], nums2 = [2,4,6], k = 3
        输出: [1,2],[1,4],[1,6]
        解释: 返回序列中的前 3 对数：
            [1,2],[1,4],[1,6],[7,2],[7,4],[11,2],[7,6],[11,4],[11,6]
        示例 2:

        输入: nums1 = [1,1,2], nums2 = [1,2,3], k = 2
        输出: [1,1],[1,1]
        解释: 返回序列中的前 2 对数：
             [1,1],[1,1],[1,2],[2,1],[1,2],[2,2],[1,3],[1,3],[2,3]
        示例 3:

        输入: nums1 = [1,2], nums2 = [3], k = 3 
        输出: [1,3],[2,3]
        解释: 也可能序列中所有的数对都被返回:[1,3],[2,3]

    问题分析:
        暴力的方法就不讲了，很好实现.

        一般第K大的问题，八九不离十就是堆了(尽管暴力也是可以用堆)

        分析本题的过程中，会发现，貌似是一个没有规律推进的，一个n^2的过程

        KlogK 利用堆的核心思想就是，额外利用了 <nums1[i] , nums2[j+1]> 一定在 <nums1[i] , nums2[j]> 的后面
        这一性质，所以先把所有的 <nums1[0~i], nums[0]> 放入堆里，
        每弹出一个 <nums1[i], nums[j]> 就把  <nums1[i], nums[j+1]> 丢进堆里.
        https://leetcode.com/problems/find-k-pairs-with-smallest-sums/discuss/84551/simple-Java-O(KlogK)-solution-with-explanation
        这个回答的图，描述的很形象
*/

# define node pair<int,pair<int,int>>
class Solution {
public:
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        int i=0, j=0;
        auto cmp = [](node & a, node & b){
            return a.first > b.first;
        };
        if ( k==0 || nums1.size()==0 || nums2.size()==0 ) return {};
        vector<vector<int>> res;
        priority_queue< node, vector<node>, decltype(cmp)> q(cmp);
        for ( int i=0; i<nums1.size(); ++i )
            q.push({ nums1[i]+nums2[0], {i,0}} );
        while( q.size()>0 && k>0 ){
            pair<int,int> cor = q.top().second; q.pop();
            int i = cor.first, j=cor.second;
            res.push_back({nums1[i], nums2[j]});
            if ( j+1<nums2.size() )
                q.push( {nums1[i]+nums2[j+1], {i,j+1}} );
            --k;
        }
        return res;
    }
};