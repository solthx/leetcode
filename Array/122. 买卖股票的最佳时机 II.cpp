/*
	题目描述，数组是每天的股票，每天的操作是要么买要么卖，
	求最大利润能得多少
	
	题目分析：简单贪心，涨到顶就抛出
*/

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if ( prices.size()<2 ) return 0;
        int i,res=0,mini=prices[0];
        for ( i=1; i<prices.size(); ++i ){
            if ( prices[i]<prices[i-1] ){
                res += (prices[i-1]-mini);
                mini = prices[i];
            } 
        }
        res += (prices[i-1] - mini);
        return res;
    }
};