/*
    问题描述:
        在由若干 0 和 1  组成的数组 A 中，有多少个和为 S 的非空子数组。

        示例：

        输入：A = [1,0,1,0,1], S = 2
        输出：4
        解释：
        如下面黑体所示，有 4 个满足题目要求的子数组：
        [1,0,1,0,1]
        [1,0,1,0,1]
        [1,0,1,0,1]
        [1,0,1,0,1]
        

        提示：

        A.length <= 30000
        0 <= S <= A.length
        A[i] 为 0 或 1

    问题分析:
        方法一:
            比较蠢的滑动窗口
            对于[0,0,1,0,1,0,0]
            上面这种，如果找和为2的情况的话，
            我们可以先找最小区间，即[1,0,1]
            然后得到左边和右边的0的个数，假设分别为x和y
            然后，(x+1)*(y+1) 就是当前这个最小区间所能得到的所有和为2的个数..

            利用上面这个思想，我们可以用滑动窗口来得到每一个这样的"最小区间"，
            然后通过遍历0的方法来计算出这个区间能提供的合法区间个数。。
            
            对于S=0的情况，需要特判。。 （就因为这个才显得比较蠢

        方法二: 
            前缀和 + HashMap(存个数)
            
            一个很好想到的方法就是用Hashmap来做。。mp[x]保存首个前缀和为x的个数...
            在位置i上，和为sums, 那么以位置i为结尾的子数组和为S的个数 就等于 前缀和为 sums-S 的个数..
           
        方法三:
            三指针， 即维护了两个滑动窗口, 分为别[lo, r] 和 [hi, r]，
            对应维护的两个区间和: lo_sum 和 hi_sum.

            lo是首个满足区间条件的左边界， hi是首个不满足区间条件的左边界。.
            
            在本题中，[lo,r]的和为S， 且任何x<lo, 都不存在 sum{x,r}==S
                    [hi,r]的和为S+1，且任何y>=hi，都有 sums{y,r}<S
            所以， hi-lo 就是 所有以s[r]为右边界的区间和为S的区间个数..
*/

class Solution1 {
public:
    int numSubarraysWithSum(vector<int>& A, int S) {
        if ( !S ){
            // 特判
            int res=0,len=0,pre=0,i=0;
            while(i<A.size()){
                while( i<A.size() && A[i]!=0 ) ++i;
                pre=i;
                while( i<A.size() && A[i]==0 ) ++i;
                len = i-pre; 
                res += (len*(len+1))/2;
            }
            return res;
        }
        int l=0, sums=0,res=0;
        while( l<A.size() && A[l]==0 ) ++l;
        for ( int r=l; r<A.size(); ++r ){
            sums += A[r];
            while( l<=r && sums>S )
                sums -= A[l++];
            if ( sums==S ){
                int lo = l-1, hi = r+1;
                while( lo>=0 && A[lo]==0 ) --lo;
                while( hi<A.size() && A[hi]==0) ++hi;
                res+=(l-lo)*(hi-r);
                
                ++l;
                while( l<A.size() && A[l]==0 ) ++l;
                r = hi-1;
                --sums;
            }
        }
        return res;
    }
};

class Solution2 {
public:
    int numSubarraysWithSum(vector<int>& A, int S) {
        unordered_map<int,int> mp;
        int res=0, sums=0;
        mp[0] = 1;
        for ( int i=0; i<A.size(); ++i ){
            sums += A[i];
            res += mp[sums-S];
            ++mp[sums];
        }
        return res;
    }
};



class Solution3 {
public:
    int numSubarraysWithSum(vector<int>& A, int S) {
        int lo=0,res=0, hi=0;
        int lo_sums=0, hi_sums=0;
        for ( int r=0; r<A.size(); ++r ){
            lo_sums += A[r];
            hi_sums += A[r];
            while( lo<=r && lo_sums>S )
                lo_sums -= A[lo++];
            while( hi<=r && hi_sums>=S )
                hi_sums -= A[hi++];
            res+=(hi-lo);
        }
        return res;
    }
};