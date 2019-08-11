/*
    问题描述:
        给出一个二进制数组 data，你需要通过交换位置，将数组中 任何位置 上的 1 组合到一起，并返回所有可能中所需 最少的交换次数。

        示例 1：
        输入：[1,0,1,0,1]
        输出：1
        解释： 
        有三种可能的方法可以把所有的 1 组合在一起：
        [1,1,1,0,0]，交换 1 次；
        [0,1,1,1,0]，交换 2 次；
        [0,0,1,1,1]，交换 1 次。
        所以最少的交换次数为 1。

        示例 2：
        输入：[0,0,0,1,0]
        输出：0
        解释： 
        由于数组中只有一个 1，所以不需要交换。


    问题分析:   
        最终的形态是 所有1都是连续的，所以，可以用滑动窗口来遍历，
        窗口大小为1的个数，设其为n，
        假设窗口内1的个数为m
        本题就是要求 min(n-m)

        可以用前缀和数组来求区间内1的个数
 */


class Solution {
public:
    int minSwaps(vector<int>& data) {
        int n = data.size();
        if ( n==0 ) return 0;
        int a=0, mini=INT_MAX;
        vector<int> predix(n+1,0);
        for ( int i=1; i<=n; ++i )
            predix[i] = predix[i-1] + data[i-1];
        a = predix[n];
        for ( int i=a; i<=n; ++i )
            mini = min( mini, a - (predix[i]-predix[i-a]) );
        return mini;
    }
};