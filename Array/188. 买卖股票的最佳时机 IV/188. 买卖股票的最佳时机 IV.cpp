/*
	问题描述：
		买卖股票III中限制了买卖次数为2， 在本题是买卖次数必须小于等于k次，
		把这个情况推广开了。

	问题分析：
		方法一(买卖股票III方法三的推广)：
			看懂了买卖股票III中的方法三，这题会很容易
			就是买卖股票III中的方法三的推广， 外面再套一层循环为k次就行了， 依然是dp问题
			buy[i][j] 表示在前i天，必买过j次的最大收入
			sell[i][j] 表示在前i天，必卖过j次的最大收入
			最后返回buy[n][k]就行了
			
			需要提一下的是，当天数为n时，因为在一天只可以有一个操作，要么买，要么卖
			所以当k超过n/2时，买卖次数就不受限制了，这时候又变回了“买卖股票Ⅱ”的贪心问题。

		方法二（网上的题解，也是用的dp，一个局部最优一个全局最优，有点意思就记一下）：
			有点麻烦，写到markdown里吧。。
*/

class Solution1 {
public:
    int maxProfit(int k, vector<int>& prices) {
        //buy[i][j] 表示在前i天，必买过j次的最大收入
        //sell[i][j] 表示在前i天，必卖过j次的最大收入
        
        if ( k<=0 || prices.size()<2 ) return 0;
        if ( k>=prices.size()/2 ) //卖卖次数不再受限制，直接按贪心方法求 
			return greedy(k,prices);
        
        //==============初始化==============
        vector< vector<int> > sell;
        sell.resize(prices.size()+1);
        for ( int i=0; i<=prices.size(); ++i ) sell[i].resize(k+1,0);
        vector< vector<int> > buy;
        buy.resize(prices.size()+1);
        for ( int i=0; i<=prices.size(); ++i ) buy[i].resize(k+1,0);
        //==================================
        
        
        for ( int times=1; times<=k; ++times ){ //抛出次数
            sell[1][times] = 0;
            buy[1][times] = -prices[0];
            for ( int i=2; i<=prices.size(); ++i ){
                //第i天
                sell[i][times] = max( sell[i-1][times], buy[i-1][times]+ prices[i-1] ); // 第i天不卖或卖
                buy[i][times] = max( buy[i-1][times], sell[i-1][times-1] - prices[i-1] ); // 第i天不买或买
            }
        }
        return sell[prices.size()][k];
    }
    
    int greedy(int k,vector<int> & nums){
        int res = 0;
        for ( int i=1; i<nums.size(); ++i )
            if ( nums[i]>nums[i-1] )
                res += (nums[i]-nums[i-1]);
        return res;
    }
};


class Solution2 {
public:
    int greedy(int k,vector<int> & nums){
        int res = 0;
        for ( int i=1; i<nums.size(); ++i )
            if ( nums[i]>nums[i-1] )
                res += (nums[i]-nums[i-1]);
        return res;
    }
    int maxProfit(int k, vector<int>& prices) {
        if ( !prices.size() ) return 0;
        int n = prices.size();
        if ( k>n/2 ) return greedy(k,prices);
        vector<vector<int>> global(n+1,vector<int>(n+1,0));
        vector<vector<int>> local(n+1,vector<int>(n+1,0));
        int diff;
        for ( int i=1; i<prices.size(); ++i ){
            diff = prices[i]-prices[i-1];
            for ( int j=1; j<=k; ++j ){
                local[i][j] = max(local[i-1][j],global[i-1][j-1])+diff;
                global[i][j] = max(local[i][j],global[i-1][j]);
            }
        }
        return global[n-1][k];
    }
};