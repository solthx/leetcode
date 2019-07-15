/*
    问题描述：
        给两个整数数组 A 和 B ，返回两个数组中公共的、长度最长的子数组的长度。
        示例 1:
        输入:
        A: [1,2,3,2,1]
        B: [3,2,1,4,7]
        输出: 3
        解释: 
        长度最长的公共子数组是 [3, 2, 1]。

    问题分析：
        动态规划，
        dp[i][j]表示A以第i个元素为结尾，B以第j个元素为结尾，的最长公共子数组

        状态转移公式：
            dp[i][j] = A[i]== B[j] ? dp[i-1][j-1]+1 : 0;
 */

class Solution {
    public int findLength(int[] A, int[] B) {
        // dp[i][j]记录了A中以第i个元素结尾和B中以第j个元素结尾的最长公共距离
        int res = 0;
        int[][] dp = new int[A.length + 1][B.length + 1];
        for (int i = 1; i <= A.length; ++i)
            for (int j = 1; j <= B.length; ++j) {
                if (A[i - 1] == B[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                    res = Math.max(res, dp[i][j]);
                }
            }
        return res;
    }
}