/**
    问题描述：
        骑士救公主，
        骑士在左上角，公主在右下角，
        每个格子是一个房间，正数加hp，负数减hp，
        骑士只能向右或向下走，
        求骑士能救到公主的最少hp。

    问题分析：
        看了题解。。一开始思路错了，不应该正向地去建立Dp
        应该从公主反向骑士那边推。。
        dp[i][j]是从当前位置能够救到公主的最少hp值.

        当前位置最少需要的hp可能是向下走，也可能是向右走，
        而具体向哪走，只有走过才能知道，这样做会变成dfs，
        如果想预先就知道该向哪走，那必须就先记录右边位置和下方位置的状态，
        由此可以知道，该题应该从公主的位置向骑士的位置推。
        ”能够完成某个要求的当前最少(多)xxx“来逆向推第一个位置 这也是构建Dp的一个思路。
 
        状态转移公式:
            1. dp[i][j]的最少值是1，不然骑士就死了。。
            2. 如果在当前房间的hp 在 得到了当前房间的状态（加hp 或 减hp) 之后，能够大于等于下一个房间
            所需的最少hp的话，那么当前房间的hp就能够满足。  
            那么反过来推， 知道了下一个房间的最少需要的hp数，减去当前房间的状态，那么就是在当前房间的最少hp值，
            如果dp小于0，是说明当前房间多少血都可以， 但别忘了，骑士最少也要有1点hp。

            所以最终的状态转移公式是：
                dp[i][j] = max(1, min(dp[i+1][j], dp[i][j+1]) - dungeon[i][j] )
        
        注意边界的处理。
 */

 class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        //dp[i][j]是从当前位置能够救到公主的最少体力值
        int m = dungeon.size();
        if ( m<=0 ) return 0;
        int n = dungeon[0].size();
        vector<vector<int>> dp(m+1, vector<int>(n+1, 1));
        for ( int i=m-1; i>=0; --i ){
            for ( int j=n-1; j>=0; --j ){
                if ( i<m-1 && j<n-1 )
                    dp[i][j] = max(1, min( dp[i+1][j], dp[i][j+1] )-dungeon[i][j]  );
                // 边界
                else if ( i<m-1 )
                    dp[i][j] = max(1, dp[i+1][j]-dungeon[i][j]  );
                // 边界
                else if ( j<n-1 )
                    dp[i][j] = max(1, dp[i][j+1] -dungeon[i][j]  );
                // 公主所在房间的初始值
                else dp[i][j] = max(1, -1 * dungeon[i][j] + 1);       
            }
        }
        return dp[0][0];
    }
};