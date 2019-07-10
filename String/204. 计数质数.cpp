/*
    问题描述：
        给一个数字n，计算小于n的素数个数

    问题分析：
        旧题新解，用打表来做。
        设一个notPrime数组，
        遍历时，若发现i是素数，那么就把小于n且是i的倍数的数字
        在notPrime中设为true 
        具体看代码
 */

 class Solution {
public:
    int countPrimes(int n) {
        bool notPrime[n+1];
        int res=0;
        memset(notPrime,false,sizeof(notPrime));
        for ( int i=2; i<n; ++i ){
            if ( notPrime[i]==false ){
                ++res;
                int t=1;
                while( t*i<=n ){
                    notPrime[t*i] = true;
                    ++t;
                }
            }
        }
        return res;
    }
};