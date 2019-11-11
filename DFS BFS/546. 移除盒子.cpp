/*
    问题描述:
        给出一些不同颜色的盒子，盒子的颜色由数字表示，即不同的数字表示不同的颜色。
        你将经过若干轮操作去去掉盒子，直到所有的盒子都去掉为止。每一轮你可以移除具有相同颜色的连续 k 个盒子（k >= 1），这样一轮之后你将得到 k*k 个积分。
        当你将所有盒子都去掉之后，求你能获得的最大积分和。

        示例 1：
        输入:

        [1, 3, 2, 2, 2, 3, 4, 3, 1]
        输出:

        23
        解释:

        [1, 3, 2, 2, 2, 3, 4, 3, 1] 
        ----> [1, 3, 3, 4, 3, 1] (3*3=9 分) 
        ----> [1, 3, 3, 3, 1] (1*1=1 分) 
        ----> [1, 1] (3*3=9 分) 
        ----> [] (2*2=4 分)
         

        提示：盒子的总数 n 不会超过 100。

    问题分析:
            该题提取一下问题，就是让每次删除连续相同的数字，并获得 (删除数字的个数^2) 点积分，
        然后让求最大积分。 很明显是区间dp。。 即dp[i][j]保存了删除完区间[i,j]的元素，所能获取的最大分数, 最终返回dp[0,n-1]就行了。。

        但是，当我们推公式的时候， 却推不出来:
        


        len in [1,n]:
            i in [0,n-1]:
                j = i+len+1

                if j>=n : 
                    break
                
                k in [i,j] :
                    if boxes[i] == boxes[k]:
                            在区间[i,j]中， boxes[i]和boxes[k]相等,
                        这个时候，区间被分成了:
                            [i] [i+1][k-1] [k] [k+1][j]
                        一个有可能会更新最大值的操作就是:
                            state1 = dp[i+1][k-1] +  dp[k+1][j] + 2^2 (i,k)
                            state2 = dp[i+1][k-1] + removeBoxes( [i]+[k][j] )
                            dp[i][j] = max(state1, state2)
                        
                        因此，仅仅是保存了i,j，信息是不够的。
                            所以这里，如果在引入一个状态t， 保存了区间[i,j]的前面(就是i位置的前面) 有t个元素和boxes[i]相同。
                        
                        因为在这里， t的大小往往是根据前一个状态生成的，
                        例如：
                            最开始 dp[i][j][t] 找到了k，使得boxes[i]==boxes[k] 时，区间被分成：
                                  [i] , [i+1][k-1] , [k] , [k+1][j]
                                即: 
                                    dp[i+1][k-1][0] + dp[k][j][t+1] 
                            
                            可以明显看到， 状态t的计算 ，环环相扣，每次计算都依赖 0 和 t+1 的情况，
                            故 使用记忆化搜索会来的方便一些！！！！ 
        
        memo数组就是dp[i][j][k]来记录  删除区间[i,j]且i之前有k个相同的字符 所得到的最大分数

        helper( i , j , k ):
            if dp[i][j][k]>0:
                return dp[i][j][k]
            
            # 直接和前缀合并的情况
            res = (k+1) * (k+1) + helper( i+1, j , 0 )

            for t in [i,j]:
                if boxes[i] == boxes[t]:
                    res = max(res , helper( i+1, t-1, 0 ) + helper( t, j, k+1 ) ) 
            return dp[i][j][k] = res
*/

class Solution {
public:
    int dp[110][110][110]={0};
    int removeBoxes(vector<int>& boxes) {
        return helper( boxes, 0, (int)boxes.size()-1, 0 );
    }
    
    int helper( vector<int>& boxes, int l, int r, int k ){
        if ( l>r ) return 0;
        if ( dp[l][r][k]>0 ) return dp[l][r][k];
        int res = (k+1)*(k+1) + helper( boxes, l+1, r, 0 ); // 跟之前的合并起来
        // 不合并
        for ( int t=l+1; t<=r; ++t )
            if ( boxes[l]==boxes[t] )
                res = max( res, helper( boxes, l+1, t-1, 0) + helper( boxes, t, r, k+1 ) );
        return dp[l][r][k] = res;
    }
};