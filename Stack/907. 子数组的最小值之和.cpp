/*
    问题描述:
        给定一个整数数组 A，找到 min(B) 的总和，其中 B 的范围为 A 的每个（连续）子数组。
        由于答案可能很大，因此返回答案模 10^9 + 7。

        示例：

        输入：[3,1,2,4]
        输出：17
        解释：
        子数组为 [3]，[1]，[2]，[4]，[3,1]，[1,2]，[2,4]，[3,1,2]，[1,2,4]，[3,1,2,4]。 
        最小值为 3，1，2，4，1，1，2，1，1，1，和为 17。
         
        提示：

        1 <= A <= 30000
        1 <= A[i] <= 30000

    问题分析:
        返回的结果是: Sum{ A[i]为最小元素的区间个数 * A[i] }

        对于元素A[i], 找到在左区间里首个比A[i]小的元素A[l], 找到在右区间里比A[i]小的元素A[r]，
        此时，A[i]在区间(l,r)里就是最小值，
        列举几种情况以后可以发现， 在(l,r)区间内的所有子区间中，包含A[i]元素的子区间的个数是( i-l )*( r-i )
        
        所以，问题就变成:
            对与A[i]，求其左边首个比A[i]小的元素，和右边首个比A[i]小的元素。
            为了方便处理边界情况，我们可以在原数组的最左和最右分别加上INT_MIN, 这样就不用单独处理边界了
        
        而求左方或右方的首个最大最小元素的方法，就是用单调栈来做了。
*/

class Solution {
public:
    int sumSubarrayMins(vector<int>& A) {
        // left计算左边首个比当前元素大的位置
        // right计算右边首个比当前元素大的位置
        A.insert( A.begin(), INT_MIN );
        A.push_back(INT_MIN);
        int n = A.size();
        stack<int> s;
        // 左方首个lower元素的位置
        vector<int> l_lo( n+1, -1 );
        // 右方首个lower元素的位置
        vector<int> r_lo(n+1, -1 );
        
        for ( int i=0; i<n; ){
            if ( s.empty() || A[s.top()]<=A[i] ){
                s.push(i);
                ++i;
            }else{
                r_lo[s.top()] = i;
                s.pop();
            }
        }
        
        while( !s.empty() ) s.pop();
        
        for ( int i=n-1; i>=0;  ){
            if ( s.empty() || A[s.top()]<A[i] ){
                s.push(i);
                --i;
            }else{
                l_lo[s.top()] = i;
                s.pop();
            }
        }

        // 遍历每个元素 ， 当前元素为最小元素的区间个数* 当前元素大小     
        int li, ri, rc,lc,res=0;
        for ( int i=1; i<n-1; ++i ){
            
            lc = 0; rc=0;
            
            if ( l_lo[i]==-1 ) lc=1;
            else lc =  i - l_lo[i];
            
            if ( r_lo[i]==-1 ) rc = 1;
            else rc = r_lo[i] - i ;
            res = (res + lc*rc*A[i]) % 1000000007;
        }
       
        
        return res;
    }
};