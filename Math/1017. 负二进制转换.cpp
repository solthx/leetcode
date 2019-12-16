/*
    问题描述:
        给出数字 N，返回由若干 "0" 和 "1"组成的字符串，该字符串为 N 的负二进制（base -2）表示。

        除非字符串就是 "0"，否则返回的字符串中不能含有前导零。

         

        示例 1：

        输入：2
        输出："110"
        解释：(-2) ^ 2 + (-2) ^ 1 = 2
        示例 2：

        输入：3
        输出："111"
        解释：(-2) ^ 2 + (-2) ^ 1 + (-2) ^ 0 = 3
        示例 3：

        输入：4
        输出："100"
        解释：(-2) ^ 2 = 4
         

        提示：

        0 <= N <= 10^9

    问题分析:

        假设: a%b = c, a/b =d; (a,b,c,d均大于0)

        那么 a = b*d + c;

        而b是基， 本题中，基是小于0的，所以调整一下变成:

            a = (-b) * (-d) + c  //随着基变成负数，商也变成负的了, 但余数不变..

            但，当基小于0的时候， 余数可能也是小于0的。。。而这里通过补偿的方法，来强制让余数大于0
            ( abs(c) < d, d>0 )
            a = (-b) * (-d) + c+d -d 
              = (-b+1) * (-d) + (c+d) 

            此时，(c+d) % d 一定是大于0的余数

        然后就好办了... 

        1. 先求余数 : 
            mod = ( n%(-2) + 2 ) % 2 
        2. 再求商:
            n -= mod
            n /= -2  // 即得到了-b+1
        
            res = to_string(mod) + res;

        下面代码中，从-2的情况扩展到了k的情况
*/

class Solution {
public:
    string baseNeg2(int N) {
        return N==0?"0":baseNegK(N, -2);
    }

    string baseNegK(int n, int k){
        int abs_k = abs(k);
        string res = "";
        while( n!=0 ){
            // 借位
            int mod = ( n % k + abs_k ) % abs_k;
            res += (char)('0'+mod);
            n = (n - mod) / k ;
        }
        reverse(res.begin(), res.end());
        return res;
    }
};

