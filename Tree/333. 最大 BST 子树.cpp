/*
    问题描述:   
        给定一个二叉树，找到其中最大的二叉搜索树（BST）子树，其中最大指的是子树节点数最多的。
        注意:
            子树必须包含其所有后代。

        示例:

            输入: [10,5,15,1,8,null,7]

            10 
           / \ 
          5  15 
         / \   \ 
        1   8   7

        输出: 3
        解释: 高亮部分为最大的 BST 子树。
            返回值 3 在这个样例中为子树大小。
        进阶:
            你能想出用 O(n) 的时间复杂度解决这个问题吗？

    问题分析:
        暴力的方法就不多说，这里主要介绍O(N)解法
        
        列举出几种情况，可以发现，如果一旦子树不是bst了，那么这颗树的祖宗们都可以不用考虑了.

        所以，我们可以自底向上的，利用后续遍历来做.

        当我们处于节点r的时候， 

        if r->left is bst && max( 左子树r->left) < r->val
        && r->right是bst && min( 右子树r->right ) > r->val 
        那么就可以 r 就是bst， r的节点数就是左子树节点数+右子树节点数+1

        从上面我们可以观察到， 在r节点位置，我们需要子树的三个情况:
            1. 子树最小值
            2. 子树最大值
            3. 子树节点数
        我们可以把这些状态放到vector里，然后写一个函数，来返回这些状态.
        这个函数就是helper， 返回节点r的状态

        我们可以规定:
            1. 如果子树是bst, 返回状态vector, 此时vector的size为3 (最小值，最大值，个数)
            2. 如果子树不是bst, 返回的状态vector为{-1}, size为1， 只要左右子树出现一个{-1}, 直接返回{-1}就行了
            3. 如果子树是空，返回状态vector为{}, size为0， 可以继续进行判断

        根据上面的想法，就可以coding了
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int res;
    int largestBSTSubtree(TreeNode* root) {
        if ( !root ) return 0;
        res = 1;
        helper( root );
        return res;
    }
    
    vector<int> helper( TreeNode* r ){
        if ( !r ) return {}; // 为空的情况
        if ( !r->left && !r->right ) return { r->val, r->val, 1 }; // 叶子节点
        auto lp = helper( r->left );
        auto rp = helper( r->right );
        if ( lp.size()==1 || rp.size()==1 ) return {-1}; // 不是bst
        if ( lp.size()==3 && rp.size()==3 ){ // 左右都不空
            // 根据状态进行处理
            if ( lp[1]<r->val && rp[0]>r->val ){
                int cnt = lp[2]+rp[2]+1;
                res = max( res, cnt );
                return { lp[0], rp[1], cnt };
            }else return {-1};
        }else if ( lp.size()==0 && rp.size()==3 ){ // 左空 右不空
            if ( r->val<rp[0] ){
                int cnt = rp[2]+1;
                res = max(  res, cnt);
                return {r->val, rp[1], cnt};
            }else return {-1};
        }else if (  rp.size()== 0 && lp.size()==3){ // 右空 左不空
            if ( r->val>lp[1] ){
                int cnt = lp[2]+1;
                res = max( res, cnt);
                return { lp[0], r->val, cnt};
            }else return {-1};
        }
        return {-1}; // 其他情况均不合法
    }
};
