/*
    问题描述:
        爱丽丝参与一个大致基于纸牌游戏 “21点” 规则的游戏，描述如下：

        爱丽丝以 0 分开始，并在她的得分少于 K 分时抽取数字。 抽取时，她从 [1, W] 的范围中随机获得一个整数作为分数进行累计，其中 W 是整数。 每次抽取都是独立的，其结果具有相同的概率。

        当爱丽丝获得不少于 K 分时，她就停止抽取数字。 爱丽丝的分数不超过 N 的概率是多少？

        示例 1：

        输入：N = 10, K = 1, W = 10
        输出：1.00000
        说明：爱丽丝得到一张卡，然后停止。
        示例 2：

        输入：N = 6, K = 1, W = 10
        输出：0.60000
        说明：爱丽丝得到一张卡，然后停止。
        在 W = 10 的 6 种可能下，她的得分不超过 N = 6 分。
        示例 3：

        输入：N = 21, K = 17, W = 10
        输出：0.73278
        提示：

        0 <= K <= N <= 10000
        1 <= W <= 10000
        如果答案与正确答案的误差不超过 10^-5，则该答案将被视为正确答案通过。
        此问题的判断限制时间已经减少。

    问题分析:

        翻译一下题目:
            当前已有x:
                如果x<K:
                    那么可以加 [1,w]里的任意一个数，每个数被选中的概率都是1/w
                如果x>=K:
                    如果x<=N, 这种情况就是胜利.
                    如果x>N,  这种情况就是失败.

            然后初始为0, 求胜利的概率...

        果然翻译完之后，就明朗多了... 这种模型很明显是使用 dfs记忆化来做, 即, memo[i]保存以i为起使的, 最后胜利的概率.

        (关于概率的dp, 都可以考虑下记忆化...即 “初始情况为xx最后yyy的概率” 这样, 然后更新)

        没想到的是.. 记忆化 tle了..

        dfs( N, K, W, 0 ); // 以0开始的胜的概率
        函数中

        for ( int t=i+1; t<=i+W; ++t )
            cur += (1.0/W)*dfs( N, K, W, t );
        即计算：以i为初始值，最后胜利的概率 的情况.
        需要先知道 以[i+1, ...,i+W]为初始，胜利的概率，
        然后 *1/W，就是当前能胜利的概率了..

        但是.. 最终胜利的区间，我们一开始是可以知道的,

        即 i为 [K, min( K-1+W, N )] 这个区间内，就是最终胜利的那个位置.

        主要是因为，取[1,W]内的每一个值的概率是相等的，所以，我们不必去一个一个计算里面的每一个情况，
        我们可以用一个前缀和 sums[i]，来保存 以[i, i+1, i+2, .. N] 为初始的胜利的概率的综合！

        那么：
            for ( int t=i+1; t<=i+W; ++t )
                cur += (1.0/W)*dfs( N, K, W, t );
        就可以简化成:
            cur = (1.0/W) * (sums[i+1] - sums[i+W+1]) ;

        我们先把sums初始化为0， 然后把 [K, min(K-1+W, N)] 这个区间内的值初始化为1.0
        然后自底向上去计算，直到算到dp[0], 表示以0为起使，胜利的概率。。这个就是结果了.
*/

// dfs+memo TLE
class Solution {
public:
    unordered_map<int, double> memo;
    double new21Game(int N, int K, int W) {
        return dfs( N, K, W, 0 ); // 以0开始的胜的概率
    }
    double dfs( int N, int K, int W, int i ){
        if ( memo.count(i)>0 ) return memo[i];
        if ( i>=K && i<=N ) return 1;
        if ( i>N ) return memo[i]=0.0;
        double cur = 0;
        for ( int t=i+1; t<=i+W; ++t ){
            cur += (1.0/W)*dfs( N, K, W, t );  // 这个语句很费时！
        }
        return memo[i] = cur;
    }
};

// 自底向上
class Solution {
public:
    double new21Game(int N, int K, int W) {
        double dp[30010]={0};
        int m=min( K-1+W, N );
        double sums[30010]={0};
        double base = 1.0/W;
        for ( int i=m; i>=K; --i ){
            dp[i] = 1.0;
            sums[i] = sums[i+1] + dp[i];
        }
        for ( int i=K-1; i>=0; --i ){
            dp[i] = base*(sums[i+1] - sums[i+W+1]);
            sums[i] = sums[i+1] + dp[i];
        }
        return dp[0];
    }
};