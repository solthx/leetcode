/*
    问题描述:
        亚历克斯和李继续他们的石子游戏。许多堆石子 排成一行，每堆都有正整数颗石子 piles[i]。游戏以谁手中的石子最多来决出胜负。
        亚历克斯和李轮流进行，亚历克斯先开始。最初，M = 1。
        在每个玩家的回合中，该玩家可以拿走剩下的 前 X 堆的所有石子，其中 1 <= X <= 2M。然后，令 M = max(M, X)。
        游戏一直持续到所有石子都被拿走。
        假设亚历克斯和李都发挥出最佳水平，返回亚历克斯可以得到的最大数量的石头。

        输入：piles = [2,7,9,4,4]
        输出：10
        解释：
        如果亚历克斯在开始时拿走一堆石子，李拿走两堆，接着亚历克斯也拿走两堆。在这种情况下，亚历克斯可以拿到 2 + 4 + 4 = 10 颗石子。 
        如果亚历克斯在开始时拿走两堆石子，那么李就可以拿走剩下全部三堆石子。在这种情况下，亚历克斯可以拿到 2 + 7 = 9 颗石子。
        所以我们返回更大的 10。 

    问题分析:
        一开始用dfs直接做的时候理解错了题意。
        题中要求是阿历克斯和李两个人都发挥出最佳水平，
        这个意思就是说，任何人都要去拿当前的最优情况！ 
        所以并不可以暴力的遍历所有情况选最优。

        故先表示出在数组不同状态下(其实就是在数组的不同位置上)
        当前玩家能够取得的最多石子

        所以，状态设为：
            dp[i][M] : 当数组只剩下[i,n)的时候, 也就是从数组第i个位置继续游戏，
            且定义域参数为M的情况下，当前玩家能够取得的最多石子数。
        
        因为这个游戏就两个人玩，如果总数是X，玩家A拿了Y，那么玩家B肯定就拿了X-Y
        设sums[i]表示nums在区间[i,n)上的元素和
        所以
            dp[i][M] = max( sums[i] - dp[i+x][max(x,M)] ) , x属于[1,2*M]
        
        把sums 和 负号 给提出来， 就变成了:
            dp[i][M] = sums[i] - min( dp[i+x][max(x,M)] )

        落实到代码上就是:
            for x from 1 to 2*M:
                minimum = min( minimum, dp[i+x][max(x,M)] )
            dp[i][M] = sums[i] - minimum;
        
        所以可以看出， 求dp[i][..]的时候，依赖于dp[i+x][..] ， 
        因此用dfs+记忆化dp来完成  
 */

 class Solution {
public:
    int stoneGameII(vector<int>& piles) {
        // dfs先试试
        int n = piles.size();
        int res=0;
        // dp[i][M]表示为 当前的人从i位置开始，M为M的情况下，可以拿到的最大值
        // 状态更新:
        //  dp[i][M] = max( sums[i ~ i+x-1] ) - dp[i+x][max(x,M)];
        //  等价于
        //  dp[i][M] = sums[i ~ i+x-1] - min(dp[i+x][max(x,M)]);
        vector<vector<int>> dp(n, vector<int>(n,0));
        vector<int> sums(n+1, 0);
        for ( int i=n-1; i>=0; --i ){
            sums[i] = sums[i+1] + piles[i];
        }
        return dfs( piles, dp, sums, 0, 1 );
    }
    
    int dfs(vector<int> & piles, vector<vector<int>> & dp, vector<int> & sums, int idx, int M ){
        if ( idx>=piles.size() ) return 0;
        if ( dp[idx][M]!=0 ) return dp[idx][M];
        int minimum = INT_MAX;
        for ( int x=1; x<=2*M; ++x ){
            if ( idx+x>piles.size() ) continue;
            minimum = min( minimum, dfs( piles, dp, sums, idx+x, max(x,M)));
        }
        dp[idx][M] = sums[idx] - minimum;
        return dp[idx][M];
    }
    
};