/*
    问题描述:   
        如果一个数列至少有三个元素，并且任意两个相邻元素之差相同，则称该数列为等差数列。
        例如，以下数列为等差数列:
        1, 3, 5, 7, 9
        7, 7, 7, 7
        3, -1, -5, -9

        以下数列不是等差数列。
        1, 1, 2, 5, 7

    问题分析：
        在我们手动去求解这个问题的时候，
        可以发现，在求以第i个元素为结尾的等差子序列的时候，
        则会去找 有哪些数字和满足 nums[j]-nums[k] == nums[i] - nums[j]
        因此确定两个关键点，就是i和 diff ( diff = nums[i]-nums[j] )
        然而这个diff会很大，所以用map来存..
        dp[i]是 map<longlong, int>类型，
        dp[i][diff]就是我们的状态了。。 但这个状态表示什么呢？
        
        当到第i个位置的时候，
        我们会遍历 [0,i-1]，将此游标命名为j， j属于[0,i-1],
        我们会去找 “序列内的元素至少为两个，且此等差数列的差值为nums[i]-nums[j]“ 这种序列的个数，
        然后加上当前nums[i]以后， 就变成了“序列内的元素至少为三个，且此等差数列的差值为nums[i]-nums[j]“
        这正是我们想要的，
        
        for i from 0 to n:
            for j from 0 to i:
                diff = nums[i] - nums[j]
                所以 dp[i][diff]就是 所有满足下列条件的序列个数：
                    序列内的元素至少为两个，且此等差数列的差值为diff
            
                确定下来这个以后，另一个难点就是如何推状态转移公式:
                    "序列内的元素至少为两个，且此等差数列的差值为diff" 的这种序列可以被分为
                    "序列内的元素等于两个，且此等差数列的差值为diff" 和 "序列内的元素至少为三个，且此等差数列的差值为diff"  
                    
                    前者命名为弱等差， 后者为等差，
                    弱等差加上nums[i],序列内元素最少个数从2变成了3，就变成了等差

                    前者的序列就是由 nums[i]和nums[j] 构成，只有这一个
                    后者的序列就是由 dp[j][nums[i]-nums[j]]这里面的序列， 全加上一个nums[i]， 序列性质不变，长度+1， 至少的个数从两个变成三个

                    diff = nums[i]-nums[j]
                    故dp[i][diff] = dp[j][diff] + 1;

                    但因为我们要的是所有"序列内的元素至少为三个，且此等差数列的差值为diff"这样的序列的个数，
                    所以在累加的时候，不是累加dp[i][diff]，而是 dp[j][diff]

                    就是说   dp[i][diff] = dp[j][diff] + 1;
                            res += dp[j][diff];
            
 */


class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& A) {
        int n = A.size();
        long long diff;
        int res=0;
        long long sum=0;
        int icnt=0;
        vector<unordered_map<long long,int>> dp( n ); // dp[i][diff]是以第i个元素结尾的弱等差个数
        for ( int i=1; i<n; ++i ){
            for ( int j=i-1; j>=0; --j ){
                sum = 0;
                diff = (long long)A[i]-(long long)A[j];
                if ( dp[j].count(diff)>0 )
                    sum = dp[j][diff]; //前面的弱等差 加上当前的，就变成等差了
                dp[i][diff]+=sum+1;  // 这个1是A[j]和A[i]新增的一个弱等差
                res += sum;
            }
        }
        return res;
    }
};