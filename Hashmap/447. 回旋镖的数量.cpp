/*
    问题描述：
        给定平面上 n 对不同的点，“回旋镖” 是由点表示的元组 (i, j, k) ，其中 i 和 j 之间的距离和 i 和 k 之间的距离相等（需要考虑元组的顺序）。
        找到所有回旋镖的数量。你可以假设 n 最大为 500，所有点的坐标在闭区间 [-10000, 10000] 中。
        示例:

        输入:
            [[0,0],[1,0],[2,0]]

        输出:
        2
        解释:
            两个回旋镖为 [[1,0],[0,0],[2,0]] 和 [[1,0],[2,0],[0,0]]

    问题分析：
        方法一：
            暴力了一下O(N^3) TLE...

        方法二:
            用dp优化一下, 从长度入手 
            dp[j]表示长度为j的节点有几个，
            如果dp[i]大于2的话，根据排列组合，可以有 dp[i]*(dp[i]-1)/2 种组合
            又因为 [[1,0],[0,0],[2,0]] 和 [[1,0],[2,0],[0,0]] 算两种，
            所以再乘个2 就是  dp[i]*(dp[i]-1) 种情况.
*/
class Solution {
public:
    int numberOfBoomerangs(vector<vector<int>>& points) {
        // N^2
        int res = 0;
        for ( int j=0; j<points.size(); ++j ){
            unordered_map<int,int> dp; //dp[j]表示长度为j的节点有几个
            for ( int i=0; i<points.size(); ++i  ){
                if ( i==j ) continue;
                int a = points[i][0]-points[j][0];
                int b = points[i][1]-points[j][1];
                int dis = a*a+b*b;
                dp[dis]++;
            }
            for ( auto e:dp )
                if ( e.second>1 )
                    res += e.second*(e.second-1);
        }
        return res;
    }
};
