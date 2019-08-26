/*
    问题描述:
        给定一个无向图graph，当这个图为二分图时返回true。
        如果我们能将一个图的节点集合分割成两个独立的子集A和B，并使图中的每一条边的两个节点一个来自A集合，一个来自B集合，我们就将这个图称为二分图。
        graph将会以邻接表方式给出，graph[i]表示图中与节点i相连的所有节点。每个节点都是一个在0到graph.length-1之间的整数。这图中没有自环和平行边： graph[i] 中不存在i，并且graph[i]中没有重复的值。

        示例 1:
            输入: [[1,3], [0,2], [1,3], [0,2]]
            输出: true
            解释: 
            无向图如下:
            0----1
            |    |
            |    |
            3----2
            我们可以将节点分成两组: {0, 2} 和 {1, 3}。

        示例 2:
            输入: [[1,2,3], [0,2], [0,1,3], [0,2]]
            输出: false
            解释: 
            无向图如下:
            0----1
            | \  |
            |  \ |
            3----2
            我们不能将节点分割成两个独立的子集。
        
        注意:
            graph 的长度范围为 [1, 100]。
            graph[i] 中的元素的范围为 [0, graph.length - 1]。
            graph[i] 不会包含 i 或者有重复的值。
            图是无向的: 如果j 在 graph[i]里边, 那么 i 也会在 graph[j]里边。

    问题分析:
        方法一: 节点染色标记
            可以用bfs或dfs来对节点进行染色,
            要注意，图不一定是连通的，要遍历所有的连通分量.
            ( bfs相对好想一些
            
            颜色分别用1和-1来表示，

            dfs的时候， color*-1来表示对立颜色
            bfs的时候， colors[t]*-1来表示对立颜色

        方法二: 并查集

        伪代码:
            遍历每一个连通分量:
                如果第i个节点存在边:
                    x = find( x ) 
                    y = find( graph[x][0] )
                    如果x==y 说明 x和y在同一个集合内，return false
                    for x的每一个邻接点v:
                        z = find(v)
                        如果 z==x 说明 x所属的集合内存在边 return false
                        如果 z!=y 说明 z还未被收录到x对面的集合中, 
                            set[z]=y 
            return true
 
*/

// dfs方法
class Solution1 {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        vector<int> colors( graph.size(),0 );
        for ( int i=0; i<graph.size(); ++i )
            // !colors[i] 说明是一个连通分量 
            if ( !colors[i] && !paint_sucess( graph, i, 1, colors ) )
                return false;
        return true;
    }
    
    // 表示能否成功把i以及i的邻接点们都成功染色
    bool paint_sucess( vector<vector<int>>& graph, int i, int color, vector<int>& colors ){
        if ( colors[i] ) return colors[i]==color;
        colors[i] = color;
        for ( auto &e:graph[i] )
            if ( !colors[e] && !paint_sucess(graph, e, color*-1, colors) )
                return false;
            else if ( colors[e]!=color*-1 ) return false;
        return true;
    }
};

// bfs解法
class Solution2 {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        vector<int> colors(graph.size(), 0);
        for ( int i=0; i<graph.size(); ++i ){
            // 遍历每一个连通分量
            if ( colors[i]==0 ){
                colors[i]=1;
                queue<int> q{{i}};
                while( !q.empty() ){
                    int cur = q.front(); q.pop();
                    for ( auto &e :graph[cur] ){
                        // 初次访问
                        if ( !colors[e] ){
                            q.push(e);
                            colors[e] = colors[cur]*-1;
                        }
                        else if ( colors[cur] == colors[e] ) //同一颜色存在边，则不是二分图
                            return false; 
                    }
                }
            }
        }
        return true;
    }
};

// 并查集
class Solution3 {
public:
    vector<int> set;
    // 路径压缩
    int find( int x ){
        return set[x] = (set[x]==x)?x:find(set[x]);
    }
    bool isBipartite(vector<vector<int>>& graph) {
        set.resize(graph.size());
        // 初始化
        for ( int i=0; i<graph.size(); ++i ) set[i]=i;
        for ( int i=0; i<graph.size(); ++i ){
            if ( graph[i].size()==0 ) continue;
            // 对于一个点，先计算出该点所属集合x，以及该点的邻接点所属集合y
            int x = find(i), y = find( graph[i][0] );
            // 如果两个点属于同一个集合，则不是二分图
            if ( x==y ) return false;
            // 否则，再遍历x的所有邻接点
            for ( auto &e:graph[i] ){
                // 得出 邻接点所属的集合z
                int z = find(e);
                if ( z==x ) return false;
                // 如果z不属于y，说明z是初次访问，还没更新，这里更新一下，把z放入y所属集合
                if ( z!=y ) set[e]=y; 
            }
        }
        return true;
    }
};