/*
    问题描述:
        给一个无向树，找出树中最长的一条路径。

    问题分析:
        方法一: 两遍bfs， 先随便取个点作为根，进行bfs找到最深的节点； 第二次bfs从最深的节点出发，找到最远的节点;

        方法二: dfs, 比较像 #124 https://leetcode-cn.com/problems/binary-tree-maximum-path-sum/
        以任意一点为root，与其关联的点为子节点，求出所有子节点对应的路径的前两大值max1,max2，则该点对应的最长路径为max1+max2
*/

//两次bfs
class Solution1 {
public:
    unordered_map<int, vector<int>> mp;
    int treeDiameter(vector<vector<int>>& edges) {
        for ( auto e:edges ){
            mp[e[0]].push_back(e[1]);
            mp[e[1]].push_back(e[0]);
        }
        int v=0, u, dis;
        bfs( v, edges, dis, u );
        bfs( u, edges, dis, v );
        return dis;
    }
    
    // 返回距离输入节点的最长节点，极其编号
    void bfs( int v, vector<vector<int>>& edges, int & dis, int &u ){
        dis = 0;
        bool vis[10010]={false};
        queue<int> q;
        q.push(v);
        vis[v] = true;
        while( !q.empty() ){
            for ( int j=q.size(); j>0; --j ){
                u = q.front(); q.pop();
                for ( auto e:mp[u] ){
                    if ( !vis[e] ){
                        vis[e] = true;
                        q.push(e);
                    }
                }
            }
            if ( q.size()>0 )
                ++dis;
        }
    }
};

// dfs
class Solution2 {
public:
    unordered_map<int, vector<int>> mp;
    int vis[10010]={false};
    int treeDiameter(vector<vector<int>>& edges) {
        for ( auto e:edges ){
            mp[e[0]].push_back(e[1]);
            mp[e[1]].push_back(e[0]);
        }
        int res1=0, res2=0, cur, res=0;
        vis[0]=true;
        for ( auto e:mp[0] ){
            vis[e] = true;
            cur = dfs( e, res ) + 1;
            if ( cur>res1 ){
                res2 = res1;
                res1 = cur;
            }else if ( cur>res2 ) res2 = cur;
        }
        return max(res, res1+res2);
    }
    
    int dfs( int v, int &ret ){
        int cur, res1=0, res2=0;
        for ( auto e:mp[v] ){
            if ( !vis[e] ){
                vis[e] = true;
                cur = dfs( e, ret ) + 1;
                if ( cur>res1 ){
                    res2 = res1;
                    res1 = cur;
                }else if ( cur>res2 ) res2 = cur;
            }
        }
        ret = max( ret, res1+res2 );
        return max(res1, res2);
    }
};


