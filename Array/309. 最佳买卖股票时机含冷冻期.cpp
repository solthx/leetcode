/*
	题目描述：
		买卖股票问题Ⅱ的变种，卖完股票以后，有一天的冷冻期什么也不能做
		且买卖次数不受限制，问最大利润能获得多少
		
	题目分析：
		方法一：
			首先能知道今天的三个操作：
                1. 什么也不做
                2. 昨天买今天卖
                3. 昨天之前买了一次，今天卖
				
			令profits[i] 为前i天的最大利润
			buy[i] 为前i天中，已经有一天买过了一次的最大利润
		状态更新：	
			// 前i天买过的一次的话，可以是今天买 或是 之前的某一天买
			buy[i] = max( profit[i-2] - prices[i] , buy[i-1] );
			
			// 前i天的最大利润，可以是：
				1. 今天啥也不干 profits[i-1]
				2. 昨天买，今天卖 profits[i-3]-prices[i-1]+prices[i]; (因为考虑冷冻期，所以单独列出来)
				3. 昨天之前的某一天买，今天卖 buy[i-1]+prices[i]
				
			profits[i] = max( profits[i-3]-prices[i-1]+prices[i],  buy[i-1]+prices[i] );
			profits[i] = max( profits[i],profits[i-1] );
		最终返回 profits[n]就行了 ，要主要因为 i是天数，从1开始，所以在编写程序的时候，prices[i]一个是prices[i-1]
	
		方法二：
			看了一下别人的题解，虽然我考虑过这种情况，但没推出状态公式。。
			这里也记录一下好了。
			   
			buy[i]表示上次操作是“买”的话，当前的最大收益
			sell[i]表示上次操作是“卖”的话，当前的最大收益
			
		状态更新：
			今天买，或之前买
			buy[i] = max(buy[i-1](不买),sell[i-2]-prices[i](买));
			今天卖，或之前卖
			sell[i] = max(sell[i-1](不卖),buy[i-1]+prices[i](卖));
			
		方法三：
			对方法二的优化，利用滚动数组，使得空间复杂度变成O(1)
			跑完结果双百 :)
*/

class Solution1 {
public:
    int maxProfit(vector<int>& prices) {
        if ( prices.size()<2 ) return 0;
		
        vector<int> profits(prices.size()+1,0);
        vector<int> buy(prices.size()+1,0);
        
		//初始化前两天
        buy[2] = max(-prices[0], -prices[1]) ; //买第一天的或买第二天的
        profits[2] = max( 0, prices[1]-prices[0] ); //买第一天，第二天卖， 或者什么都不做
        
        for ( int i=3; i<=prices.size(); ++i ){
            buy[i] = max( profits[i-2] - prices[i-1] , buy[i-1] );
            profits[i] = max( profits[i-3]-prices[i-1]+prices[i-1],  buy[i-1]+prices[i-1] );
            profits[i] = max( profits[i],profits[i-1] );
        }
        return profits[prices.size()];
    }
};

class Solution2 {
public:
    int buy[4000];
    int sell[4000];
    int maxProfit(vector<int>& prices) {
        if ( !prices.size() ) return 0;
        buy[0] = -prices[0];
        sell[0] = 0;
        if ( prices.size()>1 ){
            buy[1] = max(-prices[0],-prices[1]);
            sell[1] = max(0,prices[1]-prices[0]);
        }
        for ( int i=2; i<prices.size(); ++i ){
            buy[i] = max(buy[i-1],sell[i-2]-prices[i]);
            sell[i] = max(sell[i-1],buy[i-1]+prices[i]);
        }
        return sell[prices.size()-1];
    }
};

class Solution3 {
public:
    //空间复杂度为O(1)的方法 , 网上大神太强了QAQ
    int maxProfit(vector<int>& prices) {
        int buy = INT_MIN, pre_sell = 0, pre_buy=0, sell = 0;
        for ( int i=0; i<prices.size(); ++i ){
            pre_buy = buy; //在还未更新变量就进入下一个位置的时候，当前的xx就是pre_xx , 当前的pre_xx是pre_pre_xx
            buy = max(pre_sell-prices[i], pre_buy );  //因为第一次要选前者，所以把pre_buy的初始值弄成MIN_INT，但！由于上面的赋值语句，所以实际设置初始值应该设置buy为MIN_INT
            pre_sell = sell;    //把其实是pre_pre_sell的pre_sell，变成真正的pre_sell(也就是这里未更新的sell)
            sell = max(pre_sell, pre_buy+prices[i]); 
        }
        return sell;
    }
};
