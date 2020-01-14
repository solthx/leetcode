/*
    问题描述:
        给定一个不含重复单词的列表，编写一个程序，返回给定单词列表中所有的连接词。

        连接词的定义为：一个字符串完全是由至少两个给定数组中的单词组成的。

        示例:

        输入: ["cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"]

        输出: ["catsdogcats","dogcatsdog","ratcatdogcat"]

        解释: "catsdogcats"由"cats", "dog" 和 "cats"组成; 
            "dogcatsdog"由"dog", "cats"和"dog"组成; 
            "ratcatdogcat"由"rat", "cat", "dog"和"cat"组成。
        说明:

        给定数组的元素总数不超过 10000。
        给定数组中元素的长度总和不超过 600000。
        所有输入字符串只包含小写字母。
        不需要考虑答案输出的顺序。


    问题分析:
        妥妥的字典树, 把每一个单词都插入到树里， 然后遍历每一个单词，检查这个单词能否由树中的两个或两个以上的单词组成，
        树的结点记录的信息是，当前位置是否是一个单词的结尾,
        然后暴力枚举每一个个可能的前缀，例如 catsdogcats:
            c  -> atsdogcats
            ca -> tsdogcats
            cat -> sdogcats
            cats -> dogcats -> cats, d  -> ogcats
                            -> cats, do -> gcats
                            -> cats, dog-> cats -> cats, dog, c-> ats
                                                -> ...
                                                -> cats, dog, cats ✅
        
        思路很简单，实现的具体细节用注释写上了.
*/

class Solution {
public:
    struct tri_node{
        tri_node * children[26];
        bool isOver;
        tri_node(){
            for ( int i=0; i<26; ++i )
                children[i] = nullptr;
            isOver = false;
        }
    };
    
    void insert( tri_node * rt, string s ){
        if ( !rt ) return;
        int i=0;
        while( i<s.size() ){
            if ( !rt->children[s[i]-'a'] )
                rt->children[s[i]-'a'] = new tri_node();
            rt = rt->children[s[i]-'a'];
            ++i;
        }
        rt->isOver = true; // 这个位置是否是一个单词的结尾
    }
    
    // 返回word是由几个单词组成
    int check( tri_node * rt, string word ){
        tri_node * root = rt;
        // 由0个单词组成
        if ( !rt || word.size()==0 ) return 0;
        int i=0;
        while( i<word.size() && rt->children[word[i]-'a'] ){
            rt = rt->children[word[i]-'a'];
            // word[0~i]可以组成一个单词
            if ( rt->isOver ){
                // word[i,n]由几个单词组成
                int cnt = check( root, word.substr(i+1) );
                // 如果由1个及其以上单词组成，就一定是连接词，直接返回个数
                if ( cnt>0 ) return cnt+1; 
            }
            ++i;
        }
        // i<word.size()当前trie里无法构成word， 返回0
        // i>=word.size() 那么说明word已经找完， 如果当前节点位置是一个单词的末尾，那么返回1，否则返回0.. （例如在 ["abcd"]里找abc，显然在"c"这个位置虽然是"abc"的最后一个,  但trie里只有"abcd"
        if ( i<word.size() ) return 0;
        return rt->isOver;
    }
    
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        tri_node * root = new tri_node;
        vector<string> res;
        for ( auto word:words )
            insert(root, word);
        for ( auto word:words ){
            if ( check(root, word)>1 ) // 如果由一个及以上单词组成 就压入结果集
                res.push_back(word);
        }
        return res;
    }
};