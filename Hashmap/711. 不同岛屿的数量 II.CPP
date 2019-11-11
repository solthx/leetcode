/*
    问题描述:
        给定一个非空01二维数组表示的网格，一个岛屿由四连通（上、下、左、右四个方向）的 1 组成，你可以认为网格的四周被海水包围。
        请你计算这个网格中共有多少个形状不同的岛屿。如果两个岛屿的形状相同，或者通过旋转（顺时针旋转 90°，180°，270°）、翻转（左右翻转、上下翻转）后形状相同，那么就认为这两个岛屿是相同的。

        样例 1:

        11000
        10000
        00001
        00011
        给定上图，返回结果 1。

        注意 ：

        11
        1
        和

        1
        11
        是相同的岛屿。因为我们通过 180° 旋转第一个岛屿，两个岛屿的形状相同。

         

        样例 2:

        11100
        10001
        01001
        01110
        给定上图，返回结果 2。

        下面是两个不同的岛屿：

        111
        1
        和

        1
        1
         

        注意 ：

        111
        1
        和

        1
        111
        相同的岛屿。因为我们通过上下翻转第一个岛屿，两个岛屿的形状相同。

    问题分析:
        本题的一个难点就是，如何对得到的形状进行唯一的编码(注意，是形状)
        
        因为我们肯定是bfs或者dfs来得到这个图形的所有点的坐标， 因此，被编码的元素就是一个点的集合。

        我们可以对它进行各种旋转， 可以知道， 同一个图形，可以出现8种不同的样子。

        所以，当我们得到一块区域的坐标点集的时候， 就根据这一个来把其他的7个的样子也给弄出来。。

        即: (i,j) (i,-j), (-i,j), (-i,-j) 然后横纵坐标换一下，就得到了8个情况了。。

        得到8个情况以后， 因为可能是出现在坐标的各种位置， 所以对其进行类似“标准化”一样的操作， 即全部减去最小的那个坐标。。。这样就都被位移到原点的位置了

        最终，得到的8个点集就是标准化后的样子， 尽管表示的形状一样，但它们的内部的样子确是不一样的，因此，在对8个坐标点集进行排序。

        最后，再对8个点集进行排序。。。 然后取出其中特定的一个。。作为编码。。。
        （两次排序的目的，是为了内部坐标的顺序也是固定的） 
*/

class Solution {
public:
    int numDistinctIslands2(vector<vector<int>>& grid) {
        set<vector<vector<int>>> st;
        for ( int i=0; i<grid.size(); ++i )
            for ( int j=0; j<grid[0].size(); ++j ){
                if ( grid[i][j] == 1 ){
                    //cout<<i<<" "<<j<<endl;
                    vector<vector<int>> cur;
                    dfs( grid, i, j, cur );
                    process( cur );
                    st.insert(cur);
                }
            }
        return st.size();
    }
    
    void dfs( vector<vector<int>>& grid, int i, int j, vector<vector<int>>& cur ){
        if ( i<0 || i>=grid.size() || j<0 || j>=grid[0].size() || grid[i][j]==0 )
            return ;
        grid[i][j] = 0;
        cur.push_back({i,j});
        dfs( grid, i+1, j ,cur);
        dfs( grid, i, j+1 ,cur);
        dfs( grid, i-1, j ,cur);
        dfs( grid, i, j-1 ,cur);
    }
    
    void process( vector<vector<int>>& cur ){
        vector<vector<vector<int>>> shape( 8 );
        // 根据一种情况，得出8种情况
        for ( auto e:cur ){
            int i=e[0], j=e[1];
            shape[0].push_back({i,j});
            shape[1].push_back({j,i});
            shape[2].push_back({i,-j});
            shape[3].push_back({-j,i});
            shape[4].push_back({-i,j});
            shape[5].push_back({j,-i});
            shape[6].push_back({-i,-j});
            shape[7].push_back({-j,-i});
        }
        
        // 对每一个点确定顺序（排序），并归一化(减去最小值的坐标)
        for ( auto &e:shape ){
            sort( e.begin(), e.end() );
            int a = e[0][0], b=e[0][1];
            for ( auto & p:e ){
                p[0] -= a;
                p[1] -= b;
            }
        }
        
        // 确定shape的顺序
        sort( shape.begin(), shape.end() );
        cur = shape[7]; // 恒取第一个，其实这里取0～7的哪一个都可以。。
    }
};