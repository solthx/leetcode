/*
    问题描述:
        设计一个支持以下两种操作的数据结构：
            void addWord(word)
            bool search(word)
            search(word) 可以搜索文字或正则表达式字符串，字符串只包含字母 . 或 a-z 。 . 可以表示任何一个字母。

        示例:
            addWord("bad")
            addWord("dad")
            addWord("mad")
            search("pad") -> false
            search("bad") -> true
            search(".ad") -> true
            search("b..") -> true
        
        说明:
            你可以假设所有单词都是由小写字母 a-z 组成的。

    问题分析:
        search操作多了个正则表达式的'.'匹配，
        只要跳过'.'之后，后面的字符串再当前节点的任意一个子节点里匹配成功，就算匹配成功
*/

class WordDictionary {
public:
    struct tri_node{
        int count; 
        //vector<tri_node*> children;  
        tri_node * children[26];
    };
    
    tri_node * create_node(  ){
        tri_node * res = new tri_node();
        res->count = 0;
        //res->children.resize(26);
        for ( int i=0; i<26; ++i )
            res->children[i] = NULL;
        return res;
    } 
    
    tri_node * root;
    
    /** Initialize your data structure here. */
    WordDictionary() {
        root = create_node();
    }
    
    /** Adds a word into the data structure. */
    void addWord(string word) {
        tri_node * p = root;
        int i=0;
        while( i<word.size() ){
            if ( p->children[word[i]-'a']==NULL ){
                 p->children[word[i]-'a'] = create_node();
            }
            p = p->children[word[i]-'a'];
            ++i;
        }
        p->count+=1;
    }
    
    bool find( tri_node*r,  string word ){
        tri_node * p = r;
        int i=0;
        while( i<word.size() && p ){
            if ( word[i]!='.' ){
                if ( p->children[word[i]-'a']==NULL ){
                     p->children[word[i]-'a'] = create_node();
                }
                p = p->children[word[i]-'a'];
                ++i;
            }else{
                for ( auto e:p->children )
                    if ( e!=NULL && find( e,word.substr(i+1) ) )
                        return true;
                return false;
            }
        }
        if ( !p ) return i>=word.size();
        return i>=word.size() && p->count>0;
    }
    
    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
    bool search(string word) {
        return find( root, word );
    }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */