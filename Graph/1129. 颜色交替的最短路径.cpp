/*
    问题描述:
        在一个有向图中，节点分别标记为 0, 1, ..., n-1。这个图中的每条边不是红色就是蓝色，且存在自环或平行边。

        red_edges 中的每一个 [i, j] 对表示从节点 i 到节点 j 的红色有向边。
        类似地，blue_edges 中的每一个 [i, j] 对表示从节点 i 到节点 j 的蓝色有向边。

        返回长度为 n 的数组 answer，其中 answer[X] 是从节点 0 到节点 X 的最短路径的长度，
        且路径上红色边和蓝色边交替出现。如果不存在这样的路径，那么 answer[x] = -1。

        示例 1：

        输入：n = 3, red_edges = [[0,1],[1,2]], blue_edges = []
        输出：[0,1,-1]

    问题分析:
        好久没做图的题了。。
        思路不是太难想，dijkstra的dis数组的变形，
            dis[i][0]  0到达i的最短路，且前一个经过的边是红
            dis[i][1]  0到达i的最短路，且前一个经过的边是蓝
        然后设一个red_queue和blue_queue, 使用bfs来不停的更新。

        red_queue是保存了上一个经过了红边后的路径节点，用于更新dis[i][1]
        blue_queue是保存了上一个经过了蓝边后的路径节点，用于更新dis[i][0]

        最终的res[i]=min(dis[i][0],dis[i][1])
        如果res[i]还是INT_MAX，表示不可达，直接-1          
 */

 class Solution {
public:
    vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& red_edges, vector<vector<int>>& blue_edges) {
        
        // dis[i][0]  0到达i的最短路，且前一个是红
        // dis[i][1]  0到达i的最短路，且前一个是蓝

        // 5:04
        // 5:39
        vector<int> res(n);
        vector<vector<int>> dis( n+1, vector<int>(2,INT_MAX));
  
        vector<vector<int>> blue(n+1);  // blue[i]是经过蓝边，i能够抵达的地方
        vector<vector<int>> red(n+1);   // red[i]是经过红边，i能抵达的地方
        
        queue<int> blue_queue;
        queue<int> red_queue;
 
        for ( auto v:red_edges ){
            red[v[0]].push_back(v[1]);
            if ( v[0]==0 ){
                dis[v[1]][0] = 1;
                red_queue.push( v[1] );
            }
        }
        for ( auto v:blue_edges ){
            blue[v[0]].push_back(v[1]);
            if ( v[0]==0 ){
                dis[v[1]][1] = 1;
                blue_queue.push(v[1]);
            }
        }
        
        while( !red_queue.empty() || !blue_queue.empty() ){
            if ( red_queue.size()>0 ){
                int i_red = red_queue.front(); red_queue.pop();
                for ( int i=0; i<blue[i_red].size(); ++i ){
                    int pass_blue_v = blue[i_red][i];
                    if (  dis[i_red][0]+1 < dis[ pass_blue_v ][1] ){
                        dis[ pass_blue_v ][1] = dis[i_red][0]+1;
                        blue_queue.push(pass_blue_v);
                    }
                }
            }
            
            if ( blue_queue.size()>0 ){
                int i_blue = blue_queue.front(); blue_queue.pop();
                for ( int i=0; i<red[i_blue].size(); ++i ){
                    int pass_red_v = red[i_blue][i];
                    if (  dis[i_blue][1]+1 < dis[ pass_red_v ][0] ){
                        dis[ pass_red_v ][0] = dis[i_blue][1]+1;
                        red_queue.push(pass_red_v);
                    }
                }
            }
        }
        
        res[0]=0;
        for ( int i=1; i<n; ++i ){
            res[i] = min( dis[i][0], dis[i][1]);
            if (res[i]==INT_MAX) res[i] = -1;
        }
        return res;
        
    }
};