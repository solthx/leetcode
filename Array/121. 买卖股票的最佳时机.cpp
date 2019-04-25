/*
	题目描述：
		数组里的每个元素代表股票价钱，买一次，抛一次，求最大利润
		
		示例 1:
		输入: [7,1,5,3,6,4]
		输出: 5
		解释: 在第 2 天（股票价格 = 1）的时候买入，在第 5 天（股票价格 = 6）的时候卖出，最大利润 = 6-1 = 5 。
			 注意利润不能是 7-1 = 6, 因为卖出价格需要大于买入价格。
		
		示例 2:
		输入: [7,6,4,3,1]
		输出: 0
		解释: 在这种情况下, 没有交易完成, 所以最大利润为 0。

	问题分析：
		思路一：
			mi[i]记录前i天最便宜的股票
			ma[i]记录后i天最贵的股票
			for i from 0 to n-1:
				res = max(res, ma[i]-mi[n-i-1])
			res就是最大利润
			
		思路二： 直接在线处理
			mini记录当前的最便宜的股票
			res记录当前最大利润
			
			对于第i天的股票（prices[i]）：
				res  =  max(res , prices[i]-mini)
				mini =  min(mini, prices[i] )  // 更新mini
			
*/

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if ( prices.size()<=1 ) return 0;
        int a,b,n = prices.size();
        int res = 0;
        /*
            解法一：比较慢，比较浪费空间
        vector<int> mi;
        vector<int> ma;
        mi.push_back(prices[0]);
        for ( int i=1; i<n; ++i ){
            mi.push_back(min(mi.back(),prices[i]));
        }
        ma.push_back(prices[n-1]);
        for ( int i=n-2; i>=0; --i ){
            ma.push_back(max(ma.back(),prices[i]));
        }
        for ( int i=0; i<n; ++i )
            res = max( res, ma[i]-mi[n-i-1]);*/
        
        //解法二：在线处理
        int mini=prices[0];
        for ( int i=1; i<prices.size(); ++i ){
            res = max(res, prices[i]-mini);
            if ( mini>prices[i] ) mini = prices[i];
        }
        return res;
    }
    
};