/*
    问题描述：
        给定一个 m x n 的非负整数矩阵来表示一片大陆上各个单元格的高度。“太平洋”处于大陆的左边界和上边界，而“大西洋”处于大陆的右边界和下边界。
        规定水流只能按照上、下、左、右四个方向流动，且只能从高到低或者在同等高度上流动。

        请找出那些水流既可以流动到“太平洋”，又能流动到“大西洋”的陆地单元的坐标。

        提示：

        输出坐标的顺序不重要
        m 和 n 都小于150
         
        示例：

        给定下面的 5x5 矩阵:

        太平洋 ~   ~   ~   ~   ~ 
            ~  1   2   2   3  (5) *
            ~  3   2   3  (4) (4) *
            ~  2   4  (5)  3   1  *
            ~ (6) (7)  1   4   5  *
            ~ (5)  1   1   2   4  *
                *   *   *   *   * 大西洋

        返回:

        [[0, 4], [1, 3], [1, 4], [2, 2], [3, 0], [3, 1], [4, 0]] (上图中带括号的单元).
        。

    问题分析：
        对每一个坐标进行一次bfs， 然后超时了，复杂度为O(N^2*M^2)

        反向搜索也是一个重要的思想，在本题中就得到了应用. 
        即，从边界开始进行搜索遍历，vis1数组保存了，太平洋的水能够到达的位置，
        vis2保存了大西洋的水能够到达的位置， 最后再遍历一遍地图，如果一个位置既能到达
        大西洋，又能到达太平洋，那么这个位置就选中.

        从本题之后开始，每个题解将用c++和java分别写一遍
*/


// C++解法
class Solution {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& grid) {
        vector<vector<int>> res;
        int n = grid.size();
        if ( n==0 ) return {};
        int m = grid[0].size();
        int dir[4][2] = {{0,1}, {1,0},{-1,0},{0,-1}};
        queue<pair<int,int>> q1;
        queue<pair<int,int>> q2;
        vector<vector<bool>> vis1(n, vector<bool>(m, false));
        vector<vector<bool>> vis2(n, vector<bool>(m, false));
        for ( int i=0; i<n; ++i ){ 
            q1.push({i,0});
            q2.push({i,m-1});
        }
        for ( int i=0; i<m; ++i ){
            q1.push({0,i});
            q2.push({n-1,i});
        }
        bfs( grid, q1, vis1 );
        bfs( grid, q2,vis2 );
        for ( int i=0; i<n; ++i )
            for ( int j=0; j<m; ++j )
                if ( vis1[i][j] && vis2[i][j] )
                    res.push_back({i,j});
        return res;
    }
        
    void bfs( vector<vector<int>>& grid, queue<pair<int,int>>&q, vector<vector<bool>>& vis ){
        int n = grid.size(), m = grid[0].size();
        int dir[4][2] = {{0,1}, {1,0},{-1,0},{0,-1}};
        while( q.size()>0 ){
            pair<int,int> cur = q.front(); q.pop();
            if (  vis[cur.first][cur.second] ) continue;
            vis[cur.first][cur.second] = true;
            for ( int k=0; k<4; ++k ){
                int y = cur.first + dir[k][0];
                int x = cur.second + dir[k][1];
                if ( y>=0 && x>=0 && x<m && y<n && !vis[y][x] && grid[y][x]>=grid[cur.first][cur.second] ){
                    q.push({y,x});
                }
            }
        }
    }
    
};


// Java解法
class Solution {
    public List<List<Integer>> pacificAtlantic(int[][] matrix) {
        int n = matrix.length;
        List<List<Integer>> res = new ArrayList<>();
        if ( n==0 ) return res;
        int m = matrix[0].length;
        boolean [][] vis1 = new boolean[n][m];
        boolean [][] vis2 = new boolean[n][m];
        Queue<int []> q1 = new LinkedList<>();
        Queue<int []> q2 = new LinkedList<>();
        
        int [][] dir = new int[][]{{0,1},{1,0},{-1,0},{0,-1}};
        
        for ( int i=0; i<n; ++i ){
            q1.offer( new int[]{i,0} );
            q2.offer( new int[]{i,m-1} );
        }
        for ( int i=0; i<m; ++i ){
            q1.offer( new int[]{0,i} );
            q2.offer( new int[]{n-1,i} );
        }
        
        while( q1.size()>0 ){
            int [] cur = q1.poll();
            if ( vis1[cur[0]][cur[1]] ) continue;
            vis1[cur[0]][cur[1]] = true;
            for ( int k=0; k<4; ++k ){
                int y = cur[0] + dir[k][0];
                int x = cur[1] + dir[k][1];
                if ( y>=0 && x>=0 && y<n && x<m && !vis1[y][x] && matrix[y][x]>=matrix[cur[0]][cur[1]] )
                    q1.offer(new int[]{y,x});
            }
        }
        
        while( q2.size()>0 ){
            int [] cur = q2.poll();
            if ( vis2[cur[0]][cur[1]] ) continue;
            vis2[cur[0]][cur[1]] = true;
            for ( int k=0; k<4; ++k ){
                int y = cur[0] + dir[k][0];
                int x = cur[1] + dir[k][1];
                if ( y>=0 && x>=0 && y<n && x<m && !vis2[y][x] && matrix[y][x]>=matrix[cur[0]][cur[1]] )
                    q2.offer(new int[]{y,x});
            }
        }
        
        for ( int i=0; i<n; ++i )
            for ( int j=0; j<m; ++j )
                if ( vis1[i][j] && vis2[i][j] )
                    res.add( makePair(i,j) );
        return res;
    }
    
    private ArrayList<Integer> makePair(final int i,final int j){
        return new ArrayList<Integer>(){{add(i); add(j);}};
    }
}