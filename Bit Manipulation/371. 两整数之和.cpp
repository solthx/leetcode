/*
    问题描述:
        不使用运算符 + 和 - ​​​​​​​，计算两整数 ​​​​​​​a 、b ​​​​​​​之和。

        示例 1:

        输入: a = 1, b = 2
        输出: 3
        示例 2:

        输入: a = -2, b = 3
        输出: 1

    问题分析:
        两个数的相加可以等价转换成另外两个数的相加:
            a+b = 不带进位的(a+b) + 只带进位的(a+b)
                =     a^b      +  (a&b)<<1
        
        举个例子:
            8 + 9 = 17
            01000 + 01001 = 00001(不进位) + 10000(只有进位) 
            a   +  b    =  a^b         + (a&b)<<1  

        因此，如果a&b是0的话，直接返回a^b，就是答案了,
             如果a&b不是0，说明有进位，那就要等价转换一下, 变成 a^b + (a&b)<<1  
        
        ps: leetcode的c++编译器，不能对负数进行左移，因此要把最高位变成0 (a&b&0x7fffffff)<<1
            但java可以
*/

// C++
class Solution {
public:
    int getSum(int a, int b) {
        // 8 + 9 = 17
        // 01000 + 01001 = 00001(不进位) + 10000(只有进位) 
        //   a   +  b    =  a^b         + (a&b)<<1  
        if ( (a&b)==0 ) return a^b;
        return getSum( a^b,  (a&b&0x7fffffff)<<1 ); // leetCode的编译器不能对负数进行左移，就是说最高位符号位必须要为0, 因此 & 一个0x7fffffff
    }
};

// Java
class Solution {
    public int getSum(int a, int b) {
        return (a&b)==0?a^b:getSum( a^b,  (a&b)<<1 );
    }
}