/*
    问题描述:
       假设你有一个特殊的键盘包含下面的按键：

        Key 1: (A)：在屏幕上打印一个 'A'。

        Key 2: (Ctrl-A)：选中整个屏幕。

        Key 3: (Ctrl-C)：复制选中区域到缓冲区。

        Key 4: (Ctrl-V)：将缓冲区内容输出到上次输入的结束位置，并显示在屏幕上。

        现在，你只可以按键 N 次（使用上述四种按键），请问屏幕上最多可以显示几个 'A'呢？

        样例 1:

        输入: N = 3
        输出: 3
        解释: 
        我们最多可以在屏幕上显示三个'A'通过如下顺序按键：
        A, A, A
         

        样例 2:

        输入: N = 7
        输出: 9
        解释: 
        我们最多可以在屏幕上显示九个'A'通过如下顺序按键：
        A, A, A, Ctrl A, Ctrl C, Ctrl V, Ctrl V
         

        注释:

        1 <= N <= 50
        结果不会超过 32 位有符号整数范围。
    
    问题分析:
        一开始想O(N)解的，实在想不出来...
        看到N才为50， 就往N^2想了..

        N^2的Dp还是不难想的， dp[i]保存第i次可以得到的最多字符数，
        然后遍历 0~i-2 (i-2,i-1,i)这三次操作留给全选、复制、粘贴

        对于第j为位置上, 当前最多dp[j]个字符， 除去全选、复制、粘贴之后，
        距离i还剩(i-2-j)的可操作次数， 每个可操作次数都是粘贴一次，
        加上原本的dp[j]， 即 有(i-2-j+1)个dp[j]
        即 dp[j]*(i-1-j)

        dp[1]=1
        for i from 2 to n:
            for j from 1 to n-2:
                dp[i] = max(dp[i], dp[j]*(i-1-j)); 
*/

class Solution {
public:
    int maxA(int N) {
        // O(N^2)解法
        if(N<=1) return N;
        vector<int> dp( N+1 );
        dp[1]=1; 
        for ( int i=2; i<=N; ++i ){
            int cur = i;
            for ( int j=1; j<=i-2; ++j ){
                cur = max(cur, dp[j]*(i-1-j));
            }
            dp[i] = cur;
        }
        return dp[N];
    }
};