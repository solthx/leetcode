/*
    问题描述:
        给定两个单词（beginWord 和 endWord）和一个字典 wordList，找出所有从 beginWord 到 endWord 的最短转换序列。转换需遵循如下规则：

        每次转换只能改变一个字母。
        转换过程中的中间单词必须是字典中的单词。
        
        说明:
            如果不存在这样的转换序列，返回一个空列表。
            所有单词具有相同的长度。
            所有单词只由小写字母组成。
            字典中不存在重复的单词。
            你可以假设 beginWord 和 endWord 是非空的，且二者不相同。
        
        示例 1:
            输入:
            beginWord = "hit",
            endWord = "cog",
            wordList = ["hot","dot","dog","lot","log","cog"]

            输出:
            [
                ["hit","hot","dot","dog","cog"],
                ["hit","hot","lot","log","cog"]
            ]

        示例 2:
            输入:
            beginWord = "hit"
            endWord = "cog"
            wordList = ["hot","dot","dog","lot","log"]

            输出: []

            解释: endWord "cog" 不在字典中，所以不存在符合要求的转换序列。

    问题分析:
        本题的解决思路就是，构建一个转换图，然后进行bfs或dfs来得到最短路径.
        而这种找最短路的问题，可以通过构建一个图，先后做dijkstra来找，也可以通过bfs来找.
        本题主要是通过bfs来做.

            一个最朴素的想法就是，开一个队列和visited， 然后用visited保存曾经访问过的节点，
        然后来做bfs，再用path来记录指向当前节点的前一个节点，最后通过dfs来得到路径， 
        这里要注意的是，visited的标记要等到一层都结束以后，才可以做，
        因为例如:
            
            abh _____
                    |
                    v
            abc -->abe
                    ^
            abf ____|

        因为，一般的visited标记都是在入队的时候进行检测并标记，然后处理，都是一次标记一次入队一次处理
        但这里需要一次标记一次入队多次处理，
        我们希望abe被存入队列一次，被标记一次，但是指向它的节点却有三个，我们需要把这个三个节点都存入abe的path中
        解决的一个办法就是，当发现xxx已经被访问过的时候，再加一个判断处理，就是xxx是否是在当前层被标记的，如果是的话，就也更新path，进行处理
        上例中，
        abh->abe , abc->abe, abf->abe, 这三个abe都是在第二层被访问的，所以在第二层第二次访问abe的时候，abe已经被标记了，
        且上一次标记也是在第二层(当前层)，所以可以进行处理.
        
        因此，大题思路就是:
            1. bfs , 指向的下一个的字符串是和当前字符串距离为1的字符串。
            2. 用path记录所有指向当前字符串的字符串序列.
            3. 当遇到非第一次访问的字符串时，要判断是否是在当前层第一次被访问的，如果是的话，也需要进行path更新
            4. 通过dfs来生成路径，存入返回数组res里.
        
        该题在实现上，也颇有技巧，下面来记录一下. 记录顺序由差变优
        技巧主要体现在两个地方:
            1. visited的实现方式
            2. 如何找到所有与当前字符串距离为1 的那些字符串

        方法一: TLE
            1. 用visited数组来记录一个字符串是否被访问过，
            然后用set来记录当前层访问的字符串，
            在这一层结束的时候，把set里的字符串的visited统一进行标记, 通过延迟标记visited来解决上面的 3.
            
            2. 暴力查找和当前字符串距离为1的字符串，查找复杂度为O(M*N) M为字符串长度，N为字符串数组长度
            
            这两个方法都是好想，好实现，但效率糟糕的想法，下面一点点进行优化.
        
        方法二:  388ms
            1. 不再使用visited数组，而是使用set来代替visited， 
            把元素从set里移除 等价 对字符串进行标记，
            然后通过记录 {字符串 : 字符串的访问层数}，这样的pair, 来解决
            同层多次访问同一字符串的情况.
            如果 step[xxx]表示 在第几层访问到xxx

            逻辑会很清楚：
            假设 yyy 转换 得到xxx
                1. 存在于set中: (未访问过xxx)
                    1.1 从set中删掉xxx，表示已经访问了xxx
                    1.2 向step记录xxx在第几层
                    1.3 更新path
                        
                2. 不存在于set中，但存在于step中: (说明不是第一次访问xxx)
                    1.2 如果 step[yyy]+1 == step[xxx] ( 说明上次的访问层数和当前是同一层 )
                        更新path
            
            2. 对于如何寻找所有距离为1的字符串， 如果N很大的话，暴力会开销很大.
            一般对于这种字符串的题，因为英文字母就26个，所以可以利用枚举的思想，
            即 set里保存了待访问的字符串，
            然后对于当前得到的字符串yyy,想找到所以和它距离为一的字符串xxx
            可以通过改变每一个位上的字符，然后去set查找是否存的方式.
            这样的复杂度为O( M*26*logN ) N又是不断变小的，所以开销会小的多.
        
        方法三： 224ms
            用两个set来代替queue， 这两个set分别代表当前层和下一层 ,
            然后更新完下一层之后，再swap这两个层，类似滚动数组的思想，
            然后对于 多次访问同一字符串 的情况，如果不是第一次访问xxx了，
            那么就去下一层的set里去找xxx，如果存在，说明是在当前层访问的xxx，
            这样子理解更直观. 

        方法四:  60ms
            双向bfs
            可以从起点和终点两边同时进行bfs，
            用三个set来模拟，set1用于保存起点这一侧的当前字符串， set2用于保存终点这一侧
            的当前字符串， set3用于保存下一层的结果,属于临时的set
            
            具体的遍历方法和方法三几乎一样，
            只不过多加点东西，
            
            一个是bool forward， 如果是true的话，说明是从起点向终点遍历， false的话，说明是反的，
            根据这个变量来更新path，

            另一个是每次遍历前，选取起始侧和终点侧，元素较小的那个set来开始bfs， 
            扫描结束从 下一个字符串就是endWord, 变成下一个字符串存在于另一侧的set中


        小结:
            学到的新思想:
                1. 一个set代替visited
                2. 用两个set代替queue， 一个表示当前层，一个表示下一层，用于 当前层和下一层有着“不是太明了的”联系的情况.
                3. 对于字符匹配的题目，如果数组过大，可以适当考虑枚举！
                4. 双向bfs的思想.
*/

