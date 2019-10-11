/*
    问题描述：
        给定整数数组 A，每次 move 操作将会选择任意 A[i]，并将其递增 1。

        返回使 A 中的每个值都是唯一的最少操作次数。

        示例 1:

        输入：[1,2,2]
        输出：1
        解释：经过一次 move 操作，数组将变为 [1, 2, 3]。
        示例 2:

        输入：[3,2,1,2,1,7]
        输出：6
        解释：经过 6 次 move 操作，数组将变为 [3, 4, 1, 2, 5, 7]。
        可以看出 5 次或 5 次以下的 move 操作是不能让数组的每个值唯一的。
        提示：

        0 <= A.length <= 40000
        0 <= A[i] < 40000

    问题分析:
        看了题解才会做...
        
        重点是利用连续这一特性, 

        cnt记录了多余的数字个数，
        sums为增加次数

        先排序
        for i from 1 to n:
            if A[i]==A[i-1] : 
                ++cnt
                sums -= A[i-1]
            else if A[i]>A[i-1]+1:
                # 应该放到区间[A[i-1]+1, A[i]-1]里面
                # give为可以放的个数, 由可以放的个数(A[i]-A[i-1]-1) 和 需要放的个数cnt 决定 
                give = min( cnt, A[i]-A[i-1]-1 )
                sums +=  (A[i-1]+1) + (A[i-1]+2) + .. + (A[i-1]+give)
                # 也可以写成 sums += A[i-1]*give + (1 + 2 + .. + give)
                        sums += A[i-1]*give + ((1+give)*give)/2
                cnt -= give # 这么多已经被加完了
        if cnt>0:
            # 还有剩余的需要加
            sums += A[n-1]*cnt + (cnt*(cnt+1))/2
        return sums

*/

class Solution {
public:
    int minIncrementForUnique(vector<int>& A) {
        sort(A.begin(), A.end());
        int sums = 0;
        int cnt = 0;
        for ( int i=1; i<A.size(); ++i ){
            if ( A[i]==A[i-1] ){
                ++cnt;
                sums-=A[i];
            }else{
                int give = min( cnt, A[i]-A[i-1]-1 );
                sums += (A[i-1]*give)+(give+1)*give/2;
                cnt -= give;
            }
        }
        if ( cnt>0 ){
            int val = A.back();
            sums += cnt*val + (cnt*(cnt+1))/2;
        }
        return sums;
    }
};