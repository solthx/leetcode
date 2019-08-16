/*
    问题描述：
        给一个有序链表，用它来构造一个二叉搜索树

    问题分析:
        构造二叉搜索树就是在有序序列里不停的找中点的过程，
        这里通过快慢指针来找到一个子序列的中点，
        记录终点，然后把当前链表切成两段，递归构建
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
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
    TreeNode* sortedListToBST(ListNode* head) {
        if ( !head ) return NULL;
        if ( !head->next ) return new TreeNode(head->val);
        ListNode*fast=head->next, *slow=head, *pre_slow=NULL;
        while( fast ){
            pre_slow = slow;
            slow = slow->next;
            fast = fast->next;
            if ( fast ) fast = fast->next;
        }
        pre_slow->next = NULL;
        TreeNode * root = new TreeNode(slow->val);
        root->left = sortedListToBST(head);
        root->right = sortedListToBST(slow->next);
        return root;
    }
};