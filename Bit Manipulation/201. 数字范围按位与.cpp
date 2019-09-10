/*
    问题描述:
        给定范围 [m, n]，其中 0 <= m <= n <= 2147483647，
        返回此范围内所有数字的按位与（包含 m, n 两端点）。
        
        示例 1: 
            输入: [5,7]
            输出: 4
        
        示例 2:
            输入: [0,1]
            输出: 0

    问题分析：
        列出几个例子:
            10-11:
                1010
                1011
         结果为: 1010
                ^^^

            26-30:
                11010　　
                11011　　
                11100　　
                11101　　
                11110

         结果为: 11000
                ^^ 


        由此可以看出， 只要找到 n和m在二进制下的相同前缀就可以了！
        对于找出两个二进制数的相同前缀， 实现方法有如下几种
*/

class Solution1 {
public:
    // 方法一: mask法
    int rangeBitwiseAnd(int m, int n) {
        // mask取值为 1...111111
        //           1...111110
        //           1...111100
        //           1...111000
        //           1...110000
        //           ...
        // ps: mask&-mask将返回二进制最低位的1的位置 , 树状数组里的lowbit
        int mask = INT_MAX;
        while( (m&mask) != (n&mask) )
            mask -= (mask&-mask);
        return m&mask;
    }
};

class Solution2 {
public:
    // 方法二
    // 不再使用mask，因为值是大于0的，所以右移后，前缀是补0的
    // 所以可以让n和m右移，然后记录移动位数， 直到m和n相等后，再向左移动回去
    int rangeBitwiseAnd(int m, int n) {
        int i=0;
        while( n!=m ){
            n>>=1;
            m>>=1;
            ++i;
        }  
        return n<<i;
    }
};

class Solution3 {
public:
    // 方法三: 方法二的递归版. 移动的位数就是递归的层数 
    int rangeBitwiseAnd(int m, int n) {
        return m>=n?m: (rangeBitwiseAnd(m/2, n/2)<<1);
    }
};
