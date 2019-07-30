/*
    问题描述：
        给定一个 m x n 的矩阵，如果一个元素为 0，则将其所在行和列的所有元素都设为 0。请使用原地算法。
        示例 1:
        输入: 
        [
          [1,1,1],
          [1,0,1],
          [1,1,1]
        ]
        输出: 
        [
          [1,0,1],
          [0,0,0],
          [1,0,1]
        ]

        示例 2:
        输入: 
        [
          [0,1,2,0],
          [3,4,5,2],
          [1,3,1,5]
        ]
        输出: 
        [
          [0,0,0,0],
          [0,4,5,0],
          [0,3,1,0]
        ]

        空间复杂度要求O(1)

    问题分析：
        常数级的空间复杂度的方法没想出来，
        看了题解知道的方法。。
        即：
            遍历矩阵，当发现0的时候，把该位置(x,y)的(x,0)和(0,y)
            这两个位置给置0， 然后重新遍历第一行第一列，
            把含第一行上有0的那一列全置0， 对第一列同理。
            然后再单独处理一下第一行和第一列的情况，就行了。
 */

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        if ( matrix.size()<=0 ) return ;
        bool rows=false, cols=false;
        for ( int i=0; i<matrix.size(); ++i )
            for ( int j=0; j<matrix[0].size(); ++j )
                if ( matrix[i][j]==0 ){
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                    if ( i==0 ) rows=true;
                    if ( j==0 ) cols=true;
                }
        for ( int i=1; i<matrix.size(); ++i )
            if ( matrix[i][0]==0 ){
                for (int j=1; j<matrix[0].size(); ++j ){
                    matrix[i][j] = 0;
                }
            }
        
        for ( int i=1; i<matrix[0].size(); ++i )
            if ( matrix[0][i]==0 ){
                for ( int j=1; j<matrix.size(); ++j )
                    matrix[j][i] = 0;
            }
        // 第一列需要全部置0
        if ( cols )
            for ( int i=0; i<matrix.size(); ++i )
                matrix[i][0] = 0;
        // 第一行需要全部置0
        if ( rows )
            for ( int i=0; i<matrix[0].size(); ++i )
                matrix[0][i] = 0;
        return;
    }
};