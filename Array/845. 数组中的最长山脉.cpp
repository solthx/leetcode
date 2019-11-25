/*
    问题描述:
        我们把数组 A 中符合下列属性的任意连续子数组 B 称为 “山脉”：

        B.length >= 3
        存在 0 < i < B.length - 1 使得 B[0] < B[1] < ... B[i-1] < B[i] > B[i+1] > ... > B[B.length - 1]
        （注意：B 可以是 A 的任意子数组，包括整个数组 A。）

        给出一个整数数组 A，返回最长 “山脉” 的长度。

        如果不含有 “山脉” 则返回 0。

         

        示例 1：

        输入：[2,1,4,7,3,2,5]
        输出：5
        解释：最长的 “山脉” 是 [1,4,7,3,2]，长度为 5。
        示例 2：

        输入：[2,2,2]
        输出：0
        解释：不含 “山脉”。
         

        提示：

        0 <= A.length <= 10000
        0 <= A[i] <= 10000

    问题分析:
        方法一:
            双指针.. 找到山峰点，然后向两边扫描，比较简单。。就不多说了。。

        方法二:
            思想类似 #376 摆动序列那题 (https://github.com/solthx/leetcode/blob/master/Array/376.%20%E6%91%86%E5%8A%A8%E5%BA%8F%E5%88%97.cpp).

            即用变量up来记录上升或者下降的状态， 然后根据数组 当前的上下坡状态(A[i]和A[i-1]比较大小)和之前的上下坡状态(由变量up来记录)， 
            最终来确定，当前位置处于什么状态, 一共有以下几个情况:
                1. 之前在上坡， 现在依然处于上坡.
                2. 之前在下坡， 现在依然处于下坡.
                3. 之前处于上坡，现在开始了下坡
                4. 之前处于下坡，现在开始了上坡
                5. 之前处于下坡，现在是平地( 相等的情况 )
                6. 之前处于上坡，现在是平地( 相等的情况 )
            
            用一个变量来记录当前的山脉长度:
                1,2 的情况都是仅仅对长度加1
                3 的情况不仅要对长度加1 ，还需要改变up状态
                4，5，6 都是代表已经找完了山脉的情况:
                    4,5 的情况是可以更新 res的
                    6 的情况是不可能更新res 的 ， 因为山脉的结束，一定是以下坡为结束
            
            然后可以coding了。
            需要注意的是， i-1是山脉起使的位置， 因此在4，5的情况中，更新完res，那么上一个山脉的最后一个位置，有可能是下一个山脉的起使位置，因此对于4, 5的情况，需要回溯一个位置
*/

class Solution2 {
public:
    int longestMountain(vector<int>& A) {
        int res=0, length = 1;
        bool up = true;
        for ( int i=1; i<A.size(); ++i ){
            if ( (A[i]>A[i-1] && up) || (A[i-1]>A[i] && !up ) ){
                // 上升的情况和下降的情况
                ++length;
            }else if ( A[i-1]-A[i]>0 && up && length>1 ){
                // 上升转下坡
                up = false;
                ++length;
            }else {
                // 其他情况
                /*
                    1. 上升的情况下，相等了；
                    2. 下降的情况下，相等了； 
                    3. 下降转上升
                */
                if ( !up ){ // 只要是下降，就可以更新
                    res = max(res, length);
                    --i;  //因为下坡的最后一个位置，可能是下一次上坡的第一个位置， 所以回溯一个位置
                }
                up = true;
                length = 1;
            }
        }
        if ( !up )
            res = max( res, length );
        return res==1?0:res;

    }
};


class Solution1 {
public:
    int longestMountain(vector<int>& A) {
        int i=1, res=0; 
        while( i+1<A.size() ){
            int l = i;
            int r = i;
            while( l>0 && A[l-1]<A[l] ) --l;
            while( r+1<A.size() && A[r]>A[r+1] ) ++r; 
            if ( l!=i && r!=i )
                res = max( res, r-l+1 );
            i = r+1;
        }
        return res;
    }
};