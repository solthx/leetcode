/*
    问题描述：
        给你一个 m x n 的二进制矩阵 mat。

        每一步，你可以选择一个单元格并将它反转（反转表示 0 变 1 ，1 变 0 ）。如果存在和它相邻的单元格，那么这些相邻的单元格也会被反转。（注：相邻的两个单元格共享同一条边。）

        请你返回将矩阵 mat 转化为全零矩阵的最少反转次数，如果无法转化为全零矩阵，请返回 -1 。

        二进制矩阵的每一个格子要么是 0 要么是 1 。

        全零矩阵是所有格子都为 0 的矩阵。

        示例 1：
        
        输入：mat = [[0,0],[0,1]]
        输出：3
        解释：一个可能的解是反转 (1, 0)，然后 (0, 1) ，最后是 (1, 1) 。
        示例 2：

        输入：mat = [[0]]
        输出：0
        解释：给出的矩阵是全零矩阵，所以你不需要改变它。
        示例 3：

        输入：mat = [[1,1,1],[1,0,1],[0,0,0]]
        输出：6
        示例 4：

        输入：mat = [[1,0,0],[1,0,0]]
        输出：-1
        解释：该矩阵无法转变成全零矩阵
         

        提示：

        m == mat.length
        n == mat[0].length
        1 <= m <= 3
        1 <= n <= 3
        mat[i][j] 是 0 或 1 。


    问题分析:
        3*3的matrix通过位运算编码到一个int里来作为状态，
        然后bfs暴力，O(2^9).. 好像没啥难度.. 
*/

class Solution {
public:
    int dir[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
    int n,m;
    int minFlips(vector<vector<int>>& mat) {
        int  res = INT_MAX;
        n = mat.size();
        if ( n ) m = mat[0].size();
        int bit = trans_to_bit( mat );
        if ( bit==0 ) return 0; 
        queue<int> q;
        q.push(bit);
        unordered_set<int> st; // 已经出现的状态说明已经访问过了，就不访问了
        st.insert( bit );
        int step=0;
        while( q.size()>0 ){
            for ( int ts = q.size(); ts>0; --ts ){
                int b = q.front(); q.pop();
                for ( int i=0; i<n; ++i ){
                    for ( int j=0; j<m; ++j ){
                        int nb = helper( b, i, j );
                        if ( st.count(nb)>0 ) continue;
                        if ( nb==0 ) return step+1;
                        st.insert( nb );
                        q.push(nb);
                    }
                }
            }
            ++step;
        }
        return -1;
    }

    int helper( int bit, int i, int j ){
        bit ^= (1<<(to_idx(i,j)));
        for ( int k=0; k<4; ++k ){
            int y = i+dir[k][0];
            int x = j+dir[k][1];
            if ( y>=0 && x>=0 && y<n && x<m )
                bit ^= ( 1<<(to_idx(y,x)) );
        }
        return bit;
    }

    // matrix编码成一个int
    int trans_to_bit( vector<vector<int>>& mat ){
        int bit = 0;
        for ( int i=0; i<mat.size(); ++i )
            for ( int j=0; j<mat[0].size(); ++j ){
                if ( mat[i][j]==1 )
                    bit |= ( 1<<(to_idx(i,j)) );
            }
        return bit;
    }

    // 二维坐标转化一维坐标
    inline int to_idx(int i,int j){
        return i*m+j;
    }


};