class Solution3 {
public:
    // 两个set代替当前层和下一层的方法三
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> dic(wordList.begin(), wordList.end());
        if ( dic.count(endWord)==0 ) return {};
        unordered_map<string, vector<string>> path; // path[s] -> s
        unordered_set<string> cur{{beginWord}}, next;
        bool found = false;
        while( !cur.empty() && !found ){
            for ( auto & vs : cur ){
                string adj = vs;
                dic.erase(vs);
                for ( int i=0; i<vs.size(); ++i ){
                    for ( char c='a'; c<='z'; ++c ){
                        if ( adj[i]==c ) continue;
                        adj[i] = c;
                        if ( vs==endWord ) 
                            found = true;
                        if ( dic.count( adj )>0  ){
                            dic.erase(adj);
                            path[adj].push_back(vs);
                            next.insert( adj );
                        }else if ( next.count( adj )>0 )
                            path[adj].push_back(vs);
                    }
                    adj[i] = vs[i];
                }
            }
            cur.clear();
            swap(cur, next);
        }
        vector<vector<string>> res;
        vector<string> cu;
        if ( !found ) return {};
        dfs( endWord, res, cu, path, beginWord );
        for ( auto &e:res )
            reverse(e.begin(), e.end());
        return res;
    }
    
     void dfs( string s, vector<vector<string>> & res, vector<string> & cur, unordered_map<string, vector<string>> & path, string tag ){
        cur.push_back( s );
        if ( path[s].size()==0 && s==tag ){
            res.push_back( cur );
            cur.pop_back();
            return ;
        }
        for ( auto e:path[s] )
            dfs( e, res, cur, path, tag );
        cur.pop_back();
    }
};


//=================================Solution4=====================================

