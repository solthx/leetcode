/*
    问题描述：
        一个“快乐数”定义为：对于一个正整数，每一次将该数替换为它每个位置上的数字的平方和，然后重复这个过程直到这个数变为 1，
        也可能是无限循环但始终变不到 1。如果可以变为 1，那么这个数就是快乐数。
        示例: 

        输入: 19
        输出: true
        解释: 
        12 + 92 = 82
        82 + 22 = 68
        62 + 82 = 100
        12 + 02 + 02 = 1

    问题分析：
        举几个例子可以看出，任何数最终都会收敛到个位数，
        而在个位数里，只有1和7不会死循环，
        故只要判断当其循环到个位数的时候是否落在1或7这两个数上。
*/
class Solution {
    public boolean isHappy(int n) {
        int res=n, tmp=0, Acc=0;
        while( res>=10 ){
            tmp = res;
            Acc = 0;
            while( tmp>0 ){
                Acc += (tmp%10) * (tmp%10);
                tmp /= 10;
            }
            res = Acc;
        }
        return res==1 || res==7;
    }
}
