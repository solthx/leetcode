/*
    问题描述:
        在节点网络中，只有当 graph[i][j] = 1 时，每个节点 i 能够直接连接到另一个节点 j。

        一些节点 initial 最初被恶意软件感染。只要两个节点直接连接，且其中至少一个节点受到恶意软件的感染，那么两个节点都将被恶意软件感染。这种恶意软件的传播将继续，直到没有更多的节点可以被这种方式感染。

        假设 M(initial) 是在恶意软件停止传播之后，整个网络中感染恶意软件的最终节点数。

        我们可以从初始列表中删除一个节点。如果移除这一节点将最小化 M(initial)， 则返回该节点。如果有多个节点满足条件，就返回索引最小的节点。

        请注意，如果某个节点已从受感染节点的列表 initial 中删除，它以后可能仍然因恶意软件传播而受到感染。

         

        示例 1：

        输入：graph = [[1,1,0],[1,1,0],[0,0,1]], initial = [0,1]
        输出：0
        示例 2：

        输入：graph = [[1,0,0],[0,1,0],[0,0,1]], initial = [0,2]
        输出：0
        示例 3：

        输入：graph = [[1,1,1],[1,1,1],[1,1,1]], initial = [1,2]
        输出：1
         

        提示：

        1 < graph.length = graph[0].length <= 300
        0 <= graph[i][j] == graph[j][i] <= 1
        graph[i][i] = 1
        1 <= initial.length < graph.length
        0 <= initial[i] < graph.length

    问题分析：
        方法一: 枚举+bfs
            转换成邻接表，然后枚举每一种情况，即删除Initial里第i个节点之后，最终的感染节点数,
            然后取最小的那个就行了.

        方法二: dfs+并查集
            顺序遍历Initial里的节点，并dfs进行染色,仅对未被染色的节点染色，染完第一个节点之后，

            所有和第一个节点在同一个连通分量里的节点都被染色了，无论其是不是在Initial里，

            对第二个第三个..同理

            在Initial里，颜色相同的节点一定不可能是结果(说明在同一个连通分量里).

            在集合Initial中，如果Initial[i]的颜色唯一，

            则说明Initial[i]所在的连通分量里 仅仅是由Initial[i]染成功的. 计算出这个连通分量里节点个数就OK了，

            用并查集来计算连通分量里节点个数..

            然后对于每一个这样的Initial[i], 取节点数最多的那个. 若存在多个，则选i最小的那个.
*/

class Solution1 {
public:
    // 枚举+BFS
    unordered_map<int, vector<int>> mp;
    int minMalwareSpread(vector<vector<int>>& graph, vector<int>& initial) {
        int res = INT_MAX;
        int cur,ret = -1;
        for ( int i=0; i<graph.size(); ++i )
            for ( int j=0; j<graph[0].size(); ++j )
                if ( graph[i][j]==1 )
                    mp[i].push_back(j);
        sort( initial.begin(), initial.end() );
        for ( auto v:initial ){
            cur = bfs( v,graph, initial );
            if ( cur<res ){
                res = cur;
                ret = v;
            }
        }
        return ret;
    }

    int bfs( int v, vector<vector<int>>& graph, vector<int>& initial ){
        bool vis[301] = {false};
        int res = 0;
        queue<int> q;
        // 初始化
        for ( auto u:initial ){
            if ( u!=v ){  // 节点v从Initial中剔除
                vis[u] = true;
                q.push(u);
            }
        }
        // 记录所有节点都被感染后的总节点数
        while( q.size()>0 ){
            res+=q.size();
            for ( int j=q.size(); j>0; --j ){
                int cur = q.front(); q.pop();
                for ( auto t:mp[cur] ){
                    if ( !vis[t]  ){
                        vis[t] = true;
                        q.push(t);
                    }
                }
            }
        }
        return res;
    }
};

// 并查集+DFS
class Solution2 {
public:
    int n;
    int color[400]={0}; // color[i]表示第i个节点的颜色
    unordered_map<int, vector<int>> mp; // 邻接表来存储
    int pre[400]; // 并查集 pre[i]若小于0，则说明是根， -pre[i]为该集合内的节点数， 若大于0则说明是其父节点

    int find( int x ){
        if ( pre[x]<0 ) return x;
        return pre[x] = find(pre[x]);
    }

    void merge( int a, int b ){
        int x = find(a);
        int y = find(b);
        if ( x==y ) return ;
        pre[x] += pre[y];
        pre[y] = x;
    }

    void fill_color( int f, int c ){
        color[f] = c;
        for ( auto v:mp[f] ){
            if ( !color[v] )
                fill_color(v, c);
            merge( f, v );
        }
    }

    int minMalwareSpread(vector<vector<int>>& graph, vector<int>& initial) {
        if ( initial.size()==0 ) return 0;
        sort(initial.begin(), initial.end());
        n = graph.size();
        int color_idx = 1;  // 颜色的idx
        int color_cnt[400]={0};  // color_cnt[c]表示颜色c的个数
        // 初始化
        for ( int i=0; i<graph.size(); ++i ){
            pre[i] = -1;
            for ( int j=0; j<graph[0].size(); ++j )
                if ( graph[i][j]==1 )
                    mp[i].push_back(j);
        }
        // 染色
        for ( auto i:initial){
            if ( !color[i] )
                fill_color( i , color_idx++ );
            color_cnt[color[i]]++;
        }
        // 找最大
        int m = 0, ret=-1;
        for ( auto i:initial ){
            int rt = find(i);
            if ( color_cnt[color[i]]==1 && -pre[rt] > m  ){
                m = -pre[rt];
                ret = i;
            }
        }
        return ret==-1? initial[0] : ret ;
    }
};
