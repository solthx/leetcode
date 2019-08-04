/*
    问题描述:
        编写一个程序，通过已填充的空格来解决数独问题。
        一个数独的解法需遵循如下规则：
        数字 1-9 在每一行只能出现一次。
        数字 1-9 在每一列只能出现一次。
        数字 1-9 在每一个以粗实线分隔的 3x3 宫内只能出现一次。
        空白格用 '.' 表示。

        Note:
        给定的数独序列只包含数字 1-9 和字符 '.' 。
        你可以假设给定的数独只有唯一解。
        给定数独永远是 9x9 形式的。

    问题分析:
        了解完#36的一次遍历法后，
        用dfs暴力遍历所有情况。
        为了方便实现，
        rows[i][val]不再表示第i行上val的个数
        而是第i行上还可以取几个val （初始化为1
        cols，boxes同理
 */

 class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        if ( board.size()==0 || board[0].size()==0 ) return ;
        vector<vector<int>> rows(10, vector<int>(10,1));
        vector<vector<int>> cols(10, vector<int>(10,1));
        vector<vector<int>> boxes(10, vector<int>(10,1));
        for ( int i=0; i<board.size(); ++i ){
            for ( int j=0; j<board[0].size(); ++j ){
                if ( board[i][j]=='.' ) continue;
                int val = board[i][j]-'0';
                int b_idx = (i/3)*3 + j/3;
                --rows[i][val];
                --cols[j][val];
                --boxes[b_idx][val];
            }
        }
        dfs( rows, cols, boxes, board );
    }
    
    bool dfs(vector<vector<int>>& rows, vector<vector<int>>& cols, vector<vector<int>>& boxes, vector<vector<char>>& board ){
        int res=true;
        for ( int i=0; i<board.size(); ++i ){
            for ( int j=0; j<board[0].size(); ++j ){
                int b_idx = (i/3)*3 + j/3;
                if ( board[i][j]!='.' ) continue;
                res=false;
                for ( int val=1; val<=9; ++val ){
                    if ( rows[i][val]>0 && cols[j][val]>0 && boxes[b_idx][val]>0 ){
                        board[i][j] = '0'+val;
                        --rows[i][val];
                        --cols[j][val];
                        --boxes[b_idx][val];
                        if ( dfs( rows, cols, boxes, board ) )
                            return true;
                        ++rows[i][val];
                        ++cols[j][val];
                        ++boxes[b_idx][val];
                        board[i][j] = '.';
                    }
                }
                if ( board[i][j]=='.' ) return false;
            }
        }
        return res;
    }
};