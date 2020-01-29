/*
    问题描述:
        给定数组 nums 由正整数组成，找到三个互不重叠的子数组的最大和。

        每个子数组的长度为k，我们要使这3*k个项的和最大化。

        返回每个区间起始索引的列表（索引从 0 开始）。如果有多个结果，返回字典序最小的一个。

        示例:

        输入: [1,2,1,2,6,7,5,1], 2
        输出: [0, 3, 5]
        解释: 子数组 [1, 2], [2, 6], [7, 5] 对应的起始索引为 [0, 3, 5]。
        我们也可以取 [2, 1], 但是结果 [1, 3, 5] 在字典序上更大。
        注意:

        nums.length的范围在[1, 20000]之间。
        nums[i]的范围在[1, 65535]之间。
        k的范围在[1, floor(nums.length / 3)]之间。

    问题分析:
        一开始往最大和的方向去想了.. 即dp[i][j]表示前i个元素分为3个子数组的最大和..

        状态更新也很简单.. 
        即 以第i个元素为结尾的话分len个子数组的最大和， 就是 { 取dp[i-1][len]的情况,  取以第i个元素为结尾的子数组的情况( dp[i-k][len-1] + sums{i-k+1,i} ) }
        这两个情况里的一个..

        len from 2 to 3:
            i from 1 to n :
                dp[i][len] = max( dp[i-1][len], dp[i-k][len-1] + sums{i-k+1,i} ) 

        后来一看.. 居然让求三个子数组的首个index ( 我倒...

        求打印路径的思想 就是 根据后一个的位置来推前一个的位置..

        就用path[i][j] 记录了 前i个元素分得了j个子数组以后的第j个子数组的index.. 
        
        知道了最后一个子数组的首个index之后( 就是path[n][3] )

        last_index1 = path[n][3]

        区间范围就从[0,n]的第3个子数组 变为 [0, last_index1]的第2个子数组 

        last_index2 = path[last_index1][2]

        区间范围就从[0,last_index1]的第2个子数组 变为 [0, last_index2]的第1个子数组 
        
        。。

        依次找到所有的index.. （ 打印路径这一块挺绕的.. 但只要抓住从后向前推的思想，想想也能明白

        然后得到的res数组就是 一个逆向的 子数组的首个index
        做一个reverse 之后就是答案了.。

        实现的时候，方便起见，可以记录子数组的最后一个位置，然后在存入res数组的时候 再-k+1就行了..

        这个思路也可以解决K个无重叠子数组的最大和..

        时空复杂度为O(N*K) 

*/

class Solution {
public:
    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
        /*
            dp[i][j] 表示 前i个元素分成j个子数组所能得到的最大值
            初始化 len = 1的情况
            len from 2 to 3:
                i from 1 to n :
                    dp[i][len] = max( dp[i-1][len], dp[i-k][len-1]+sums{i-k+1,i} ) 
        */
        const int T = 3;
        int n=nums.size();
        int sums[20001]={0};
        int dp[20001][4]={0};
        int path[20001][4]={0};
        
        // 预先求一下前缀和
        for ( int i=1; i<=nums.size(); ++i )
            sums[i] = sums[i-1] + nums[i-1];

        // dp
        for ( int len=1; len<=T; ++len )
            for ( int i=k*len; i<=nums.size(); ++i ){
                if ( dp[i-1][len]<dp[i-k][len-1]+sums[i]-sums[i-k] ){
                    // 取 以第i个元素为结尾的区间 的情况
                    dp[i][len] = dp[i-k][len-1]+sums[i]-sums[i-k];
                    path[i][len] = i;
                }else{
                    // 取前一个.. i-1的情况 
                    dp[i][len] = dp[i-1][len];
                    path[i][len] = path[i-1][len];
                }
            }
        
        // 打印路径
        vector<int> res;
        int last = path[n][T];
        res.push_back( last-k );
        for ( int i=T-1; i>=1; --i ){
            last = path[last-k][i];
            res.push_back( last-k );
        }
        reverse(res.begin(), res.end());
        return res;
    }
};





