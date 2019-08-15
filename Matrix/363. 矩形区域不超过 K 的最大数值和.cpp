/*
    问题描述：
        给定一个非空二维矩阵 matrix 和一个整数 k，找到这个矩阵内部不大于 k 的最大矩形和。
        示例:
        输入: matrix = [[1,0,1],[0,-2,3]], k = 2
        输出: 2 
        解释: 矩形区域 [[0, 1], [-2, 3]] 的数值和是 2，且 2 是不超过 k 的最大数字（k = 2）。
        说明：

        矩阵内的矩形区域面积必须大于 0。
        如果行数远大于列数，你将如何解答呢？

    问题分析:
        上次做这题的时候，用暴力做过去以后就过去了。。
        这次再补充一个 O(N^3*logN)的解法。。。
        
        这个解法的巧妙之处在于他的 降维操作， 把二维的问题转换成了一维的问题。。
    
        就是把对于 每一列的[L,R]区间和给投影出来成一个一位数组。
        例如:
            LR          row
            1  0  1      1
            0 -5  7      0    ➡➡➡    最大区间和为[1,0,2] = 3
            2  4  -3     2
            
                ⬇⬇⬇

            L  R        row
            1  0  1      1
            0 -5  7      -5   ➡➡➡    最大区间和为[6] = 6
            2  4  -3     6
            
                ⬇⬇⬇

            L     R     row
            1  0  1      2
            0 -5  7      2    ➡➡➡    最大区间和为[2,2,3] = 7
            2  4  -3     3
        
        当L==a, R==b的时候， 我们得到了一个row， 然后 row中的区间和的含义: 就是以L和R为左右边界，row区间范围为上下边界的一个矩阵和
        所以只要求出了row中所有区间和不超过K的最大数值和， 就得到了：以L和R为左右边界，区间和不超过K的最大数值和 了。
        
        然后我们只要遍历所有的L，R的组合， 最终就能得到这个矩形区域中不超过K的最大数值和
        遍历LR的复杂度是 O(N^2) , N是col数， 在row中找区间和不超过K的最大数值和 的复杂度为O(M*logM) , 因此总复杂度为O(N^2*M*logM)

        而怎么在row中找区间和不超过K的最大值个数，类似 #560. 和为K的子数组 
        核心思想就是用map来记录前缀和,
        我们的目标是找  preSum[i] - preSum[j] <= k 
            也就是去找 preSum[j] >= preSum[i] - k。 i>j
            所以，遍历得到preSum[i]的时候，我们就去找我们想要的preSum[j]，
            也就是在有序的情况下，首个大于等于preSum[i]-k的值
            这里可以用红黑树set 的lower_bound( val ) : 返回首个大于等于val的元素的位置， set内部是递增有序的

        这里还要注意的是，set初始化的时候，要放一个0进去，

        因为如果preSum[i]==k, 那么直接是前i个元素的和就是k了，
        但preSum[i]-k==0, 如果set里没有0的话，就会找不到
        因此，set里初始化放个0，就是加上了“ 前i个元素的和直接就等于k ”这一情况

        知道这些以后，代码就好写了
*/

class Solution {
public:
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
        int n = matrix.size(), m=matrix[0].size(), res=INT_MIN;      
        for ( int L=0; L<m; ++L ){
            vector<int> row( n, 0 );
            for ( int R=L; R<m; ++R ){
                for ( int i=0; i<n; ++i ){
                    row[i] += matrix[i][R];
                }
                set<int> st{{0}};
                vector<int> predix( n+1, 0);
                for ( int i=1; i<=n; ++i ){
                    predix[i] = predix[i-1] + row[i-1];
                    set<int>::iterator it = st.lower_bound( predix[i]-k );
                    if ( it!=st.end() )
                        res = max( res, predix[i] - *it );
                    st.insert(predix[i]);
                }
            }    
        }
        return res;
    }
};