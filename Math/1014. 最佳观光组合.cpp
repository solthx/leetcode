/*
    问题描述:
        给定正整数数组 A，A[i] 表示第 i 个观光景点的评分，并且两个景点 i 和 j 之间的距离为 j - i。
        一对景点（i < j）组成的观光组合的得分为（A[i] + A[j] + i - j）：景点的评分之和减去它们两者之间的距离。
        返回一对观光景点能取得的最高分。

        示例：
            输入：[8,1,5,2,6]
            输出：11
            解释：i = 0, j = 2, A[i] + A[j] + i - j = 8 + 5 + 0 - 2 = 11
         
        提示：
            2 <= A.length <= 50000
            1 <= A[i] <= 1000

    问题分析:
        方法一: 前缀和的思想
            和https://github.com/solthx/leetcode/blob/master/Math/1131.%20%E7%BB%9D%E5%AF%B9%E5%80%BC%E8%A1%A8%E8%BE%BE%E5%BC%8F%E7%9A%84%E6%9C%80%E5%A4%A7%E5%80%BC.cpp
            的思想有点像。
            对于求 (A[i] +- A[j] +- i +- j) 的最值问题，
            
            可以通过调整位置， 转换成 (A[i] +- i) +- (A[j] +- j)
            这是思路一.

            如果对i和j没有要求的话， 那就是可以参考 #1131 ， 这种情况比较好搞，因为既然没要求，那根据
            “变量名无关”的特性，只要考虑一个情况就行了.

            而本题对i和j有要求， 即（i < j），
            那么可以用 left[i] 和 right[j] 来分别保存 [0,i] 和 [j,n] 区间内的最值， 然后作差或作和
            （总之就是利用前缀和的思想来做）
 
        方法二:
            本题要求 max( A[i]+A[j]+ i-j ) 
            也就是求 max( A[i]+i + A[j]-j )
            
            也就是 max{A[i]+i} + max{A[j]-j}
            且满足 i<j

            这个只要遍历一遍就行了，
            
            maxi记录 [0,i]里的max{A[i]+i}， 
            然后遍历一遍记录 max{A[j]-j}
            res实时记录结果

            最后返回res
*/

class Solution1 {
public:
    int maxScoreSightseeingPair(vector<int>& A) {
        int n = A.size();
        vector<int> left(n+1,INT_MIN), right(n+2,INT_MIN);
        for ( int i=1; i<=n; ++i ){
            left[i] = max( left[i-1], A[i-1]+i-1 );
            right[n-i+1] = max( right[n-i+2], A[n-i]-(n-i) );
        }
        int res = INT_MIN;
        for ( int i=1; i<n; ++i ){
            res = max(res, left[i]+right[i+1]);
        }
        return res;
    }
};

class Solution2 {
public:
    int maxScoreSightseeingPair(vector<int>& A) {
        int res=INT_MIN,left=INT_MIN;
        for ( int i=0; i<A.size(); ++i ){
            res = max( res, left+A[i]-i );
            left = max( left, A[i]+i );
        }
        return res;
    }
};