/*
    问题描述:
        给定一个元素都是正整数的数组A ，正整数 L 以及 R (L <= R)。
        求连续、非空且其中最大元素满足大于等于L 小于等于R的子数组个数。

        例如 :
        输入: 
        A = [2, 1, 4, 3]
        L = 2
        R = 3
        输出: 3
        解释: 满足条件的子数组: [2], [2, 1], [3].
        注意:

        L, R  和 A[i] 都是整数，范围在 [0, 10^9]。
        数组 A 的长度范围在[1, 50000]。


    问题分析：
        题目看错了两次 T_T..

        看到子数组，就可以考虑滑动窗口！ 因为说的是最大值，所以，滑动窗口扫的是 “不存在大于R的元素的区间",
        然后计算出该区间内能得到的所有子区间， 再减去该区间内  "由小于L的元素组成的所有的子区间" 的情况，就是满足最大元素在[L,R]的情况个数了..
        
        相当于遍历了数组2次，因此复杂度为O(N)..

        看了题解以后，发现代码可以更简洁一些: 
            https://leetcode-cn.com/problems/number-of-subarrays-with-bounded-maximum/solution/qu-jian-zi-shu-zu-ge-shu-by-leetcode/
        
        其实思想都是一样的。。 时空复杂度也一样的。。 遍历次数也是一样的..
*/


class Solution1 {
public:
    // 滑动窗口
    int numSubarrayBoundedMax(vector<int>& A, int L, int R) {
        int res= 0, l = 0, r=0, maxi=A[0];
        while( r<A.size() ){
            while( r<A.size() && A[r]>R ) ++r;
            if ( r>=A.size() ) break;
            l = r;
            ++r;  // r指向首个不合法位置
            maxi = A[l];
            if ( r<A.size() ){ 
                // 存在下一个元素
                if (  maxi<=R )  // 递增情况
                    while( r<A.size() ){
                        maxi = max(maxi,A[r]);
                        if ( maxi<=R )
                            ++r;
                        else break;
                    }
                else if ( maxi<=R )  // 递增情况
                    while( r<A.size()  ){
                        maxi = max(maxi,A[r]);
                        if ( maxi<=R )
                            ++r;
                        else break;
                    }
            }
            //  计算 "由小于L的元素组成的所有的子区间" 的情况
            for ( int t = l; t<r; ++t ){
                if ( A[t]<L ){
                    ++tmp;
                }else{
                    if ( tmp>0 ) res -= ( tmp*(tmp+1)/2 );
                    tmp=0;
                }
            }
            if ( tmp>0 ) res -= ( tmp*(tmp+1)/2 );
            res += ( len*(len+1)/2 );
        }
        return res;
    }
};

// 化简后的代码
class Solution2 {
public:
    int numSubarrayBoundedMax(vector<int>& A, int L, int R) {
        return count(A, R) - count(A, L-1);
    }
    int count(vector<int>&A, int b){
        int cur=0, res = 0;
        for ( int c:A ){
            cur = c<=b?cur+1:0;
            res += cur;
        }
        return res;
    }
};