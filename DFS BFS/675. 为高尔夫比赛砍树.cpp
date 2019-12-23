/*
    问题描述:
        你被请来给一个要举办高尔夫比赛的树林砍树. 树林由一个非负的二维数组表示， 在这个数组中：

        0 表示障碍，无法触碰到.
        1 表示可以行走的地面.
        比1大的数 表示一颗允许走过的树的高度.
        你被要求按照树的高度从低向高砍掉所有的树，每砍过一颗树，树的高度变为1。

        你将从（0，0）点开始工作，你应该返回你砍完所有树需要走的最小步数。 如果你无法砍完所有的树，返回 -1 。

        可以保证的是，没有两棵树的高度是相同的，并且至少有一颗树需要你砍。

        示例 1:

        输入:
        [
             [1,2,3],
             [0,0,4],
             [7,6,5]
        ]
        输出: 6
         

        示例 2:

        输入:
        [
             [1,2,3],
             [0,0,0],
             [7,6,5]
        ]
        输出: -1
         

        示例 3:

        输入:
        [
             [2,3,4],
             [0,0,5],
             [8,7,6]
        ]
        输出: 6

        解释: (0,0) 位置的树，你可以直接砍去，不用算步数
         

        提示: 矩阵大小不会超过 50x50 。

    问题分析:
        需要注意的坑是:
            只要不是0的地方都可以走！！只是轮不到砍这个高度的树的时候不能砍！！！！

        知道了这个以后，其实就好办了. 因为砍树的顺序，其实是确定的了，就是从小到大去砍.

        砍树的顺序固定以后，就是求每次砍完当前树，再去砍下一个树之间的最短距离就行了.

        因此，可以先用一个堆来保存所有需要砍的树，每次pop出树高最矮的那棵, 然后计算从当前位置到
        下一棵树的位置的最短距离， 如果去不了就返回-1

        题不难，本题难在实现上..

        因为按上面这么搞.. 就tle了..

        我以为是思路错了。。看了题解才知道，是可以优化的。。 主要是在实现上的优化:
            把二维变一维, queue里存数比存结构体或vector效率要高得多
                x,y的范围都是[0,50]
                所以可以
                    y*50+x = c 来编码,
                    y=c/50, x=c%50来解码

*/

class Solution {
public:
    int n,m;
    struct node{
        int y;
        int x;
        int val;
        node(int y_, int x_, int v):y(y_),x(x_),val(v){}
    };
    int cutOffTree(vector<vector<int>>& forest) {
        /*
            思路:
                用最小堆来保存<y,x,树高>
                每个下一次pop出来的值,  就是两个坐标的最短位置, 然后当前坐标变成上一次pop出来的坐标

            TLE:
                优化:
                    1. 用结构体代替vector
                    2. 把二维变一维, queue里存数比存结构体或vector效率要高得多
                        x,y的范围都是[0,50]
                        所以可以
                            y*50+x = c 来编码,
                            y=c/50, x=c%50来解码
        */
        auto cmp = [](node&a, node&b){
            return a.val>b.val;
        };
        priority_queue<node, vector<node>, decltype(cmp)> q(cmp);
        if ( forest.size()==0 || forest[0].size()==0 || forest[0][0]==0 ) return -1;
        n = forest.size();
        m = forest[0].size();
        for ( int i=0; i<n; ++i )
            for ( int j=0; j<m; ++j )
                if ( forest[i][j]>0 )
                    q.push(node(i,j,forest[i][j]));
        node pre = node(0,0,forest[0][0]);
        int route=0, res = 0;
        while(q.size()>0){
            auto cur = q.top(); q.pop();
            if ( (route = getRoute(pre, cur, forest))>=0 ){
                forest[pre.y][pre.x] = 1;
                res += route;
                pre = cur;
            }else return -1;
        }
        return res;
    }

    int getRoute( node& start, node& end, vector<vector<int>>& forest ){
        if ( start.x==end.x && start.y==end.y ) return 0;
        int dir[4][2]={{1,0},{0,1},{-1,0},{0,-1}};
        int step=0;
        int vis[3000]={false};
        queue<int> q;
        q.push(start.y*50 + start.x);
        vis[start.y*50+start.x]= true;
        while( q.size()>0 ){
            for ( int j=q.size(); j>0; --j ){
                auto cur = q.front(); q.pop();
                for ( int k=0; k<4; ++k ){
                    int y = cur/50 + dir[k][0];
                    int x = cur%50 + dir[k][1];
                    if ( x>=0 && y>=0 && x<m && y<n && !vis[y*50+x] && forest[y][x]!=0 ){
                        if ( y==end.y && x==end.x ) return step+1;
                        vis[y*50+x] = true;
                        q.push(y*50+x);
                    }
                }
            }
            ++step;
        }
        return -1;
    }
};

