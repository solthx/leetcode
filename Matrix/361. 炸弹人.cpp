/*
    问题分析:
        想象一下炸弹人游戏，在你面前有一个二维的网格来表示地图，
        网格中的格子分别被以下三种符号占据：

        'W' 表示一堵墙
        'E' 表示一个敌人
        '0'（数字 0）表示一个空位
        
        请你计算一个炸弹最多能炸多少敌人。
        由于炸弹的威力不足以穿透墙体，炸弹只能炸到同一行和同一列没被墙体挡住的敌人。
        注意：你只能把炸弹放在一个空的格子里
        
        示例:
        输入: [["0","E","0","0"],["E","0","W","E"],["0","E","0","0"]]
        输出: 3 
        解释: 对于如下网格

        0 E 0 0 
        E 0 W E 
        0 E 0 0

        假如在位置 (1,1) 放置炸弹的话，可以炸到 3 个敌人

    问题分析:
        方法一:
            用Dp记录在每一个位置的上下左右方的敌人数，
            然后重新遍历grid来计算
            空间开销有些大
        
        方法二:
            引用于 CSDN用户：Grandyang
                需要一个rowCnt变量，用来记录到下一个墙之前的敌人个数。还需要一个数组colCnt，其中colCnt[j]表示第j列到下一个墙之前的敌人个数。
                算法思路是遍历整个数组grid，对于一个位置grid[i][j]，对于水平方向，如果当前位置是开头一个或者前面一个是墙壁，我们开始从当前位置往后遍历，
                遍历到末尾或者墙的位置停止，计算敌人个数。对于竖直方向也是同样，如果当前位置是开头一个或者上面一个是墙壁，
                我们开始从当前位置向下遍历，遍历到末尾或者墙的位置停止，计算敌人个数。可能会有人有疑问，为啥rowCnt就可以用一个变量，
                而colCnt就需要用一个数组呢，为啥colCnt不能也用一个变量呢？原因是由我们的遍历顺序决定的，我们是逐行遍历的，在每行的开头就统计了该行的敌人总数，
                所以再该行遍历没必要用数组，但是每次移动时就会换到不同的列，我们总不能没换个列就重新统计一遍吧，所以就在第一行时一起统计了存到数组中供后来使用。有了水平方向和竖直方向敌人的个数，
                那么如果当前位置是0，表示可以放炸弹，我们更新结果res即可
 */



class Solution1 {
public:
    int maxKilledEnemies(vector<vector<char>>& grid) {
        if ( grid.size()==0 || grid[0].size()==0 ) return 0;
        int n=grid.size(), m=grid[0].size();
        //<向左，向右>
        vector<vector<pair<int,int>>> rows(n, vector<pair<int,int>>(m,{0,0}));
        vector<vector<pair<int,int>>> cols(n, vector<pair<int,int>>(m,{0,0}));
        //初始化rows
        for ( int i=0; i<n; ++i ){
            rows[i][0].first = (grid[i][0]=='E')?1:0;
            rows[i][m-1].second = (grid[i][m-1]=='E')?1:0;
            for ( int j=1; j<m; ++j ){
                if ( grid[i][j]=='E' )
                    rows[i][j].first = rows[i][j-1].first + 1;
                else if ( grid[i][j]=='W') 
                    rows[i][j].first = 0;    
                else  rows[i][j].first = rows[i][j-1].first; 
                
                if ( grid[i][m-1-j]=='E' )
                    rows[i][m-1-j].second = rows[i][m-j].second + 1;
                else if ( grid[i][m-1-j]=='W' )
                    rows[i][m-1-j].second = 0;
                else rows[i][m-1-j].second = rows[i][m-j].second;
            }
        }
        //初始化cols
        // <向上，向下>
        for ( int j=0; j<m; ++j ){
            cols[0][j].first = (grid[0][j]=='E')?1:0;
            cols[n-1][j].second = (grid[n-1][j]=='E')?1:0;
            for ( int i=1; i<n; ++i ){
                if ( grid[i][j]=='E' )
                    cols[i][j].first = cols[i-1][j].first + 1;
                else if ( grid[i][j]=='W') 
                    cols[i][j].first = 0;    
                else  cols[i][j].first = cols[i-1][j].first; 
                
                if ( grid[n-i-1][j]=='E' )
                    cols[n-i-1][j].second = cols[n-i][j].second + 1;
                else if ( grid[n-i-1][j]=='W' )
                    cols[n-i-1][j].second = 0;
                else cols[n-i-1][j].second = cols[n-i][j].second;
            }
        }
        int res = 0;
        for ( int i=0; i<n; ++i )
            for ( int j=0; j<m; ++j ){
                if( grid[i][j]=='0' )
                    res = max(res,rows[i][j].first+rows[i][j].second + cols[i][j].first+cols[i][j].second);
            }
        return res;
    }
};

//==============================================================

class Solution2 {
public:
    int maxKilledEnemies(vector<vector<char>>& grid) {
        if ( grid.size()==0 || grid[0].size()==0 ) return 0;
        int n=grid.size(), m=grid[0].size();
        vector<int> colCnt(m, 0);
        int rowCnt=0,res=0;
        for ( int i=0; i<n; ++i ){
            for ( int j=0; j<m; ++j ){
                if ( j==0 || grid[i][j-1]=='W' ){
                    rowCnt = 0;
                    for ( int k=j; k<m && grid[i][k]!='W' ; ++k ){
                        if ( grid[i][k]=='E' )
                            rowCnt++;
                    }
                }
                if ( i==0 || grid[i-1][j]=='W' ){
                    colCnt[j] = 0;
                    for ( int k=i; k<n && grid[k][j]!='W'; ++k ){
                        if ( grid[k][j]=='E' )
                            ++colCnt[j];
                    }
                }
                
                if ( grid[i][j]=='0' )
                    res = max(res, rowCnt+colCnt[j]);
                
                
            }
        }
        return res;
    }
};

