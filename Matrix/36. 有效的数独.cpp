/*
    问题描述:
        判断一个 9x9 的数独是否有效。只需要根据以下规则，验证已经填入的数字是否有效即可。
        数字 1-9 在每一行只能出现一次。
        数字 1-9 在每一列只能出现一次。
        数字 1-9 在每一个以粗实线分隔的 3x3 宫内只能出现一次。
        数独部分空格内已填入了数字，空白格用 '.' 表示。

    问题分析:
        遍历三次矩阵，分别判断，很简单。。
        这里说下官方题解的一次遍历的解决方法。

        rows[i][val] 表示第i行上， 值为val的个数
        cols[j][val] 表示第j列上,  值为val的个数
        boxes[k][val] 表示第k个box中，值为val的个数
    
        唯一要提的就是如何根据坐标(i,j)确定k的值
        k = (i/3)*3 +j/3 （除是整除

        知道这个以后，就简单多了。
 */

class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        //一次遍历法
        int rows[10][10]={0};
        int cols[10][10]={0};
        int boxes[10][10]={0};
        for ( int i=0; i<board.size(); ++i )
            for ( int j=0; j<board.size(); ++j ){
                if ( board[i][j]=='.' ) continue;
                int val = board[i][j]-'0';
                int b_idx = (i/3)*3 + j/3;
                if ( ++rows[i][val]>1 ) return false;
                if ( ++cols[j][val]>1 ) return false;
                if ( ++boxes[b_idx][val]>1 ) return false;
            }   
        return true;
    }
};

/*
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        for ( int j=0; j<9; ++j ){
            int cnt[10]={0};
            for ( int i=0; i<9; ++i )
                 if ( board[i][j]>='0' && board[i][j]<='9' && ++cnt[board[i][j]-'0']>1 )
                    return false;
        }
        
        for ( int i=0; i<9; ++i )
            if ( !isValid( board[i] ) ) return false;
        
        
        for ( int i=0; i<9; i+=3 )
            for ( int j=0; j<9; j+=3 )
                if ( !helper( board,i,j ) )
                    return false;
        return true;
    }
    
    bool isValid(vector<char>& v){
        int cnt[10]={0};
        for ( auto e:v ){
            if ( e>='0' && e<='9' && ++cnt[e-'0']>1 )
                return false;
        }
        return true;
    }
    
    bool helper( vector<vector<char>>& board, int i, int j ){
        int cnt[10]={0};
        for ( int y=i; y<i+3; ++y ){
            for ( int x=j; x<j+3; ++x ){
                if ( board[y][x]>='0' && board[y][x]<='9' && ++cnt[board[y][x]-'0']>1 )
                    return false;
            }
        }
        return true;
    }
};

*/