/*
    问题描述：
        你想在一个空旷的土地上盖房子，在最短的距离内到达所有的建筑物。你只能上下左右移动。你得到的是一个二维数组网格的值为0、1或2，其中:

        每一个0标记一个空的土地，你可以自由地通过。
        每一个1标记一个你不能通过的建筑物。
        每一个2标记一个你不能通过的障碍。
        Example
        例如，给定三个建筑物(0,0),(0,4),(2,2)和障碍物(0,2):

            1 - 0 - 2 - 0 - 1
            |   |   |   |   |
            0 - 0 - 0 - 0 - 0
            |   |   |   |   |
            0 - 0 - 1 - 0 - 0
        点(1,2)是建造房屋理想的空地，因为3+3+1=7的总行程距离最小。所以返回7。

    问题分析：
        对每个非0元素进行BFS来计算到达所有建筑物距离的总和，
        注意，这个总和必须到达所有建筑物，缺一个都不行。
        
        ---分割线---
        如果是对0来进行bfs，会超时，因为0很多！
        而1是很少的，故应该反向过来，对1进行bfs
        对每一个0的位置(i,j)：
            dis[i][j]保存了所有1到当前0的距离总和
            计算能到达当前0的1的个数，即canReach[i][j]
        用1去bfs来更新上面的dis和canReach.
 */


class Solution {
public:
    /**
     * @param grid: the 2D grid
     * @return: the shortest distance
     */
    int shortestDistance(vector<vector<int>> &grid) {
        // write your code here
        if ( grid.size()==0 || grid[0].size()==0 ) return 0;
        int n=grid.size(), m=grid[0].size();
        
        // dis[i][j]表示当前位置到所有1的距离和
        // canReach[i][j] 表示当前位置能够到达的building数 
        vector<vector<int>> dis(n, vector<int>(m, 0));
        vector<vector<int>> canReach(n, vector<int>(m, 0));
        int res = INT_MAX, cnt=0;
        for ( int i=0; i<grid.size(); ++i )
            for ( int j=0; j<grid[0].size(); ++j )
                if ( grid[i][j]==1 ){
                    calculate_distance(dis, canReach, i, j, grid, cnt);
                    ++cnt;
                }
        res = INT_MAX;
        for ( int i=0; i<grid.size(); ++i )
            for ( int j=0; j<grid[0].size(); ++j )
                if ( grid[i][j]==0 && canReach[i][j]==cnt )
                    res = min(dis[i][j], res);
        
        return res==INT_MAX?-1:res;
    }
    
    void calculate_distance( vector<vector<int>> & dis, vector<vector<int>> & canReach, int i, int j, vector<vector<int>>& grid, int cnt ){
        int step=0, n=grid.size(), m=grid[0].size();
        queue<pair<int,int>> q;
        vector<vector<bool>> visited( n, vector<bool>(m,false));
        q.push({i,j});
        visited[i][j] = true;
        int dir[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};
        while( !q.empty() ){
            int len = q.size();
            for ( int t=0; t<len; ++t ){
                pair<int,int> cor = q.front(); q.pop();
                for ( int k=0; k<4; ++k ){
                    int y = cor.first + dir[k][0];
                    int x = cor.second +dir[k][1];
                    if ( x>=0 && y>=0 && x<m && y<n && !visited[y][x] && grid[y][x]==0 ){
                        //访问过当前位置
                        visited[y][x] = true;
                        //更新dis
                        dis[y][x] += (step + 1);
                        //更新canReach
                        canReach[y][x] += 1;
                        q.push({y,x});
                    }
                }
            }
            // step为从i，j到达当前位置需要的步数，初始为0
            ++step;
        }
        return;
    }
};

/* 

TLE
class Solution {
public:
    int shortestDistance(vector<vector<int>> &grid) {
        // write your code here
        int res = INT_MAX, cnt=0;
        for ( int i=0; i<grid.size(); ++i )
            for ( int j=0; j<grid[0].size(); ++j )
                if ( grid[i][j] == 1 )
                    ++cnt;  //建筑物的个数
        for ( int i=0; i<grid.size(); ++i )
            for ( int j=0; j<grid[0].size(); ++j )
                if ( grid[i][j]==0 ){
                    res = min(res, calculate_distance(i, j, grid, cnt));
                }
        return res==INT_MAX?-1:res;
    }
    
    // step为从i，j到达当前位置需要的步数，初始为0
    int calculate_distance( int i, int j, vector<vector<int>> &grid, int cnt){
        queue<pair<int,int>> q;
        int c=0;
        int n = grid.size(), m = grid[0].size();
        vector<vector<bool>> book(n, vector<bool>(m,false));
        q.push(make_pair(i,j));
        int dir[4][2] = {{1,0},{0,1},{-1,0},{0,-1}};
        book[i][j] = true;
        int step=0, res=0;
        int x,y;
        while( !q.empty() ){
            int len = q.size();
            for ( int t=0; t<len; ++t ){
                pair<int,int> cor = q.front(); q.pop();
                for ( int k=0; k<4; ++k ){
                    y = cor.first+dir[k][0];
                    x = cor.second+dir[k][1];
                    
                    if ( x>=0 && y>=0 && x<m && y<n && !book[y][x] ){
                        book[y][x] = true;
                        if ( grid[y][x]==0 ){
                            q.push(make_pair(y,x));
                        }else if ( grid[y][x]==1 ){
                            res += (step+1);
                            ++c;
                        }
                    }
                }
            }
            ++step; 
        }
        return c==cnt?res:INT_MAX;
    }
    
};*/