/*
    问题描述：
        返回与给定的前序和后序遍历匹配的任何二叉树。
         pre 和 post 遍历中的值是不同的正整数。

        示例：

        输入：pre = [1,2,4,5,3,6,7], post = [4,5,2,6,7,3,1]
        输出：[1,2,3,4,5,6,7]
         

        提示：

        1 <= pre.length == post.length <= 30
        pre[] 和 post[] 都是 1, 2, ..., pre.length 的排列
        每个输入保证至少有一个答案。如果有多个答案，可以返回其中一个。

    问题分析:
        前序遍历是 根左右， 即自定向下的，也就是右边的节点都在当前节点的下面.
        而后续遍历 是左右根， 与前序遍历正好相反， 当前节点左边的节点，都是在当前节点的上面.

        根据这个特征，可以用前序遍历来确定根节点rt， 然后在后续遍历中找到根rt的位置idx， 这个位置idx左边的所有元素都在当前确定的这个根
        的下面, 即: 如果在idx的左边的所有节点，都已经作为根确定过了，或者idx==0， 那么说明当前节点的下面的所有节点都已经被确定了，那么就可以确定当前节点的位置了，
        我们通过vis数组来记录某一节点是否被确定下来了， 用分治的方法，把所有节点都给全都下来，复杂度为O(NlogN)
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
    bool vis[31]={false};
    TreeNode* constructFromPrePost(vector<int>& pre, vector<int>& post) {
        int i = 0;
        return helper( i, pre, post,0, (int)post.size()-1 );
    }

    // i为当前需要确定的节点在前序遍历中的位置, l和r确定了当前区间的范围(算是个剪枝吧)
    TreeNode* helper( int & i, vector<int>& pre, vector<int>& post, int l, int r ){
        if ( i>=pre.size() ) return NULL; 
        int idx, rt = pre[i];
        // 在后续遍历中找到根节点的位置
        for ( int t=l; t<=r; ++t ){
            if ( post[t]==rt ){
                idx=t;
                break;
            }
        }
        // 这个位置是第一次访问，所以一定还没被确定
        TreeNode * cur = new TreeNode(rt);
        vis[idx] = true; // 当前节点的位置已经被确定了！
        // 如果idx==0 或是 前面的前点都被确定了， 就直接返回了(左右孩子都是null）（ 如果前一个位置被确定了，那说明都被确定了.
        if ( idx==0 || vis[idx-1]==true ) return cur;
        // 否则递归的往下搞
        cur->left = helper( ++i, pre, post, l, idx );
        cur->right = vis[idx-1]?NULL:helper( ++i, pre, post, l, idx );
        return cur;
    }
};