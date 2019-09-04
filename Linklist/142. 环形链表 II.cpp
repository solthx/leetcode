/*
    问题描述:
        https://leetcode-cn.com/problems/linked-list-cycle-ii/

    问题分析:
        快慢指针来判断是否存在环， fast和slow在环内某一点相遇，
        可以看另外一题: https://github.com/solthx/leetcode/tree/master/Array/287.%20%E5%AF%BB%E6%89%BE%E9%87%8D%E5%A4%8D%E6%95%B0
        
        这次要记录的是另一个更加直观的理解，
        fast走两步相当于slow走一步, 
        所以 fast相当于走了 两个 "slow走的路程",
        然后他们却在同一点相遇,
        因此， fast从相遇位置的下一个位置开始， slow从第一个元素开始，同时开始走，一定会在入环处相遇! 
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
    ListNode *detectCycle(ListNode *head) {
        //快慢指针
        if ( !head ) return NULL;
        ListNode * fast = head->next, *slow = head;
        while( fast && slow && fast!=slow ){
            slow = slow->next;
            fast = fast->next;
            if ( fast ) fast=fast->next;
        }
        if ( fast!=slow ) return NULL;
        slow = slow->next;
        while( head!=slow ){
            head = head->next;
            slow = slow->next;
        }
        return head;
    }
};