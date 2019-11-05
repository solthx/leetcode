/*
    问题描述:
        给你一个正整数数组 nums，你需要从中任选一些子集，然后将子集中每一个数乘以一个 任意整数，并求出他们的和。
        假如该和结果为 1，那么原数组就是一个「好数组」，则返回 True；否则请返回 False。

        示例 1：

        输入：nums = [12,5,7,23]
        输出：true
        解释：挑选数字 5 和 7。
        5*3 + 7*(-2) = 1
        示例 2：

        输入：nums = [29,6,10]
        输出：true
        解释：挑选数字 29, 6 和 10。
        29*1 + 6*(-3) + 10*(-1) = 1
        示例 3：

        输入：nums = [3,6]
        输出：false
        

        提示：

        1 <= nums.length <= 10^5
        1 <= nums[i] <= 10^9

    问题分析:
        即 找出是否存在 a1x1 + a2x2 + .. + akxk = 1 有解
        
        a1x1 + a2x2 + .. + akxk = 1 有解的充要条件是
        1 是 a1, a2, ... ,ak的最大公约数的倍数
        即 
            1 % gcd( a1,a2,..,ak ) == 0  

        又 a,b如果最小公倍数为1， 那么 a,b,c的最大公约数为1

        因此， 只要 gcd( a1, a2, ..., an ) = 1
        那么就ok了。

        （看来基础数论知识还是必要了解以下...

        本次收获:
            ax + by = c 有解的充要条件为 c % gcd( a,b ) == 0 (也记作 gcd(a,b)|c  )
            （该结论可以推广到一般情况，即： a,b,c,e,...）

        延伸: 
            扩展欧几里得算法(如果存在就求出特解)
            裴蜀定理 : 在ax +by = c的所有解中， gcd(a,b)是最小的那个。
*/

class Solution {
public:
    bool isGoodArray(vector<int>& nums) {
        if ( nums.size()==1 ) return nums[0]==1; 
        int res = gcd(nums[1], nums[0]);
        for ( int i=2; i<nums.size(); ++i ){
            res = gcd( res, gcd( nums[i], nums[i-1] ) );
        }
        return res == 1;
    }
};