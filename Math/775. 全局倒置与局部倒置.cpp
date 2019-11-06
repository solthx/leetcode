/*
    问题描述:
        数组 A 是 [0, 1, ..., N - 1] 的一种排列，N 是数组 A 的长度。全局倒置指的是 i,j 满足 0 <= i < j < N 并且 A[i] > A[j] ，局部倒置指的是 i 满足 0 <= i < N 并且 A[i] > A[i+1] 。
        当数组 A 中全局倒置的数量等于局部倒置的数量时，返回 true 。

        示例 1:

        输入: A = [1,0,2]
        输出: true
        解释: 有 1 个全局倒置，和 1 个局部倒置。
        示例 2:

        输入: A = [1,2,0]
        输出: false
        解释: 有 2 个全局倒置，和 1 个局部倒置。
        注意:

        A 是 [0, 1, ..., A.length - 1] 的一种排列
        A 的长度在 [1, 5000]之间
        这个问题的时间限制已经减少了。
    
    问题分析:
        方法一：
            读懂题目以后，其实不难。。 
            
            其实就是找是否存在位置距离大于1的逆序对。。(因为位置差等于1的逆序对既是局部倒置，又是全局倒置)

            所以，开一个数组nums，记录当前位置右边的最小值，一旦发现A[i]>nums[i+2]，就直接返回false

        方法二:
            看了一眼grandyan大神的解法，发现了另一种比较好的题解。。
            因为，本题还说了数组 A 是 [0, 1, ..., N - 1] 的一种排列,
            因此， 可以和下标对应起来，

            A[i]相等于是第i+1小，
            因此，只有满足在i-1, i, i+1, 这三个位置， 才有可能不是距离大于1的逆序对中的一个数。。。

            因此， 只要发现A[i]和i的差的绝对值 大于了1， 那么就一定存在一个数和A[i]组成距离大于1的逆序对，这时候直接返回false就行了。。
*/

class Solution1 {
public:
    bool isIdealPermutation(vector<int>& A) {
        int n = A.size(); 
        if ( A.size()<=1 ) return true;
        vector<int> nums( n, INT_MAX );
        nums[n-1] = A[n-1];
        for ( int i=n-2; i>=0; --i )
            nums[i] = min( A[i], nums[i+1] );
        for ( int i=0; i<n-2; ++i )
            if ( A[i]>nums[i+2] )
                return false;
        return true;
    }
};

class Solution2 {
public:
    bool isIdealPermutation(vector<int>& A) {
        for ( int i=0; i<A.size(); ++i )
            if ( abs(A[i]-i)>1 ) return false;
        return true;
    }
};