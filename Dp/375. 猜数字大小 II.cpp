/*
    问题描述：
        我们正在玩一个猜数游戏，游戏规则如下：
        我从 1 到 n 之间选择一个数字，你来猜我选了哪个数字。
        每次你猜错了，我都会告诉你，我选的数字比你的大了或者小了。
        然而，当你猜了数字 x 并且猜错了的时候，你需要支付金额为 x 的现金。
        直到你猜到我选的数字，你才算赢得了这个游戏。

        给定 n ≥ 1，计算你至少需要拥有多少现金才能确保你能赢得这个游戏。

    问题分析：
        当思路不是太清晰的时候，可以手动列出前几项，
        ...
        列出之后，我们就能知道该如何选择dp数组了。
        dp[i][j]表示 当数字在区间[i,j]里时，必胜所需要的最少金钱数。

        状态转移公式： dp[i][j] = min(dp[i][j], k + max(dp[i][k-1], dp[k+1],dp[j]) )
 */

class Solution {
public:
    int getMoneyAmount(int n) {
        vector<vector<int>> dp( n+1, vector<int>(n+1, 0));
        for ( int len=2; len<=n; ++len  ){
            for ( int i=1; i+len-1<=n; ++i ){
                int j=i+len-1;
                for ( int k=i; k<=j; ++k ){
                    // [i,k) k (k,j]
                    // 核心就是下面这个，行数那么多主要是处理边界
                    // dp[i][j] = min(dp[i][j], k + max(dp[i][k-1], dp[k+1],dp[j]) )
                    if ( dp[i][j]>0 ){
                        if ( k>i && k<j )
                            dp[i][j] = min( dp[i][j], k + max(dp[i][k-1], dp[k+1][j] ));
                        else if ( k==i )
                            dp[i][j] = min( dp[i][j], dp[k+1][j]+k );
                        else if ( k==j )
                            dp[i][j] = min( dp[i][j], dp[i][k-1]+k );
                    }else{ 
                        if ( k>i && k<j )
                            dp[i][j] = k + max(dp[i][k-1], dp[k+1][j] );
                        else if ( k==i )
                            dp[i][j] =  dp[k+1][j]+k ;
                        else if ( k==j )
                            dp[i][j] =  dp[i][k-1]+k ;
                    }
                }
            }
        }
        return dp[1][n];
    }
};