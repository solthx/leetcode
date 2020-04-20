/*
    问题描述:
        给一个0~1的浮点数，将其转换成一个二进制的形式，如果无法转成二进制，那么就输出“ERROR”

    问题分析:
        两个点:
            1.  无法转成二进制的情况就是发生无限循环的情况！ 
            因此可以通过设置一个最多迭代次数，超过了这个阈值就假设是不可能表示的！
            假设这个阈值就是32

            2. 如果直接用double来模拟的话，那么无法满足 2^{-30}的精度，
            换个思路，我们通过对num乘2然后看其个位 这种方法，来去看转换成的二进制形式小数部分的每一个位置！

            了解了上面两个想法，就好做了。
*/
class Solution {
public:
    const string ERROR = "ERROR";
    string printBin(double num) {
        if (num>1) return ERROR;
        double d = 1;
        string res = "0.";
        int i=32; // 设置一个最大迭代次数(num精度越高，这个数就越大，这里设置成32够用了)
        while(num>0 && --i){
            num *= 2;
            int d = num; 
            if (d==0)
                res += "0";
            else if (d==1){
                num -= 1;
                res += "1";
            }else return ERROR;
        }
        return num==0?res:ERROR;
    }
};