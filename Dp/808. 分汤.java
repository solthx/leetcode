/*
    问题描述:
        有 A 和 B 两种类型的汤。一开始每种类型的汤有 N 毫升。有四种分配操作：
        提供 100ml 的汤A 和 0ml 的汤B。
        提供 75ml 的汤A 和 25ml 的汤B。
        提供 50ml 的汤A 和 50ml 的汤B。
        提供 25ml 的汤A 和 75ml 的汤B。
        当我们把汤分配给某人之后，汤就没有了。每个回合，我们将从四种概率同为0.25的操作中进行分配选择。如果汤的剩余量不足以完成某次操作，我们将尽可能分配。当两种类型的汤都分配完时，停止操作。

        注意不存在先分配100 ml汤B的操作。

        需要返回的值： 汤A先分配完的概率 + 汤A和汤B同时分配完的概率 / 2。

        示例:
        输入: N = 50
        输出: 0.625
        解释:
        如果我们选择前两个操作，A将首先变为空。对于第三个操作，A和B会同时变为空。对于第四个操作，B将首先变为空。
        所以A变为空的总概率加上A和B同时变为空的概率的一半是 0.25 *(1 + 1 + 0.5 + 0)= 0.625。
        注释:

        0 <= N <= 10^9。
        返回值在 10^-6 的范围将被认为是正确的。

    问题分析:
        本题的状态转移很容易想到, 但难点主要在于能不能发现 N很大的时候，概率为1.

        dfs(i , j)  保存 当A还剩i， B还剩j的时候，汤A先分配完的概率 + 汤A和汤B同时分配完的概率 / 2 的值

        状态转移: memo[A][B] = 0.25* ( dfs( A-100, B )+dfs( A-75,B-25 )+ dfs( A-50,B-50 )+dfs(A-25,B-75) );

        但N太大了，无法保存状态. 

        一个优化方法是， 因为减去的都是25的倍数， 因此，对 （N/25）向上取整， 减去的汤的值，也除25, 这样，整体状态都小了25倍。。但依然还是很大。。
        然后变成了 dp(i, j) = 1/4 * (dp(i - 4, y) + dp(i - 3, y - 1) + dp(i - 2, y - 2) + dp(i - 1, y - 3))



        比较难的地方在于第二个优化方法, 

        第二个优化方法是:  
            分配操作有 (4, 0)，(3, 1)，(2, 2) 和 (1, 3) 四种，那么在一次分配中，
            汤 A 平均会少 (4 + 3 + 2 + 1) / 4 = 2.5 份，汤 B 平均会少 (0 + 1 + 2 + 3) / 4 = 1.5 份。
            因此在 N 非常大的时候，A 会有很大的概率比 B 先分配完，所有概率应该非常接近 1。事实上，当 N >= 500 * 25 时，
            所求概率已经大于 0.999999 了（可以通过上面的动态规划方法求出），它和 1 的误差（无论是绝对误差还是相对误差）都小于 10^-6。
            因此在 N >= 500 * 25 时，我们只需要输出 1 作为答案即可。
*/

class Solution {
    double[][] memo = new double[200][200];

    public double soupServings(int N) {
        if (N % 25 != 0)
            N += 25;
        N /= 25;
        if (N >= 200)
            return 1;
        return dfs(N, N);
    }

    public double dfs(int A, int B) {
        if (A <= 0 && B <= 0)
            return 0.5;
        else if (A <= 0)
            return 1;
        else if (B <= 0)
            return 0;
        if (memo[A][B] > 0)
            return memo[A][B];
        double res;
        res = 0.25 * (dfs(A - 4, B) + dfs(A - 3, B - 1) + dfs(A - 2, B - 2) + dfs(A - 1, B - 3));
        return memo[A][B] = res;
    }
}