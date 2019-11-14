/*
    问题描述：
        给定一个整数数组 A，返回 A 中最长等差子序列的长度。

        回想一下，A 的子序列是列表 A[i_1], A[i_2], ..., A[i_k] 其中 0 <= i_1 < i_2 < ... < i_k <= A.length - 1。并且如果 B[i+1] - B[i]( 0 <= i < B.length - 1) 的值都相同，那么序列 B 是等差的。

         

        示例 1：

        输入：[3,6,9,12]
        输出：4
        解释： 
        整个数组是公差为 3 的等差数列。
        示例 2：

        输入：[9,4,7,2,10]
        输出：3
        解释：
        最长的等差子序列是 [4,7,10]。
        示例 3：

        输入：[20,1,15,3,10,5,8]
        输出：4
        解释：
        最长的等差子序列是 [20,15,10,5]。
         

        提示：

        2 <= A.length <= 2000
        0 <= A[i] <= 10000

    问题分析：

        先找主要矛盾， 矛盾在于“差”； 因此在保存状态的时候， 要保存差;
        
        长度2000， 可以n^2一下。

        因此，dp[i][j]就是保存了以第i个元素为结尾且等差为j的等差数列的长度。

        尽管可以用unordered_map来保存差。。

        但也可以用offset来做一个偏移， 即 差最小为-10000, 所以加个10000的offset就可以不用unordered_map了， 速度会快很多。
*/

class Solution {
public:
    int longestArithSeqLength(vector<int>& A) {
        int res = 0;
        //vector<unordered_map<int,int>> dp(A.size()); 
        vector<vector<int>> dp(A.size());
        for (auto& row : dp)
            row.resize(20001, 0);
        for ( int i=1; i<A.size(); ++i )
            for ( int j=0; j<i; ++j ){
                int diff = A[i]-A[j];
                dp[i][diff+10001] = dp[j][diff+10001]+1;
                res = max(res, dp[i][diff+10001] );
            }
        return res+1;
    }
};