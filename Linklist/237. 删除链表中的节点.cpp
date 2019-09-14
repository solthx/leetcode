/*
    问题描述:
        给某个链表中的一个节点，删除这个节点.
    
    问题分析:
        删除某个节点的话，必须要知道这个节点的pre,
        然而这里不知道节点的pre, 
        所以可以转换一下思路，
        把下一个节点的值赋给当前值，然后删掉下一个节点.
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    void deleteNode(ListNode* node) {
        ListNode * p = node->next; // 记录下一个节点
        node->val = p->val;   // 把下一个节点的值赋值给当前值
        node->next = p->next;   // 删除下一个节点
        delete p;       // 释放掉内存
    }
};