/*
	题目描述：
		在卖股票Ⅱ的基础上，限制了买卖次数，最多买卖两次，
		问最大利润是多少。
	
	题目分析：
		解法一：
			O(N^2) 超时解法
			先算出前i天抛出一次的最大利润
			再迭代算出 从第i天到最后一天 只抛出一次所获得的最大利润
			相减找出最大值

		解法二：
			不要用迭代，用类似找前i天抛出一次的最大利润的方法，
			找出在后i天内， 只抛出一次所获得的最大利润时，
			从O(N^2)优化到O(N)
		
		解法三：
			另辟蹊径，
			看了网上的解法，分别设了四个状态，
			f_sell[i]:  在第i个位置必买过一次后，当前收益的最大值
			f_buy[i] :  在第i个位置必卖一次后，当前收一次的最大值
			s_sell[i]:  在第i个位置必买过两次后，当前收益的最大值
			s_buy[i]:   在第i个位置必卖过两次后，当前收益的最大值
		
			状态转移公式是：
			f_buy[i] = max(f_buy[i-1],-prices[i]);  //要么不在这次买(f_buy[i-1]) ， 要么在这次买(-prices[i])
			f_sell[i] = max(f_sell[i-1],f_buy[i-1]+prices[i]); //要么不在这次卖(f_sell[i-1])，要么在这次卖(f_buy[i-1]+prices[i])
			
			s_buy[i] = max(s_buy[i-1],f_sell[i-1]-prices[i]);   //要么不在这次买(s_buy[i-1]) ， 要么在这次买(f_sell[i-1]-prices[i])
			s_sell[i] = max( s_buy[i-1]+prices[i],s_sell[i-1] ); //要么不在这次卖(s_sell[i-1]) , 要么在这次卖(s_buy[i-1]+prices[i])
			
			看起来有点复杂，其实这么一设还是挺清晰的。
*/



class Solution_1&2 {
public:
    int maxProfit(vector<int>& prices) {
        //O(N^2) 超时解法
        //先算出前i天抛出一次的最大利润
        //再迭代算出 从第i天到最后一天 只抛出一次所获得的最大利润
        //相减找出最大值
        if ( prices.size()<2 ) return 0;
        /*
        vector<int> once; //once[i]表示前i天抛出一次后的最大利润
        once.resize(prices.size());
        int mini=prices[0];
        once[0] = 0;
        for ( int i=1; i<prices.size(); ++i ){
            once[i] = max( once[i-1], prices[i]-mini );
            mini = min(mini, prices[i]);
        }
        int maxi=0,res = 0;
        for ( int i=2; i<prices.size(); ++i ){
            mini = prices[i]; 
            maxi=0; //i到最后一天，只抛出一次所获得的最大利润为maxi
            for ( int j=i+1; j<prices.size(); ++j ){
                maxi = max(maxi, prices[j]-mini);
                mini = min(mini,prices[j]);
            }
            res = max(res, once[i-1] + maxi);
        }

        return max(res,once.back());*/
        
        //法一优化到O(N)
        //在找从第i天到最后一天 只抛出一次所获得的最大利润时，
        //不要用迭代，用类似找前i天抛出一次的最大利润的方法
        vector<int> once; //once[i]表示前i天抛出一次后的最大利润
        once.resize(prices.size());
        int mini=prices[0];
        once[0] = 0;
        for ( int i=1; i<prices.size(); ++i ){
            once[i] = max( once[i-1], prices[i]-mini );
            mini = min(mini, prices[i]);
        }
        vector<int> ronce; //ronce[i]表示在后i天内，抛出一次后的最大利润
        ronce.resize(prices.size());
        int maxi=prices.back();
        ronce[0] = 0;
        int n = prices.size(),res=0;
        for ( int j=1; j<prices.size(); ++j ){
            ronce[j] = max( ronce[j-1],maxi-prices[n-j-1] );
            maxi = max(maxi, prices[n-j-1]);
        }
        //print(ronce);
        
        //找出最值，即
        // 第[1,i]天抛一次的最大利润+第[i,n]天抛一次最大利润
        //中的最大利润，就是答案了。
        for ( int i=0; i<prices.size(); ++i ){
            res = max(res,once[i]+ronce[n-i-1]);
        }
        return res;
    }
};

class Solution3 {
public:
    int f_sell[50001];  //在第i个位置必买过一次后，当前收益的最大值
    int f_buy[50001];   //在第i个位置必卖一次后，当前收一次的最大值
    int s_sell[50001];  //在第i个位置必买过两次后，当前收益的最大值
    int s_buy[50001];   //在第i个位置必卖过两次后，当前收益的最大值
    
    int maxProfit(vector<int>& prices) {
        if ( !prices.size() ) return 0;
        f_sell[0] = 0;
        f_buy[0] = -prices[0];
        for ( int i=1; i<prices.size(); ++i ){
            f_buy[i] = max(f_buy[i-1],-prices[i]);  //要么不在这次买(f_buy[i-1]) ， 要么在这次买(-prices[i])
            f_sell[i] = max(f_sell[i-1],f_buy[i-1]+prices[i]);  //要么不在这次卖(f_sell[i-1])，要么在这次卖(f_buy[i-1]+prices[i])
        }
        
        s_buy[2] = f_sell[1]-prices[2];   
        s_sell[2] = INT_MIN;
        for ( int i=3; i<prices.size(); ++i ){
            s_buy[i] = max(s_buy[i-1],f_sell[i-1]-prices[i]);   //要么不在这次买(s_buy[i-1]) ， 要么在这次买(f_sell[i-1]-prices[i])
            s_sell[i] = max( s_buy[i-1]+prices[i],s_sell[i-1] ); //要么不在这次卖(s_sell[i-1]) , 要么在这次卖(s_buy[i-1]+prices[i]) 
        }
        return max(f_sell[prices.size()-1],s_sell[prices.size()-1]);   //因为有可能买了2次的却不如买了1次的收益多，所以取最大
    }
    
};