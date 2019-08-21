/*
    问题描述：
        给定一个包含非负数的数组和一个目标整数 k，编写一个函数来判断该数组是否含有连续的子数组，其大小至少为 2，总和为 k 的倍数，即总和为 n*k，其中 n 也是一个整数。
        
        示例 1:
        输入: [23,2,4,6,7], k = 6
        输出: True
        解释: [2,4] 是一个大小为 2 的子数组，并且和为 6。
        
        示例 2:
        输入: [23,2,6,4,7], k = 6
        输出: True
        解释: [23,2,6,4,7]是大小为 5 的子数组，并且和为 42。
        说明:

        数组的长度不会超过10,000。
        你可以认为所有数字总和在 32 位有符号整数范围内。

    问题分析:
        方法一: 前缀和暴力.
            这个方法太容易想到了..就不赘述了.. 主要介绍后面的hashmap

        方法二: hashmap
            暴力完以后，也尝试用hashmap做了一下, 但还是没作出来..
            看了题解才知道，原来hashmap配合前缀和的时候还可以这么用.

            之前遇到的hashmap和前缀和的题， 都是以preSum[i]为目标区间的右边界，
            举个例子，找和为k个区间个数,
            我们希望找到这样子的区间 [ j+1, i ] 使得nums[j+1]+..+nums[i]==k
            前缀和的形式就是 preSum[i]-preSum[j]==k
            所以，当我们遍历到preSum[i]的时候，那个时候i之前的前缀和都已经放入map里了，
            因此，我们希望根据右边界preSum[i]来找左边界preSum[j]== preSum[i]-k

            然而，上面的是最经典的思路，根据题目对区间的要求的不同，可能会有变化，
            主要体现在 到第i个位置，找什么值

            先根据题目对区间的条件限制， 列出公式，看能否推导化简, 例如本题的分析过程如下:

                我们希望：
                    preSum[i] - preSum[j] == n*k
                    且j-i>1
                
                也就是说
                    ( a+n1*k ) - (b+n2*k) == n*k 
                    a-b + (n1-n2)*k == n*k
                    a - b == (n-n1+n2)*k == N*k
                    
                    对两边同时mod k得到
                        (a-b)%k==0 
                        a%k == b%k
                    所以，每次我们都去找 preSum[i]%k 是否出现过，
                    如果出现过，那么就找到了b, 也就找到了“preSum[j”，
                    如果没出现过，就把preSum[i]%k 放入 map中，以便后面的前缀和来查询

                    同时，之所以用map不用set，是因为要用map 来记录出现的位置
                    如果当前位置和上一次出现位置相邻，那也非法(题目限制)
                    所以要多加一个判断.
*/

class Solution1 {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        // O(N^2) 前缀和+暴力
        if ( !k ){
            for ( int i=0; i<nums.size()-1; ++i )
                if ( nums[i]==0 && nums[i]==nums[i+1] ) return true;
            return false;
        }
        k = abs(k);
        int n = nums.size();
        vector<int> preSum(n+1, 0);
        for (  int i=1; i<=n; ++i )
            preSum[i] = preSum[i-1] + nums[i-1];
        for ( int i=1; i<=n; ++i ){
            for ( int j=0; j<i-1; ++j ){
                if ( (preSum[i]-preSum[j])%k==0 )
                    return true;
            }
        }
        return false;
    }
};


class Solution2{
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        // O(NlogN) 前缀和+hashmap
        if ( !k ){
            for ( int i=0; i<nums.size()-1; ++i )
                if ( nums[i]==0 && nums[i]==nums[i+1] ) return true;
            return false;
        }
        k = abs(k);
        int idx=1, curSum=0, n = nums.size();
        map<int,int> mp;
        mp[0] = 0;
        for ( auto e:nums ){
            curSum += e;
            if ( mp.count( curSum%k )>0   ){
                if (idx - mp[curSum%k]>1)
                    return true;
            }
            else mp[curSum%k] = idx;
            idx++;
        }
        return false;
    }
};