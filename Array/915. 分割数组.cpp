/*
    问题描述:
        给定一个数组 A，将其划分为两个不相交（没有公共元素）的连续子数组 left 和 right， 使得：

        left 中的每个元素都小于或等于 right 中的每个元素。
        left 和 right 都是非空的。
        left 要尽可能小。
        在完成这样的分组后返回 left 的长度。可以保证存在这样的划分方法。

        示例 1：

            输入：[5,0,3,8,6]
        输出：3
            解释：left = [5,0,3]，right = [8,6]
        
        示例 2：
            输入：[1,1,1,0,6,12]
            输出：4
            解释：left = [1,1,1,0]，right = [6,12]
         

        提示：
            2 <= A.length <= 30000
            0 <= A[i] <= 10^6
            可以保证至少有一种方法能够按题目所描述的那样对 A 进行划分。


    问题分析：
        方法一:
            时间复杂度O(N)
            空间复杂度O(N) 
            开个数组，记录右边的最大值... 开个变量记录左边最小值.. 没啥好说的..
        
        方法二:
            时间复杂度O(N)
            空间复杂度O(1)
            一次遍历
            
            左边每个元素小于等于右边的每个元素
         => 左边最大值 小于等于 右边最小值
         => 因此，可以用贪心的思想， 假设cut的位置在i ( cut左边的元素都小于等于右边的元素 ), 然后从左往右扫描数组，
            设上一次cut的位置为i， 从左往右扫描的当前位置为t，[0,i]的最大值为maxi， 对于t>i：
                1. 如果发现A[t]>=A[i]，那么没问题，因为我们要的就是对于每个t>i,A[t]>A[i].. 
                2. 如果发现A[t]<A[i]，那么cut的位置就不能在i处， 应该更新cut的位置，即更新到t， 然后更新maxi变为 [0,t]的最大值..
            扫描完之后，cut+1就是右区间的首个元素位置.. 

            思想... 算是 数学+分类讨论 吧..
*/

class Solution1 {
public:
    // 前缀数组
    int partitionDisjoint(vector<int>& A) {
        if ( A.size()==0 ) return 0;
        vector<int> dp(A.size()+1, INT_MAX);
        int r=(int)A.size()-1;
        while( r>=0 ){
            dp[r] = min( A[r], dp[r+1] );
            --r;
        }
        int cur = A[0];
        r = 0;
        while( r<A.size() ){
            cur = max( cur, A[r] );
            if ( cur<=dp[r+1] ) return r+1;
            ++r;  
        }
        return -1;
    }
};

class Solution2 {
public:
    // 一次遍历
    int partitionDisjoint(vector<int>& A) {
        if ( A.size()==0 ) return 0;
        int left_maxi = A[0], cut = A[0], pos=0, i = 0;
        while( i<A.size() ){
            left_maxi = max(left_maxi, A[i]);
            if ( A[i]<cut ){
                cut = left_maxi;
                pos = i;
            }
            ++i;
        }
        return pos+1;
    }
};