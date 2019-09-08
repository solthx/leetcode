/*
    问题描述:
        给定一个链表，每个节点包含一个额外增加的随机指针，该指针可以指向链表中的任何节点或空节点。
    要求返回这个链表的深拷贝。 

    示例：
    输入：
        {"$id":"1","next":{"$id":"2","next":null,"random":{"$ref":"2"},"val":2},"random":{"$ref":"2"},"val":1}

    解释：
        节点 1 的值是 1，它的下一个指针和随机指针都指向节点 2 。
        节点 2 的值是 2，它的下一个指针指向 null，随机指针指向它自己。
     
    提示：
        你必须返回给定头的拷贝作为对克隆列表的引用。

    问题分析:
        方法一:
            哈希表
            用hashmap保存在同一个位置上，原始节点和新建节点的映射.
            然后再构造深拷贝.

        方法二:
            有丝分裂法.
            这种思想也很棒.
            就是对于这种链表的深拷贝,
            分为以下几步:
                1. 对每一个节点进行复制，即： 1->2->3 复制后变成 1->1->2->2->3->3
                2. cur->next->random = cur->random->next 
                    因为每个节点后面就是每个节点的拷贝份
                    所以，利用这个特性，来对每一个拷贝份进行连接更新
                3. 切断，即把原始链表和复制后的备份的链表进行分离.
*/

// 法一: 哈希表法
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if ( !head ) return NULL;
        unordered_map<Node*, Node*> mp;
        Node * cur = head;
        Node * dummy = new Node();
        Node * last = dummy;
        while( cur ){
            Node * tp = new Node();
            tp->next = NULL;
            tp->val = cur->val;
            last->next = tp;
            last = tp;
            mp[cur] = tp;
            cur = cur->next;
        }
        cur = head;
        last = dummy->next;
        while( cur ){
            last->random = mp[cur->random];
            last = last->next;
            cur = cur->next;
        }
        return dummy->next;
    }
};

// 法二: 有丝分裂法
class Solution {
public:
    Node* copyRandomList(Node* head) {
        // 空间O(1)， 有丝分裂法
        if ( !head ) return NULL;
        Node * cur = head;
        while( cur ){
            Node * tp = new Node( cur->val, cur->next, NULL );
            cur->next = tp;
            cur = tp->next;
        }
        cur = head;
        while( cur ){
            if ( cur->random )
                cur->next->random = cur->random->next;
            cur = cur->next;
            if ( cur ) cur = cur->next;
        }
        cur = head;
        Node * res = cur->next;
        Node * nxt = cur->next;
        while( nxt ){
            cur->next = nxt->next;
            cur = nxt;
            nxt = cur->next;
        }
        return res;
    }
};
