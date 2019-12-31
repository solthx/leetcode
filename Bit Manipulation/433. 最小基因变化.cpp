/*
    问题描述:
        一条基因序列由一个带有8个字符的字符串表示，其中每个字符都属于 "A", "C", "G", "T"中的任意一个。
        假设我们要调查一个基因序列的变化。一次基因变化意味着这个基因序列中的一个字符发生了变化。
        例如，基因序列由"AACCGGTT" 变化至 "AACCGGTA" 即发生了一次基因变化。
        与此同时，每一次基因变化的结果，都需要是一个合法的基因串，即该结果属于一个基因库。
        现在给定3个参数 — start, end, bank，分别代表起始基因序列，目标基因序列及基因库，请找出能够使起始基因序列变化为目标基因序列所需的最少变化次数。如果无法实现目标变化，请返回 -1。

        注意:

            起始基因序列默认是合法的，但是它并不一定会出现在基因库中。
            所有的目标基因序列必须是合法的。
            假定起始基因序列与目标基因序列是不一样的。
        示例 1:

        start: "AACCGGTT"
        end:   "AACCGGTA"
        bank: ["AACCGGTA"]

        返回值: 1
        示例 2:

        start: "AACCGGTT"
        end:   "AAACGGTA"
        bank: ["AACCGGTA", "AACCGCTA", "AAACGGTA"]

        返回值: 2
        示例 3:

        start: "AAAAACCC"
        end:   "AACCCCCC"
        bank: ["AAAACCCC", "AAACCCCC", "AACCCCCC"]

        返回值: 3

    问题分析：
        方法一: naive bfs
            bfs可以莽过去, bfs时，每次把访问过的bank里的字符串给删掉，可以快一点..

        方法二: bit manipulation + bfs
            字符串长度为8， 且可以选择的有4种情况，这4种情况可以编码成2个bit，然后就可以把
            长度为8的字符串编码成一个16bit的数字，然后通过位运算来模拟bfs的条件判断..

        本题不难，但貌似出现频率比较高。。各大公司都爱考。。 位运算练手题
*/

// naive bfs
class Solution1 {
public:
    int minMutation(string start, string end, vector<string>& bank) {
        unordered_set<string> st(bank.begin(), bank.end());
        if ( st.count(end)==0 ) return -1;
        vector<char> mp = { 'A', 'C', 'G', 'T' };
        queue<string> q;
        int step=0;
        q.push(start);
        while( q.size()>0 ){
            for ( int j=q.size(); j>0; --j ){
                auto cur = q.front(); q.pop();
                for ( int i=0; i<cur.size(); ++i ){
                    for ( auto c:mp ){
                        if ( cur[i]!=c ){
                            string nxt = cur;
                            nxt[i] = c;
                            if ( st.count(nxt)>0 ){
                                if ( nxt==end ) return step+1;
                                q.push(nxt);
                                st.erase(nxt);
                            }
                        }
                    }
                }
            }
            ++step;
        }
        return -1;
    }
};

// 位运算版本
class Solution2 {
public:
    unordered_map<char, int> mp = { {'A',0},{'C',1},{'G',2},{'T',3} };  
    unordered_map<int, char> de = { {0,'A'},{1,'C'},{2,'G'},{3,'T'} };  // 这个其实可以不需要的。
    
    int minMutation(string start, string end, vector<string>& bank) {
        // 状态总共32种, int有32位, 可以尝试每一个位保存一个状态
        int first = encode( start );
        int last = encode( end );
        unordered_set<int> st;
        for ( auto s:bank )
            st.insert(encode(s));
        if ( st.count(last)==0 ) return -1;
        queue<int> q;
        q.push(first);
        int step=0;
        while( q.size()>0 ){
            for ( int j=q.size(); j>0; --j ){
                int state = q.front(); q.pop();
                for ( int i=0; i<end.size(); ++i ){ //8位 
                    // 改变第i位
                    for ( int c=0; c<4; ++c ){ //4个字符
                        if ( (state & (3<<(2*i))  )!= (c<<(2*i) )) { 
                            int next_state =  ( helper(state, i) | (c<<(2*i) ) ) ;
                            if ( st.count(next_state)>0 ){
                                if ( next_state==last ) return step+1;
                                st.erase(next_state);
                                q.push(next_state);
                            }
                        }
                    }
                }
                
            }
            ++step;
        }
        return -1;
    }
    int helper( int state, int i ){
        state |= (3<<(2*i));
        state -= (3<<(2*i));
        return state;
    }
    string decode( int state ){
        string res;
        for ( int i=0; i<8; ++i ){
            char c = de[ (state>>(2*i)) % 4 ];
            res += c;
        }
        reverse(res.begin(), res.end());
        return res;
    }
    int encode(string s){
        int res = 0;
        for ( auto c:s )
            res = (res<<2) + mp[c];
        return res;
    }
};