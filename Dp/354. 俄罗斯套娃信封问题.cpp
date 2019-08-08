/*
    问题描述:
        就是矩阵嵌套。
        大的在下，小的在上，
        下面的长和宽严格大于上面的
    
    问题分析：
        方法一:
            先排序
            dp[i]表示前i个矩阵中的最大嵌套数,
            for i from 1 to n :
                for j from 1 to i:
                    if ( matrix[i] 严格大于 matrix[j] )
                        dp[i] = max( dp[i], dp[j] + 1 )

        方法二:
            先排序，使得宽递增，然后高递减
            之所以让高递减，是因为这样就能满足下面的条件： 
                在所有宽相同的矩阵中，不存在递增的高
            
            于是乎，这样排完序后，所有矩阵中，高的最长递增序列，就是最大嵌套数
            ( 排序保证了宽是非递减的， 递增保证了宽不相同，高严格递增，
            最终就满足了宽递增，高递增... 实在是妙 )

            最长递增子序列的求法就是 dp[i]是长为i的递增子序列的最大元素(就是最后一个元素)
            所以dp[1~i]都是递增有序的，
            对于nums[i]，去dp[1~i]中找到最后一个比nums[i]小的dp，设其为dp[t]， 
            dp[t]<nums[i] , dp[t+1]>=nums[i]
            这个时候，如果t+1>=len，那就给长度+1, dp[len++] = nums[i]
            如果t+1<len 那就更新dp[t+1] dp[t+1] = min( dp[t+1], nums[i] )

            因为dp是有序的，所以可以二分一下找dp[t]
 */

class Solution1 {
public:
    //O(N^2)
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        int n = envelopes.size();
        if ( n==0 ) return 0;
        int res=1;
        sort(envelopes.begin(),envelopes.end(), cmp); 
        vector<int> dp(n, 1);
        for ( int i=0; i<n; ++i ){
            for ( int j=0; j<i; ++j ){
                if ( envelopes[i][0]>envelopes[j][0] && envelopes[i][1]>envelopes[j][1] )
                    dp[i] = max(dp[i], dp[j]+1);
            }
            res = max(dp[i],res);
        }
        return res;
        
    }
    
    static bool cmp( vector<int> & a, vector<int> & b ){
        if ( a[0]!=b[0] )
            return a[0]<b[0];
        return a[1]<b[1];
    }
    
};

//O(NlogN)
class Solution2 {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        int l,r,mid,len=1, n = envelopes.size();
        sort( envelopes.begin(), envelopes.end(), cmp );
        vector<int> dp(n+1,0);
        for ( int i=0; i<n; ++i ){
            l=1; r=len;
            while( l<=r ){
                int mid = (l+r)/2;
                // 找最后一个小于..[i][1]的dp
                if ( envelopes[i][1]>dp[mid] ) l=mid+1;
                else r = mid-1;
            }
            // 这里的l就是最后一个小于..[i][1]的dp 的后一个元素
            if ( l>=len ) dp[len++] = envelopes[i][1];
            else dp[l] = min( dp[l], envelopes[i][1] ); 
        }
        return len-1;
    }
    static bool cmp( vector<int> & a, vector<int> & b ){
        if ( a[0]!=b[0] )
            return a[0]<b[0];
        return a[1]>b[1];
    }
};



