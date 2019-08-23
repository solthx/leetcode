/*
    问题描述:
        假设有 n 台超级洗衣机放在同一排上。开始的时候，每台洗衣机内可能有一定量的衣服，也可能是空的。
        在每一步操作中，你可以选择任意 m （1 ≤ m ≤ n） 台洗衣机，与此同时将每台洗衣机的一件衣服送到相邻的一台洗衣机。
        给定一个非负整数数组代表从左至右每台洗衣机中的衣物数量，请给出能让所有洗衣机中剩下的衣物的数量相等的最少的操作步数。如果不能使每台洗衣机中衣物的数量相等，则返回 -1。

        示例 1：
            输入: [1,0,5]
            输出: 3
            解释: 
                第一步:    1     0 <-- 5    =>    1     1     4
                第二步:    1 <-- 1 <-- 4    =>    2     1     3    
                第三步:    2     1 <-- 3    =>    2     2     2   
        
        示例 2：
            输入: [0,3,0]
            输出: 2
            解释: 
                第一步:    0 <-- 3     0    =>    1     2     0    
                第二步:    1     2 --> 0    =>    1     1     1     
        
        示例 3:
            输入: [0,2,0]
            输出: -1
            解释: 
                不可能让所有三个洗衣机同时剩下相同数量的衣物。
             

            提示：
                n 的范围是 [1, 10000]。
                在每台超级洗衣机中，衣物数量的范围是 [0, 1e5]。

    问题分析:
        看了10min， 没太有思路，就看了题解...
        
        1. 先判断能否等分成n份
        2. 如果可以分的话，算出平均值avg.
        3. 算出前缀和 preSum[i] = sum{nums[0], .. ,nums[i]}
        3. 从左向右扫描，在第i个位置:
            3.1 先找计算需要向左区间( [0,i-1] )输送的衣服, lcnt = (i-1)*avg - preSum[i-1]
            3.2 再计算出需要向右区间( [i+1,n] )输送的衣服, rcnt = (n-i)*avg - (preSum[n]-preSum[i])
            3.3 四种情况:
                1. lcnt>0 && rcnt>0 : 说明两边的衣服都太多了，需要同时向第i个位置上输送衣服， 此时的最大操作次数为 max( lcnt, rcnt )
                2. lcnt<0 && rcnt<0 : 说明两边的衣服都太少了，第i个位置上的衣服太多了，需要从第i个位置上向两边输送，
                    但是，一次一个位置只能输送走一件衣服(尽管在同一时刻可以接收多件，但只能输出一件)，所以此时的最大操作次数为依次传输的次数，即(abs( lcnt+rcnt ))
                3. lcnt>0 && rcnt<0 : 说明右边衣服太少了，左边衣服太多了，最大操作次数为 max( abs(lcnt), abs(rcnt) );
                4. 和3同理
*/

class Solution {
public:
    int findMinMoves(vector<int>& machines) {
        
        if ( machines.size()==0 ) return 0;
        int n=machines.size(),res =0;
          
        vector<int> sums(n+2,0);
        for ( int i=1; i<=n; ++i )
            sums[i] = sums[i-1] + machines[i-1];
        if ( sums[n]%n!=0 ) return -1;
        int avg = sums[n]/n;
      
        for ( int i=1; i<=n; ++i ){
            int lcnt = sums[i-1] - (i-1)*avg;
            int rcnt = (sums[n]-sums[i]) - (n-i)*avg;
            if ( lcnt>0 && rcnt>0 ) res = max( res, max(lcnt,rcnt) );
            else if ( lcnt<0 && rcnt<0 ) res = max( res, -lcnt-rcnt );
            else res = max( res, max(abs(lcnt),abs(rcnt)) );
        }
        return res;
    }
};