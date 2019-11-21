/*
    问题描述:
        「推箱子」是一款风靡全球的益智小游戏，玩家需要将箱子推到仓库中的目标位置。
        游戏地图用大小为 n * m 的网格 grid 表示，其中每个元素可以是墙、地板或者是箱子。

        现在你将作为玩家参与游戏，按规则将箱子 'B' 移动到目标位置 'T' ：

        玩家用字符 'S' 表示，只要他在地板上，就可以在网格中向上、下、左、右四个方向移动。
        地板用字符 '.' 表示，意味着可以自由行走。
        墙用字符 '#' 表示，意味着障碍物，不能通行。 
        箱子仅有一个，用字符 'B' 表示。相应地，网格上有一个目标位置 'T'。
        玩家需要站在箱子旁边，然后沿着箱子的方向进行移动，此时箱子会被移动到相邻的地板单元格。记作一次「推动」。
        玩家无法越过箱子。
        返回将箱子推到目标位置的最小 推动 次数，如果无法做到，请返回 -1。

        看图: https://leetcode-cn.com/problems/minimum-moves-to-move-a-box-to-their-target-location/

        输入：grid = [["#","#","#","#","#","#"],
                    ["#","T","#","#","#","#"],
                     ["#",".",".","B",".","#"],
                     ["#",".","#","#",".","#"],
                     ["#",".",".",".","S","#"],
                     ["#","#","#","#","#","#"]]
        输出：3
        解释：我们只需要返回推箱子的次数。
        示例 2：

        输入：grid = [["#","#","#","#","#","#"],
                    ["#","T","#","#","#","#"],
                     ["#",".",".","B",".","#"],
                     ["#","#","#","#",".","#"],
                     ["#",".",".",".","S","#"],
                     ["#","#","#","#","#","#"]]
        输出：-1
        示例 3：

        输入：grid = [["#","#","#","#","#","#"],
                     ["#","T",".",".","#","#"],
                     ["#",".","#","B",".","#"],
                     ["#",".",".",".",".","#"],
                     ["#",".",".",".","S","#"],
                     ["#","#","#","#","#","#"]]
        输出：5
        解释：向下、向左、向左、向上再向上。
        示例 4：

        输入：grid = [["#","#","#","#","#","#","#"],
                     ["#","S","#",".","B","T","#"],
                     ["#","#","#","#","#","#","#"]]
        输出：-1
         

        提示：

        1 <= grid.length <= 20
        1 <= grid[i].length <= 20
        grid 仅包含字符 '.', '#',  'S' , 'T', 以及 'B'。
        grid 中 'S', 'B' 和 'T' 各只能出现一个。


    问题分析:
        本题在普通的bfs上加了一些限制， 同时对bfs时，需要保存两个状态，即箱子的位置和人的位置.
        在进行bfs时， 寻找下一个位置的时候，要满足下面几个条件(假设下一个箱子的位置是(y,x), 下一个人的位置是(ry, rx)):
            1. rx,ry,y,x不越界
            2. 这个位置状态曾经为抵达过(用vis数组保存,即使vis[ry][rx][y][x])
            3. 移动方向的反方向的位置是可以站人的( 例如 从(1,1)移动到了(1,2)， 那么就需要玩家站在(1,0)的位置推，因此(1,0)就是反方向位置 )
            4. 移动方向的反方向的位置是当前玩家可以抵达的 ( 这个再通过一个bfs来判断是否可达就行了。 )

        设计好上面的思路，实现起来虽然略繁琐， 但并不难。

        本题的两个收获:
            1. 先想清楚，再coding! 边coding边想思路是大忌！！！！
            2. vis数组保存状态的时候，不要仅仅拘泥于保存一个位置！！ 可以保存多个位置，或位置+其他状态的组合。。总之vis数组依然是保存状态的， 位置只是状态的一种。
*/

class Solution {
public:
    int minPushBox(vector<vector<char>>& grid) {
        queue<vector<int>> q;
        int vis[30][30][30][30] = {0};
        int n = grid.size(), m=grid[0].size(),sx,sy;
        for ( int i=0; i<n; ++i )
            for ( int j=0; j<m; ++j )
                if ( grid[i][j]=='B' ){
                    q.push({i,j});
                }else if (grid[i][j]=='S'){
                    sy = i;
                    sx = j;
                }
        vis[q.front()[0]][q.front()[1]][sy][sx]=1;
        q.push({q.front()[0], q.front()[1], sy, sx});
        q.pop();

        int res = 0;
        int dir[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
        while( !q.empty() ){
            for ( int j=q.size(); j>0; --j ){
                auto cur = q.front(); q.pop();
                for ( int k=0; k<4; ++k ){
                    int y = cur[0] + dir[k][0];
                    int x = cur[1] + dir[k][1];
                    int ry = cur[0] - dir[k][0];
                    int rx = cur[1] - dir[k][1];
                    if ( x>=0 && rx>=0 &&y>=0 &&ry>=0 && x<m && rx<m && y<n && ry<n&& vis[y][x][ry][rx]==0 && grid[ry][rx]!='#' && grid[y][x]!='#' && canReach( grid, ry, rx, cur[2], cur[3], cur[0],cur[1] ) ){
                        vis[y][x][ry][rx] =1;
                        if ( grid[y][x] == 'T' )
                            return res+1;
                        q.push({y,x,ry,rx});
                    }
                }
            }
            ++res;
        }
        return -1;
    }

    // 判断是否可达
    bool canReach( vector<vector<char>>& grid, int y, int x, int ty, int tx, int fobidy, int fobidx  ){
        queue<vector<int>> q;
        int vis[30][30] = {0};
        q.push({y,x});
        vis[y][x] = 1;
        vis[fobidy][fobidx] = 1;
        int dir[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
        while( q.size()>0 ){
            auto cur = q.front(); q.pop();
            for ( int k=0; k<4; ++k ){
                int ny = cur[0] + dir[k][0];
                int nx = cur[1] + dir[k][1];
                if ( ny>=0 && nx>=0 &&ny<grid.size() && nx<grid[0].size() && vis[ny][nx]==0 && grid[ny][nx] != '#' ){
                    if ( ny==ty && nx==tx ) return true;
                    vis[ny][nx] = true;
                    q.push({ny,nx});
                }
            }
        }
        return false;
    }
};