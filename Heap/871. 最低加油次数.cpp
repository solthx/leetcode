/*
    问题描述:
        汽车从起点出发驶向目的地，该目的地位于出发位置东面 target 英里处。

        沿途有加油站，每个 station[i] 代表一个加油站，它位于出发位置东面 station[i][0] 英里处，并且有 station[i][1] 升汽油。

        假设汽车油箱的容量是无限的，其中最初有 startFuel 升燃料。它每行驶 1 英里就会用掉 1 升汽油。

        当汽车到达加油站时，它可能停下来加油，将所有汽油从加油站转移到汽车中。

        为了到达目的地，汽车所必要的最低加油次数是多少？如果无法到达目的地，则返回 -1 。

        注意：如果汽车到达加油站时剩余燃料为 0，它仍然可以在那里加油。如果汽车到达目的地时剩余燃料为 0，仍然认为它已经到达目的地。

        

        示例 1：

        输入：target = 1, startFuel = 1, stations = []
        输出：0
        解释：我们可以在不加油的情况下到达目的地。
        示例 2：

        输入：target = 100, startFuel = 1, stations = [[10,100]]
        输出：-1
        解释：我们无法抵达目的地，甚至无法到达第一个加油站。
        示例 3：

        输入：target = 100, startFuel = 10, stations = [[10,60],[20,30],[30,30],[60,40]]
        输出：2
        解释：
        我们出发时有 10 升燃料。
        我们开车来到距起点 10 英里处的加油站，消耗 10 升燃料。将汽油从 0 升加到 60 升。
        然后，我们从 10 英里处的加油站开到 60 英里处的加油站（消耗 50 升燃料），
        并将汽油从 10 升加到 50 升。然后我们开车抵达目的地。
        我们沿途在1两个加油站停靠，所以返回 2 。
 

    提示：

        1 <= target, startFuel, stations[i][1] <= 10^9
        0 <= stations.length <= 500
        0 < stations[0][0] < stations[1][0] < ... < stations[stations.length-1][0] < target

    问题分析：
        方法一： 堆
            可以维护一个集合，这个集合就是当前可以到达所有位置，然后每次从这个集合里面挑出能够加油最多的那一个，
            然后加上，再更新这个集合（看是否又可以抵达到新的油站），直到能够抵达target为止。。

            这个集合可以用set来维护也可以用堆来维护...
            复杂度O（NlogN)
        
        方法二： 动态规划
            跟方法一的思路差不多，可以用dp[i]保存加i次油后能够抵达的最远距离，
            然后更新加第i+1次油的时候，可以遍历所有油站，来选出最大的那个.. （可以通过vis数组来标记哪个油站被用过了，
            这里是直接修改stations来做的，加完油就把对应的油站给归0，让他只能被加一次..
            复杂度O(N^2)
*/

class Solution1 {
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        priority_queue<int> q; // 当前能够访问的油站，可以加的油量
        q.push(startFuel);
        if (startFuel>=target) return 0;
        int l=0, r = 0,step=0;
        while( q.size()>0){
            int cur = q.top(); q.pop();
            r += cur;  // 每次都加最多的油
            for(int i=l; i<stations.size(); l=++i){
                // 更新q， 因为每个油站只能被访问一次，且是有序的
                // 所以可以滚动来存.. 这一步复杂度平摊下来就是O(N)了
                if ( r>=stations[i][0] ){
                    q.push(stations[i][1]);
                }else break;
            }
            if ( r>=target ) return step;
            ++step;
        }
        return -1;
    }
};


class Solution2 {
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        int dp[501]={0},e; // 走i步能走的最远距离
        dp[0] = startFuel;
        if (startFuel>=target) return 0;
        for(int i=1; i<=stations.size(); ++i){
            e=-1;
            for(int j=0; j<stations.size() && stations[j][0]<=dp[i-1]; ++j){
                if ( e==-1 || stations[e][1]<stations[j][1])
                    e = j;
            }
            if (e==-1) continue;
            dp[i] = dp[i-1] + stations[e][1];
            stations[e][1] = 0;
            if (dp[i]>=target) return i;
        }
        return -1;
    }
};