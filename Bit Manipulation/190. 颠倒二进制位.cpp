/*
    问题描述:
        颠倒给定的 32 位无符号整数的二进制位。

    问题分析:
        按位模拟就行.
        并不需要用栈
*/

class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        stack<int> st;
        int times = 32;
        uint32_t res = 0x00000000;
        while( times-- ){
            res<<=1;//结果左移一位，空出位置与n最后一位相加
            res+=n&1; //加上n的最后一位
            n>>=1; //n右移一位，供下一轮与结果相加
        }
        return res;
    }
};