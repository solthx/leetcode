/*
    问题描述：
        给定两个单词 word1 和 word2，计算出将 word1 转换成 word2 所使用的最少操作数 。
        你可以对一个单词进行如下三种操作：

        插入一个字符
        删除一个字符
        替换一个字符

        示例：
        输入: word1 = "horse", word2 = "ros"
        输出: 3
        解释: 
        horse -> rorse (将 'h' 替换为 'r')
        rorse -> rose (删除 'r')
        rose -> ros (删除 'e')

    问题分析：
        dp[i][j]表示 word1的前i个字符变成word2的前j个字符 需要的最少操作次数。

        如果word1[i]==word2[j]:
            继承上一个， dp[i][j] = dp[i-1][j-1]

        如果word1[i]!=word2[j]:
            取“经插入或删除或替换操作之后，使得word1的前i个字符变成word2的前j个字符”的最少操作次数。
            1. 插入: dp[i-1][j] + 1 
            2. 删除: dp[i][j-1] + 1
            3. 替换: dp[i-1][j-1] + 1
        dp[i][j] = min ( 1., 2., 3. );

        优化:
            可以把空间优化到O(N)，
            观察公式可以发现，当前i仅仅依赖于i-1
            所以用A[j]为dp[i][j]， 然后类似滚动数组那样更新i

        ！！！注意：
            这里多说一点，使用Dp的时候，一定别忘记初始化，
            尤其是对于多维Dp，初始化时情况要想全，不要漏！！
 */

 class Solution {
public:
    int minDistance(string word1, string word2) {
        //空间复杂度O(N)  类似滚动数组
        int n=word1.size(), m=word2.size();
        vector<int> cur(m+1,0); // cur[j]表示dp[i][j]
        vector<int> pre(m+1,0); // pre[j]表示dp[i-1][j]
        // i==0
        for ( int i=1; i<=m; ++i )
            pre[i] = i;
        for ( int i=1; i<=n; ++i ){
            pre[0] = i-1;
            cur[0] = i;
            for ( int j=1; j<=m; ++j ){
                if ( word1[i-1]==word2[j-1] ) 
                    cur[j] = pre[j-1];
                else cur[j] = min(cur[j-1], min(pre[j],pre[j-1]))+1;
            }
            pre = cur;
        }
        return pre[m];
    }
};

/*
空间复杂度O(N^2)
class Solution {
public:
    int minDistance(string word1, string word2) {
        vector<vector<int>> dp(word1.size()+1, vector<int>(word2.size()+1, 0));
        for ( int i=1; i<=word1.size(); ++i )
            dp[i][0] = i;
        for ( int j=1; j<=word2.size(); ++j )
            dp[0][j] = j;
        for ( int i=1; i<=word1.size(); ++i )
            for ( int j=1; j<=word2.size(); ++j ){
                if ( word1[i-1]==word2[j-1] ) 
                    dp[i][j] = dp[i-1][j-1];
                else dp[i][j] = min(dp[i-1][j-1], min(dp[i][j-1], dp[i-1][j])) + 1;
            }
        return dp[word1.size()][word2.size()];
    }
};
*/

