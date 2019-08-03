/*
    问题描述：
        给一个01矩阵， 计算一个位置，使得在这个位置到所有的1的曼哈顿距离最短
        曼哈顿计算公式：

        输入: 
            1 - 0 - 0 - 0 - 1
            |   |   |   |   |
            0 - 0 - 0 - 0 - 0
            |   |   |   |   |
            0 - 0 - 1 - 0 - 0
        输出: 6 

    问题分析:
        317.Shortest Distance from All Buildings 建筑物的最短距离 那题的弱化版，
        bfs做了然后TLE。。看来不是弱化版

        从一维考虑这个"曼哈顿距离"的话， 计算0到英文字符的距离
        ___A___0___B___
        即在A，B之间的位置，到字母距离最短，且这个最短距离是 A到B的距离
        如果是奇数的话
        ___A__B__C___
        那么0在位置B的时候，到A，B，C的距离最短。

        所以，奇数就是在中间那个数的位置，偶数就是在中间那两个数的中间的那些位置。
        确定位置以后，计算到两边的距离。

        二维的情况不过是 两个一维情况 (x,y)
 */

 class Solution {
public:
    int minTotalDistance(vector<vector<int>>& grid) {
        vector<int> rows, cols;
        for ( int i=0; i<grid.size(); ++i )
            for ( int j=0; j<grid[0].size(); ++j )
                if ( grid[i][j]==1 ){
                    rows.push_back(i);
                    cols.push_back(j);
                }
        sort(rows.begin(), rows.end());
        sort(cols.begin(), cols.end());
        int res= 0;
        int i=0, j=rows.size()-1;
        while( i<j ){
            res += (rows[j]+cols[j]-rows[i]-cols[i]);
            ++i;--j;
        }
        return res;
    }
};