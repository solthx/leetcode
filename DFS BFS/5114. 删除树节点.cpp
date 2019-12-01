/*
    问题描述:
        给你一棵以节点 0 为根节点的树，定义如下：

        节点的总数为 nodes 个；
        第 i 个节点的值为 value[i] ；
        第 i 个节点的父节点是 parent[i] 。
        请你删除节点值之和为 0 的每一棵子树。

        在完成所有删除之后，返回树中剩余节点的数目。

        示例：
        输入：nodes = 7, parent = [-1,0,0,1,2,2,2], value = [1,-2,4,0,-2,-1,-1]
        输出：2
         

        提示：

        1 <= nodes <= 10^4
        -10^5 <= value[i] <= 10^5
        parent.length == nodes
        parent[0] == -1 表示节点 0 是树的根。


    问题分析:
        
        就是删除和为0的子树。 先计算出每个节点的子树和. 
        然后计算以当前节点为根的子树和不为0的节点个数。

        注意，再找节点不为0的节点个数时， 复杂度必须要O(N), 
        因此，开一个memo数组来记录当前节点的状态，用记忆化来优化一下，不然会超时.
*/


class Solution {
public:
    // 转换成 父-孩 的保存方式，比较好求子树和
    unordered_map<int, vector<int>> children;
    int deleteTreeNodes(int nodes, vector<int>& parent, vector<int>& value) {
        for ( int i=0; i<nodes; ++i )
            if( parent[i]!=-1 )
                children[parent[i]].push_back(i);
        vector<int> memo( nodes, -1 ); // -1为为访问, 1则说明和为0， 0则说明非0
        calculate_sum( 0 ,value ); // 计算子树和
        for ( int i=0; i<nodes; ++i )
            dfs( i, parent, value, memo ); // 标记节点
        int res= 0;
        for ( int i=0; i<nodes; ++i )
            res+=( memo[i]==0 ); // 计算个数
        return res;
    }
    
    int dfs( int i, vector<int>& parent, vector<int>& value, vector<int>& memo ){
        if ( memo[i]>=0 ) return memo[i];
        if ( parent[i]==-1 ) return memo[i] = (value[i]==0) ;
        if ( value[i]==0 ) return memo[i] = 1;
        dfs( parent[i], parent, value, memo );
        return memo[i]=memo[parent[i]];
    }
    
    void calculate_sum( int i ,vector<int>& value){
        for ( auto d:children[i] ){
            calculate_sum( d ,value );
            value[i] += value[d];
        }
    }
};
