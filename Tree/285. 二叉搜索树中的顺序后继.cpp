/*
    问题描述:
        一个二叉搜索树, 给一个root和一个节点p，比p大的那个最小值的那个节点

    问题分析:
        这题不难, 但想几行代码搞定的话，还是需要分析一下的.
        利用bst的性质进行二分,
        如果当前节点比target大，那就记录当前节点后，然后去左子树找看有更小的么,
        如果当前节点比target小或等于当前节点, 那就去找比当前节点大的节点，就去右子树找.
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
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        TreeNode* res=NULL;
        while( root ){
            if ( root->val>p->val ){
                res = root;
                root = root->left;
            }else 
                root = root->right;
            }
        }
        return res;
    }
};