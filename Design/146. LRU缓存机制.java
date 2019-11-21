/*
    问题描述:
        运用你所掌握的数据结构，设计和实现一个  LRU (最近最少使用) 缓存机制。它应该支持以下操作： 获取数据 get 和 写入数据 put 。

        获取数据 get(key) - 如果密钥 (key) 存在于缓存中，则获取密钥的值（总是正数），否则返回 -1。
        写入数据 put(key, value) - 如果密钥不存在，则写入其数据值。当缓存容量达到上限时，它应该在写入新数据之前删除最近最少使用的数据值，从而为新的数据值留出空间。

        进阶:

        你是否可以在 O(1) 时间复杂度内完成这两种操作？

        示例:

        LRUCache cache = new LRUCache( 2 ); // 2为缓存容量

        cache.put(1, 1);
        cache.put(2, 2);
        cache.get(1);       // 返回  1
        cache.put(3, 3);    // 该操作会使得密钥 2 作废
        cache.get(2);       // 返回 -1 (未找到)
        cache.put(4, 4);    // 该操作会使得密钥 1 作废
        cache.get(1);       // 返回 -1 (未找到)
        cache.get(3);       // 返回  3
        cache.get(4);       // 返回  4

    问题分析:
        直接说最优解法的思想好了: hashmap + 双向链表

        hashmap存储: key->链表节点  和 key->value 的映射
        
        双向链表: 表头位置保存最久未使用， 表尾位置保存刚使用过的。
        每次访问一个节点，都把这个节点给挪到表尾。
        
        思想就是这个思想，多实现几次吧。。 毕竟是超超超高频考点。
 */

class LRUCache {
    private final class Node {
        int val;
        Node prev, next;

        Node(int v, Node p, Node nxt) {
            val = v;
            prev = p;
            next = nxt;
        }

        Node() {
        }
    }

    // 维护一个双向链表 + hashmap
    // 超过容量而需要删除的时候，就把头节点删了
    HashMap<Integer, Integer> mp = new HashMap<>(); // key->value
    HashMap<Integer, Node> node_mp = new HashMap<>(); // key->node
    Node head;
    int capacity = 0;

    public LRUCache(int capacity) {
        this.capacity = capacity;
        head = new Node();
        head.prev = head;
        head.next = head;
    }

    private Node removeNode(Node node) {
        node.prev.next = node.next;
        node.next.prev = node.prev;
        return node;
    }

    public int get(int key) {
        if (!mp.containsKey(key))
            return -1;
        int res = mp.get(key);
        removeNode(node_mp.get(key));
        Node cur = new Node(key, null, null);
        addLast(cur);
        node_mp.put(key, cur);
        return res;
    }

    void addLast(Node node) {
        if (node == null)
            return;
        Node pre = head.prev;
        node.prev = pre;
        node.next = head;
        node.prev.next = node;
        node.next.prev = node;
    }

    public void put(int key, int value) {
        if (mp.size() == capacity && !mp.containsKey(key)) {
            int d = head.next.val;
            removeNode(head.next);
            mp.remove(d);
            node_mp.remove(d);
        }
        if (mp.containsKey(key)) {
            mp.put(key, value);
            get(key);
        } else {
            mp.put(key, value);
            Node cur = new Node(key, null, null);
            addLast(cur);
            node_mp.put(key, cur);
        }

    }
}

/**
 * Your LRUCache object will be instantiated and called as such: LRUCache obj =
 * new LRUCache(capacity); int param_1 = obj.get(key); obj.put(key,value);
 */