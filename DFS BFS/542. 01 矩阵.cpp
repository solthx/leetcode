/*
    问题描述：
        给定一个由 0 和 1 组成的矩阵，找出每个元素到最近的 0 的距离。

        两个相邻元素间的距离为 1 。
        示例: 
        
        输入:
        0 0 0
        0 1 0
        1 1 1

        输出:
        0 0 0
        0 1 0
        1 2 1
    
    问题分析：
        对每一个非0元素都进行一次bfs，然后TLE。
        本来想记忆化搜索做的，写一会发现这是上下左右方向不受限制，
        方向不限制，不好使用记忆化...
        看了题解以后，解法真是妙。
        每一个位置上的元素，记录了到0的最小距离，
        因此从所有的0开始，去给周围最近的非0元素来更新距离，
        再利用这些非0元素继续去更新，
        其思路也是一种逆向思路，
        让我计算非0元素到0的距离，也就是计算0到非0元素的距离。。

        上面的这个更新的过程，距离的大小也是递增的(
        例如 第一次更新了所有到0的距离为1的元素，
        第二次利用上一次更新的元素再次更新距离为1的元素，
        也就是变成了距离0为2个元素。。 以此类推)， 所以，
        初始化的时候先把0元素初始化成0， 非0元素初始化为正无穷，
        每次只更新比当前元素大的非0元素（距离大小递增)
 */

 class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
        if ( matrix.size()==0 || matrix[0].size()==0 ) return {};
        int n = matrix.size(), m=matrix[0].size();
        int dir[4][2] = {{1,0},{0,1},{-1,0},{0,-1}};
        queue<pair<int,int>> q;
        vector<vector<int>> res(n, vector<int>(m, 0));
        // 初始化，把所有0元素入队
        for ( int i=0; i<n; ++i )
            for ( int j=0; j<m; ++j )
                if ( matrix[i][j]==0 )
                    q.push(make_pair(i,j));
                else 
                    res[i][j] = INT_MAX;
        while( !q.empty() ){
            pair<int,int> cor = q.front(); q.pop();
            for ( int k=0; k<4; ++k ){
                int y = cor.first + dir[k][0];
                int x = cor.second + dir[k][1];
                if ( y<0 || x<0 || y>=n || x>=m || res[y][x]<=res[cor.first][cor.second] )
                    continue;
                res[y][x] = res[cor.first][cor.second] + 1;
                q.push(make_pair(y,x));
            }
        }
        return res;
    }
};