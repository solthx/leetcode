/*
    问题描述:
        给你一个整数数组 target 。一开始，你有一个数组 A ，它的所有元素均为 1 ，你可以执行以下操作：
        令 x 为你数组里所有元素的和
        选择满足 0 <= i < target.size 的任意下标 i ，并让 A 数组里下标为 i 处的值为 x 。
        你可以重复该过程任意次
        如果能从 A 开始构造出目标数组 target ，请你返回 True ，否则返回 False 。

         

        示例 1：

        输入：target = [9,3,5]
        输出：true
        解释：从 [1, 1, 1] 开始
        [1, 1, 1], 和为 3 ，选择下标 1
        [1, 3, 1], 和为 5， 选择下标 2
        [1, 3, 5], 和为 9， 选择下标 0
        [9, 3, 5] 完成
        示例 2：

        输入：target = [1,1,1,2]
        输出：false
        解释：不可能从 [1,1,1,1] 出发构造目标数组。
        示例 3：

        输入：target = [8,5]
        输出：true
         

        提示：

        N == target.length
        1 <= target.length <= 5 * 10^4
        1 <= target[i] <= 10^9

    问题分析:
        分析一下本题的依赖关系可以知道，

        从前向后推，会有 N^N 种情况，
        从[1,1,1,1,1..,1]开始
        即，第i次的和丢到哪个位置上，一共N个位置..

        但是！ 从后向前推的话，一定是只有一种情况！！
        如果已经得到了
        nums = [A1, ... Ai,.., An]

        那么max(nums)一定就是上一层所有区间加成的和，

        假设上一层所有元素的和放到了第j个位置上
        那么 sums(nums) - max(nums) 就是上一层 除了nums[j]以外
        所有元素的和，假设 exsum=sums(nums) - max(nums)

        那么就可以推出，在上一层中，第j个位置原本的值的大小就是:
            max(nums) - exsum
        然后我们就可以把数组还原成了上一层的状态..

        然后按着这个逻辑，可以把数组还原成最初的状态，
        最初的状态就是全1的状态。。 同时，如果得到的nums[j]<=0了，
        那么一定非法，说明还原不到最初的状态，直接返回false就行了..

        所以我们就维护一个堆，来保存nums，这样就能直接返回当前数组里的最大值了 

        收获:
            本题是逆推思想的应用。。。抓依赖关系之后，如果可以从后一个状态推回前一个状态，
            同时能够大幅度的减少复杂度，那么可以用逆推来做!  
*/
#define ll long long
class Solution {
public:
    bool isPossible(vector<int>& target) {
        priority_queue<ll> q; //大顶堆
        for(auto&d:target)
            q.push(d);
        ll x = target.size(),sums=0;
        for(auto&d:target) // 求和
            sums+=d;
        while(q.size()>0 && q.top()>1) {
            ll cur = q.top(); q.pop();
            // cur是当前最大值，pre是当前最大值在上一层状态中对应的值
            ll pre = cur - (sums-cur);
            sums -= cur;  // sums减去当前最大值
            sums += pre;  // 然后再加上上一层对应的值，就变成了上一层状态的sums
            q.push(pre);
            if (pre<=0) return false; // 不可能的情况
        }
        return true;
    }
};