/*
    问题描述：
        你打算利用空闲时间来做兼职工作赚些零花钱。
        这里有 n 份兼职工作，每份工作预计从 startTime[i] 开始到 endTime[i] 结束，报酬为 profit[i]。
        给你一份兼职工作表，包含开始时间 startTime，结束时间 endTime 和预计报酬 profit 三个数组，请你计算并返回可以获得的最大报酬。
        注意，时间上出现重叠的 2 份工作不能同时进行。
        如果你选择的工作在时间 X 结束，那么你可以立刻进行在时间 X 开始的下一份工作。

        示例 1：
        输入：startTime = [1,2,3,3], endTime = [3,4,5,6], profit = [50,10,40,70]
        输出：120
        解释：
        我们选出第 1 份和第 4 份工作， 
        时间范围是 [1-3]+[3-6]，共获得报酬 120 = 50 + 70。
        
        示例 2：

        输入：startTime = [1,2,3,4,6], endTime = [3,5,10,6,9], profit = [20,20,100,70,60]
        输出：150
        解释：
        我们选择第 1，4，5 份工作。 
        共获得报酬 150 = 20 + 70 + 60。
        
        示例 3：

        输入：startTime = [1,1,1], endTime = [2,3,4], profit = [5,6,4]
        输出：6
         
        提示：

        1 <= startTime.length == endTime.length == profit.length <= 5 * 10^4
        1 <= startTime[i] < endTime[i] <= 10^9
        1 <= profit[i] <= 10^4

    问题分析：
        这种处理区间的重合问题，

        可以考虑对end进行排序(end比较重要)

        然后找最大profit 就是dp了

        dp[i]保存了前i个区间（区间已经有序），所能得到的最大的profit
        
        状态转移就是 dp[i] = max( dp[i-1], dp[pre] + profit[i] )
        max里的两个情况，分别代表 对第i个区间的“不取” 和 "取"的情况

        不取： 那么就是dp[i-1]
        取： 先找到和第i个区间不重合的前一个区间，假设是第pre个区间，
            然后dp[pre] + 当前这个区间的profit

        ps: 找pre区间这一步可以遍历 ， 也可以二分，
            （虽然我用二分分了一下，发现速度变慢了 
*/

class Solution {
public:
    // 离散化时间, dp[i]表示前i区间，能获得的最大收益
    // dp[i] = max( dp[pre]+pro, dp[i-1] ); 
    class node{
        public:
            int start;
            int end;
            int profit;
            node(int a,int b,int c){
                start = a;
                end = b;
                profit = c;
            }
    };
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        int n = profit.size();
        vector<node> nums;
        nums.push_back({0,0,0});
        vector<int> dp( n+2, 0 );
        for ( int i=0; i<n; ++i )
            nums.push_back( node(startTime[i], endTime[i], profit[i]) );
        
        auto cmp = [](node &a, node & b){ 
            return vector<int>{ a.end, a.start, a.profit } < vector<int>{ b.end, b.start, b.profit };  
        };
        sort( nums.begin(), nums.end(), cmp);
        int l,r,mid,target;
        int res = 0,j;
        for ( int i=1; i<=n; ++i ){
            // 遍历
            /*for ( int j=i-1; j>=0; --j ){
                if ( nums[j].end <= nums[i].start ){
                    dp[i] = max( dp[i-1], dp[j]+nums[i].profit );
                    break;
                }
            }*/
            // 找到首个nums[j].end <= nums[i].start
            // 二分
            l=0; r=i-1; target=nums[i].start;
            while( l<=r ){
                mid= l+(r-l)/2;
                if ( nums[mid].end<=target ){
                    j = mid;
                    l = mid+1;
                }else {
                    r = mid-1;
                }
            }
            dp[i] = max( dp[i-1], dp[j]+nums[i].profit );
            res = max(res, dp[i]);
        }
        return res;
    }
};