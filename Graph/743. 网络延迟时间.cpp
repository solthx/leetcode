/*
    问题描述:
        有 N 个网络节点，标记为 1 到 N。

        给定一个列表 times，表示信号经过有向边的传递时间。 times[i] = (u, v, w)，其中 u 是源节点，v 是目标节点， w 是一个信号从源节点传递到目标节点的时间。

        现在，我们向当前的节点 K 发送了一个信号。需要多久才能使所有节点都收到信号？如果不能使所有节点收到信号，返回 -1。

        注意:

        N 的范围在 [1, 100] 之间。
        K 的范围在 [1, N] 之间。
        times 的长度在 [1, 6000] 之间。
        所有的边 times[i] = (u, v, w) 都有 1 <= u, v <= N 且 0 <= w <= 100。

    问题分析:
        即找出从k节点，到 每一个节点的最短路径 中， 最长的那条. 
        注意判断连通性.

        之所以记录这题，是因为。。。这好像是我在lc上遇到的第一个最短路问题..

        但数据量小的可怜。。

        可以dijkstra邻接矩阵实现，邻接表实现，堆优化。

        下次再试试spfa的解法把。。。 先放着 
*/

# define inf 0x3f3f3f3f
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int N, int K) {
        int res=0;
        vector<int> dis(N+1, inf);
        vector<vector<int>> mp(N+1, vector<int>(N+1, inf));
        for ( auto p:times ){
            mp[p[0]][p[1]] = p[2];
            if ( p[0]==K ){
                dis[p[1]] = p[2];
            }
        }
        vector<bool> vis( N+1, false );
        vis[K] = true;
        int cnt = 1;
        while( 1 ){
            int e = -1, mini = inf;
            for ( int i=1; i<=N; ++i )
                if ( !vis[i] && dis[i]<mini ){
                    mini = dis[i];
                    e = i;
                }
            if ( e==-1 ) break;
            vis[e] = true;
            res = max( res, dis[e] );
            ++cnt;
            for ( int i=1; i<=N; ++i ){
                if ( !vis[i] && dis[i]>dis[e]+mp[e][i] ){
                    dis[i] = dis[e]+mp[e][i];
                }
            }
        }
        return (cnt==N)?res:-1;
    }
};