/*
    问题描述:
        实现一个 Trie (前缀树)，包含 insert, search, 和 startsWith 这三个操作。
        示例:
            Trie trie = new Trie();

            trie.insert("apple");
            trie.search("apple");   // 返回 true
            trie.search("app");     // 返回 false
            trie.startsWith("app"); // 返回 true
            trie.insert("app");   
            trie.search("app");     // 返回 true

        说明:
            你可以假设所有的输入都是由小写字母 a-z 构成的。
            保证所有输入均为非空字符串。

    问题分析:
        https://blog.csdn.net/lisonglisonglisong/article/details/45584721
        本题是模版题
*/

class Trie {
public:
    /** Initialize your data structure here. */
    struct tri_node{
        int count; 
        tri_node * children[26];
    };
    
    tri_node * create_node(  ){
        tri_node * res = new tri_node();
        res->count = 0;
        for ( int i=0; i<26; ++i )
            res->children[i] = NULL;
        return res;
    } 
    /** Inserts a word into the trie. */
    void insert(string word) {
        tri_node * p = root;
        int i=0;
        for ( auto &c:word ){
            if ( p->children[c-'a']==NULL )
                 p->children[c-'a'] = create_node();
            p = p->children[c-'a'];
        }
        p->count+=1;
    }
    
    tri_node * root;
    
    Trie() {
        root = create_node();    
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        tri_node * p = root;
        int i=0;
        for ( auto & c:word ){
            if ( p->children[c-'a']==NULL ) return false;
            p = p->children[c-'a']; // p一定不是null
        }
        // word是曾经出现过的单词的前缀的时候， p->count为0
        return p->count>0;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string word) {
        tri_node * p = root;
        int i=0;
        while( i<word.size() && p ){
            if ( p->children[word[i]-'a']==NULL ) return false;
            p = p->children[word[i]-'a'];
            ++i;
        }
        return i>=word.size();
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */