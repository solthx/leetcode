/*
    问题描述:
        你有一大块巧克力，它由一些甜度不完全相同的小块组成。我们用数组 sweetness 来表示每一小块的甜度。
        你打算和 K 名朋友一起分享这块巧克力，所以你需要将切割 K 次才能得到 K+1 块，每一块都由一些 连续 的小块组成。
        为了表现出你的慷慨，你将会吃掉 总甜度最小 的一块，并将其余几块分给你的朋友们。
        请找出一个最佳的切割策略，使得你所分得的巧克力 总甜度最大，并返回这个 最大总甜度。

        示例 1：
            输入：sweetness = [1,2,3,4,5,6,7,8,9], K = 5
            输出：6
            解释：你可以把巧克力分成 [1,2,3], [4,5], [6], [7], [8], [9]。
        
        示例 2：
            输入：sweetness = [5,6,7,8,9,1,2,3,4], K = 8
            输出：1
            解释：只有一种办法可以把巧克力分成 9 块。
        
        示例 3：
            输入：sweetness = [1,2,2,1,2,2,1,2,2], K = 2
            输出：5
            解释：你可以把巧克力分成 [1,2,2], [1,2,2], [1,2,2]。

        提示：
            0 <= K < sweetness.length <= 10^4
            1 <= sweetness[i] <= 10^5

    问题分析：
        比赛的时候完全没想到用二分做... 

        不过这题给了我一些启发，，
        
        就是要对（值），敏感起来！！！！！！！

        可以对值进行二分，或者dp！ 

        就是当问题是问关于值的时候，务必考虑一下二分，或dp
        
        本题就是对值进行的二分！！

        每一组，巧克力甜度的取值范围为[1, sum{sweetness[0~n]} ]

        然后，二分每一组的甜度, 计算出 每一组的甜度都不小于mid的时候，可以分几组，
        我们的目标是找到能分成K+1组的那个最大值

        因为这样二分会得到一个区间[a,b] 即当mid属于[a,b]的时候， 每一组的甜度都不小于mid的时候，可以分K+1组
        
        我们要的是那个b

        这样问题就简单明了了.
*/

class Solution {
public:
    int maximizeSweetness(vector<int>& sweetness, int K) {
        int cnt=0,l=1,mid, r=accumulate(sweetness.begin(), sweetness.end(), 0);
        ++K; // 切K刀就是分为K+1组，先对K加一
        int res = 0;
        while( l<=r ){
            mid = l+(r-l)/2;
            // 返回每一组的甜度都不小于mid的时候，可以分几组
            cnt = count( sweetness, mid );
            if ( cnt>=K ){ // 大于K或等于K的时候，都说明可以再大一些，但对于等于K的情况要记录一下
                l = mid +1;
                res = mid;
            }
            else r = mid -1 ; // 小于K组，说明每组的量太大了，需要减少
        }
        return res;
    }
    
    int count( vector<int>& sweetness, int val ){
        int cur = 0, res = 0;
        // 每组最少分val个， 可以分几组
        for ( auto e:sweetness ){
            if ( cur+e>=val ){
                ++res;
                cur=0;
            }else cur += e;
        } 
        return res;
    }
};