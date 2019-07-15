/*
    问题描述：
        初始时有 n 个灯泡关闭。 第 1 轮，你打开所有的灯泡。 第 2 轮，每两个灯泡你关闭一次。 第 3 轮，每三个灯泡切换一次开关（如果关闭则开启，如果开启则关闭）。第 i 轮，每 i 个灯泡切换一次开关。 
        对于第 n 轮，你只切换最后一个灯泡的开关。 找出 n 轮后有多少个亮着的灯泡。
        
        示例:
        输入: 3
        输出: 1 
        解释: 
        初始时, 灯泡状态 [关闭, 关闭, 关闭].
        第一轮后, 灯泡状态 [开启, 开启, 开启].
        第二轮后, 灯泡状态 [开启, 关闭, 开启].
        第三轮后, 灯泡状态 [开启, 关闭, 关闭]. 
        你应该返回 1，因为只有一个灯泡还亮着。

    问题描述：
        1. 先是模拟，然后TLE
        
        2. 然后这种数学问题，正确的阶梯姿势应该是“找规律”
        先列出 n = 3,4,5,6,7,8,9,.. （不一定列到9项，只是因为本题列到n=9才会出现不同
        然后可以看出， 由平方得到的数字的位置上，灯最后总是亮的（1,4，9，16，25，。。）
        这时就可以写程序了

        3. 在2的基础上，可以看出，个数就是sqrt(n)向下取整，即直接 return (int)sqrt(n);
 */

class Solution1 {
    // 模拟 TLE
    public int bulbSwitch(int n) {
        int[] bulb = new int[n + 1];
        int j;
        Arrays.fill(bulb, 1);
        for (int i = 2; i <= n; ++i) {
            j = 0;
            while (j + i <= n) {
                bulb[j + i] = (bulb[j + i] + 1) % 2;
                j += i;
            }
        }
        int res = 0;
        for (int t = 1; t <= n; ++t)
            res += bulb[t];
        return res;
    }
}

class Solution2 {
    public int bulbSwitch(int n) {
        int res = 1;
        while (res * res <= n)
            ++res;
        return res - 1;
    }
}

class Solution3 {
    public int bulbSwitch(int n) {
        return (int) Math.sqrt(n);
    }
}