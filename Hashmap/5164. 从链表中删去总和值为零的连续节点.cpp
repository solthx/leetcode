/*
    问题描述:
        给你一个链表的头节点 head，请你编写代码，反复删去链表中由 总和 值为 0 的连续节点组成的序列，直到不存在这样的序列为止。
        删除完毕后，请你返回最终结果链表的头节点。

        你可以返回任何满足题目要求的答案。
        （注意，下面示例中的所有序列，都是对 ListNode 对象序列化的表示。）

        示例 1：
            输入：head = [1,2,-3,3,1]
            输出：[3,1]
            提示：答案 [1,2,1] 也是正确的。
        
        示例 2：
            输入：head = [1,2,3,-3,4]
            输出：[1,2,4]
        
        示例 3：
            输入：head = [1,2,3,-3,-2]
            输出：[1]
        

        提示：
            给你的链表中可能有 1 到 1000 个节点。
            对于链表中的每个节点，节点的值：-1000 <= node.val <= 1000.

    问题分析:
        连续的节点可以理解成连续区间，
        然后就变成区间和为0的为题了， 果断hashmap
        <int, ListNode*> 表示从开头到ListNode*的位置的区间和为int
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
    ListNode* removeZeroSumSublists(ListNode* head) {
        if ( !head ) return NULL;
        ListNode * dummy = new ListNode(-1);
        dummy->next = head; // 加个头节点，方便从0开始
        bool finish=false;
        while( helper(dummy) );
        return dummy->next;
    }
    
    // 当删掉一段和为0的区间时，返回true
    // 当不存在和为0的区间时，返回false
    bool helper( ListNode* head ){
        bool res=false;
        map<int, ListNode*> mp;
        mp[0] = head;
        int curSum=0;
        ListNode * p = head->next;
        while( p!=NULL ){
            curSum += p->val;
            if ( mp.count(curSum)>0 ){
                ListNode * cur = mp[curSum];
                ListNode * sav = cur->next;
                cur->next = p->next;
                p->next = NULL;
                cur = sav;
                return true;
            }
            mp[curSum] = p;
            p = p->next;
        }
        return false;
    }
};