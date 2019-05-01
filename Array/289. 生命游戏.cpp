/*
	题目描述：
		给定一个包含 m × n 个格子的面板，每一个格子都可以看成是一个细胞。
		每个细胞具有一个初始状态 live（1）即为活细胞， 或 dead（0）即为死细胞。
		每个细胞与其八个相邻位置（水平，垂直，对角线）的细胞都遵循以下四条生存定律：

			如果活细胞周围八个位置的活细胞数少于两个，则该位置活细胞死亡；
			如果活细胞周围八个位置有两个或三个活细胞，则该位置活细胞仍然存活；
			如果活细胞周围八个位置有超过三个活细胞，则该位置活细胞死亡；
			如果死细胞周围正好有三个活细胞，则该位置死细胞复活；
		根据当前状态，写一个函数来计算面板上细胞的下一个（一次更新后的）状态。
		下一个状态是通过将上述规则同时应用于当前状态下的每个细胞所形成的，其中细胞的出生和死亡是同时发生的。

	题目分析：
		方法一：
			开一个新的数组res来记录下一次更新后的状态，最后再赋值回给board
		
		方法二：
			原地解法，不再开res来记录，因为board的值域只有{0,1}
			所以我们利用十位上的数来记录更新后的状态，个位上的数是原始转换
			
			这里定的规则是：
				个位为前一次，十位为下一次状态
				十位为2说明细胞凉了
				十位为1说明细胞活了
*/



class Solution {
public:
    void gameOfLife(vector<vector<int>>& board) {
        //原地解法
        //2开头为凉了，1开头为存活
        //vector<vector<int>> res(board.begin(),board.end());
        
        int alive=0,x,y,n=board.size(),m=board[0].size();
        
        int dir[8][2] = {
            {0,1},{1,1},{1,0},
            {-1,0},{-1,-1},{0,-1},
            {1,-1},{-1,1}
        };
        
        
        for ( int i=0; i<n; ++i ){
            for ( int j=0; j<m; ++j ){
                alive=0;
                for ( int t=0; t<8; ++t ){
                    y = i + dir[t][0];
                    x = j + dir[t][1];
                    if ( x>=0 && x<m && y>=0 && y<n ){
                        if ( board[y][x]%10==1 ) alive++;
                    }
                }
                
                if ( alive<2 || alive>3 ) board[i][j] += 20;
                else{
                    if ( alive==3 ) board[i][j] += 10;
                    else if ( alive==2 ){
                        if ( board[i][j]==0 ) board[i][j] += 20;
                        else board[i][j] += 10;
                    }
                }
            }
        }
		/*
		for ( int i=0; i<n; ++i )
			for ( int j=0; j<m; ++j )
				board[i][j] = res[i][j];
		*/
        for ( int i=0; i<n; ++i )
            for ( int j=0; j<m; ++j )
                if ( board[i][j]<20 ) board[i][j] = 1;
                else board[i][j] = 0;
        
        
    }
};