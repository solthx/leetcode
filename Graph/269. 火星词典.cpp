/*
    问题描述:
        现有一种使用字母的全新语言，这门语言的字母顺序与英语顺序不同。
        假设，您并不知道其中字母之间的先后顺序。但是，会收到词典中获得一个 不为空的 单词列表。因为是从词典中获得的，所以该单词列表内的单词已经 按这门新语言的字母顺序进行了排序。
        您需要根据这个输入的列表，还原出此语言中已知的字母顺序。

        示例 1：

        输入:
            [
                "wrt",
                "wrf",
                "er",
                "ett",
                "rftt"
            ]

        输出: "wertf"
        示例 2：

        输入:
            [
                "z",
                "x"
            ]

        输出: "zx"
        示例 3：

        输入:
            [
                "z",
                "x",
                "z"
            ] 

        输出: "" 

        解释: 此顺序是非法的，因此返回 ""。
        注意：

        你可以默认输入的全部都是小写字母
        假如，a 的字母排列顺序优先于 b，那么在给定的词典当中 a 定先出现在 b 前面
        若给定的顺序是不合法的，则返回空字符串即可
        若存在多种可能的合法字母顺序，请返回其中任意一种顺序即可

    问题分析：
        这题的难点就在于“正确理解题意”
        开玩笑的。。 这里说的有序是指单词之间有序，而不是单词内部有序
        可以根据单词的前后关系来建立一个依赖图，
        例如"wrt"在"wrf"的前面， 那么‘t’就小于‘f’, t->f
        而如果"wrf"在"wrc"的前面，我们只要建立依赖 f->c就行了，不需要在建立t->c
        因为这个依赖关系是可传递的。

        建立完依赖关系图后，做一个拓扑排序就行了。 
        这里注意，因为有可能有些字母根本没出现在依赖关系图里， 最后记得把他们也丢进返回的string里 
        
*/

class Solution {
public:
    string alienOrder(vector<string>& words) {
        unordered_map<int, set<int>> mp;
        vector<int> indegree( 26, -1 );
        vector<bool> finish( 26, false );
        // 看有哪些字母
        for ( auto s:words )
            for ( auto c:s ){
                finish[c-'a'] = true;
                indegree[c-'a'] = 0;
            }
        // 图的构建
        for ( int i=1; i<words.size(); ++i ){
            int j = 0;
            while( j<words[i-1].size() && j<words[i].size() && words[i-1][j]==words[i][j] ) ++j;
            if ( j>=words[i-1].size() || j>=words[i].size() ) continue;
            if ( mp[words[i-1][j]-'a' ].count( words[i][j]-'a' )==0 ){
                mp[words[i-1][j]-'a' ].insert( words[i][j]-'a' );
                indegree[words[i][j]-'a']+=1;
            }
        }
        
        // topsort
        queue<int> q;
        for ( int i=0; i<26; ++i )
            if ( indegree[i]==0 )
                q.push(i);
        
        string res="";
        while( !q.empty() ){
            int cur = q.front(); q.pop();
            finish[cur] = false;
            res += (char)(cur+'a');
            for ( auto e:mp[cur] )
                if ( --indegree[e]==0 ) 
                    q.push(e);
        }
       
        for ( int i=0; i<26; ++i )
            if ( finish[i]==true )
                if ( indegree[i]>0 ) return "";
                else res += (char)(i+'a');
        return res;
    }
};