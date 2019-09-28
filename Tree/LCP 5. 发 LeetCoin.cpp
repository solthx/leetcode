/*
    问题描述:
        力扣决定给一个刷题团队发LeetCoin作为奖励。同时，为了监控给大家发了多少LeetCoin，力扣有时候也会进行查询。

        该刷题团队的管理模式可以用一棵树表示：

        团队只有一个负责人，编号为1。除了该负责人外，每个人有且仅有一个领导（负责人没有领导）；
        不存在循环管理的情况，如A管理B，B管理C，C管理A。
         

        力扣想进行的操作有以下三种：

        给团队的一个成员（也可以是负责人）发一定数量的LeetCoin；
        给团队的一个成员（也可以是负责人），以及他/她管理的所有人（即他/她的下属、他/她下属的下属，……），发一定数量的LeetCoin；
        查询某一个成员（也可以是负责人），以及他/她管理的所有人被发到的LeetCoin之和。
         

        输入：

        N表示团队成员的个数（编号为1～N，负责人为1）；
        leadership是大小为(N - 1) * 2的二维数组，其中每个元素[a, b]代表b是a的下属；
        operations是一个长度为Q的二维数组，代表以时间排序的操作，格式如下：
        operations[i][0] = 1: 代表第一种操作，operations[i][1]代表成员的编号，operations[i][2]代表LeetCoin的数量；
        operations[i][0] = 2: 代表第二种操作，operations[i][1]代表成员的编号，operations[i][2]代表LeetCoin的数量；
        operations[i][0] = 3: 代表第三种操作，operations[i][1]代表成员的编号；
        输出：

        返回一个数组，数组里是每次查询的返回值（发LeetCoin的操作不需要任何返回值）。由于发的LeetCoin很多，请把每次查询的结果模1e9+7 (1000000007)。

         

        示例 1：

        输入：N = 6, leadership = [[1, 2], [1, 6], [2, 3], [2, 5], [1, 4]], operations = [[1, 1, 500], [2, 2, 50], [3, 1], [2, 6, 15], [3, 1]]
        输出：[650, 665]
        解释：团队的管理关系见下图。
        第一次查询时，每个成员得到的LeetCoin的数量分别为（按编号顺序）：500, 50, 50, 0, 50, 0;
        第二次查询时，每个成员得到的LeetCoin的数量分别为（按编号顺序）：500, 50, 50, 0, 50, 15.

        图在这: https://leetcode-cn.com/problems/coin-bonus/

    问题分析:
        虽然很明显用线段树。。但好像还是不太一样..

        node节点: parent记录父亲节点编号， cnt记录包括自己在内的组内人数，
        coins记录了包括自己在内的组内人数的coins总数

        对于操作1:  给第i号节点加 val个coins
            1. 对第i个节点加val个coins
            2. 向上更新  

        对于操作2:  给第i号以及其组内所有人加 cnt*coins个coins
            1. 更新第i个节点
            2. 向上更新
            3. 向下更新

        对于操作3: 直接返回coins就行了

*/

# define mod 1000000007
class Solution {
public:
    class node{
        public :
        int coins;
        vector<int> child;
        int cnt; // 孩子数量(包括自己)
        int parent;
        node(){
            coins=0;
            parent = -1;
            cnt = 1;
        }
    };
    vector<node> tree;
    void update_cnt( int r ){
        int res=tree[r].cnt;
        for ( auto v:tree[r].child ){
            update_cnt( v );
            res += tree[v].cnt;
        }
        tree[r].cnt = res;
    }
    
    void push_down( int r, int val ){
        tree[r].coins += ( tree[r].cnt*val );
        for ( auto v:tree[r].child ){
            push_down( v,val );
        }
    }
    
    vector<int> bonus(int n, vector<vector<int>>& leadership, vector<vector<int>>& operations) {
        // 模拟一下试试
        tree.resize(n+10, node());
        
        // build
        for ( auto p:leadership ){
            tree[p[0]].child.push_back( p[1] );
            tree[p[1]].parent = p[0];
        }
        int rt = -1;
        for ( int i=1; i<=n; ++i)
            if ( tree[i].parent==-1 ){
                rt = i;
                break;
            }
        update_cnt( rt );
        vector<int> res;
        for ( auto p:operations ){
            if ( p[0]==1 ){
                // 给p[1]的coins加p[2]
                int addition = p[2];
                tree[p[1]].coins = (tree[p[1]].coins + p[2])%mod;
                int r = tree[p[1]].parent;
                while( r!=-1 ){
                    tree[r].coins = (tree[r].coins + (long long)addition)%mod;
                    r = tree[r].parent;
                }
            }else if ( p[0]==2 ){
                // 给p[1]以及他的孩子们的coins加p[2]
                int addition = (p[2]*((long long)tree[p[1]].cnt))%mod;
                tree[p[1]].coins = (tree[p[1]].coins + (long long)addition)%mod;
                int r = tree[p[1]].parent;
                while( r!=-1 ){
                    tree[r].coins = (tree[r].coins + (long long)addition)%mod;
                    r = tree[r].parent;
                }
                for ( auto v:tree[p[1]].child )
                    push_down( v, p[2] );
            }else if ( p[0]==3 ){
                res.push_back( tree[p[1]].coins );
            }
        }
        return res;
    }
};