/*
    问题描述：
        简单描述一下题目，就是给一个矩阵，只有0，1，-1元素，
        -1的位置不能走， 1代表该位置有一个樱桃，摘走就没了(变成0)
        现在问，一个人从左上角走到右下角， 再从右下角走回左上角，
        左上去右下 只能走右或走下，
        右下回左上 只能走左或走上.
        他最多能摘到多少樱桃?

    问题分析:

        记忆化搜索。

        一开始想贪心，也就是返回两次 从左上角走到右下角能拿到的最大樱桃总数  的和。
        但遇到下面这个情况就GG了
            1 1 1 1 0 0 0
            0 0 0 1 0 0 0
            0 0 0 1 0 0 1
            1 0 0 1 0 0 0
            0 0 0 1 0 0 0
            0 0 0 1 0 0 0
            0 0 0 1 1 1 1
        贪心的走，会漏掉一个1 ， 而这种情况是可以拿到全部樱桃的。。 所以不能像上面那样贪心

        本题可以等价想成 两个人从左上角开始走，问两人走到右下角后，能获得的最大樱桃数
        如果用dp解的话，开一个状态: dp[x1][x2][y1][y2]表示 A走到(x1,y1) B走到(x2,y2)的时候
        能获得的最大樱桃数量.
        但因为只能向右走和向下走，所以 x1+y1 == x2+y2 恒成立
        所以y2可以用 x1+x2-y1来表示

        dp[x1][x2][y1]表示 A走到(x1,y1) B走到(x2,y2)的时候
        能获得的最大樱桃数量.

        然后记忆化dfs的过程 跟 "只有一个人从左上走到右下获取的最大樱桃树" 很类似，
        只不过多的条件就是:
            1. 判断 (x1,y1)和(x2,y2) 是否在同一个位置( 因为要加上这个位置的樱桃数，如果在同一个位置要避免重复加 )
            2.  从两种情况( 来自左边的更新，来自上面的更新 )
                变成了四种情况 ( 两个人的两种情况相乘 2*2 )
        其他的和"只有一个人从左上走到右下获取的最大樱桃树"的情况几乎一样。。 

*/

# define inf 0x3f3f3f3f
class Solution {
public:
    int cherryPickup(vector<vector<int>>& grid) {
        if ( grid.size()==0 ||grid[0].size()==0 ) return 0;
        int n = grid.size(), m=grid[0].size();
        vector<vector<vector<int>>>  memo( n, vector<vector<int>>(m , vector<int>(n,INT_MIN)) );
        return max(0, helper( 0, 0, 0, memo, grid )); 
    }
    
    int helper( int x1, int y1, int x2, vector<vector<vector<int>>> & memo, vector<vector<int>>& grid){
        int y2 = x1+y1-x2;
        int n = grid.size(), m = grid[0].size();
        if ( x1>=n || y1>=m || x2>=n || y2>=m ) return -inf;
        if ( grid[x1][y1]==-1 || grid[x2][y2]==-1 ) return -inf;
        // 记忆化搜索的时候， 只要memo数组变化了，不再等于初值了，就返回！ 而不是大于等于0才返回
        if ( memo[x1][y1][x2]>INT_MIN ) return memo[x1][y1][x2]; // memo[x1][y1][x2]表示为 A从(x1,y1), B从(x2,y2)开始，走到右下角所得到的最大樱桃数;
        if ( x1==n-1 && y1==n-1 ) return grid[x1][y1];
        int cur = ( x1==x2 ) ? grid[x1][y1] : grid[x1][y1]+grid[x2][y2];
        memo[x1][y1][x2] = cur + max( max( helper( x1+1, y1, x2+1,memo, grid ), helper( x1+1, y1, x2, memo, grid ) ) , max( helper(x1, y1+1, x2+1, memo, grid), helper( x1, y1+1, x2, memo, grid ) ) );
        return memo[x1][y1][x2];
    }
    
    
};