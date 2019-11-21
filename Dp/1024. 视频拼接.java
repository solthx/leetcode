/*
    问题描述:
        你将会获得一系列视频片段，这些片段来自于一项持续时长为 T 秒的体育赛事。这些片段可能有所重叠，也可能长度不一。
        视频片段 clips[i] 都用区间进行表示：开始于 clips[i][0] 并于 clips[i][1] 结束。我们甚至可以对这些片段自由地再剪辑，例如片段 [0, 7] 可以剪切成 [0, 1] + [1, 3] + [3, 7] 三部分。
        我们需要将这些片段进行再剪辑，并将剪辑后的内容拼接成覆盖整个运动过程的片段（[0, T]）。返回所需片段的最小数目，如果无法完成该任务，则返回 -1 。
        示例 1：

        输入：clips = [[0,2],[4,6],[8,10],[1,9],[1,5],[5,9]], T = 10
        输出：3
        解释：
        我们选中 [0,2], [8,10], [1,9] 这三个片段。
        然后，按下面的方案重制比赛片段：
        将 [1,9] 再剪辑为 [1,2] + [2,8] + [8,9] 。
        现在我们手上有 [0,2] + [2,8] + [8,10]，而这些涵盖了整场比赛 [0, 10]。
        示例 2：

        输入：clips = [[0,1],[1,2]], T = 5
        输出：-1
        解释：
        我们无法只用 [0,1] 和 [0,2] 覆盖 [0,5] 的整个过程。
        示例 3：

        输入：clips = [[0,1],[6,8],[0,2],[5,6],[0,4],[0,3],[6,7],[1,3],[4,7],[1,4],[2,5],[2,6],[3,4],[4,5],[5,7],[6,9]], T = 9
        输出：3
        解释： 
        我们选取片段 [0,4], [4,7] 和 [6,9] 。
        示例 4：

        输入：clips = [[0,4],[2,8]], T = 5
        输出：2
        解释：
        注意，你可能录制超过比赛结束时间的视频。
         

        提示：

        1 <= clips.length <= 100
        0 <= clips[i][0], clips[i][1] <= 100
        0 <= T <= 100


    问题分析:
        对于这种区间问题的思路：
            1. 按照end排序+贪心
            2. Dp( 一维dp -> 区间dp )
            3. 二分
            4. 分治
        
        方法一: 排序+贪心
            先按照end排序;
            target初始为T,
            while( target>0 ) 
                1. 在所有end比target要大的区间里，选中start最小的那个区间
                2. 若没找到，则说明不存在，返回-1
                3. 若找到了，则把target更新为选中区间的start

        方法二: 动态规划
            一开始光想着怎么用区间dp来做。。发现复杂度到O(N^3)了。。就没用dp做。。
            看了题解以后发现，根本没必要用到二维dp。。一维的就足够了。。（二维反而保存了很多没用的状态，使得复杂度上升

            dp[i]保存了区间[0,i]所需要的最少视频数

            fill(dp, INT_MAX)
            dp[0]=0
            for len from 1 to T:
                for interval in clips:
                    // 当前长度处于
                    if interval.start<=len and len<=interval.end:
                        dp[len] = min( dp[len], dp[interval.start]+1 )
            
            虽然可以先排序再二分，优化到O(NlogN)
            但本题数据量比较小... 二刷再优化吧
*/

// 排序+贪心
class Solution1 {
    public int videoStitching(int[][] clips, int T) {
        Arrays.sort( clips, (a,b)->{
            if ( a[1]!=b[1] )
                return a[1]-b[1];
            return -a[0]+b[0];
        } );
        int res = 0;
        int r = clips.length-1, target = T, mini;
        while( target>0 ){
            mini = Integer.MAX_VALUE;
            while( r>=0 && clips[r][1]>=target ){
                mini = Math.min(  mini, clips[r][0]);
                --r;
            }
            if ( mini == Integer.MAX_VALUE ) return -1;
            ++res;
            target = mini;
        }
        return res;
    }
}

class Solution2 {
    public int videoStitching(int[][] clips, int T) {
        int [] dp = new int[200];
        Arrays.fill(dp,1000);
        dp[0]=0;
        for ( int len = 1; len<=T; ++len )
            for ( int [] p: clips )
                if ( len>=p[0] && len<=p[1] )
                    dp[len] = Math.min(dp[len], dp[p[0]]+1);
        return dp[T]==1000?-1:dp[T];
    }
}