// 双向bfs
class Solution4 {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> dic(wordList.begin(), wordList.end());
        if ( dic.count(endWord)==0 ) return {};
        unordered_map<string, vector<string>> path; // path[s] -> s
        unordered_set<string> start{{beginWord}}, end{{endWord}}, next;
        bool found = false;
        bool forward = true;
        while( !start.empty() && !end.empty() && !found ){
            if ( start.size()>end.size() ){
                swap(start, end);
                forward = !forward;
            }
            for ( auto & vs : start ){
                string adj = vs;
                dic.erase(vs);
                for ( int i=0; i<vs.size(); ++i ){
                    for ( char c='a'; c<='z'; ++c ){
                        if ( adj[i]==c ) continue;
                        adj[i] = c;
                        if ( end.count( adj ) ){
                            if ( forward )
                                path[adj].push_back(vs);
                            else path[vs].push_back(adj);
                            found = true;
                        }
                        else if ( dic.count( adj )>0  ){
                            dic.erase(adj);
                            if ( forward )
                                path[adj].push_back(vs);
                            else path[vs].push_back(adj);
                            next.insert( adj );
                        }else if ( next.count( adj )>0 ){
                           if ( forward )
                                path[adj].push_back(vs);
                            else path[vs].push_back(adj);
                        }
                    }
                    adj[i] = vs[i];
                }
            }
            start.clear();
            swap( start, next );
        }
        vector<vector<string>> res;
        vector<string> cu;
        if ( !found ) return {};
        dfs( endWord, res, cu, path, beginWord );
        for ( auto &e:res )
            reverse(e.begin(), e.end());
        return res;
    }
    
    void dfs( string s, vector<vector<string>> & res, vector<string> & cur, unordered_map<string, vector<string>> & path, string tag ){
        cur.push_back( s );
        if ( path[s].size()==0 && s==tag ){
            res.push_back( cur );
            cur.pop_back();
            return ;
        }
        for ( auto e:path[s] )
            dfs( e, res, cur, path, tag );
        cur.pop_back();
    }
};


// 比较蠢的方法二

//=================================Solution4=====================================

class Solution2 {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        unordered_map<string, int> steps{{beginWord,1}}; // steps[s]表示需要走几步能到s
        unordered_set<string> dic(wordList.begin(), wordList.end());
        if ( dic.count(endWord)==0 ) return {};
        dic.erase(endWord);
        dic.erase(beginWord);
        unordered_map<string, vector<string>> path; // path[s] -> s
        queue<string> q;
        q.push({beginWord});
        bool found = false;
        int step=1;
        while( !q.empty() && !found ){
            for ( int j=q.size(); j>0; --j ){
                string vs = q.front(); q.pop();
                string adj = vs;
                for ( int i=0; i<vs.size(); ++i ){
                    for ( char c='a'; c<='z'; ++c ){
                        if ( adj[i]==c ) continue;
                        
                        adj[i] = c;
                        
                        // adj为 vs经过一次变换得到的字符串
                        
                        if ( adj==endWord ){
                            found = true;
                            path[adj].push_back(vs);
                        }else{
                            // 同一层上，之前已经访问并删除过adj
                            if ( steps.count( adj ) && steps[adj]>steps[vs] )
                                path[adj].push_back(vs);
                        }
                        if ( dic.count(adj)==0 ) continue ; 
                        dic.erase( dic.find(adj) );
                        steps[adj] = steps[vs] + 1;
                        q.push(adj);
                        path[adj].push_back( vs );
                    }
                    adj[i] = vs[i];
                }
            }
        }

        vector<vector<string>> res;
        vector<string> cur;
        if ( !found ) return {};
        dfs( endWord, res, cur, path );
        for ( auto &e:res )
            reverse(e.begin(), e.end());
        return res;
    }
    
    void dfs( string s, vector<vector<string>> & res, vector<string> & cur, unordered_map<string, vector<string>> & path ){
        cur.push_back( s );
        if ( path[s].size()==0 ){
            
            res.push_back( cur );
            cur.pop_back();
            return ;
        }
        for ( auto e:path[s] )
            dfs( e, res, cur, path );
        cur.pop_back();
    }
};