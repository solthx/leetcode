/*
    问题描述:
        给定一个二维网格 board 和一个字典中的单词列表 words，找出所有同时在二维网格和字典中出现的单词。
        单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母在一个单词中不允许被重复使用。

        示例:
        输入: 
            words = ["oath","pea","eat","rain"] and board =
            [
                ['o','a','a','n'],
                ['e','t','a','e'],
                ['i','h','k','r'],
                ['i','f','l','v']
            ]
        输出: 
            ["eat","oath"]
        说明:
            你可以假设所有输入都由小写字母 a-z 组成。

    问题分析：
        字典树的一个最大的优势就是能快速的找到一个单词是否出现在 一个字符串集合里，或是属于字符串集合里的某个单词的前缀。
        本题将使用字典树来解决，但有两种解决方法；

        方法一: 
            1. 对tri树的查找操作稍加修改，使得 find(word) 返回:
                1.1 当word完全出现在字符串集合中， 那么返回1
                1.2 当word是属于字符串集合中某个单词的前缀，那么返回0
                1.3 当word不可能出现在字符串集合中， 那么返回-1
            2. 然后遍历board, dfs过程中，根据find的返回情况，来进行操作:
                2.1  如果是-1，直接返回，说明不可能了
                2.2  如果是0， 那就继续dfs
                2.3  如果是1， 不仅要继续dfs, 还要把结果给存入set中。之所以发现了这个单词还要继续做dfs是因为，
                有可能会有 "aa"和"aab", 也就是一个单词本身就是另一个单词的前缀的情况.
            
            上面的去重方法是把所有找到的单词都存入set中...
            
            一个在tri树的应用中，比较秀的去重方法是， 在tri的node节点中，加一个变量str
            当该节点是一个单词的最后一个字符时，str中就存入这个单词。
            如果当前节点不是一个单词的最后一个字符，str就为空。

            我们可以在做dfs的时候，只要发现tri_node->str不为空，那就说明已经找到了单词的最后一个字母了，
            这时把之前保存的str存入结果数组中，然后再把str清空，这一步很关键，这样做之后，同一个单词就不会重复存入了。
        
        方法二：
            可以不用写search函数，而是以tri节点来作为当前的访问状态，
            例如，一个字符串"abc"，当访问到b的时候，我们之前是保存"ab"
            而现在只要保存节点a下面的节点b就可以代替"ab"，从而省去到树中再查找的开销.
            用tri_node* node来代替 string cur

        本题代码有点长，就只记录比较优秀的方法二了，能用节点表示中间状态，就用节点表示中间状态，
        代码更简洁，也好理解，速度也快.
*/

class Solution {
public:
    struct tri_node{
        string str;
        tri_node * children[26];  
    };
    
    tri_node * root;
    vector<string> res;
    
    // 构造node
    tri_node * create_node(){
        tri_node * res = new tri_node();
        for ( int i= 0; i<26; ++i )
            res->children[i] = NULL;
        return res;
    }
    
    // 插入操作
    void insert( string word ){
        tri_node * p = root; 
        int i = 0;
        while( i<word.size() ){
            if ( p->children[word[i]-'a']==NULL )
                p->children[word[i]-'a'] = create_node();
            p = p->children[word[i]-'a'];
            ++i;
        }
        p->str = word; //记得在字符串的最后一个字符节点上，保存这个字符串
    }
    
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        if ( board.size()==0 || board[0].size()==0 ) return {};
        int n = board.size(), m = board[0].size();
        root = create_node();
        // 构建字典树
        for ( auto s:words )
            insert( s );

        vector<vector<bool>> visited( n, vector<bool>(m,false) );
        for ( int i=0; i<n; ++i )
            for ( int j=0; j<m; ++j )
                // 如果c这个字符是 某个单词的首个字符的话， root->children[c-'a']就一定非空
                if ( root->children[board[i][j]-'a']!=NULL )
                    dfs( board, i, j,root->children[board[i][j]-'a'], visited );
                
        return res;
    }
    
    void dfs( vector<vector<char>>& board, int i, int j, tri_node* node , vector<vector<bool>>& visited){
        // 标记该位置，使得在之后的dfs中不可访，记得回溯
        visited[i][j] = true;
        int n = board.size(), m = board[0].size();

        // 说明访问到最后一个节点了，直接存入这个单词
        if ( node->str.size()>0 ){
            res.push_back( node->str );
            node->str.clear();
        }
        
        int dir[4][2]= {{1,0},{0,1},{-1,0},{0,-1}};
        for ( int k=0; k<4; ++k ){
            int y = i+dir[k][0];
            int x = j+dir[k][1];
            // 只要c是当前位置的后一个字符，那么node->children[c-'a']一定不空！
            // 这是个很重要的剪枝
            if ( x>=0 && y>=0 && x<m &&y<n &&!visited[y][x] && node->children[ board[y][x]-'a' ] )
                dfs( board, y, x, node->children[ board[y][x]-'a' ], visited );
        } 
        // 回溯
        visited[i][j] = false;
    }
};