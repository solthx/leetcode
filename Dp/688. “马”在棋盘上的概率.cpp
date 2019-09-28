/*
    题目描述:
       已知一个 NxN 的国际象棋棋盘，棋盘的行号和列号都是从 0 开始。即最左上角的格子记为 (0, 0)，最右下角的记为 (N-1, N-1)。 

        现有一个 “马”（也译作 “骑士”）位于 (r, c) ，并打算进行 K 次移动。 

        如下图所示，国际象棋的 “马” 每一步先沿水平或垂直方向移动 2 个格子，然后向与之相垂直的方向再移动 1 个格子，共有 8 个可选的位置。
        
        https://leetcode-cn.com/problems/knight-probability-in-chessboard/

        现在 “马” 每一步都从可选的位置（包括棋盘外部的）中独立随机地选择一个进行移动，直到移动了 K 次或跳到了棋盘外面。

        求移动结束后，“马” 仍留在棋盘上的概率。

         

        示例：

        输入: 3, 2, 0, 0
        输出: 0.0625
        解释: 
        输入的数据依次为 N, K, r, c
        第 1 步时，有且只有 2 种走法令 “马” 可以留在棋盘上（跳到（1,2）或（2,1））。对于以上的两种情况，各自在第2步均有且只有2种走法令 “马” 仍然留在棋盘上。
        所以 “马” 在结束后仍在棋盘上的概率为 0.0625。
         

        注意：

            N 的取值范围为 [1, 25]
            K 的取值范围为 [0, 100]
            开始时，“马” 总是位于棋盘上
    
    问题分析:
        总感觉本题的难点在对概率的计算方式上...

        在本题中，正确的概率计算方式应该是:
            以(x0,y0) 3步到达位置(x3,y3)的概率为例，
            (x0,y0)->(x1,y1)->(x2,y2)->(x3,y3)
            
            令P(x0,y0)为到达(x0,y0)的概率

            P(x3,y3) = P(x0,y0)*P(x1,y1)*P(x2,y2)*(1/8)

        知道这一点之后，就很容易了，
        dp[i][j][k]为走了k步后，到达(i,j)位置的概率.

        状态转移公式为:
            dp[y][x][k+1] += dp[i][j][k]/8    // (i,j) 走了一步到达 (y,x)

        最后sum{ dp[][][K] }就是答案了
*/

class Solution {
public:
    double knightProbability(int N, int K, int r, int c) {
        double dp[N+1][N+1][K+1];
        for ( int k=0; k<=K; ++k )
            for ( int i=0; i<=N; ++i )
                for ( int j=0; j<=N; ++j )
                    dp[i][j][k]=0.0;
        dp[r][c][0] = 1.0;
        int out = 0;
        int in = 0;
        int dir[8][2] = {{1,2},{2,1},{-1,2},{-2,1},{1,-2},{2,-1},{-1,-2},{-2,-1}};
        for ( int k=0; k<K; ++k ){
            for ( int i=0; i<N; ++i ){
                for ( int j=0; j<N; ++j ){
                    if ( dp[i][j][k]>0 ){
                        for ( int t=0; t<8; ++t ){
                            int y = i+dir[t][0];
                            int x = j+dir[t][1];
                            if ( x>=0 && x<N && y>=0 && y<N ){
                                dp[y][x][k+1] += dp[i][j][k]/8;
                            }
                        }
                    }
                }
            }
        }
        double res= 0;
        for ( int i=0; i<N; ++i )
            for ( int j=0; j<N; ++j )
                if (dp[i][j][K]>0) 
                    res += dp[i][j][K];
        return res;
        
    }
};

