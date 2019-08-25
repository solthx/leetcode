/*
    问题描述:
        公司计划面试 2N 人。第 i 人飞往 A 市的费用为 costs[i][0]，飞往 B 市的费用为 costs[i][1]。
        返回将每个人都飞到某座城市的最低费用，要求每个城市都有 N 人抵达。

        示例：

        输入：[[10,20],[30,200],[400,50],[30,20]]
        输出：110
        解释：
        第一个人去 A 市，费用为 10。
        第二个人去 A 市，费用为 30。
        第三个人去 B 市，费用为 50。
        第四个人去 B 市，费用为 20。

        最低总费用为 10 + 30 + 50 + 20 = 110，每个城市都有一半的人在面试。
        
        提示：

        1 <= costs.length <= 100
        costs.length 为偶数
        1 <= costs[i][0], costs[i][1] <= 1000

    问题分析：
        差值排序.
        一个新思路: 从差值入手
          令  diff = cost[i][0] (去A的费用) - cost[i][1] (去B的费用)             
        
        如果diff大于0， 说明去A比去B要多花diff
        如果diff小于0， 说明去A比去B要少花diff

        假设先集体去B， cost = cost[0][1] + .. +cost[n-1][1]
        然而，因为要有一半的人要去A，所以需要把 cost中 n/2个 cost[i][1] 换成 cost[i][0]
        也就是说要对cost 加上 n/2个 ( cost[i][0] - cost[i][1] ) ，也就是加上n/2个diff
        至于是哪n/2个，那当然是最小的那n/2个了， 越小越好.. 因为我们希望总费用最低嘛..

        所以，我们先求一个sum{B}，
        然后，按给(cost[i][0] - cost[i][1])降序排序，
        然后选取前n/2个最小的加回去
        就是答案.

        感觉这种贪心方法 比较适用于解决 互斥取物品，求取最大最小值
*/

class Solution {
public:
    int twoCitySchedCost(vector<vector<int>>& costs) {
        vector<int> nums;
        int res = 0;
        for ( auto e:costs ){
            nums.push_back( e[0]-e[1] );
            res += e[1];
        }
        sort( nums.begin(), nums.end() );
        for ( int i=0; i<costs.size()/2; ++i ){
            res += nums[i];
        }
        return res;
    }
};