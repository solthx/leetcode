/*
    问题描述:
        给你一个整数数组 arr，每一次操作你都可以选择并删除它的一个 回文 子数组 arr[i], arr[i+1], ..., arr[j]（ i <= j）。
        注意，每当你删除掉一个子数组，右侧元素都会自行向前移动填补空位。
        请你计算并返回从数组中删除所有数字所需的最少操作次数。

         

        示例 1：

        输入：arr = [1,2]
        输出：2
        示例 2：

        输入：arr = [1,3,4,1,5]
        输出：3
        解释：先删除 [4]，然后删除 [1,3,1]，最后再删除 [5]。
         

        提示：

        1 <= arr.length <= 100
        1 <= arr[i] <= 20

    问题分析:
        数据量这么小。。可以尽情保存状态。

        该题中， 左边和右边的相同数字可以一起删掉。。

        该题得到的最大收获就是:
            看似是在区间两端进行的操作， 也是可以使用区间dp的！！！因为，两端的情况都是从长度为1开始慢慢演化得到的！！
        
        在本题中, dp[i][j]就保存了在区间[i,j]中，删除所有字符的最少操作次数。

        对区间更新的状态转移就是：
            k属于[i,j]

            dp[i][j] = INT_MAX
            确定区间[i,j]：
                if dp[i] == dp[k]:
                    dp[i][j] = min( dp[i][j], max( 1, dp[i+1][k-1]+dp[k+1][j] ));
                else:
                    dp[i][j] = min( dp[i][j], dp[i][k]+dp[k+1][j] )
*/

class Solution {
public:
    int minimumMoves(vector<int>& arr) {
        int dp[103][103]={0};
        for ( int i=1; i<=102; ++i ){
            dp[i][i] = 1;
        }
        int n = arr.size();
        for ( int len=2;len<=n; ++len )
            for ( int i=1; i+len-1<=n; ++i ){
                int j=i+len-1;
                dp[i][j] = INT_MAX;
                for ( int k=i; k<=j; ++k ){
                    if  ( arr[i-1]==arr[k-1] ){
                        dp[i][j] = min( dp[i][j], max( 1, dp[i+1][k-1] ) + dp[k+1][j] );
                    }else{
                        dp[i][j] = min( dp[i][j], dp[i][k] + dp[k+1][j] );
                    }
                    
                }
            }
        return dp[1][n];
    }
};