/*
    问题描述：
        给一个嵌套整数序列，请你返回每个数字在序列中的加权和，它们的权重由它们的深度决定。

        序列中的每一个元素要么是一个整数，要么是一个序列（这个序列中的每个元素也同样是整数或序列）。

        与 前一个问题 不同的是，前一题的权重按照从根到叶逐一增加，而本题的权重从叶到根逐一增加。

        也就是说，在本题中，叶子的权重为1，而根拥有最大的权重。

        示例 1:

        输入: [[1,1],2,[1,1]]
        输出: 8 
        解释: 四个 1 在深度为 1 的位置， 一个 2 在深度为 2 的位置。
        示例 2:

        输入: [1,[4,[6]]]
        输出: 17 
        解释: 一个 1 在深度为 3 的位置， 一个 4 在深度为 2 的位置，一个 6 在深度为 1 的位置。 1*3 + 4*2 + 6*1 = 17。

    问题分析：
        方法一:
            通过先计算最大深度len， 然后用 (len+1 - 当前深度)来作为权重，就可以了..


        方法二：
            这里记录一个比较棒的思想。。

            例如，如果从上往下走，但每层的权重倍数却是从下往上算，
            
            那么可以用累加和的形式来实现这个，

            每向下走一层，就加一次上一层得到的数，这样就会变成往下走了几层就加了几次，

            完美地做了一个转换.

*/
class Solution1 {
public:
    int depthSumInverse(vector<NestedInteger>& nestedList) {
        int len = getLen( nestedList);
        return helper( nestedList, len, 1 );
    }
    int getLen( vector<NestedInteger>& nest ){
        int len = 1;
        for ( auto e:nest )
            if ( !e.isInteger() )
                len = max( len, getLen( e.getList() ));
        return len+1;
    }
    int helper( vector<NestedInteger>& nestedList, int  w, int d ){
        int res = 0;
        int ww = w-d;
        for ( auto e:nestedList ){
            if ( e.isInteger() ) res += e.getInteger()*ww;
            else res += helper( e.getList(), w, d+1 );
        }
        return res;
    }
};


class Solution2 {
public:
    int depthSumInverse(vector<NestedInteger>& nest) {
        int unweighted = 0;
        int res = 0;
        while( nest.size()>0 ){
            vector<NestedInteger> cur;
            for ( auto e:nest ){
                if ( e.isInteger() ) unweighted += e.getInteger();
                else cur.insert( cur.end(), e.getList().begin(), e.getList().end() );
            }
            res += unweighted;
            nest = cur;
        }
        return res;
    }
};

/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Constructor initializes an empty nested list.
 *     NestedInteger();
 *
 *     // Constructor initializes a single integer.
 *     NestedInteger(int value);
 *
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Set this NestedInteger to hold a single integer.
 *     void setInteger(int value);
 *
 *     // Set this NestedInteger to hold a nested list and adds a nested integer to it.
 *     void add(const NestedInteger &ni);
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */