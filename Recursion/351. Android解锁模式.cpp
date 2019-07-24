/*
    问题描述：
        对一个3x3的格子手机按键，
        对于解锁手势，
        最少划过m个按键，
        最多划过n个按键，
        问有多少种不同的解锁手势

    问题分析：
        分为两类：
            1. 可以直接抵达，例如 周围的8的位置 + 走“日”字的8个位置
            2. 需要有条件的抵达，例如从4到6，需要已经经过5，
                                 从1到9，需要已经经过5
        分清这两种情况后，分情况处理，做dfs会简单很多

        优化：
            1，3，7，9的情况相同
            2，4，6，8的情况相同
            可以只计算 按键1的情况*4 + 按键2的情况*4 + 按键5的情况
 */

class Solution {
public:
    /**
     * @param m: an integer
     * @param n: an integer
     * @return: the total number of unlock patterns of the Android lock screen
     */
    int numberOfPatterns(int m, int n) {
        // Write your code here
        // 暴力
        int res=0;
        // 优化
        vector<vector<int>> mp(3,vector<int>(3,0));
        dfs(0, 0, mp, res, m, n, 1);
        dfs(0, 1, mp, res, m, n, 1);
        res*=4;
        dfs(1, 1, mp, res, m, n, 1);
        // for ( int i=0; i<3; ++i )
        //     for ( int j=0; j<3; ++j )
        //         dfs(i, j, mp, res, m, n, 1);
        return res;
    }
    
    void dfs( int i, int j,  vector<vector<int>> & mp, int &res, int m, int n, int step ){
        if ( step>=m && step<=n ) res++;
        if ( step>n )
            return;
        mp[i][j] = 1;
        // 可以直接抵达的位置
        int dir[16][2] = {
          {0,1},{1,0},{0,-1},{-1,0},{1,1},{1,-1},{-1,1},{-1,-1},
          {1,-2},{-2,1},{1,2},{2,1},{-1,2},{2,-1},{-1,-2},{-2,-1}
        };
        // 无障碍直接通过
        for ( int k=0; k<16; ++k  ){
            int x = j + dir[k][0];
            int y = i + dir[k][1];
            if ( x>=0 && y>=0 && x<3 && y<3 )
                if ( mp[y][x]==0 )
                    dfs(y,x,mp,res,m,n,step+1);
        }
        // 需要条件才能抵达的位置
        int jump[8][2] = {
          {0,2},{2,0},{2,2},{-2,-2},{0,-2},{-2,0},{2,-2},{-2,2}  
        };
        for ( int k=0; k<8; ++k  ){
            int x = j + jump[k][0];
            int y = i + jump[k][1];
            if ( x>=0 && y>=0 && x<3 && y<3 )
                if ( mp[ i+jump[k][1]/2 ][ j+jump[k][0]/2 ]!=0 && mp[y][x]==0 )
                    dfs(y,x,mp,res,m,n,step+1);
        }
        
        mp[i][j] = 0;
    }
    
};