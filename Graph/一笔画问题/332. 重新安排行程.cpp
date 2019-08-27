/*
    问题描述:
        给定一个机票的字符串二维数组 [from, to]，子数组中的两个成员分别表示飞机出发和降落的机场地点，对该行程进行重新规划排序。所有这些机票都属于一个从JFK（肯尼迪国际机场）出发的先生，所以该行程必须从 JFK 出发。
        
        说明:
            如果存在多种有效的行程，你可以按字符自然排序返回最小的行程组合。例如，行程 ["JFK", "LGA"] 与 ["JFK", "LGB"] 相比就更小，排序更靠前
            所有的机场都用三个大写字母表示（机场代码）。
            假定所有机票至少存在一种合理的行程。
        
        示例 1:
            输入: [["MUC", "LHR"], ["JFK", "MUC"], ["SFO", "SJC"], ["LHR", "SFO"]]
            输出: ["JFK", "MUC", "LHR", "SFO", "SJC"]
        
        示例 2:
            输入: [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
            输出: ["JFK","ATL","JFK","SFO","ATL","SFO"]
            解释: 另一种有效的行程是 ["JFK","SFO","ATL","JFK","ATL","SFO"]。但是它自然排序更大更靠后。

    问题分析：
        感觉题目表达的不是很好。。
        这里说的合理是指，能够根据手头已有的机票 来走完所有的路程.
        可以建模成一笔画问题.

        然后才是，如果存在多条路线，则返回字典序最小的那个.
    
        以本题为切入口，来介绍一笔画问题的解决思想.

        当我们想处理一笔画问的时候，一个难点就是该如何判断我选的下一条边是不是能一口气走到底。
        如果我们能够知道这样的路线的话，直接做一个dfs来遍历图就解决了.

        但正向扫描的话，需要很大的复杂度才能找到这样的边(因为要遍历每一种可能的情况)， 这是不可行的，
        所以我们不妨逆向来做。 也就是先找到最后一个节点，然后再找倒数第二个节点，。。直到找到第一个节点

        要这么做的话，就需要用dfs和栈来做.

        在进行dfs的过程中，犹豫该选哪一条边的时候，我们先随便选一条，然后进入下一层dfs
        
        每条边只能被访问一次，可以使用visited数组也可以直接删掉

        当当前节点再也找不出 能够访问下去的边的时候， 就说明当前节点之后的点 都已经被访问过了，这个时候就把当前节点压入栈中，
        ( 节点被压入栈中，说明该节点被访问过了 )
        
        这样一直做下去，最终，我们就得到了一个逆序的“一笔画”序列

        然后把这些元素从栈中pop出来就行了，如果用的vector直接做reverse就可以了.

        因为题目要求了字典序最小，所以可以事先进行排序，或者用有序容器来存储(例如set,multiset..)

        下面是代码实现
*/

class Solution1 {
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        // 排序+dfs 使用visited数组
        auto cmp = []( vector<string>& a, vector<string>& b ){
            return a[1]<b[1];  
        };
        unordered_map<string, vector<pair<string, int>>> mp;
        int idx=0;
        sort( tickets.begin(), tickets.end(), cmp );
        for ( auto e:tickets )
            mp[e[0]].push_back({e[1],idx++});
        vector<bool> visited(idx,false);
        vector<string> res, cur;
        dfs( res, mp, "JFK", visited );
        reverse(res.begin(),res.end());
        return res;
    }
    
    void dfs( vector<string> & res, unordered_map<string, vector<pair<string, int>>>& mp, string cur, vector<bool> & visited  ){
        for ( auto &e:mp[cur] )
            if ( !visited[e.second] ){
                visited[e.second] = true;
                dfs( res, mp, e.first, visited );
            }
        res.push_back( cur );
    }
    
};



//=======================Solution2====================================
class Solution2 {
public:
    // 用 multiset+dfs  multiset内部有序，可以不用visited来标记，直接删边
    unordered_map<string, multiset<string> > mp;
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        for ( auto ticket:tickets )
            mp[ticket[0]].insert( ticket[1] );
        vector<string> res;
        dfs( "JFK", res );
        reverse(res.begin(), res.end());
        return res;
    }
    
    void dfs( string cur, vector<string>& res ){
        while ( mp[cur].size()>0 ){
            string sav = *mp[cur].begin();
            mp[cur].erase( mp[cur].begin() );
            dfs(sav, res);
        }
        res.push_back(cur);
    }
    
};


//=======================Solution3====================================
class Solution3 {
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        // 用栈来代替递归
        unordered_map<string, set<string> > mp;
        stack<string> s;
        for ( auto ticket:tickets )
            mp[ticket[0]].insert( ticket[1] );
        vector<string> res;
        s.push("JFK");
        while( !s.empty() ){
            string tops = s.top(); //top为当前节点
            if ( mp[tops].size()!=0 ){
                // 如果还有边能访问，就先别存当前节点，先压入栈里
                string sav = *mp[tops].begin();
                mp[tops].erase(mp[tops].begin());
                s.push( sav );
            }else{
                // 当找不到吓一条边的时候，就把当前节点给存进去.
                s.pop();
                res.push_back(tops);
            }
        }
        reverse(res.begin(), res.end());
        return res;
    }
};