/*
    问题描述:
        有图不大好描述,看链接把
        https://leetcode-cn.com/problems/out-of-boundary-paths/

    问题分析:
        先用bfs，然后TLE了。。
        看了下数据范围，确定是dp没跑了.
        dp[i][j][k] 表示 走了k步后 到达(i,j)的个数
        坐标范围 x属于[1,n] ，最后统计0和n+1的位置 （就是走k步走出界的不同走法
        y同理
    
        状态更新:
            (r,c)是 (y,x) 走一步就可以到达的坐标
            dp[r][c][step+1] = (dp[r][c][step+1]+dp[y][x][step])%mod;
*/

# define mod 1000000007
class Solution {
public:
    int findPaths(int m, int n, int N, int i, int j) {
        vector<vector<vector<int>>> dp( m+2, vector<vector<int>>(n+2, vector<int>(N+1,0)) );
        // dp[i][j][k] 表示 走了k步后 到达(i,j)的个数
        // 坐标范围 x属于[1,n] ，最后统计0和n+1的位置
        // y同理
        /*
            状态更新:
                (r,c)是 (y,x) 走一步就可以到达的坐标
                dp[r][c][step+1] = (dp[r][c][step+1]+dp[y][x][step])%mod;
        */
        int dir[4][2] = {{0,1},{1,0},{0,-1},{-1,0}}, res=0;
        i+=1; j+=1;
        dp[i][j][0]=1;
        for ( int step=0; step<N; ++step ){
            for ( int y=1; y<=m; ++y ){
                for ( int x=1; x<=n; ++x ){
                    if ( dp[y][x][step]>0 ) // 剪枝加速
                        for ( int k=0; k<4; ++k ){
                            int r=y+dir[k][0];
                            int c=x+dir[k][1];
                            dp[r][c][step+1] = (dp[r][c][step+1]+dp[y][x][step])%mod;
                        }
                }
            }
        }

        //统计所有走不同的步数 走出界的路线个数
        for ( int s=1; s<=N; ++s ){
            for ( int y=1; y<=m; ++y ){
                res = ( res+dp[y][0][s] )%mod;
                res = ( res+dp[y][n+1][s])%mod;
            }
            for ( int x=1; x<=n; ++x ){
                res = ( res+dp[0][x][s] )%mod;
                res = ( res+dp[m+1][x][s])%mod;
            }
        }
        return res;
    }
};

