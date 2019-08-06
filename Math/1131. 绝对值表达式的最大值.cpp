/*
    问题描述:
        给你两个长度相等的整数数组，返回下面表达式的最大值：
        |arr1[i] - arr1[j]| + |arr2[i] - arr2[j]| + |i - j|
        其中下标 i，j 满足 0 <= i, j < arr1.length。

        示例 1：
        输入：arr1 = [1,2,3,4], arr2 = [-1,4,5,6]
        输出：13

        示例 2：
        输入：arr1 = [1,-2,-5,0,10], arr2 = [0,-2,-1,-7,-4]
        输出：20

    问题分析:
        本题的两个点:
            1. 遇到绝对值，拆绝对值，分情况讨论
            2. 对偶情况，对于i和j的变量名交换后依然跟原来一样的这种情况下，
            (与变量无关)，我们可以大胆的假设i>j, 然后脱绝对值
        
        假设i>j之后，可以把情况变成下面四个情况
        1. |a[i] - a[j]| + |b[i] - b[j]| + i - j = (a[i] + b[i] + i) - (a[j] + b[j] + j)  (a[i] >= a[j], b[i] >= b[j])
        2. |a[i] - a[j]| + |b[i] - b[j]| + i - j = (a[i] - b[i] + i) - (a[j] - b[j] + j)  (a[i] >= a[j], b[i] < b[j])
        3. |a[i] - a[j]| + |b[i] - b[j]| + i - j = (-a[i] + b[i] + i) - (-a[j] + b[j] + j) (a[i] < a[j], b[i] >= b[j])
        4. |a[i] - a[j]| + |b[i] - b[j]| + i - j = (-a[i] - b[i] + i) - (-a[j] - b[j] + j) (a[i] < a[j], b[i] < b[j])

        然后遍历数组，求对应的四个变量：
        ppp  =  (a[i] + b[i] + i)
        pmp  =  (a[i] - b[i] + i)
        mpp  =  (-a[i] + b[i] + i)
        mmp  =  (-a[i] - b[i] + i)
        的最大值和最小值，然后相减就行了。
        
        ps:
            ppp就是三个数的符号，正正正，plusplusplus,ppp 其他同理 m=minus
 */

 class Solution {
public:
    int maxAbsValExpr(vector<int>& a, vector<int>& b) {
        // mpp = minus plus plus 
        int ppp, pmp, mpp, mmp;
        int max_ppp, max_pmp, max_mpp, max_mmp;
        int min_ppp, min_pmp, min_mpp, min_mmp;
        max_ppp = max_pmp = max_mpp = max_mmp = INT_MIN;
        min_ppp = min_pmp = min_mpp = min_mmp = INT_MAX;
        for ( int i=0; i<a.size(); ++i ){
            ppp = a[i] + b[i] + i;
            pmp = a[i] - b[i] + i;
            mpp = -a[i] + b[i] + i;
            mmp = -a[i] - b[i] + i;
            
            max_ppp = max( max_ppp, ppp );
            max_pmp = max( max_pmp, pmp );
            max_mpp = max( max_mpp, mpp );
            max_mmp = max( max_mmp, mmp );
            
            min_ppp = min( min_ppp, ppp );
            min_pmp = min( min_pmp, pmp );
            min_mpp = min( min_mpp, mpp );
            min_mmp = min( min_mmp, mmp );
        }
        return max( max( max_ppp-min_ppp, max_pmp-min_pmp ), max( max_mpp-min_mpp, max_mmp-min_mmp  )   );
    }
};