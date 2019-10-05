/*
    问题描述:
        编写一段程序来查找第 n 个超级丑数。
        超级丑数是指其所有质因数都是长度为 k 的质数列表 primes 中的正整数。

        示例:
            输入: n = 12, primes = [2,7,13,19]
            输出: 32 
            解释: 给定长度为 4 的质数列表 primes = [2,7,13,19]，前 12 个超级丑数序列为：[1,2,4,7,8,13,14,16,19,26,28,32] 。
        
        说明:
            1 是任何给定 primes 的超级丑数。
             给定 primes 中的数字以升序排列。
            0 < k ≤ 100, 0 < n ≤ 106, 0 < primes[i] < 1000 。
            第 n 个超级丑数确保在 32 位有符整数范围内。

    问题分析：
        丑数的这类题( 即找 只能由 [x1,x2,...,xn] 中的元素 相乘得到的数 (第一个丑数为1) )
        两种经典方法：
            1. 堆：  
                用1先初始化堆（第一个丑数是1）， 然后, 每次从里面拿出一个最小的mini,
                把 mini*x1, mini*x2, ... , 依次压入堆里,
                然后第k次弹出的元素，就是第k个丑数
                因为会由重复，所以还需要用set来去重

            2. Dp:
                从https://github.com/solthx/leetcode/blob/master/Math/264.%20%E4%B8%91%E6%95%B0II.java
                丑数II 可以知道，

                
                下一个丑数，一定是由[x1,x2,x3]里的一个数，乘上一个已经得到的丑数 (这样才能保证 这个丑数的因数 只存在于[x1,x2,x3]里)

                令丑数数组为 ugly[]

                下一个丑数就是 
                    for i from 1 to 3
                        min{ xi * ugly[?] }
                
                那么如何确定"?"的大小呢，

                假设只有 [x1,x2,x3]
                具体一点，假设 [2,3,5]
                
                观察下面的例子：
                    丑数数组 {1,2,3,4,5,6,8,9,10,...} 
                    
                    乘数是2  (1) <1x2>,  2x2,   2x2,   <3x2>, <4x2>,    5x2...
                    乘数是3  (2) 1x3  ,  <1x3>, 2x3,   <2x3>, 3x3,    <3x3>...
                    乘数是5  (3) 1x5  ,  1x5,   <1x5>, 1x5,   2x5,     3x5...
                
                不难发现， 
                给每一个xi 都分配一个idx游标， 它们都从0开始, 
                当第k个丑数，取 xi * ugly[idxi] 的时候（令其等于minik），
                那么就给在当前层中，所有 xj * ugly[idxj] == minik 的哪些idexj的大小都加1 ， 向后移一位. （这一步也就是去除重复)
                
                就这样，不断的用历史的ugly数组，来得到下一个ugly数
*/


// 动态规划
class Solution2 {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        int k = primes.size();
        vector<int> idx( k, 0 );
        int mini;
        vector<int> res = {1};
        for ( int i=0; i<n-1; ++i ){
            mini = INT_MAX;
            for ( int j=0; j<k; ++j ){
                if ( mini> res[idx[j]]*primes[j] ) 
                    mini = res[idx[j]]*primes[j];
            }
            for ( int j=0; j<k; ++j ){
                if ( mini==res[idx[j]]*primes[j] )
                    ++idx[j];
            }
            res.push_back(mini);
        }
        return res.back();
    }
};


class Solution {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        // 堆
        priority_queue<int, vector<int>, greater<int>> q;
        set<int> st;
        q.push(1);
        for ( auto e:primes ){ 
            q.push(e);
            st.insert( e );
        }
        while( --n ){
            int k = q.top(); q.pop();
            for ( auto e:primes ){
                if ( (long long)k*e<=INT_MAX && st.count(k*e)==0 ){
                    q.push(k*e);
                    st.insert(k*e);
                }
            }
        }
        return q.top();
    }
};