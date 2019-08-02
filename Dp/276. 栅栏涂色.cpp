/*
    问题描述：
        有 k 种颜色的涂料和一个包含 n 个栅栏柱的栅栏，
        每个栅栏柱可以用其中一种颜色进行上色。你需要给所有栅栏柱上色，
        并且保证其中相邻的栅栏柱 最多连续两个 颜色相同。然后，返回所有有效涂色的方案数。
        
        注意:
        n 和 k 均为非负的整数。
        
        示例:
        输入: n = 3，k = 2
        输出: 6

    问题分析:
        方法一:
            状态:
                dp[i][k][0] 第i个元素涂颜色k后的合法染色方案（保证前一个不是k
                dp[i][k][1] 第i个元素涂颜色k后的合法染色方案（保证前一个是k
            转移公式:
                if ( pre!=color )
                    dp[i][color][0] += (dp[i-1][pre][0]+dp[i-1][pre][1]);
                if ( i>1 )
                    dp[i][color][1] += dp[i-1][color][0];
            复杂度O(N*K*K) 果不其然TLE( 死在了K很大的情况上 )
        
        方法二:
            K的复杂度太高，但是只要把颜色列入状态中，就避免不了是K*K的复杂度，
            所以或许是状态中不需要用到K，
            仔细想一下，其实每个颜色的情况都是一样的，
            所以可以只考虑当前的一种颜色的染色方案，然后乘k倍就行了。

            状态:
                dp[i][0] 表示第i个位置染了颜色0，且和前一个位置不一样的颜色后的总个数 
                dp[i][1] 表示第i个位置染了颜色0，且和前一个位置一样的颜色后的总个数

            状态转移:
                如果当前染色和前一个不一样，那么当前能够染色0的方案就是 dp[i-1][0]+dp[i-1][1]
                (虽然dp表示染色0，但因为就算是染色1，染色2，方案数都相同的)
                因为和前一个颜色不一样，所以当前选取颜色有k-1种，
                故 dp[i][0] = (k-1)*(dp[i][0]+dp[i][1])

                如果当前染色和前一个一样，那么只能选一种，即前一个"染色和前一个不同的"那个一方案
                即dp[i-1][0]。(如果选了dp[i-1][1]，就会是连续三个颜色相同了)
                故 dp[i][1] = dp[i-1][0]
            
            最终返回结果就是:
                (dp[n][0]+dp[n][1]) * k   dp只记录一种颜色，共有k个颜色

            因为只涉及当前两个和前面两个，故可以用4个变量来代替之，
            使得空间优化到O(1)
 */
class Solution {
public:
    int numWays(int n, int k) {
        if ( n==0 || k==0 ) return 0;
        // dp[i][0] 表示第i个位置染了0和前一个位置不一样的颜色后的总个数
        // dp[i][1] 表示第i个位置染了0和前一个位置一样的颜色后的总个数
        // 状态转移公式:
        //     dp[i][0] = (k-1)*(dp[i][0]+dp[i][1])
        //     dp[i][1] = dp[i-1][0];
        //vector<vector<int>> dp(n+1, vector<int>(2,0));
        int pre_same=0, pre_diff = 1;
        int same=0,diff=1;
        //dp[1][0] = 1;
        //dp[1][1] = 0;
        for ( int i=2; i<=n; ++i ){
            //dp[i][0] = (k-1)*(dp[i-1][0]+dp[i-1][1]);
            //dp[i][1] = dp[i-1][0];
            diff = (k-1)*(pre_diff+pre_same);
            same = pre_diff;
            pre_diff = diff;
            pre_same = same;
        }
        return (same+diff)*k;
        //return (dp[n][0]+dp[n][1])*k;
    }
};
/*
class Solution {
public:
    // O(N*k*k)  TLE
    int numWays(int n, int k) {
        if ( n==0 || k==0 ) return 0;
        //dp[i][k][0] 第i个元素涂颜色k后的合法染色方案（保证前一个不是k
        //dp[i][k][1] 第i个元素涂颜色k后的合法染色方案（保证前一个是k
        int dp[n+1][k][2];
        memset(dp,0,sizeof(dp));
        for ( int i=0; i<k; ++i ){
            dp[1][i][0] = 1;
            dp[1][i][1] = 0;
        }
        
        for ( int i=2; i<=n; ++i ){
            for ( int color=0; color<k; ++color ){
                for ( int pre=0; pre<k; ++pre ){
                    if ( pre!=color )
                        dp[i][color][0] += (dp[i-1][pre][0]+dp[i-1][pre][1]);
                }
                if ( i>1 )
                    dp[i][color][1] += dp[i-1][color][0];
            }
        }
        int res=0;

        for ( int i=0; i<k; ++i ){
            res += ( dp[n][i][0]+dp[n][i][1] );
        }
        return res;
    }
};*/