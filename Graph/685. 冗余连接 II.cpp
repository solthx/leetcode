/*
    问题分析:
        在本问题中，有根树指满足以下条件的有向图。该树只有一个根节点，所有其他节点都是该根节点的后继。每一个节点只有一个父节点，除了根节点没有父节点。
        输入一个有向图，该图由一个有着N个节点 (节点值不重复1, 2, ..., N) 的树及一条附加的边构成。附加的边的两个顶点包含在1到N中间，这条附加的边不属于树中已存在的边。
        结果图是一个以边组成的二维数组。 每一个边 的元素是一对 [u, v]，用以表示有向图中连接顶点 u and v和顶点的边，其中父节点u是子节点v的一个父节点。
        返回一条能删除的边，使得剩下的图是有N个节点的有根树。若有多个答案，返回最后出现在给定二维数组的答案。

        示例 1:
            输入: [[1,2], [1,3], [2,3]]
            输出: [2,3]
            解释: 给定的有向图如下:
             1
            / \
           v   v
           2-->3
        
        示例 2:

            输入: [[1,2], [2,3], [3,4], [4,1], [1,5]]
            输出: [4,1]
            解释: 给定的有向图如下:
                5 <- 1 -> 2
                     ^    |
                     |    v
                     4 <- 3
        
        注意:
            二维数组大小的在3到1000范围内。
            二维数组中的每个整数在1到N之间，其中 N 是二维数组的大小。

    问题分析：
        wa了几次以后找到了规律。。。需要分类讨论

        分为三种情况:
            1. 不存在度为2的节点， 但存在环:
                5 -> 1 -> 2
                     ^    |
                     |    v
                     4 <- 3
                这种情况，可以维护一个并查集，记录并返回导致环出现的那条边.
            
            2. 存在度为2的节点:
                只要发现了度为2的节点，就开始处理:

                2.1 不存在环:
                
                     1
                    / \
                   v   v
                   2 -> 3

                如果度为2的节点不存在环，那么就直接返回导致度为2产生的那条边..

                2.2 存在环:
                
                     4
                    /
                   v
                   1
                  / ^
                 v   \
                 2 -> 3

                如果存在环，且存在度为2， 假设度为2的点为c
                那么删掉这样的边，即v->c满足:
                    indegree[v]>0
                    v出现在环中

                知道这些就可以coding了
*/

class Solution {
public:
    vector<int> set;
    int find( int x ){
        return set[x]=(set[x]==x)?x:find(set[x]);
    }
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        int x,y,a=-1,b=-1,c=-1;
        set.resize(edges.size()+1);
        vector<int> indegree(edges.size()+1,0);
        vector<int> path(edges.size()+1,-1);  // path[i]保存了指向节点i的节点号
        vector<int> res(2,0);  // 用于记录首个产生回路的边
        for ( int i =0; i<=edges.size(); ++i ) set[i]=i;
        for ( auto &e:edges ){
            
            if ( ++indegree[e[1]]>1 ){
                // 存在度为2的点
                unordered_map<int, vector<int>> mp;
                for ( auto ts:edges )
                    mp[ts[0]].push_back( ts[1] );
                // e[1]是度为2的点，也是环的起始点，e[0]和path[e[1]]是指向e[1]的两个节点，最后那个e[1]是环的终点
                // 只要在环路中发现了e[0]或path[e[1]]，那这个被发现的点和e[1]构成的边就要删掉
                // 如果环路中没有发现e[0]或path[e[1]]，说明不存在环 即返回-1
                int cur = dfs( mp,  e[1], e[0], path[e[1]], e[1] );
                if ( cur==-1 ){ 
                    // 存在度为2的点，且无环 
                    return {e[0],e[1]};
                }else // 存在度为2的点，且有环
                    return {cur,e[1]};
            }

            // 假设不存在度为2的节点，那么就记录第一条也是最后一条导致环路的那条边
            x = find(e[0]);
            y = find(e[1]);
            path[e[1]] = e[0];
            if ( x==y ){
                res[0]=e[0];
                res[1]=e[1];
            }
            set[x]=y;
        }
        // 不存在度为2的节点，就返回上面记录的这条边
        return res;
    }
    
    int dfs( unordered_map<int, vector<int>>& mp, int cur, int a, int b, int c ){
        for ( auto e:mp[cur] ){
            if ( e==a ) return a;
            else if ( e==b ) return b;
            else if ( e==c ) return -1;
            int d = dfs( mp, e, a, b, c );
            if ( d!=-1 ) return d;
        }
        return -1;
    }
};