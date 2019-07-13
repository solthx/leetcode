/*
    问题描述：
       
    

    问题分析：
        1. 需要用到的数学知识：
            1. a^b % 1337 = (a%1337)^b % 1337
            2. xy % 1337 = ((x%1337) * (y%1337)) % 1337

        2. 给的是数组的一个好处就是，
        设当前结果是res，
        res = pow(res,10) * pow(res,b[i]) 这样循环计算
        
        3. 然后就是因为数可能会很大，因此上面的pow函数自己写（应用到上面的数学知识
        写Pow()）
        
*/
class Solution {
    public int superPow(int a, int[] b) {
        int res = 1;
        int tmp;
        for (int e : b) {
            res = (pow_(res, 10) * pow_(a, e)) % 1337;
        }
        return res;
    }

    int pow_(int a, int b) {
        // return a^b
        if (b == 0 || a == 1)
            return 1;
        if (b == 1)
            return a % 1337;
        int x = a % 1337, y = b % 1337;
        int res = pow_(x, y / 2);
        return ((res * res) % 1337) * (pow_(x, y % 2)) % 1337;
    }
}
