/*
    问题描述:
        如果序列 X_1, X_2, ..., X_n 满足下列条件，就说它是 斐波那契式 的：
        n >= 3
        对于所有 i + 2 <= n，都有 X_i + X_{i+1} = X_{i+2}
        给定一个严格递增的正整数数组形成序列，找到 A 中最长的斐波那契式的子序列的长度。如果一个不存在，返回  0 。

        （回想一下，子序列是从原序列 A 中派生出来的，它从 A 中删掉任意数量的元素（也可以不删），而不改变其余元素的顺序。例如， [3, 5, 8] 是 [3, 4, 5, 6, 7, 8] 的一个子序列）

         

        示例 1：

        输入: [1,2,3,4,5,6,7,8]
        输出: 5
        解释:
        最长的斐波那契式子序列为：[1,2,3,5,8] 。
        示例 2：

        输入: [1,3,7,11,12,14,18]
        输出: 3
        解释:
        最长的斐波那契式子序列有：
        [1,11,12]，[3,11,14] 以及 [7,11,18] 。
         

        提示：

        3 <= A.length <= 1000
        1 <= A[0] < A[1] < ... < A[A.length - 1] <= 10^9
        （对于以 Java，C，C++，以及 C# 的提交，时间限制被减少了 50%）

    问题分析：
        dfs先试了一下，果不其然的TLE了。。

        那么dp应该没跑了。。

        因为斐波那契数列的第i项肯定是由前两个确定的值所得到的，
        所以，就把两个数的坐标来作为状态进行保存，根据这个来逆推前一个。

        dp[i][j]表示以第j个元素为最后一个，第i个元素为倒数第二个的最长斐波那契数列的长度

        状态转移:
        for i from 1 to n:
            for j from i+1 to n:
                diff = A[j]-A[i]  //这个差就是前一个斐波那契的倒数第三个元素
                l = index[diff]   //得到这个元素的坐标
                dp[i][j] = max(dp[i][j], dp[l][i] + 1); // 进行状态更新
        
        得到坐标这一步，也可以在原数组进行二分查找来得到。。
*/

class Solution {
public:
    int lenLongestFibSubseq(vector<int>& A) {
        unordered_map<int,int> index;
        for ( int i=0; i<A.size(); ++i )
            index[A[i]] = i;
        int dp[1001][1001]={0}; // dp[i][j]是以第i个元素和第j个元素为结尾的斐波那契数列的最长长度
        // N^2 * logN
        int res = 0;
        for ( int i=0; i<A.size(); ++i )
            for ( int j=i+1; j<A.size(); ++j ){
                dp[i][j] = 2;
                int diff = A[j]-A[i];
                /*int mid, l = 0, r = i-1;
                while( l<=r ){
                    mid = l + (r-l)/2;
                    if ( A[mid]>diff ) r = mid-1;
                    else if ( A[mid]<diff ) l = mid +1 ;
                    else{
                        l = mid;
                        break;
                    }
                }*/
                if ( i>0 && diff > A[i-1] ) break;
                if ( index.count( diff ) ){
                    int l = index[diff];
                    dp[i][j] = max(dp[i][j], dp[l][i] + 1);
                    res = max( res, dp[i][j]);
                }
            }
        return res;
    }
};