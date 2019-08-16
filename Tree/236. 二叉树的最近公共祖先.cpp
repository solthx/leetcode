/*
    问题描述:
        给一个树根和两个节点，找这两个节点的最近公共祖先

    问题分析:
        后序遍历，去左子树找，找不到就返回NULL
                去右子树找，找不到就返回NULL
        从下向上，返回第一个左右子树的查找结果都不为空的结果。
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
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if ( !root || root==p || root==q ) return root;
        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);    
        if ( left && right ) return root;
        return left?left:right;
    }
    
};