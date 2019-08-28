/*
    问题描述:
        验证原始的序列 org 是否可以从序列集 seqs 中唯一地重建。序列 org 是 1 到 n 整数的排列，其中 1 ≤ n ≤ 104。重建是指在序列集 seqs 中构建最短的公共超序列。（即使得所有  seqs 中的序列都是该最短序列的子序列）。确定是否只可以从 seqs 重建唯一的序列，且该序列就是 org 。
        示例 1：
        输入：
            org: [1,2,3], seqs: [[1,2],[1,3]]
        输出：
            false
        解释：
            [1,2,3] 不是可以被重建的唯一的序列，因为 [1,3,2] 也是一个合法的序列。
         
        示例 2：
        输入：
            org: [1,2,3], seqs: [[1,2]]
        输出：
            false
        解释：
            可以重建的序列只有 [1,2]。

        示例 3：
        输入：
            org: [1,2,3], seqs: [[1,2],[1,3],[2,3]]
        输出：
            true
        解释：
            序列 [1,2], [1,3] 和 [2,3] 可以被唯一地重建为原始的序列 [1,2,3]。
         

        示例 4：
        输入：
            org: [4,1,5,2,6,3], seqs: [[5,2,6,3],[4,1,5,2]]
        输出：
            true

    问题分析:
        可以根据seqs里的序列建立依赖关系，
        然后进行拓扑排序，
        可以通过改变拓扑排序的遍历顺序来得到两个原始序列，
        如果这两个原始序列都和org相同，那么说明就是唯一的了。

        改变topsort的顺序，可以通过用set来记录当前节点可以访问的节点，
        第一个序列是从小到大找， begin->end
        第二个序列是从大到小找， rbegin->rend
        
        需要注意的是，indegree数组， queue，都要分开来做... 
*/

class Solution {
public:
    bool sequenceReconstruction(vector<int>& org, vector<vector<int>>& seqs) {
        int i=0, len=seqs.size();
        bool existed=false;
        int n = org.size();
        // 拓扑排序， 升序一次，逆序一次，如果三个序列相同说明唯一且正确
        if ( seqs.size()==0  ) return org.size()==0;   
        vector< set<int> > mp(n+1);
        vector<int> indegree( org.size()+1, -1 );
        vector<int> indegree2( org.size()+1, -1 );
        
        for ( auto v:seqs )
            for ( auto c:v ){
                existed = true;
                if ( c>n|| c<=0 ) return false;
                indegree[c]=0;
                indegree2[c]=0;
            }
        if ( !existed ) return false;
        for ( auto v:seqs ){
            for ( int i=1; i<v.size(); ++i ){
                if ( mp[v[i-1]].count( v[i] )==0 ){
                    mp[v[i-1]].insert( v[i] );
                    indegree[v[i]]+=1;
                    indegree2[v[i]]+=1;
                }
            }
        }
        queue<int> q1, q2;
        vector<int> forward, backward;
        for ( int i=1; i<indegree.size(); ++i )
            if ( indegree[i]==0 ){
                q1.push(i);
            }
        for ( int i=indegree2.size()-1; i>=0; --i )
            if ( indegree2[i]==0 ){
                q2.push(i);
            }
        while( !q1.empty() ){
            int cur = q1.front(); q1.pop();
            forward.push_back(cur);
            for ( auto it = mp[cur].begin(); it!=mp[cur].end(); ++it ){
                if ( --indegree[*it]==0 )
                    q1.push(*it);
            }
        }
        while( !q2.empty() ){
            int cur = q2.front(); q2.pop();
            backward.push_back(cur);
            for ( auto it = mp[cur].rbegin(); it!=mp[cur].rend(); ++it ){
                if ( --indegree2[*it]==0 )
                    q2.push(*it);
            }
        }
        if ( backward.size() !=forward.size() || forward.size()!=org.size() ) return false;
        for ( int i=0; i<org.size(); ++i )
            if ( forward[i]!=backward[i] || forward[i]!=org[i] ) return false;
        return true;
    }
};
