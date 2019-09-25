/*
    问题描述：
        给定两个 稀疏矩阵 A 和 B，请你返回 AB。你可以默认 A 的列数等于 B 的行数。

    问题分析:
        矩阵相乘实现比较简单，
        对于稀疏矩阵， 加个判断语句就行，
        for  i from 1 to A的行数:
            for j from 1 to A的列数:
                if  A[i][j]!=0 :   //剪枝
                    for k from 1 to B的列数:
                        if B[j][k] != 0:
                            res[i][k] = A[i][j] * B[j][k];     
*/

class Solution {
public:
    vector<vector<int>> multiply(vector<vector<int>>& A, vector<vector<int>>& B) {
        vector<vector<int>> res( A.size(), vector<int>(B[0].size(),0) ); 
        for ( int h=0; h<A.size(); ++h ){
            for ( int c=0; c<A[0].size(); ++c ){
                if ( A[h][c]!=0 )
                    for ( int i=0; i<B[0].size(); ++i ){
                        if ( B[c][i]!=0 )
                            res[h][i] += (A[h][c]*B[c][i]);
                    }
            }
        }
        return res;
    }
};