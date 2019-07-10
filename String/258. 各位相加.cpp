/*
    问题描述：
        给定一个非负整数 num，反复将各个位上的数字相加，直到结果为一位数。

        示例:
        输入: 38
        输出: 2 
        解释: 各位相加的过程为：3 + 8 = 11, 1 + 1 = 2。 由于 2 是一位数，所以返回 2。

    问题分析：
        要求在O(1)的复杂度解决
        找规律可以发现：
            n%9==0时，结果是9
            n%9!=0时，结果是n%9
            n==0时， 结果是0
*/
class Solution {
public:
    int addDigits(int num) {
        // return num==0?0: (num%9==0? 9:num%9);
        // 找规律，可以看出
        if ( num==0 ) 
            return num;
        else if ( num%9==0 )
            return 9;
        else 
            return num%9;
    }
};