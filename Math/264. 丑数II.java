/*
    问题描述：
        编写一个程序，找出第 n 个丑数。
        丑数就是只包含质因数 2, 3, 5 的正整数。

        示例:
        输入: n = 10
        输出: 12
        解释: 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 是前 10 个丑数。

    问题分析：
        方法一：
            用最小堆来做，
            最小堆里一开始只有一个1，
            然后每次弹出最小值A，再把A*2，A*3，A*5压入最小堆，
            直到弹出第n个数。
        
        方法二：
            动态规划，
            找规律可以看出，新增进来的丑数都是由之前的丑数相乘得到的，
            也就是通过之前计算的丑数，得到了当前丑数，因此可以用DP
            
            系数是{1,2,3,4,5,6,8,9,10,...} , 也就是丑数数组
            乘数是2  (1) <1x2>,  2x2,   2x2,   <3x2>, <4x2>,    5x2...
            乘数是3  (2) 1x3  ,  <1x3>, 2x3,   <2x3>, 3x3,    <3x3>...
            乘数是5  (3) 1x5  ,  1x5,   <1x5>, 1x5,   2x5,     3x5...

            每次都是选中(1),(2),(3)中最小的那个，然后选中的系数(丑数)更改为下一个系数(丑数)   
            要注意，3✖2和2✖3都是6，不要重复压入，记得过滤掉相同的值      
*/

class Solution1 {
    public int nthUglyNumber(int n) {
        long res = -1, pre = -1;
        PriorityQueue<Long> A = new PriorityQueue<Long>();
        HashSet<Long> set = new HashSet<Long>();
        A.add(1L);
        while (n-- > 0) {
            // 过滤相同元素，下一个丑数一定比当前丑数要大！
            while (A.size() > 0 && res >= A.peek())
                A.poll();
            res = A.peek();
            A.poll();
            A.add(res * 2);
            A.add(res * 3);
            A.add(res * 5);
        }
        return (int) res;
    }
}

class Solution2 {
    public int nthUglyNumber(int n) {
        if (n == 1)
            return 1;
        int[] ugly = new int[n * 3];
        int res = 0;
        int idx1 = 0, idx2 = 0, idx3 = 0, idx = 0;
        int a, b, c;
        ugly[0] = 1;
        for (int i = 0; i < n - 1; ++i) {
            a = ugly[idx1] * 2;
            b = ugly[idx2] * 3;
            c = ugly[idx3] * 5;
            // res是当前选中的丑数
            res = Math.min(Math.min(a, b), c);
            // 把和当前丑数相等的值都进行更新
            // 以防重复存入相同的丑数（例如3✖2和2✖3）
            if (res == a) {
                idx1++;
            }
            if (res == b) {
                idx2++;
            }
            if (res == c) {
                idx3++;
            }
            ugly[++idx] = res; // 把新的丑数存入数组
        }
        return res;
    }
}
