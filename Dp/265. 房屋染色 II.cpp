/**
    问题描述：
        这里有n个房子在一列直线上，现在我们需要给房屋染色，共有k种颜色。每个房屋染不同的颜色费用也不同，
        你需要设计一种染色方案使得相邻的房屋颜色不同，并且费用最小。费用通过一个nxk 的矩阵给出，
        比如cost[0][0]表示房屋0染颜色0的费用，cost[1][2]表示房屋1染颜色2的费用。

        样例1
            输入:
            costs = [[14,2,11],[11,14,5],[14,3,10]]
            输出: 10
            说明:
            三个屋子分别使用第1,2,1种颜色，总花费是10。
 
    问题分析：
        dp[i][k] 记录了前i个房子满足条件后且第i个房子颜色为k的最小花费数
        
        状态转移公式很好想
            dp[i][k] = cost[i] + min( dp[i-1][1],  dp[i-1][2], ..., dp[i-1][k]);

        如果每次都暴力搜索前一个的最小值的话， 时间开销会很大。。

        这里的一个小技巧是，每次都记录dp[i-1][1~k]的最小和次小，以及对应的颜色，
        在进行状态更新的时候， 如果当前颜色和最小的那个颜色相同，那就加次小的，
        否则就默认加最小的那个。。
        这样优化一下，速度会一下子上去。。
 */

 class Solution {
public:
    /**
     * @param costs: n x k cost matrix
     * @return: an integer, the minimum cost to paint all houses
     */
    int minCostII(vector<vector<int>> &costs) {
        // write your code here
        int n = costs.size();
        if ( n<=0 ) return 0;
        int k = costs[0].size();
        vector<vector<int>> dp( n+1, vector<int>(k,0));
        int res=INT_MAX, mini;
        // p1记录了dp[i-1]中的最小cost的颜色和最小cost
        // p2记录了第二小
        pair<int,int> p1,p2,t1,t2; // <color, cost_mini>
        p1.first = p2.first = -1;
        p2.second = p1.second = 0;
        for ( int i=1; i<=n; ++i ){
            t1.second = t2.second = INT_MAX;
            for ( int color=0; color<k; ++color ){
                //mini = helper( dp, i-1, color, k );
                // 更新前i个元素，以各种color颜色为结尾的最小cost
                if ( p1.first!=color ){
                    dp[i][color] = costs[i-1][color] + p1.second;
                }else{
                    dp[i][color] = costs[i-1][color] + p2.second;
                }
                // 更新t1,t2，用来更新下一个p1,p2
                if ( dp[i][color]<t1.second ){
                    t2.first = t1.first;
                    t2.second = t1.second;
                    t1.first = color;
                    t1.second = dp[i][color];
                }else if ( dp[i][color]<t2.second ){
                    t2.first = color;
                    t2.second = dp[i][color];
                }
                if ( i==n )
                    res = min(res, dp[i][color]);
            }
            // 更新p1, p2
            p1 = t1;
            p2 = t2;
        }
        return res;
    }
    
    // 每次都主动搜索前i-1元素中 各个颜色的最小cost
    int helper( vector<vector<int>> & dp, int idx, int color, int k ){
        int res=INT_MAX;
        for ( int i=0; i<k; ++i ){
            if ( i!=color )
                res = min(res, dp[idx][i]);
        }
        return res;
    }
    
};