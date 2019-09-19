/*
    问题描述:
        对于一个具有树特征的无向图，我们可选择任何一个节点作为根。图因此可以成为树，在所有可能的树中，具有最小高度的树被称为最小高度树。给出这样的一个图，写出一个函数找到所有的最小高度树并返回他们的根节点。

        格式

        该图包含 n 个节点，标记为 0 到 n - 1。给定数字 n 和一个无向边 edges 列表（每一个边都是一对标签）。

        你可以假设没有重复的边会出现在 edges 中。由于所有的边都是无向边， [0, 1]和 [1, 0] 是相同的，因此不会同时出现在 edges 里。

        示例 1:

        输入: n = 4, edges = [[1, 0], [1, 2], [1, 3]]

             0
             |
             1
            / \
           2   3 

        输出: [1]
        示例 2:

        输入: n = 6, edges = [[0, 3], [1, 3], [2, 3], [4, 3], [5, 4]]

             0  1  2
              \ | /
                3
                |
                4
                |
                5 

        输出: [3, 4]
        说明:

         根据树的定义，树是一个无向图，其中任何两个顶点只通过一条路径连接。 换句话说，一个任何没有简单环路的连通图都是一棵树。
        树的高度是指根节点和叶子节点之间最长向下路径上边的数量。

    问题分析:
        拓扑排序，在队空前的最后一波，就是答案.
        要注意的是，因为是无向图，所以拓扑排序的时候，indegree不再是等到0再入队，而是1  (理由的话，举个例子就明白了，这里不多说了)
*/

class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        vector<int> res;
        unordered_map<int, vector<int>> mp;
        queue<int> q;
        vector<bool> visited(n,false);
        vector<int> indegree(n, 0);
        for ( auto e:edges ){
            indegree[e[1]]++;
            indegree[e[0]]++;
            mp[e[0]].push_back(e[1]);
            mp[e[1]].push_back(e[0]);
        }               
        for ( int i=0; i<n; ++i )
            if ( indegree[i]<=1 )
                q.push(i);
        while( !q.empty() ){
            for ( int j=q.size()-1; j>=0; --j ){
                int t = q.front(); q.pop();
                res.push_back(t);
                for ( auto adj:mp[t] ){
                    if ( visited[adj] ) continue;
                    if ( --indegree[adj] == 1 ){
                        visited[adj]=true;
                        q.push(adj);
                        res.push_back(adj);
                    }
                }
            }
            if ( !q.empty() ) res.clear();
        }
        return res;
        
    }
};
