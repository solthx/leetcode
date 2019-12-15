/*
    问题描述:
        会员到期了.. 题被锁了.. 简述一下题意.
        给一个数组 和 一个数组k，
        要求返回 长度大于等于K的，且平均值最大的 子数组
        
        note:
            1 <= k <= n <= 10,000.
            Elements of the given array will be in range [-10,000, 10,000].
            The answer with the calculation error less than 10-5 will be accepted.
 
    问题分析:
        一、先来看怎么求最大平均子数组:
            使用二分搜索的方法去找这个最大的平均值.

            二分法的思路就是在满足有序的前提下:
                1. 确定范围
                2. 确定区间的收缩范围.

            就上面这个问题而言, 平均值的可能性从小到大是天然递增的, 满足有序:
                1. 确定范围：
                    平均值最小为 l = min{ nums[..] } (所有元素都是最小值)
                    平均值最大为 r = max{ nums[..] } (所有元素都是最大值)
                    所以，最大子数组的平均值的大小就在 [l,r]里.

                2. 确定区间的收缩范围:
                    对于mid：
                        1. 如果存在比mid更大的平均值，那么就需要到[mid, r]的区间里搜索
                        2. 如果不存在比mid更大的平均值, 那么可能mid就是最大平均值，或者mid大于最大的平均值, 
                        所以这种情况的话，候选者就在[l,mid]区间里.
                        ps：(因为搜索的值是double类型的，所以不用对区间的边界+1或者-1)
                    
                    接下来就是怎么确定 mid 是不是最大平均值..
                
                        如果对于任意子区间, 都有:

                            子区间和 - mid * 子区间长度 < 0
                        
                        那么就可以断定, mid>=当前最大平均值.

                        上面的公式也可以写成:
                        
                        t∈[lo,hi]
                            sum{ nums[t] - mid } < 0
                    
                    所以，我们凑出一个 nums[t]-mid 的一个sums前缀数组，然后问题就变成了是否存在小于0的区间和.

                    sums[i] 表示 [0,i]的 区间和的差 
                    
                    for i from 0 to n-1 :
                        // mi 记录 [0, i] 的最小区间和
                        mx = max( mx, sums[i]-mini )
                        mi = min( mi, sums[i] )    

                    如果最大区间和依然小于0， 那么就说明每个区间和都小于0！


        二、 知道了怎么求最大平均子数组之后， 然后就是控制k的大小了:
            即把上面的“是否存在大于等于0的区间和”  改成  “是否存在长度大于等于K的，且区间和大于等于0的区间”

            伪代码只要改成，先计算出前k的的区间和，然后mi来记录 [0, i-k] 里最小的子区间和,
            这时, sums[i] - mi 就变成了 长度大于等于k的当前最大的区间和了..
*/

class Solution {
    double [] sums = null;
    public double findMaxAverage(int[] nums, int k) {
        int maxi = -10000, mini = 10000;
        sums = new double[nums.length+1];
        for ( int d:nums ){
            maxi = Math.max(maxi,d);
            mini = Math.min( mini,d );
        }
        double l = mini, r = maxi, mid;
        while( r-l>1e-5 ){
            mid = (l+r)/2;
            if ( hasLarger( nums, mid,k ) ) // 存在比当前mid值更大的区间和，
                l = mid;
            else r = mid;
        }
        return l;
    }

    private boolean hasLarger( int [] nums,  double t,int k ){
        sums[0] = 0.0;
        for ( int i=1; i<=nums.length; ++i )
            sums[i] = sums[i-1]+nums[i-1]-t;
        double mini = 0; 
        for ( int i=k; i<=nums.length; ++i ){
            if ( sums[i] - mini >= 1e-7 )
                return true;
            mini = Math.min( mini, sums[i-k+1]); 
        }
        return false;
    }
}