/*
    问题描述:
        给定一个正整数数组 w ，其中 w[i] 代表位置 i 的权重，请写一个函数 pickIndex ，它可以随机地获取位置 i，选取位置 i 的概率与 w[i] 成正比。

        说明:

        1 <= w.length <= 10000
        1 <= w[i] <= 10^5
        pickIndex 将被调用不超过 10000 次
        示例1:

        输入: 
        ["Solution","pickIndex"]
        [[[1]],[]]
        输出: [null,0]
        示例2:

        输入: 
        ["Solution","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex"]
        [[[1,3]],[],[],[],[],[]]
        输出: [null,0,1,1,1,0]
        输入语法说明：

        输入是两个列表：调用成员函数名和调用的参数。Solution 的构造函数有一个参数，即数组 w。pickIndex 没有参数。输入参数是一个列表，即使参数为空，也会输入一个 [] 空列表。

    问题分析:
        按权重的随机选择 => Pi = wi / sum{w}
        
        可以将权重总和的值 抽象成一段区间， 然后每一种情况占有的权重wi 就是这个总区间上的一段..

        因此，权重越大， 占的区间就越大， 值落入这个区间的概率就越大..

        因此， 做完上面的这种抽象之后， 我们把区间分成了一段一段的.. 
        
        每一段区间对应一个情况.. 区间长度为wi ， 总区间长度为sum{w}

        随机在区间上产生一个点， 看这个点落在哪个区间里.. 落在哪个区间，就取对应区间的情况..

        因此，可以用前缀和的形式来对上面的区间进行建模， 在找随机产生的点落在哪个区间上的时候，
        可以使用二分查找来做..
*/

class Solution {
public:
    vector<int> w;
    Solution(vector<int>& W) {
        this->w = W;
        for ( int i=1; i<w.size(); ++i )
            w[i] += w[i-1];
    }
    
    int pickIndex() {
        double rd = ((double)rand() / RAND_MAX) * w.back();
        int l = 0 , r = (int)w.size()-1;
        while( l<=r ){
            int mid = l + (r-l)/2;
            if ( (double)w[mid]<rd )  l = mid +1 ;
            else if ( (double)w[mid]>rd ) r= mid -1;
            else return mid;
        }
        return l;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(w);
 * int param_1 = obj->pickIndex();
 */

