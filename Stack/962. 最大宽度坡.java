/*
    问题描述：
        给定一个整数数组 A，坡是元组 (i, j)，其中  i < j 且 A[i] <= A[j]。这样的坡的宽度为 j - i。

        找出 A 中的坡的最大宽度，如果不存在，返回 0 。

        示例 1：

        输入：[6,0,8,2,1,5]
        输出：4
        解释：
        最大宽度的坡为 (i, j) = (1, 5): A[1] = 0 且 A[5] = 5.
        示例 2：

        输入：[9,8,1,0,1,9,4,0,4,1]
        输出：7
        解释：
        最大宽度的坡为 (i, j) = (2, 9): A[2] = 1 且 A[9] = 1.
         

        提示：

        2 <= A.length <= 50000
        0 <= A[i] <= 50000
         
    问题分析:
        方法一:
            单调栈的思想。。 维护一个单调递减序列：
                1. 如果第i个位置比序列的最小元素还小，就加入序列
                2. 如果第i个位置上的元素不是最小元素，那么递减序列里一定存在一个元素小于等于当前元素，用二分查找的方法来找到比当前元素小的最大元素。然后更新res
        
        方法二:
            对方法一的改进， 有点像贪心的味道了， 以第一个元素为起始的递减序列， 一定是最靠近左边的一个递减序列， 而最大宽度的两个元素构成，一定是 ：
            一个元素来自最靠近左边的递减序列， 一个元素来自最靠近右边的递增序列， 因此，先扫描一遍，得到一个递减栈序列，然后从后往前进行扫描，和栈顶元素进行比较，并更新res
*/

class Solution {
    public int maxWidthRamp(int[] A) {
        // 二分 NlogN 
        int n = A.length;
        // st[i][1]保存坐标， st[i][0]保存值
        // 其实可以直接保存坐标来得到值的。。都一样的。。
        int [][] st = new int[n][2];
        int len = 0, res=0;
        for ( int i=0; i<n; ++i ){
            if ( len==0 || A[i]<st[len-1][0] ){
                st[len][0] = A[i];
                st[len++][1] = i; 
            }else{
                int l = 0, r = len-1, mid;
                while( l<=r ){
                    mid = l + (r-l)/2;
                    if ( st[mid][0]>A[i] ) l = mid+1;
                    else if ( st[mid][0]<A[i] ) r = mid-1;
                    else{
                        l = mid;
                        break;
                    }
                }
                if ( l>=0 && st[l][0]<=A[i] ){
                    res = Math.max( res, i-st[l][1] );
                }
            }
        }
        return res;
    }
}

class Solution2 {
    public int maxWidthRamp(int[] A) {
        // 方法二: 贪心 O(N)
        Deque<Integer> st = new ArrayDeque<>();
        int res=0, top = -1, n=A.length;
        for ( int i=0; i<n; ++i )
            if ( st.size()==0 || A[st.getLast()]>A[i] )
                st.offerLast(i);
        for ( int i=n-1; i>=0; --i ){
            while( st.size()>0 && A[st.getLast()] <= A[i] )
                res = Math.max(res, i-st.pollLast());
        }
        return res;
    }
}