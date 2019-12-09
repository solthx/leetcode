/*
    问题描述:
        给定一个无向、连通的树。树中有 N 个标记为 0...N-1 的节点以及 N-1 条边 。
        第 i 条边连接节点 edges[i][0] 和 edges[i][1] 。
        返回一个表示节点 i 与其他所有节点距离之和的列表 ans。

        示例 1:

        输入: N = 6, edges = [[0,1],[0,2],[2,3],[2,4],[2,5]]
        输出: [8,12,6,10,10,10]
        解释: 
        如下为给定的树的示意图：
            0
           / \
          1   2
             /|\
            3 4 5

        我们可以计算出 dist(0,1) + dist(0,2) + dist(0,3) + dist(0,4) + dist(0,5) 
        也就是 1 + 1 + 2 + 2 + 2 = 8。 因此，answer[0] = 8，以此类推。
        说明: 1 <= N <= 10000

    问题分析:
        最直接的思路就是对第每一个节点都做一次遍历求和，得到这个节点到所有节点的距离,
        但O(N^2)的复杂度对10^4肯定会TLE.. 因此要想办法优化.

        对N^2算法的优化，就是去找重复计算了哪些信息, 

        以上面的样例为例， 在计算0->5的距离的时候，分别是经过了0->2->5，即里面包含了2->5的距离，
        在求其他节点的时候也是同理的，即在求a->b->...->c得距离的时候，同时也计算b->..->c，等等等等的距离信息.

        那么我们就可以想，当求出了0到所有节点的距离和之后， 能不能通过 这个距离和来得到 另一个节点到所有节点的距离和呢？ 这样的话复杂度就是O(N)了.. 

        那就特殊化一个例子， 假如我们已经求出了 0到所有节点的距离之和， 现在想求2到所有节点的距离之和,

        为了方便说明，假设res[i]表示节点i到所有节点的距离和， Tree_k表示以k为根节点的子树

        （***）可以看到：    
            在edge(0,2)中间切一刀，把所有节点分成了两部分( Tree_j内的节点，和其他节点 ):

                part 1. Tree_2内的节点，即以2为根的那棵子树的所有节点(2,3,4,5)，在计算res[0]的时候， Tree_2里的所有节点到0的距离 比 到2的距离  对每一个节点来说都多了1 (总共多了4，即这个子树的节点数(2,3,4,5))
                
                part 2. 其他节点，即不包含 Tree_2 的节点 的其他节点(即0,1) , 在计算res[0]的时候， 这一部分的节点到0的距离 比 到2的距离 对每个节点来说都少了1 (总共少了2)


        所以，如果想通过 res[i]->res[j] , 需要的额外信息:
            1. 以节点j为根的那棵子树(记为Tree_j)的所有节点(包括j)，记为 cnt[j]
            2. 节点j到 Tree_j 内所有节点的距离和 ， 记为 sums[j]
        
            需要满足的条件:
            j是i的孩子节点
    
        把上面的情况广义化一下:

        假设i是j的父节点，且res[i]已知，求res[j]:
            res[j] =  part1里的节点到j的距离 + part2里的节点到j的距离

            part1里的节点到j的距离:
                就是sums[j].

            part2里的节点到j的距离:
                res[i]是所有节点到i的距离，part2不需要Tree_j的节点到i的距离，所以用 res[i] - sums[j]
            但sums[j]是Tree_j的节点到j的距离，因此需要做一个offset的补偿，这部分补偿就是 根据part1和part2的节点数来做的补偿，part1部分就是Tree_j的节点数，就是cnt[j],
            part2的节点数就是(N-cnt[j]), 补偿方法上面已经说过了( (***)那里 )， 然后就是：
                
            ( res[i]-sums[j]-cnt[j] ) + (N-cnt[j])  
                
        res[j] = sums[j] + ( res[i]-sums[j]-cnt[j] ) + (N-cnt[j])  
               = res[i] - cnt[j] + (N-cnt[j]);
               = res[i] + N - 2*cnt[j];
        
        后边就好做了.

        实现的时候注意:
            1. 无向图，记得两边都存
            2. 做两次dfs，第一次初始化cnt和sums， 第二次求res
*/

class Solution {
    private int [] subtreeSums = new int[10010];
    private int [] subtreeCnt = new int[10010];
    private Map<Integer, List<Integer>> mp = new HashMap<>();
    public int[] sumOfDistancesInTree(int N, int[][] edges) {
        if ( N==0 ) return new int[]{};
        for (int i = 0; i < N; i++) 
            mp.put(i,new ArrayList<Integer>());
        // 构建邻接表
        for ( int [] edge:edges ){
            mp.get(edge[0]).add(edge[1]);
            mp.get(edge[1]).add(edge[0]);
        }
        // 初始化subtreeSums 和 subtreeCnt
        dfs( -1, 0 );
        int [] res = new int[N];
        res[0] = subtreeSums[0];
        solve( res, -1, 0, N );
        return res; 
    }

    void dfs( int pre, int r ){
        if ( mp.get(r)==null ) return ;
        for ( int child:mp.get(r) ){
            if ( pre==child ) continue;
            dfs( r, child );
            subtreeCnt[r] += subtreeCnt[child];
            subtreeSums[r] += ( subtreeSums[child]+subtreeCnt[child] );
        }
        subtreeCnt[r]+=1;
    }

    void solve( int [] res, int pre, int father, int N ){
        if ( mp.get(father)==null ) return ;
        for ( int child:mp.get(father) ){
            if ( child==pre ) continue;
            //int left_part = res[father] - subtreeSums[child] - subtreeCnt[child] + ( N-subtreeCnt[child] );
            //int right_part = subtreeSums[child];
            //res[child] = left_part + right_part;
            res[child] = res[father] - subtreeCnt[child] + ( N-subtreeCnt[child] );
            solve(res, father, child, N);
        }
    }
}