/*
    问题描述:
        给定多个 words，words[i] 的权重为 i 。

        设计一个类 WordFilter 实现函数WordFilter.f(String prefix, String suffix)。这个函数将返回具有前缀 prefix 和后缀suffix 的词的最大权重。如果没有这样的词，返回 -1。

        例子:

        输入:
        WordFilter(["apple"])
        WordFilter.f("a", "e") // 返回 0
        WordFilter.f("b", "") // 返回 -1
        注意:

        words的长度在[1, 15000]之间。
        对于每个测试用例，最多会有words.length次对WordFilter.f的调用。
        words[i]的长度在[1, 10]之间。
        prefix, suffix的长度在[0, 10]之前。
        words[i]和prefix, suffix只包含小写字母。

    问题分析:
        方法一:
            建两个字典树，一个保存前缀，一个保存后缀。
            叶子上保存以当前结点为前缀/后缀的单词编号, 

            查询操作，分别返回以xxx为前缀的 index集， 和以xxx为后缀的index集，

            因为插入是从小到大插的，所以这个index集是有序的。

            然后找同时出现在 前缀的index集和 后缀的index集中 最大的那个index..

            注意， 返回index集的时候，返回指针，不然会TLE（因为如果返回vector，那么每次都会创建一个vector开销会很大..

        方法二:
            建立一个字典树就可以了。。对于"apple"，就插入 
            "{apple",
            "e{apple",
            "le{apple",
            "ple{apple",
            "pple{apple",
            "apple{apple"
            查询前缀abc和后缀123， 就查询 abc{123 是否存在树中。。。

            用这个思想来做..  
*/

// 方法1 两个字典树 分别记录前缀和后缀
class WordFilter {
public:
    struct tri_node{
        tri_node * children[26];
        vector<int> st;
        tri_node(){
            for ( int i=0; i<26; ++i )
                children[i] = NULL;
        }
    };
    
    struct tri_node * suffix; // 后缀
    struct tri_node * prefix; // 前缀
    
    void insert( tri_node * rt, string s, int w ){
        int i=0;
        while( i<s.size() ){
            if ( rt->children[s[i]-'a']==NULL )
                rt->children[s[i]-'a'] = new tri_node();
            rt->st.push_back( w ); 
            rt = rt->children[s[i]-'a'];
            ++i;
        }
        rt->st.push_back(w);
    }
    
    WordFilter(vector<string>& words) {
        suffix = new tri_node(); // 后缀
        prefix = new tri_node();
        for ( int i=0; i<words.size(); ++i ){
            insert( prefix, words[i], i );
            insert( suffix, string(words[i].rbegin(), words[i].rend()), i );
        }
    }
    
    vector<int>* search( tri_node * rt, string s ){
        int i = 0;
        while( i<s.size() ){
            if ( rt->children[s[i]-'a']==NULL )
                return {};
            rt = rt->children[s[i]-'a'];
            ++i;
        }
        return &rt->st;
    }
    
    int f(string p, string s) {
        reverse(s.begin(), s.end());
        vector<int>* v1=search( prefix, p );
        vector<int>* v2=search( suffix, s );
        if(v1==nullptr||v2==nullptr)return -1;//前缀或后缀有一个为空，就表示没有这样的单词
        if(p.size()==0)return *v2->rbegin();//前缀字符串为空，返回后缀字典树中的最大权重
        if(s.size()==0)return *v1->rbegin();//后缀字符串为空，返回前缀字典树中的最大权重
        auto it1=v1->rbegin();
        auto it2=v2->rbegin();
        while(it1!=v1->rend()&&it2!=v2->rend())//查找的时候排除边缘条件后对比权值就行
        {
            if(*it1==*it2)return *it1;
            if(*it1>*it2)it1++;
            else it2++;
        }
        return -1;
    }
};



// 方法二  前缀{后缀 编码
class WordFilter {
public:
    struct tri_node{
        tri_node * children[27];
        int weight;
        tri_node(){
            for ( int i=0; i<27; ++i )
                children[i] = NULL;
            weight = -1;
        }
    };
    
    struct tri_node * tree; 

    void insert( tri_node * rt, string s, int w ){
        int i=0;
        while( i<s.size() ){
            if ( rt->children[s[i]-'a']==NULL )
                rt->children[s[i]-'a'] = new tri_node();
            rt->weight = max( rt->weight, w );
            rt = rt->children[s[i]-'a'];
            ++i;
        }
        rt->weight = max( rt->weight, w );
    }
    
    WordFilter(vector<string>& words) {
        tree = new tri_node();
        int id=0;
        for ( auto word:words ){
            string rs = "{" + word;
            for ( int i=(int)word.size()-1; i>=0; --i ){
                insert( tree, rs, id );
                rs = word[i] + rs;
            }
            insert( tree, word+"{"+word, id );
            ++id;
        }
    }
    
    int search( tri_node * rt, string s ){
        int i = 0;
        while( i<s.size() ){
            if ( rt->children[s[i]-'a']==NULL )
                return -1;
            rt = rt->children[s[i]-'a'];
            ++i;
        }
        return rt->weight;
    }
    
    int f(string p, string s) {
        string pat = s+"{"+p;
        return search(tree, pat);
    }
};
