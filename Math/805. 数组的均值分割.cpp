/*
    问题描述:
        给定的整数数组 A ，我们要将 A数组 中的每个元素移动到 B数组 或者 C数组中。（B数组和C数组在开始的时候都为空）
        返回true ，当且仅当在我们的完成这样的移动后，可使得B数组的平均值和C数组的平均值相等，并且B数组和C数组都不为空。

        示例:
            输入: 
            [1,2,3,4,5,6,7,8]
            输出: true
            解释: 我们可以将数组分割为 [1,4,5,8] 和 [2,3,6,7], 他们的平均值都是4.5。
        
        注意:
            A 数组的长度范围为 [1, 30].
            A[i] 的数据范围为 [0, 10000].

    问题分析:
        本题看起来极像要用dp来做（尽管可以，但速度有些慢

        本题要求的是:
            是否能把A数组分成两波数组，使得这两波数组的平均值一样。

        本题的关键点有两个:
            1. 先化简, 设B数组有b个元素，C数组有c个元素:
                sum{B}/b = sum{C}/c = sum{A}/n
            =>  sum{B}/b*n = sum{A}
            又因为数组的和为整数，故有:
                sum{B}*n % b == 0

            2. 变量无关性，因为B和C无关，所以用到对称性。
            假设B数组包含了m个元素， C数组包含了n-m个元素，
            那么B和C一定有一个数组包含的元素是小于n/2个的。

            所以，在穷举B数组包含了多少个元素的时候，不再是[1,n]，而是[1,n/2]
            这个时候，穷举的复杂度就变成了变得可以接受了。

        实现:
            1. 穷举B数组可能的个数，看是否存在一个长度，使得满足上面的条件。
            2. 在穷举的时候，先用 sum{B}*n % b == 0 来检查 这个长度是否有存在的可能。

*/
class Solution {
public:
    int sums=0;
    bool splitArraySameAverage(vector<int>& A) {
        sort( A.begin(), A.end() ); // 为了加速，排个序； 其实不排序也没事
        sums = accumulate(A.begin(), A.end(), 0);
        int n = A.size()/2, m=A.size();
        for ( int len=1; len<=n; ++len ){
            if ( (sums*len) %m==0 && dfs( A, 0, len, sums * len / m ) )
                return true;
        }
        return false;
    }
    
    // 一个比较好的思想就是靠减来完成； 而不要用加，不然还要开额外的变量
    bool dfs( vector<int>& A, int idx, int len, int target ){
        if ( len==0 ) return target==0 ;
        if ( target<0 ) return false;
        if( len<0 ) return false;
        for ( int i=idx; i<A.size(); ++i ){
            if ( i>idx && A[i]==A[i-1] ) continue;
            if ( dfs( A, i+1, len-1, target-A[i] ) ) return true;
        }
        return false;
    }
};