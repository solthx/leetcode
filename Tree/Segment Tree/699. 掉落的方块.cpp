/*
    问题描述：
        在无限长的数轴（即 x 轴）上，我们根据给定的顺序放置对应的正方形方块。

        第 i 个掉落的方块（positions[i] = (left, side_length)）是正方形，其中 left 表示该方块最左边的点位置(positions[i][0])，side_length 表示该方块的边长(positions[i][1])。

        每个方块的底部边缘平行于数轴（即 x 轴），并且从一个比目前所有的落地方块更高的高度掉落而下。在上一个方块结束掉落，并保持静止后，才开始掉落新方块。

        方块的底边具有非常大的粘性，并将保持固定在它们所接触的任何长度表面上（无论是数轴还是其他方块）。邻接掉落的边不会过早地粘合在一起，因为只有底边才具有粘性。

        返回一个堆叠高度列表 ans 。每一个堆叠高度 ans[i] 表示在通过 positions[0], positions[1], ..., positions[i] 表示的方块掉落结束后，目前所有已经落稳的方块堆叠的最高高度。

            示例 1:

            输入: [[1, 2], [2, 3], [6, 1]]
            输出: [2, 5, 5]
            解释:

            第一个方块 positions[0] = [1, 2] 掉落：
            _aa
            _aa
            -------
            方块最大高度为 2 。

            第二个方块 positions[1] = [2, 3] 掉落：
            __aaa
            __aaa
            __aaa
            _aa__
            _aa__
            --------------
            方块最大高度为5。
            大的方块保持在较小的方块的顶部，不论它的重心在哪里，因为方块的底部边缘有非常大的粘性。

            第三个方块 positions[1] = [6, 1] 掉落：
            __aaa
            __aaa
            __aaa
            _aa
            _aa___a
            -------------- 
            方块最大高度为5。

            因此，我们返回结果[2, 5, 5]。
             

            示例 2:

            输入: [[100, 100], [200, 100]]
            输出: [100, 100]
            解释: 相邻的方块不会过早地卡住，只有它们的底部边缘才能粘在表面上。

            注意:

            1 <= positions.length <= 1000.
            1 <= positions[i][0] <= 10^8.
            1 <= positions[i][1] <= 10^6.
            
    问题分析:
        方法一: 线段树
            线段树很擅长处理 有关区间操作的题， 比如这题， 
            只要每次落一个箱子，把箱子的长度看成是一个区间，
            然后把这段区间的值 重新置成 "该区间当前的最大值+箱子的高度"
            然后再重新去查询整个区间的最大值， 并加入res中
            思路非常清晰明了。

            这题考察的另一个东西就是对线段树的离散化处理， 因为线段树的开销是4倍的数组长度，
            就本题的10^8来说，别说4倍，1倍都开不动。。 因此需要离散化处理。

            至于什么是离散化处理，就举个例子:
                [ [1000000000,1], [999999,2] ]
            如果positions数组长成上面的这样样子，
            那么我们要开1000000000*4的大小来存储这两个区间，显然是不合理的，
            而离散化处理，就是一个编码解码的过程( 本题中只有编码 )
                [999999, 999999+2] -> [1, 1+2]
                [1000000000, 1000000000+1] -> [2, 2+1]
            就类似上面的一个过程.
                实现方法就是：
                    1. 开两个map ( unordered_map<int,int> encode, decode; )
                    2. 开一个set ( set<int> st; )
                    3. 先把区间两端的值的大小存入set中
                    4. 因为set是内部有序的，所以重新给原本的区间位置从1开始编码
                        rank = 1
                        for ( auto e:st ):
                            encode[e] = rank
                            decode[rank] = e
                    5. 然后把原本数组里的值 e 都用 encode[e] 来替代，
                    如果最后返回的结果里有需要原区间的位置，就再用decode[c]来还原
            
            本次线段树实现的功能:
                1. 区间查询最大值
                2. 区间赋值
*/


