/*
    问题描述:
        给定一个整数数组 A，返回其中元素之和可被 K 整除的（连续、非空）子数组的数目。

        示例：
            输入：A = [4,5,0,-2,-3,1], K = 5
            输出：7
            解释：
            有 7 个子数组满足其元素之和可被 K = 5 整除：
            [4, 5, 0, -2, -3, 1], [5], [5, 0], [5, 0, -2, -3], [0], [0, -2, -3], [-2, -3]
         

        提示：
            1 <= A.length <= 30000
            -10000 <= A[i] <= 10000
            2 <= K <= 10000

    问题分析:
        看这数据量，应该要求复杂度 <= O(NlogN)
        
        这种经典题，几乎就是hashmap+前缀和了.
        
        本题和 #523 类似

        核心思想: 把所有数都映射到 [0, k) 这个区间中
        因为，两个数之间如果差m*k， 那么映射到[0,k)中之后， 应该是同一个数

        例如， k=5 , a=4, b=14,  a%5==4, b%5==4

        原因如下:
                ( nums[i]-nums[j] ) % k==0
                ( a+n1*k ) - (b+n2*k) == n*k 
                a-b + (n1-n2)*k == n*k
                a - b == (n-n1+n2)*k == N*k
                对两边同时mod k得到
                    (a-b)%k==0 
                    a%k == b%k

        所以我们在利用前缀和+hashmap的基础上:
            1. 保存 nums[i] % k
            2. 对于负数，想映射到 [0,k) , 可以( (nums[i]%k)+k ) % k
        
        我们开一个hashmap, 是mp，
        令t = mp[i]表示， 有t个数之间的差为 k*n,
        他们组成了 C_t^{2} 个情况， 即 t*(t-1)/2 个情况
        
        然后对于mp[0]， 即有mp[0]个元素可以被k整除，他们本身就可以让k整除，
        所以mp[0]的情况是  mp[0]*(mp[0]-1)/2 + mp[0]
*/

class Solution {
public:
    int subarraysDivByK(vector<int>& A, int K) {
        vector<int> mp(K,0);
        int presum = 0, res=0;
        for ( int i=0; i<A.size(); ++i ){
            presum += A[i];
            mp[ (presum%K + K)%K ]++;
        }
        for ( auto e:mp )
            res += (e*(e-1)/2);
        return res+mp[0];
    }
};