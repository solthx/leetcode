# TSP问题

原始问题为: 从V点出发，访问图里的每一个结点之后又回到了V点，求满足这一路线特点的最小开销.

TSP问题属于NP困难问题，目前还没有多项式时间的解法，在数据量较大的时候有近似算法(如遗传算法, 退火算法等)，目前已知的该问题的最优解算法就是 状态压缩+Dp来做，复杂度为O(N*2^N),
所以一般TSP问题的数据规模不会超过20.. 

## 1. 原始问题的解法:

dp[state][v] 表示 : 从起始结点开始， 已经访问了state中的结点，且当前在第v个结点，此时的最小开销..  其中, state是对结点编号的二进制编码, 其中state的二进制表示的第i位的状态对应是否访问过第i个结点，可令0为未访问，1为已访问.  谁是起始结点，就对谁进行初始化.

状态转移为:
    
    dp[state|(1<<u)][u] = min( dp[state|(1<<u)][u], dp[state][v] + dis[u][v] );

    就是从v转移到u，然后对u进行的更新... 
    
    dis[u][v] 为u到v的最短距离， 可以用Floyd预先来计算出.. 


## 2. 起始点不等于终点的情况

这个情况很简单， 只是返回值的不同而已.. [题目详情](https://leetcode-cn.com/classic/problems/unique-paths-iii/description/)

先对二维图里的合法点进行编码，得到一维的编号，然后当作TSP问题来解.. (ps: lc开不了1<<20那么大的数组，可以开在外面，不过记得初始化哦!)

cpp solution
```cpp
int dp[20][1<<20]={0};
class Solution {
public:
    int m;
    int uniquePathsIII(vector<vector<int>>& grid) {
        int dir[4][2] = {{0,1},{1,0},{-1,0},{0,-1}};
        m = grid[0].size();
        int xs,ys,xe,ye;
        int cnt=0;
        int encode[21][21]={0};
        memset(dp, 0, sizeof(dp));
        vector<vector<int>> decode(20, vector<int>(2,0));
        int sta,end;
        // 编码
        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[0].size(); ++j) {
                if (grid[i][j] == -1) continue;
                decode[cnt] = {i, j};
                encode[i][j] = cnt++;
                if (grid[i][j] == 1) sta = encode[i][j];
                if (grid[i][j] == 2) end = encode[i][j];
            }
        }

        // 初始化
        dp[sta][1<<sta]=1;
        for ( int state = 1; state< (1<<cnt) ; ++state ){
            for ( int v=0; v<cnt; ++v ){
                if ( (state&(1<<v))==0 || dp[v][state]==0  ) continue;
                int i = decode[v][0] , j = decode[v][1];
                for ( int k=0; k<4; ++k ){
                    int y=i+dir[k][0];
                    int x=j+dir[k][1];    
                    if ( x>=0 && y>=0 && x<grid[0].size() && y<grid.size() && grid[y][x]!=-1 ){
                        if ( (state&(1<<(encode[y][x]))) !=0  )continue;
                        dp[encode[y][x]][state|(1<<encode[y][x])] += dp[v][state];
                    }
                }
            }
        }
        // 返回结果
        return dp[end][(1<<cnt)-1];
    }
    
};
```


## 3. 每个结点只能访问一次的情况

如果在原始问题上加一个限制，即：每个结点只能访问一次。 这个时候就不能用Floyd来辅助求了，因为在floyd的过程中，没有记录结点的访问信息，所以在这个情况下，就直接用原始的邻接矩阵来得距离就行了!!   同时，在对邻接点进行更新的时候，只能对当前state中未访问的点进行更新， 这时要进行一次过滤..  最后！！！ 虽然每个点只能访问一次，但是结点0是要访问2次的，对应初始化的情况 和 最后返回到起点的情况.. 所以 dp[(1<<n)-1][0] 永远是得不到更新的.. 这时，我们可以加一层对起始点邻接点的扫描， 来尝试找出最短的那个情况(其邻接点一定是都访问一次的)

[题目链接](https://www.nowcoder.com/questionTerminal/3d1adf0f16474c90b27a9954b71d125d)

cpp solution
```cpp
# include <iostream>
# include <cstdlib>
# include <cstring>
using namespace std;

# define inf 0x3f3f3f3f
int main(void){
    int n;
    while( ~scanf("%d", &n) ){
        int g[n][n];
        int dp[1<<n][n];
        memset(g,0x3f,sizeof(g));
        memset(dp,0x3f,sizeof(dp));
        
        for ( int i=0; i<n; ++i )
            for ( int j=0; j<n; ++j )
                cin>>g[i][j];
        
        for ( int i=0; i<n; ++i )
            dp[(1<<i)|1][i] = g[0][i];
        
            for ( int state=1; state<1<<n; ++state ){
                for ( int v=0; v<n; ++v ){
                if ( (state&(1<<v))==0 ) continue;
                for ( int u=0; u<n; ++u ){
                    if ( (state&(1<<u))!=0 ) continue;
                    dp[state|(1<<u)][u] = min( dp[state|(1<<u)][u], dp[state][v]+g[v][u] );                 
                }
            }
        }
        int res=inf;
        for(int i=1;i<n;i++){
            res = min(res,dp[(1<<n)-1][i] + g[i][0]);
        }
        cout<<res<<endl;
    }
    
    return 0;
}
```