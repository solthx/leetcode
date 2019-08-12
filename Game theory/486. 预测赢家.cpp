/*
    问题描述：
        给一个数组，A和B每次从数组两端取走一个数，
        最终谁取走的数的总和更大，谁就胜出

        问是否先手必胜?
    
    问题分析:
        本题博弈的思想和#1140 石子游戏II 如出一辙
        
        helper(l,r,..) 保存了 当前player从区间[l,r]的两端
        选走一个数后所能取得的最大值。

        那么当前玩家所能取得的最大值就是下面两个情况里的最大:
            取走左端元素: 区间[l,r]的总和 - helper( l+1,r )
            取走右端元素: 区间[l,r]的总和 - helper( l,r-1)
        下一选手肯定也是拼劲全力的选，并且因为玩家只有两个，所以一个人选的总和是a, 区间总和是b， 那么另一个人选的肯定是b-a

        然后只要返回上面的两个情况的最大值，就是当前情况能取得的最大值了。
        
        为了减少重复的计算，用记忆数组来保存中间状态
        dp[l][r] 表示当前player在个数区间[l,r]能够拿的最大的值， 也就是helper函数的作用

        注意！这种一般是下面的这种程序模版：
        .. func(){
            if ( memo保存过 ) return memo[..]
            ...
            ...
            ...
            memo[..] = ...
            return memo[..]
        }
        // memo的保存一定是放在最后，且只有一个！

*/

class Solution {
public:
    bool PredictTheWinner(vector<int>& nums) {
        int n = nums.size();
        vector<int> sums(n+1, 0);
        for ( int i=1; i<=n; ++i )
            sums[i] = sums[i-1] + nums[i-1];
        
        vector<vector<int>> memo(n+1, vector<int>(n+1, -1));
        int first = helper( n, 1, n,  memo, nums, sums); //helper函数返回当前player在个数区间[l,r]能够拿的最大的值
        return first*1.0 >= (sums[n])/2.0;
    }
    
    int helper( int n,int l, int r, vector<vector<int>>& memo, vector<int>& nums, vector<int> & sums ){
        if ( memo[l][r]>=0 ) return memo[l][r];
        if ( l==r ) return nums[l-1];
        
        int inter = sums[r] - sums[l-1];
        int left = inter - helper( n, l+1, r, memo, nums, sums );
        int right = inter - helper(n, l, r-1,  memo, nums, sums );
        memo[l][r] = max(  left , right);
        return memo[l][r];
    }

};

