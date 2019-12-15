/*
    问题描述：
        给你一个 m * n 的网格，其中每个单元格不是 0（空）就是 1（障碍物）。每一步，您都可以在空白单元格中上、下、左、右移动。

        如果您 最多 可以消除 k 个障碍物，请找出从左上角 (0, 0) 到右下角 (m-1, n-1) 的最短路径，并返回通过该路径所需的步数。如果找不到这样的路径，则返回 -1。

         

        示例 1：

        输入： 
        grid = 
        [[0,0,0],
         [1,1,0],
         [0,0,0],
         [0,1,1],
         [0,0,0]], 
        k = 1
        输出：6
        解释：
        不消除任何障碍的最短路径是 10。
        消除位置 (3,2) 处的障碍后，最短路径是 6 。该路径是 (0,0) -> (0,1) -> (0,2) -> (1,2) -> (2,2) -> (3,2) -> (4,2).
         

        示例 2：

        输入：
        grid = 
        [[0,1,1],
         [1,1,1],
         [1,0,0]], 
        k = 1
        输出：-1
        解释：
        我们至少需要消除两个障碍才能找到这样的路径。
         

        提示：

        grid.length == m
        grid[0].length == n
        1 <= m, n <= 40
        1 <= k <= m*n
        grid[i][j] == 0 or 1
        grid[0][0] == grid[m-1][n-1] == 0

    问题分析:
        唉.. BFS模板题.. 之所以记录一下，是因为被一个Bug卡的有些久T_T..

        那就是！！！

        如果保存的状态不仅仅是<位置>，而是<位置+状态>的时候， 一定要记得，每次计算下一步的状态的时候，都要重新初始化一下啊！！！！！！！

        （这次就是因为，光用y, x来初始化状态了，但后面对状态操作的时候，是对cur[2]即剩余钥匙数  进行的操作，然后.. 逻辑上就相当于上下左右公用了一个cur， 我真是个zz..）

        唉。。记录一下这个坑把。。我太蠢了T_T。。

        by the way : 
            这种带有多种状态的bfs:
                
                1. 用vis来保存所有状态信息，来记录有没有访问过这个状态...非常暴力..

                2. 对于一些限制多的题目，还可以额外保存每一个位置上的状态, 然后进行更新.. 

*/

// 使用vis保存所有的状态..
class Solution {
public:
    int shortestPath(vector<vector<int>>& grid, int k) {
        if ( grid.size() == 0 || grid[0].size()==0 ) return 0;
        int n = grid.size(), m=grid[0].size();
        bool vis[n][m][k+1];
        memset(vis, 0, sizeof(vis));
        queue<vector<int>> q;
        q.push({0,0,k});
        vis[0][0][k]=true;
        int lv = 0;
        int dir[4][2] = {{1,0},{0,1},{-1,0},{0,-1}};
        if ( n-1==0 && m-1==0 ) return 0;
        while( q.size()>0 ){
            for ( int j=q.size(); j>0; --j ){
                auto cur = q.front(); q.pop();
                for ( int k=0; k<4; ++k ){
                    int y = cur[0] + dir[k][0];
                    int x = cur[1] + dir[k][1];
                    int v = cur[2]; // 记得保存出来啊！！！！！！！！！！！！！！！
                    if ( y>=0 &&x>=0 && y<n && x<m  ){
                        if ( n==y+1 && m==x+1 ) return lv+1;
                        if ( grid[y][x] == 1 && --v<0 ) continue;
                        if ( vis[y][x][v] ) continue;
                        vis[y][x][v] = true;
                        q.push({y,x,v});
                    }
                }
            }
            ++lv;
        }
        return -1;
    }
};

// 只保存了是否访问过这个位置， 然后用二维数组保存其他状态.. （这种方法会稍微复杂一些，因为要决定当多次访问一个位置时，在什么情况下可以再次访问这个位置。。 但好处是对数组进行了降维.. 如果本题K很大的话.. 那么第一种方案可能就根本开不出这么大的数组.
class Solution {
public:
    int shortestPath(vector<vector<int>>& grid, int k) {
        int vis[50][50]={0};
        queue<vector<int>> q;
        q.push({0,0,k});
        vis[0][0] = true;
        int lv = 0;
        int dir[4][2] = {{1,0},{0,1},{-1,0},{0,-1}};
        int cur_k[50][50] = {0}; // cur_k[i][j] 记录了上次访问到<i,j>时的剩余钥匙数量.. 
        int n = grid.size(), m=grid[0].size();
        if ( n-1==0 && m-1==0 ) return 0;
        while( q.size()>0 ){
            for ( int j=q.size(); j>0; --j ){
                auto cur = q.front(); q.pop();
                for ( int k=0; k<4; ++k ){
                    int y = cur[0] + dir[k][0];
                    int x = cur[1] + dir[k][1];
                    int v = cur[2]; // 记得保存出来啊！！！！！！！！！！！！！！！
                    if ( y>=0 &&x>=0 && y<n &&x<m  ){
                        if ( y==n-1 && x==m-1 ) return lv+1;
                        if ( grid[y][x]==1 ) v--;
                        if ( !vis[y][x] ){ // 初次访问这个位置，就初始化cur_k
                            vis[y][x] = 1;
                            cur_k[y][x] = v;
                            if (v>=0) 
                                q.push({y,x,v});
                        }else{
                            // 多次访问这个位置时，只有当剩余钥匙更多的时候，才继续保存这个状态.
                            if (  v<=cur_k[y][x] ) continue;
                            if ( v<0 ) continue;
                            if ( cur_k[y][x]<v ){
                               cur_k[y][x] = v;
                               q.push({y,x,v});
                            }
                        }
                    }
                }
            }
            ++lv;
        }
        return -1;
    }
};