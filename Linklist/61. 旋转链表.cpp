/*
    问题描述:
        给定一个链表，旋转链表，将链表每个节点向右移动 k 个位置，其中 k 是非负数。
        示例 1:

            输入: 1->2->3->4->5->NULL, k = 2
            输出: 4->5->1->2->3->NULL
            解释:
            向右旋转 1 步: 5->1->2->3->4->NULL
            向右旋转 2 步: 4->5->1->2->3->NULL

    问题分析：
        方法一:
            类似旋转数组那样， 翻转前 n-k个，然后翻转后k个，然后翻转整个.

        方法二:
            旋转链表的的话，直接通过修改指针就行了，其实没必要翻转= =..
*/

class Solution1 {
public:
    // 通过翻转来实现
    ListNode* rotateRight(ListNode* head, int k) {
        int len = get_length( head );
        if ( len==0 || k==0 ) return head;
        k = k%len;
        ListNode * cur=head;
        int step = len - k - 1;
        while( step-- )
            cur = cur->next;
        reverse( cur ); //翻转cur之后的节点
        ListNode * sav= cur->next;
        ListNode * dummy = new ListNode(-1);
        dummy->next = head;
        cur->next = NULL;
        ListNode * tail = reverse( dummy );
        tail->next = sav;
        reverse( dummy );
        return dummy->next;
    }
    
    ListNode * reverse( ListNode* dummy ){
        // 头插法
        ListNode * res =dummy->next;
        ListNode * cur = dummy->next, *sav;
        dummy->next = NULL;
        while( cur ){
            sav = cur->next; 
            cur->next = dummy->next;
            dummy->next = cur;
            cur = sav;
        }
        return res;
    }
    
    int get_length( ListNode* cur ){
        int res=0;
        while( cur ){
            ++res;
            cur = cur->next;
        }
        return res;
    }
};

/*========================Solution2===========================*/
class Solution2 {
public:
    // 直接修改指针指向
    ListNode* rotateRight(ListNode* head, int k) {
        int len=0;
        for ( ListNode* node = head; node!=NULL; node=node->next )
            ++len;
        if ( len<=1 || k==0 ) return head;
        k %= len;
        int step = len - k - 1;
        ListNode *first = head;
        while( step-- ) first = first->next;
        ListNode * res = first;
        ListNode * cur = first;
        while( cur->next!=NULL ) cur = cur->next;
        cur->next = head;
        ListNode * t = res->next;
        res->next=NULL;
        return t;
    }
};
