/*
    问题描述：
        你的赛车起始停留在位置 0，速度为 +1，正行驶在一个无限长的数轴上。（车也可以向负数方向行驶。）

        你的车会根据一系列由 A（加速）和 R（倒车）组成的指令进行自动驾驶 。

        当车得到指令 "A" 时, 将会做出以下操作： position += speed, speed *= 2。

        当车得到指令 "R" 时, 将会做出以下操作：如果当前速度是正数，则将车速调整为 speed = -1 ；否则将车速调整为 speed = 1。  (当前所处位置不变。)

        例如，当得到一系列指令 "AAR" 后, 你的车将会走过位置 0->1->3->3，并且速度变化为 1->2->4->-1。

        现在给定一个目标位置，请给出能够到达目标位置的最短指令列表的长度。

        示例 1:
        输入:
        target = 3
        输出: 2
        解释:
        最短指令列表为 "AA"
        位置变化为 0->1->3
        示例 2:
        输入:
        target = 6
        输出: 5
        解释:
        最短指令列表为 "AAARA"
        位置变化为 0->1->3->7->7->6
        说明:

        1 <= target（目标位置） <= 10000。


    问题描述：
        方法一: BFS+剪枝
            裸BFS的话，复杂度是2^D， 肯定直接TLE了..
            剪枝的地方:
                1. 存入下一个A状态的时候, 如果 abs(pos)>=2*target || abs(speed)>2*target 就直接不入队了
                2. 存入下一个R状态的时候，分别看在pos位置上, speed为+-1的时候是否访问过，如果访问过就不需要再入队了.
            经过上面两个剪枝，可以勉勉强强A过去.. 因为这题本质上还是Dp

        方法二: 动态规划
            先来分析A操作和R操作实质上是做了什么:
                1. A操作可以被当作是一个可变增量，为 {1,2,4,8,16,...}
                2. R操作是可以改变上面增量的正负以及重置增量的位置(重置位置的意思是, 比如下一个应该+8, 但重置位置之后，下一个就该+1，从头开始了)

            开始找子问题:
                抵达target的最少操作，一定是 <抵达j的最少操作 + 抵达target-j的最少操作>
                而起点又是在0， 因此，我们可以用dp[i]来保存抵达i的最少操作，dp[target]就是答案.

            而从位置0开始，抵达位置i的情况为(假设当前位置为j):
                1. 当i为( 2^k - 1 )时:
                    一路A过去，直接抵达. 此时dp[i] = k
                2. 当i不为( 2^k - 1 )时:
                   1. j>i：
                        这个情况就是j走过头了，需要折返, 折返的距离就是从j到i的距离，也就是0到j-i的距离:
                        因此，当前操作次数就是： 到达j的次数+切换方向的次数+从j到i的次数(即从0到j-i的次数)
                        (j = 2^f - 1)
                        因此 dp[i] = min( f + 1 + dp[j-i], dp[i] )

                   2. i<j:
                        这个情况就是还没到i:
                            那么可以有2种情况:
                                1. 重置, 然后从1开始加, 即： dp[j] + dp[i-j] + 2
                                2. 先往反方向走 k ( k = 2^b - 1 ) , 然后再从 j-k走到 i
                                    即: dp[j] + 1 + dp[b] + 1 + dp[i-(j-k)]
                            ps:
                               仔细观察式子可以看出，第一个的情况就是 k==b==0时的情况.
                               因此可以合并一个..

            综上, 状态转移就是:
                j = 2^forward-1;
                if i==j
                    dp[i] = forward;
                else if j>i and j-i<i:
                    dp[i] = min( dp[i], forward + 1 + dp[j-i] );
                for k = 2^back - 1:
                    if i-(j-k)>0 and i-(j-k)<i :
                        dp[i] = min( dp[i], forward + 1 + back + 1 + dp[i-(j-k)] )
*/

class Solution {
public:
    int racecar(int target) {
        // dp[i]表示到达位置i所需要的最小步数
        int dp[target+1];
        dp[1] = 1;
        dp[0] = 0;
        for ( int i=2; i<=target; ++i ){
            dp[i] = INT_MAX;
            for ( int forward = 1; (1<<forward)-1<=target*2; ++forward  ){
                // 向前走forward步, 走了j个距离
                int j = (1<<forward) -1;
                if ( i==j )
                    dp[i] = forward;
                else if ( j>i && j-i<i )
                        dp[i] = min( dp[i], forward + 1 + dp[j-i] );
                else{
                    for ( int back = 0; back<forward; ++back ){
                        // 向后走了back步, 走了k个距离
                        int k = (1<<back)-1;
                        if ( i-j+k>=0 && i-j+k<i )
                            dp[i] = min( dp[i], forward + back + 2 + dp[i-j+k] );
                    }
                }
            }
        }
        return dp[target];
    }
};