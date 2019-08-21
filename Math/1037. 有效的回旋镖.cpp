/*
    问题描述:
        给三个坐标，判断能否围成三角形

    问题分析:
        题目不难。 但要考虑清楚，做到一次ac
        1. 过滤掉不合法情况: 垂直，水平，两点重合
        2. 三点不在一条线上
*/

class Solution {
public:
    bool isBoomerang(vector<vector<int>>& points) {
        int x1 = points[0][0];
        int y1 = points[0][1];
        int x2 = points[1][0];
        int y2 = points[1][1];
        int x3 = points[2][0];
        int y3 = points[2][1];
        // 特殊情况过滤，两点相等，垂直，水平
        if ( y1==y2 && y2==y3 || x1==x2 && x2==x3 || (x1==x2&&y1==y2) || ( x1==x3&&y1==y3 ) || (x2==x3&&y2==y3) ) return false;
        // 三点不在一条线上就行
        return !((x2*y1==x1*y2) && (x2*y3==x3*y2) && (x1*y3==x3*y1));
    }
};