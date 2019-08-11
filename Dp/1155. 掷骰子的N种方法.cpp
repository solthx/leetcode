/*
    问题描述:
        这里有 d 个一样的骰子，每个骰子上都有 f 个面，分别标号为 1, 2, ..., f。
        我们约定：掷骰子的得到总点数为各骰子面朝上的数字的总和。
        如果需要掷出的总点数为 target，请你计算出有多少种不同的组合情况（所有的组合情况总共有 f^d 种），模 10^9 + 7 后返回。
        
        示例 1：
            输入：d = 1, f = 6, target = 3
            输出：1
        
        示例 2：
            输入：d = 2, f = 6, target = 7
            输出：6
        
        示例 3：
            输入：d = 2, f = 5, target = 10
            输出：1

    问题分析：
        手动列出 d=3, f=6的例子，就可以发现  在计算前i个骰子能组成数字总和个数
        的时候，需要用到 前i-1个骰子能组成数字[1~target]的总个数,

        例如：
            第i个骰子筛出1，那么前i-1个骰子只要筛出target-1就行了..

        所以状态为：
            dp[i][j]表示前i个骰子筛出数的总和为j的个数
            
            for i from 1 to d:    // 当前是第几个骰子
                for j from 1 to target:   // 前i-1个骰子构成的和为j
                    for k from 1 to f:      // 第i个骰子筛出 k
                        if ( j-k>0 )    // j-k要存在
                            dp[i][j] = dp[i-1][j-k]  
        
        本次教训:
            1. 手动推前几项找公式灵感是可以的。。但不要过于依赖找规律，要根据求解子问题
            的过程中需要的东西来创建dp数组，再进行推导。。逻辑上一定要严谨
            2. 建立循环的时候，不一定非要直接确定正确循环区间，
            可以先是写出肯定不会有问题的区间，然后在循环体里面对dp数组进行更新的时候来进行if判断

            例如:
                for j from 1 to target:   // 前i-1个骰子构成的和为j
                    for k from 1 to f:      // 第i个骰子筛出 k
                        if ( j-k>0 )    // j-k要存在
                            dp[i][j] = dp[i-1][j-k]  
                上面的代码就是for循环的区间是最大区间，但不同的情况区间变化，所以直接在里面用if来判断，

                尽管下面的代码也是对的:
                    for ( int i=2; i<=d; ++i )
                        for ( int k=1; k<=f; ++k )
                            for ( int tar=k+i-1; tar<=target; ++tar )
                                dp[i][tar] = (dp[i][tar] + dp[i-1][tar-k])%1000000007;
                但在确定区间的过程中就要多加小心
            3. stackoverflow先检查下数组开小了吗...
                    
 */

class Solution {
public:
    int numRollsToTarget(int d, int f, int target) {
        if ( d*f<target ) return 0;
        else if ( d*f==target ) return 1;
        // dp[i][j] 是 前i个骰子组成和为j的个数
        vector<vector<int>> dp(d+3, vector<int>(target*10));
        for ( int i=1; i<=f; ++i )
            dp[1][i] = 1;
        for ( int i=2; i<=d; ++i ){
            // 第i个骰子能掷出几 
            for ( int sums=1; sums<=target; ++sums ){ // tar from 1 to target 
                for ( int k=1; k<=f; ++k ){           
                    if ( sums-k>0 )
                        dp[i][sums] = (dp[i][sums] + dp[i-1][sums-k])%1000000007;
                }
            }
        }
        return dp[d][target];
    }
};