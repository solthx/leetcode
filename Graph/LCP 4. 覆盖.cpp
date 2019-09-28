/*
    问题描述:
        这题看图会很好理解: https://leetcode-cn.com/problems/broken-board-dominoes/

        你有一块棋盘，棋盘上有一些格子已经坏掉了。你还有无穷块大小为1 * 2的多米诺骨牌，你想把这些骨牌不重叠地覆盖在完好的格子上，请找出你最多能在棋盘上放多少块骨牌？这些骨牌可以横着或者竖着放。

        输入：n, m代表棋盘的大小；broken是一个b * 2的二维数组，其中每个元素代表棋盘上每一个坏掉的格子的位置。

        输出：一个整数，代表最多能在棋盘上放的骨牌数。

        示例 1：
        输入：n = 2, m = 3, broken = [[1, 0], [1, 1]]
        
        输出：2
        解释：我们最多可以放两块骨牌：[[0, 0], [0, 1]]以及[[0, 2], [1, 2]]。（见下图）
        限制：
            1 <= n <= 8
            1 <= m <= 8
            0 <= b <= n * m

    问题分析:
        这题居然是二分图的模版题T_T 

        把每个点抽象成一个节点，然后和上下左右的位置的非“broken点”构成连接的边，
        然后找出最大匹配数就行了...

        分为下面几个步骤：
            1. 建图， 一个点和上下左右的非坏点, 建立边
            2. 求最大匹配数
*/



class Solution {
public:
    vector<int> match;  //match[v]表示和节点v构成匹配的点的编号, -1表示v未匹配 
    vector<bool> visited;
    
    unordered_map<int, vector<int>> adjlist;
    
    bool dfs( int cur ){
        for ( auto v:adjlist[cur] ){
            if ( !visited[v] ){
                visited[v] = true;
                if ( match[v]==-1 || dfs( match[v] ) ){
                    match[cur] = v;
                    match[v] = cur;
                    visited[v]= false;
                    return true;
                }
                visited[v]=false;
            }
        }
        return false;
    }
    
    int domino(int n, int m, vector<vector<int>>& broken) {
        // 1. 建图， 一个点和上下左右的非坏点, 建立边
        // 2. 顶点分为奇数的和偶数的两个集合
        // 3. 求最大匹配数
        match.resize(n*m+1,-1);
        visited.resize(n*m+1, false);
        vector<vector<bool>> canvisit( n, vector<bool>(m, true) );
        // 标记坏点
        for ( auto p:broken )
            canvisit[p[0]][p[1]] = false;
        // 构建图
        for ( int i=0; i<n; ++i ){
            for ( int j=0; j<m; ++j ){
                // 记得过滤掉坏点
                if ( canvisit[i][j]==false ) continue;
                int curv = i*m + j;
                if ( i+1<n && canvisit[i+1][j] ){
                    int nxtv = (i+1)*m+j;
                    adjlist[curv].push_back(nxtv);
                    adjlist[nxtv].push_back(curv);
                }
                if ( j+1<m && canvisit[i][j+1] ){
                    int nxtv = i*m+j+1;
                    adjlist[curv].push_back(nxtv);
                    adjlist[nxtv].push_back(curv);    
                }
            }
        }
        // 开始匈牙利
        int sum = 0, N=n*m;
        for ( int i=0; i<N; ++i ){
            if ( match[i]==-1 && dfs( i ) )
                ++sum;
        }
        return sum;
    }
};