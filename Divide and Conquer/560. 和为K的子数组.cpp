/*
    问题描述:
        给定一个整数数组和一个整数 k，你需要找到该数组中和为 k 的连续的子数组的个数。
        
        示例 1 :
        输入:nums = [1,1,1], k = 2
        输出: 2 , [1,1] 与 [1,1] 为两种不同的情况。
        说明 :
        数组的长度为 [1, 20,000]。
        数组中元素的范围是 [-1000, 1000] ，且整数 k 的范围是 [-1e7, 1e7]。

    问题分析:
        方法一:
            看到只是对区间和加条件，那么分治+归并排序肯定行得通(就是写起来要小心边界)
            helper( 0, n, sums, k, sav);  返回区间(0,n]内 和为k的区间和个数
            一般这种对区间和限制的题，区间最好都取(0,n] ，因为sum[j]-sum[i] 表示的区间是(i,j]

            本题的一个细节地方就是，sums并不是严格递增的，
            因此在处理中间情况的时候要过滤前后元素相等的情况。
            如果当前元素和前一个元素相同，那么对
            “当前符合条件的区间数” 直接加上一个元素所增加的增量。

        方法二:
            其实区间和的另一个处理方法是哈希表。。(类似的还有#)
            例如:
                区间和等于k的 个数 =>
                sums[i]-sum[j]==k 的个数 =>
                sum[i]-k == sum[j] 的个数 =>
                对于sum[i]来说，看存在多少个sum[j]满足
                sums[j]==sum[i]-k  ， 就是看sum[i]-k的个数

                区间和>=k的个数 =>
                sum[i]-sum[j]>=k 的个数 =>
                对于sum[i]来说，看存在多少个sum[j]满足
                sums[j]<=sum[i]-k  ， 就是看<=sum[i]-k的个数


            用哈希表来记录个数:
                < sums[i] , cnt >
            
            当前是sums[i]，对于sums[i]来说，
            满足sums[i]-sums[j]==k的个数，
            就是究竟有多少个 sums[j]使得sums[i]-sums[j]==k成立，
            也就是sum[j]的个数， (sum[j]==sums[i]-k)
            也就是sum[i]-k的个数
            即 map[sum[i]-k]

            最后因为第i个位置只用 sums[i]，所以不用再建前缀数组，
            直接一个变量滚动就行了
                unordered_map<int,int> mp;
                mp[0] = 1;  // < sums[i], cnt >
                int cur=0, idx=1, res=0;
                for ( int i=0; i<nums.size(); ++i ){
                    cur += nums[i];
                    res += mp[cur-k];
                    mp[cur]++;
                }
                return res;

 */

class Solution1 {
public:
    int subarraySum(vector<int>& nums, int k) {
        //分治解法
        int n = nums.size();
        vector<int> sums(n+1,0);
        vector<int> sav(n+1,0);        
        for ( int i=1; i<=n; ++i )
            sums[i] = sums[i-1] + nums[i-1];
        return helper( 0, n, sums, k, sav); // 返回区间(0,n]内 和为k的区间和个数
    }
    
    int helper( int l, int r, vector<int> & sums, int k, vector<int> & sav ){
        if ( l<0 || r>=sums.size() || l>=r ) return 0;

        int mid = (l+r)/2;
        int mid_cnt=0;
        // (0,mid] 和 (mid+1,r]
        int lr_cnt = helper( l, mid, sums , k, sav) + helper( mid+1, r, sums, k,sav );
        
        int start=l;
        int tmp=0;
        for ( int end=mid+1; end<=r; ++end ){
            // 过滤相同情况，如果当前元素和前一个元素相同，那么直接加上一次的增量
            if ( end>mid+1 && sums[end]==sums[end-1] ){
                mid_cnt+=tmp;
                continue;
            }
            tmp=0;
            while( start<=mid && sums[end]-sums[start]>k ) start++;
            while ( start<=mid && sums[end]-sums[start]==k ){
                //cout<<start<<" "<<end<<endl;
                start++;
                tmp++;
            }
            mid_cnt+=tmp;
        }
        //inplace_merge( sums.begin()+l, sums.begin()+mid+1, sums.begin()+r+1 );
        int idx=0, lo=l, hi=mid+1;
        while( lo<=mid && hi<=r ){
            if ( sums[lo]<sums[hi] )
                sav[idx++] = sums[lo++];
            else sav[idx++] = sums[hi++];
        }
        while( lo<=mid )
            sav[idx++] = sums[lo++];
        while( hi<=r )
            sav[idx++] = sums[hi++];
        for ( int t=0; t<idx; ++t )
            sums[l+t] = sav[t];
        
        return mid_cnt+lr_cnt;
    }


class Solution2 {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int,int> mp;
        mp[0] = 1;  // < sums[i], cnt >
        int cur=0, idx=1, res=0;
        for ( int i=0; i<nums.size(); ++i ){
            cur += nums[i];
            res += mp[cur-k];
            mp[cur]++;
        }
        return res;
    }
};