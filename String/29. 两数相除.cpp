/*
    问题描述：
        给定两个整数，被除数 dividend 和除数 divisor。将两数相除，要求不使用乘法、除法和 mod 运算符。

        返回被除数 dividend 除以除数 divisor 得到的商。

        示例 1:

        输入: dividend = 10, divisor = 3
        输出: 3
        示例 2:

        输入: dividend = 7, divisor = -3
        输出: -2

    问题分析：
        使用二分来做，本题要说的是，下面的这种二分代码：
        i=0, j=n-1;
        while( i<=j ):
            mid = (i+j)/2;
            if ( func(mid) > val ):
                j = mid - 1;
            else if ( func(mid) < val )    
                i = mid + 1;
            else ...
        这个时候，
        如果是因为i>j跳出循环:
             第i个位置是首个    ( func(mid)>val ) 的那个元素
             第j个位置是最后一个 ( func(mid)<val ) 的那个元素

        下题是应用
 */ 
class Solution {
public:
    int divide(int dividend, int divisor) {
        long long a = abs((long long)dividend);
        long long b = abs((long long)divisor);
        bool nega = (dividend>0) ^ ( divisor>0 );
        if ( a<b ) return 0;
        if ( a==b ) return nega?-1:1;
        long long mid=0, i=0, j=a;
        while( i<=j ){
            mid = (i+j)/2;
            if ( mid*b>a ) j = mid-1;
            else if ( mid*b<a  ) i = mid +1;
            else{
                i=mid;
                break;
            }
        }
        if ( i>j) --i;
        i = nega?-1*i:i;
        if ( i>INT_MAX ) return INT_MAX;
        else if (i<INT_MIN) return INT_MIN;
        return i;
    }
};


