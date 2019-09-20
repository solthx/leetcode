/*
    问题描述:
        假设你设计一个游戏，用一个 m 行 n 列的 2D 网格来存储你的游戏地图。

        起始的时候，每个格子的地形都被默认标记为「水」。我们可以通过使用 addLand 进行操作，将位置 (row, col) 的「水」变成「陆地」。

        你将会被给定一个列表，来记录所有需要被操作的位置，然后你需要返回计算出来 每次 addLand 操作后岛屿的数量。

        注意：一个岛的定义是被「水」包围的「陆地」，通过水平方向或者垂直方向上相邻的陆地连接而成。你可以假设地图网格的四边均被无边无际的「水」所包围。

        请仔细阅读下方示例与解析，更加深入了解岛屿的判定。

        示例:

        输入: m = 3, n = 3, positions = [[0,0], [0,1], [1,2], [2,1]]
        输出: [1,1,2,3]
        解析:

        起初，二维网格 grid 被全部注入「水」。（0 代表「水」，1 代表「陆地」）

        0 0 0
        0 0 0
        0 0 0
        操作 #1：addLand(0, 0) 将 grid[0][0] 的水变为陆地。

        1 0 0
        0 0 0   Number of islands = 1
        0 0 0
        操作 #2：addLand(0, 1) 将 grid[0][1] 的水变为陆地。

        1 1 0
        0 0 0   岛屿的数量为 1
        0 0 0
        操作 #3：addLand(1, 2) 将 grid[1][2] 的水变为陆地。

        1 1 0
        0 0 1   岛屿的数量为 2
        0 0 0
        操作 #4：addLand(2, 1) 将 grid[2][1] 的水变为陆地。

        1 1 0
        0 0 1   岛屿的数量为 3
        0 1 0
        拓展：

        你是否能在 O(k log mn) 的时间复杂度程度内完成每次的计算？（k 表示 positions 的长度）

    问题分析:
        很明显使用并查集,
        对于每一个position, 看上下左右有没有1, 
        初始的岛屿增加量为1,
        然后和相邻位置，合并每一次, 这个增量就-1  (这个比较好理解，举个例子就明白了)
        
        因为要用到并查集，所以把二维坐标拉直, 即 (i,j) => i*m+j ， m为列数, n为行数. (本题中，一开始n是列数，m是行数，但我习惯n作为行, 所以给颠倒了一下)

        然后我们可以把拉直后的(i,j)丢进set集合中， 集合中的坐标都是岛屿，
        所以在看周围一圈位置是不是岛屿的时候，就去set中查询有没有就行了. 
        时间复杂度O(k*logmn)
        空间复杂度O(k)
*/

class Solution {
public:
    int n,m;
    //vector<int> pre;
    unordered_map<int,int> pre;
    int find( int x ){
        return pre.count(x)==0?x:(pre[x]=find(pre[x]));
    }
    bool merge( int a, int b ){
        // merge成功就返回true
        // a和b属于同一个集合, 就返回false
        int x = find(a);
        int y = find(b);
        if ( x==y ) return false;
        // if ( pre[x]<pre[y] ){
        //     pre[x]+=pre[y];
        //     pre[y] = x;
        // }else{
        //     pre[y]+=pre[x];
        //     pre[x]=y;
        // }
        pre[x] = y;
        return true;
    }
    vector<int> numIslands2(int n, int m, vector<vector<int>>& positions) {
        // 并查集
        this->n=n;
        this->m=m;
        int cnt=0, nodes,cur;
        vector<int> res;
        set<int> ones;
        int dir[4][2] = {{1,0},{0,1},{-1,0},{0,-1}};
        //pre.resize((m+10)*(n+10) , -1);
        int add=1, idx=0;
        for ( auto p:positions ){
            add = 1;
            cur = getNode(p[0], p[1]);
            if ( ones.count(cur)>0 ){
                res.push_back(cnt);
                continue;
            }
            for ( int k=0; k<4; ++k ){
                int y = p[0]+dir[k][0];
                int x = p[1]+dir[k][1];
                if ( x<m && y<n&& x>=0 && y>=0  ){
                    nodes = getNode(y,x);
                    if ( ones.count(nodes) ){
                        // 说明要合并
                        if (merge(nodes, cur)) add--;
                    }
                }
                
            }
            ones.insert(cur);
            cnt+=add;
            res.push_back(cnt);
        }
        return res;
    }
    
    int getNode(int i, int j){
        return n*i+j;
    }
};