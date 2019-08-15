/*
    问题描述：
        给出矩阵 matrix 和目标值 target，返回元素总和等于目标值的非空子矩阵的数量。
        子矩阵 x1, y1, x2, y2 是满足 x1 <= x <= x2 且 y1 <= y <= y2 的所有单元 matrix[x][y] 的集合。
        如果 (x1, y1, x2, y2) 和 (x1', y1', x2', y2') 两个子矩阵中部分坐标不同（如：x1 != x1'），那么这两个子矩阵也不同。

        示例 1：
            输入：matrix = [[0,1,0],[1,1,1],[0,1,0]], target = 0
            输出：4
            解释：四个只含 0 的 1x1 子矩阵。
            示例 2：

            输入：matrix = [[1,-1],[-1,1]], target = 0
            输出：5
            解释：两个 1x2 子矩阵，加上两个 2x1 子矩阵，再加上一个 2x2 子矩阵。
         

        提示：
            1 <= matrix.length <= 300
            1 <= matrix[0].length <= 300
            -1000 <= matrix[i] <= 1000
            -10^8 <= target <= 10^8

    问题分析:
        类似 #363 ，TreeSet的处理方法和那一题一样，
        只不过在求row的区间和的时候，363是求小于等于k的最大区间和，
        而这里是求row中区间和等于target的区间数量，
        这里使用map来记录， 并利用map里的lower_bound函数来实现二分
*/

class Solution {
public:
    int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
        int n = matrix.size(), m=matrix[0].size(), res=0;
        for ( int L=0; L<m; ++L ){
            vector<int> row(n,0);
            for( int R=L; R<m; ++R){
                for ( int t=0; t<n; ++t )
                    row[t] += matrix[t][R];
                int curSum = 0;
                // row区间和为target的区间个数
                // dp[i][j]为前i个元素中，和为j的个数
                unordered_map<int,int> dp;
                dp[0] = 1;
                for ( auto e:row ){
                    curSum += e;
                    res += dp[curSum-target];
                    dp[curSum]++;
                }
            }
        }
        return res;
    }
};