typedef struct{
    int l;  // 左孩子的index 
    int r;  
    int maxi;  //[l,r]中的最大值
    int change; // 懒惰节点，INT_MIN 表示 无需更新
}nodes;

class Solution {
public:
    vector<nodes> tree;
    
    void push_up( int r ){
        tree[r].maxi = max( tree[r*2].maxi, tree[r*2+1].maxi);
    }
    
    void push_down( int i ){
        // 第二段核心代码， 因为是赋值，所以和板子会有所不同
        if ( tree[i].change==INT_MIN || tree[i].l==tree[i].r ) return ;
        int addition = tree[i].change;
        tree[i].change=INT_MIN;
        tree[i*2].maxi = addition;
        tree[i*2+1].maxi = addition;
        tree[i*2].change = addition;
        tree[i*2+1].change = addition;
        push_up(i);
    }
    
    void build( int i, int left, int right ){
        if ( left==right ){
            tree[i].l = tree[i].r= left;
            tree[i].maxi = 0;
            tree[i].change = INT_MIN;
            return;
        }
        int mid = (left+right)/2;
        build( i*2, left, mid );
        build( i*2+1, mid+1, right );
        tree[i].maxi = max( tree[i*2].maxi, tree[i*2+1].maxi);
        tree[i].l=left;  
        tree[i].r=right;
    }
    
    void range_update( int i, int left, int right, int val ){
        if ( tree[i].l>=left && tree[i].r<=right ){
            // 这个地方是核心代码
            // 因为是赋值，所以是对最大值直接赋值
            // 并更新懒惰节点
            tree[i].maxi = val;
            tree[i].change = val;
            return ;
        }
        push_down(i);
        int mid = ( tree[i].l +tree[i].r )/2;
        if ( right<=mid ) range_update( i*2, left, right, val );
        else if ( left>mid ) range_update( i*2+1, left, right, val );
        else{
            range_update( i*2, left, mid, val );
            range_update( i*2+1, mid+1, right, val );
        }
        push_up(i);
    }
    
    int query( int i, int left, int right ){
        if ( left<=tree[i].l && tree[i].r <= right ) return tree[i].maxi;
        push_down(i);
        int mid = (tree[i].l+tree[i].r)/2;
        if ( right<=mid ) return query(2*i, left, right);
        else if ( left>mid ) return query( 2*i+1, left, right );
        else return max(query( 2*i,left, mid ) , query( 2*i+1, mid+1, right ));
    }
    
    vector<int> fallingSquares(vector<vector<int>>& positions) {
        // 线段树维护区间最大值, 并进行区间赋值
        // 进行离散化处理
        int n = 0; 
        vector<vector<int>> ps;
        set<int> tmp;
        // 把数组重新变成( x,y,height )的形式
        for ( auto e:positions ){ 
            ps.push_back({e[0],e[0]+e[1]-1, e[1]});  
            tmp.insert(e[0]);  
            tmp.insert(e[0]+e[1]-1);
        }
        int idx=1;
        // 进行离散化处理
        map<long,int> mp;
        for ( auto e:tmp )
            mp[e] = idx++;
        for ( int i=0; i<ps.size(); ++i ){
            ps[i][0] = mp[ps[i][0]];
            ps[i][1] = mp[ps[i][1]];
        }
        // 得到离散化处理后的数组长度
        for ( auto e:ps ) n = max( e[0], n );
        // 初始化
        tree.resize(n*4);
        build( 1, 1, n );
        vector<int> res;
        // 进行区间赋值
        for ( auto e:ps ){
            //把这段区间的值 重新置成 "该区间当前的最大值+箱子的高度"
           range_update( 1, e[0], e[1], e[2]+query(1,e[0],e[1]) );
           // 赋值后再查询整个区间的最大值
           res.push_back( query(1,1,n) );
        }
        return res;
    }
};
    