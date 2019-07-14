/*
    问题描述：
        给定一个整数矩阵，找出最长递增路径的长度。
        对于每个单元格，你可以往上，下，左，右四个方向移动。 你不能在对角线方向上移动或移动到边界外（即不允许环绕）。

        示例 1:

        输入: nums = 
        [
            [9,9,4],
            [6,6,8],
            [2,1,1]
        ] 
        输出: 4 
        解释: 最长递增路径为 [1, 2, 6, 9]。
 
    问题描述：
        记忆化搜索 （ 记忆化搜索感觉就是 DP+递归搜索 ，搜索过程中记录下子结果，然后
        在计算新结果时使用到之前记录下的子结果而不是重新计算 ）。
        dp[i][j]保存当前格子开始的最长递增路径
 */

class Solution {
    public int longestIncreasingPath(int[][] matrix) {
        if (matrix.length < 1)
            return 0;
        int len1 = matrix.length;
        int len2 = matrix[0].length;
        int res = 0;
        // 用来表示dp[i][j]是否已经计算完毕
        boolean[][] visited = new boolean[len1 + 1][len2 + 1];
        int[][] dp = new int[len1 + 1][len2 + 1];
        for (int i = 0; i < len1; ++i)
            for (int j = 0; j < len2; ++j) {
                if (visited[i][j] == false) {
                    helper(matrix, visited, dp, i, j);
                }
                if (res < dp[i][j]) {
                    res = dp[i][j];
                }
            }
        return res + 1;
    }

    void helper(int[][] matrix, boolean[][] visited, int[][] dp, int i, int j) {
        int direct[][] = { { 0, 1 }, { 1, 0 }, { -1, 0 }, { 0, -1 } };

        visited[i][j] = true;
        int x, y, len1 = matrix.length, len2 = matrix[0].length;
        for (int k = 0; k < 4; ++k) {
            x = j + direct[k][0];
            y = i + direct[k][1];
            if (x >= 0 && y >= 0 && x < len2 && y < len1 && matrix[y][x] > matrix[i][j]) {
                if (visited[y][x] == false)
                    helper(matrix, visited, dp, y, x);
                if (dp[i][j] < dp[y][x] + 1)
                    dp[i][j] = dp[y][x] + 1;
            }
        }
    }

}