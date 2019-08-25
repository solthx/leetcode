/*
    问题分析:
        村里面一共有 n 栋房子。我们希望通过建造水井和铺设管道来为所有房子供水。
        对于每个房子 i，我们有两种可选的供水方案：
        一种是直接在房子内建造水井，成本1为 wells[i]；
        另一种是从另一口井铺设管道引水，数组 pipes 给出了在房子间铺设管道的成本2，其中每个 pipes[i] = [house1, house2, cost] 代表用管道将 house1 和 house2 连接在一起的成本。当然，连接是双向的。
        请你帮忙计算为所有房子都供水的最低总成本（=成本1+成本2）。

        输入：n = 3, wells = [1,2,2], pipes = [[1,2,1],[2,3,1]]
        输出：3
        解释： 
            最好的策略是在第一个房子里建造水井（成本为 1），然后将其他房子铺设管道连起来（成本为 2），所以总成本为 3。
        
    问题分析:
        一个很秀的思路： 建立一个虚拟节点，来连接所有的点！
            构建一个虚拟节点，连接所有的点，连接所有的点的那条边的cost就是在这个节点上所要消耗的cost( 就是建井的费用 )
            然后再构造最小生成树， 最小生成树的cost和，就是答案了

        构造虚拟节点连接所有点的这个思路很棒，要记住..
*/

class Solution {
public:
    vector<int> set;
    // 路径压缩
   int Find(int x){
        if ( set[x]<0 ) return x;
        return set[x] = Find(set[x]);
    }

    bool Merge(int x,int y){
        int a = Find(x);
        int b = Find(y);
        if ( a==b ) return false;
        if ( a<b ){
            set[a] += set[b];
            set[b] = a;
        }else{
            set[b] += set[a];
            set[a] = b;    
        }
        return true;
    }
    
    
    int minCostToSupplyWater(int n, vector<int>& wells, vector<vector<int>>& pipes) {
        int res = 0, idx=1;
        set.resize(n+1, -1);
        auto cmp = [](vector<int>&a, vector<int>&b){
            return a.back()<b.back(); 
        };
        int root, cur;
        // 构造虚拟节点和虚拟边
        for ( auto e: wells ){
            pipes.push_back( { 0,idx,e } );
            ++idx;
        }
        // 开始构造最小生成树
        sort( pipes.begin(), pipes.end(), cmp );
        for ( auto e:pipes )
            if ( Merge(e[0], e[1]) )
                res += e[2];
        return res;
    }
};