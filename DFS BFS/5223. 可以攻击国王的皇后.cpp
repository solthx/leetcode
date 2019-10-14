/*
    问题描述:
        https://leetcode-cn.com/problems/queens-that-can-attack-the-king/
    
    问题分析:
        从king的位置开始,
        朝8个方向上进行扫描,

        当直线向一个方向前进的时候， 可以用方向数组.
*/
class Solution {
public:
    vector<vector<int>> queensAttacktheKing(vector<vector<int>>& queens, vector<int>& king) {
        int dir[8][2] = { {1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1},{1,0} };
        vector<vector<int>> res;
        int dp[8][8]={0};
        for ( auto p:queens ) dp[p[0]][p[1]]=1;
        for ( int k=0; k<8; ++k ){
            int y = king[0] + dir[k][0];
            int x = king[1] + dir[k][1];
            while( y>=0 && x>=0 && x<8 && y<8 && dp[y][x]!=1 ){
                y = y + dir[k][0];
                x = x + dir[k][1];
            }
            if ( y>=0 && x>=0 && x<8 && y<8 && dp[y][x]==1 )
                res.push_back({y,x});
        }
        return res;
    }
};