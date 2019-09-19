/*
    问题描述:
        你被给定一个 m × n 的二维网格，网格中有以下三种可能的初始化值：
            -1 表示墙或是障碍物
            0 表示一扇门
            INF 无限表示一个空的房间。然后，我们用 231 - 1 = 2147483647 代表 INF。你可以认为通往门的距离总是小于 2147483647 的。
        你要给每个空房间位上填上该房间到 最近 门的距离，如果无法到达门，则填 INF 即可。

        示例：

        给定二维网格：
            INF  -1  0  INF
            INF INF INF  -1
            INF  -1 INF  -1
            0   -1  INF INF

        运行完你的函数后，该网格应该变成：
            3  -1   0   1
            2   2   1  -1
            1  -1   2  -1
            0  -1   3   4

    问题分析:
        很容易想到是bfs来解决, 也很容易想到是用 
            rooms[y][x] = rooms[i][j]+1 来做更新
        
        但一开始却疯狂TLE, 因为是:
            for i ..:
                for j ..:
                    bfs( i, j, .. )
        这样的复杂度就是O(N^2*M^2)
    
        这时，需要转变一下思想！！！！！
        那就是不再按照:
            for i from 1 to n :
                for j from j to m :
                    ...
        这样的遍历，
        而是按照层数(步数) 来遍历！！！
        即，先更新从门开始，走了一步的情况(第一层)
        然后走了两步的情况(第二层), 直到不能再走(队空),
        此时，地图上的每个位置都被更新完毕!!
 */

class Solution {
public:
    void wallsAndGates(vector<vector<int>>& rooms) {
        if ( rooms.size()==0 || rooms[0].size()==0  ) return ;
        queue<pair<int,int>> q;
        int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
        for ( int i=0; i<rooms.size(); ++i )
            for ( int j=0; j<rooms[i].size(); ++j )
                if ( rooms[i][j]==0 )
                    q.push({i,j}); // 从门开始遍历, 存入门
        int n = rooms.size(), m=rooms[0].size(); 
        while( !q.empty() ){
            pair<int,int> cor = q.front(); q.pop();
            for ( int k=0; k<4; ++k ){
                int y = cor.first + dir[k][0];
                int x = cor.second + dir[k][1];
                if ( x>=0 && y>=0 && x<m && y<n && rooms[y][x]>0 && rooms[y][x]>rooms[cor.first][cor.second]+1  ){
                    rooms[y][x] = rooms[cor.first][cor.second]+1 ;
                    q.push({y,x});
                }
            }
        }
    }
    
};