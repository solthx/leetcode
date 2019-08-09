/*
    问题描述:
        给定一个非负整数数组和一个整数 m，你需要将这个数组分成 m 个非空的连续子数组。
        设计一个算法使得这 m 个子数组各自和的最大值最小。

    问题分析:
        方法一：动态规划
            状态:
                dp[i][j] 定义为将 nums[0..i] 分成 j 份时能得到的最小的分割子数组最大值。
            状态转移:
                对于第 j 个子数组，它为数组中下标 k + 1 到 i 的这一段。因此，f[i][j] 可以从 max(f[k][j - 1], nums[k + 1] + ... + nums[i]) 这个公式中得到。
                遍历所有可能的 k，会得到 f[i][j] 的最小值。
                整个算法那的最终答案为 f[n][m]，其中 n 为数组大小。
                ( 直接想可以不大好想。。建议直接手动写写出对于数组nums的 m=1,2,3..的情况
                然后摸索子问题的获取方法，最终根据这个来推出状态转移的公式 )

        方法二: 贪心+二分
            用动归A过以后，速度有点慢。。看题解以后发现居然还能这样做。。
            思路
                我们很容易就能找到这个答案的一个性质：
                    如果我们找到了一种分割方案，使得最大的分割子数组和不超过 x，那么我们也能找到一种分割方案使得最大的分割子数组和不超过 y，其中 y 大于 x。
                对于值 x，我们把这个性质定义为 F(x)。如果 F(x) 为真，那就意味着我们一定可以找到一种分割方案使得最大的分割子数组和不超过 x。
                我们让 x 的区间为 负无穷大 到 无穷大，一旦我们找到一个值 x0，使得所有的 x < x0，F(x) 都为假，所有的 x >= x0，F(x) 都为真。那么显然，这个 x0 就是我们要的答案了。
            
            算法
                我们可以用二分搜索来找到 x0。每次循环，我们让 mid = (left + right) / 2，如果 F(mid) 为假，那么我们接下来就去搜索 [mid + 1, right] 区间；如果 F(mid) 为真，那么我们接下来就去搜索 [left, mid - 1] 区间。
            对于一个给定的 x，我们可以用贪心算法来计算 F(x)。我们用累计和 sum 来记录当前子数组的和，同时用 cnt 来记录子数组的数量。我们依次处理数组中的每个元素，对每个元素 num，如果 sum + num <= x，这就意味着当前的子数组没有超过限制。否则，就需要从当前元素 num 开始分割出一个新的子数组。
            在完成遍历完整个数组之后，比较 cnt 和 m 的值。如果 cnt <= m，这就意味可以找到一种分割方案使得最大的分割子数组和不超过 x。否则，F(x) 一定为假。
 */


// 动态规划
class Solution1 {
public:
    int splitArray(vector<int>& nums, int m) {
        // dp[i][m]表示前i个元素分为m个子集后的最大子集和的最小值 
        int n = nums.size(); 
        vector<vector<long>> dp( n+1, vector<long>(m+1, 0) );
        long maxi, maxi_min=INT_MAX;
        for ( int i=1; i<=n; ++i )
            dp[i][1] = dp[i-1][1] + nums[i-1];
        
        for ( int i=2; i<=m; ++i ){
            for ( int j=1; j<=n; ++j ){
                long acc = 0, k=j;  
                maxi_min=INT_MAX;
                while( k>0 ){
                    acc += nums[k-1];
                    maxi = max( dp[k-1][i-1] , acc );
                    maxi_min = min(maxi, maxi_min);
                    --k;
                }
                dp[j][i] = maxi_min; 
            }
        }
        return dp[n][m];
    }
};

// 贪心+二分
# define ll long long
class Solution2 {
public:
    int splitArray(vector<int>& nums, int m) {
        ll sum=0;
        for ( auto e:nums )
            sum += e;
        ll l=0,r=sum, mid;
        while( l<=r ){
            mid = (l+r)/2;
            if ( helper(nums,mid,m)==false ) 
                l = mid +1;
            else r = mid -1;
        } 
        return l;
    }
    
    bool helper( vector<int> & nums, ll n, int m ){
        ll cnt=0, acc=0;
        for ( auto e:nums ){
            if ( e>n ) return false;
            if ( acc+e<=n ) acc += e;
            else{
                ++cnt; 
                acc = e;
            }
        }
        return cnt+1<=m;
    }
};
