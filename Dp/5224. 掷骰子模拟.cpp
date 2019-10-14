/*
    问题描述：
        有一个骰子模拟器会每次投掷的时候生成一个 1 到 6 的随机数。
        不过我们在使用它时有个约束，就是使得投掷骰子时，连续 掷出数字 i 的次数不能超过 rollMax[i]（i 从 1 开始编号）。
        现在，给你一个整数数组 rollMax 和一个整数 n，请你来计算掷 n 次骰子可得到的不同点数序列的数量。
        假如两个序列中至少存在一个元素不同，就认为这两个序列是不同的。由于答案可能很大，所以请返回 模 10^9 + 7 之后的结果。

        示例 1：

        输入：n = 2, rollMax = [1,1,2,2,2,3]
        输出：34
        解释：我们掷 2 次骰子，如果没有约束的话，共有 6 * 6 = 36 种可能的组合。但是根据 rollMax 数组，数字 1 和 2 最多连续出现一次，所以不会出现序列 (1,1) 和 (2,2)。因此，最终答案是 36-2 = 34。
        示例 2：

        输入：n = 2, rollMax = [1,1,1,1,1,1]
        输出：30
        示例 3：

        输入：n = 3, rollMax = [1,1,1,2,2,3]
        输出：181
         

        提示：

        1 <= n <= 5000
        rollMax.length == 6
        1 <= rollMax[i] <= 15

    问题分析：
        真的是。。比赛的时候不能老想着速度速度。。一心急就容易思路封闭。。还是应该一步一步分析。。
        八九不离十就是dp了， 

        开始推状态转移,

        既然是相同的数字不能连续，那就要看最后一个数字了，所以最后一个数字要保存
        既然相同数字不能连续超过rollMax[i]个， 那最后一个数字的连续个数也要保存
        长度为n的情况是由长度为n-1的情况推来的，所以长度也要保存。

        因此状态的保存情况就是
            dp[i][j][k] 表示以i为结尾，且连续了j个，且长为k的 满足条件的序列个数

        然后状态转移方程也不是很难推:
            for k from 1 to n:
                for i from 1 to 6:
                    for d from 1 to 6: // 用数字d结尾的 去更新 数字i结尾的
                        for j from 1 to rollMax[d]:
                            if  d==i && j+1<rollMax[d]:
                                dp[i][j+1][k] += dp[d][j][k-1]
                            if  d!=i:
                                dp[i][1][k] += dp[d][j][k-1]      
*/

class Solution {
public:
    int dieSimulator(int n, vector<int>& rollMax) {
        int mod = 1e9+7;
        int dp[7][16][5001] ={0};
        for ( int i=1; i<=6; ++i )
            dp[i][1][1] = 1;
        for ( int k=2; k<=n; ++k )
            for ( int i=1; i<=6; ++i )
                for ( int d=1; d<=6; ++d )
                    for ( int j=1; j<=rollMax[d-1]; ++j ){
                        if ( d==i && j+1<=rollMax[i-1] )
                            dp[i][j+1][k] = ( dp[i][j+1][k] + dp[d][j][k-1])%mod;
                        if ( d!=i )
                            dp[i][1][k] = (dp[i][1][k] + dp[d][j][k-1]) %mod;
                    }
        int res = 0;
        for ( int i=1; i<=6; ++i )
            for ( int j=1; j<=rollMax[i-1]; ++j )
                res = (res + dp[i][j][n])%mod;
        return res;
    }
};