/*
    问题描述:
        这题问题描述有点猛... 不好在这里说... 给链接自己看吧
        https://leetcode-cn.com/problems/the-skyline-problem/

    问题分析:
        方法一: 线段树
        
        因为本题N比较大，也需要做离散化处理， 离散化处理在#699提过了，这里不作赘述

        本题线段树实现的功能:
            1. 单点查询
            2. 区间更新最大值
            例如 [3,0,0,3] 对 区间[0~3]更新最大值2后， 该区间就成了[3,2,2,3]
        
        本题思路:
            1. 通过线段树来得到问题描述里的图B
            2. 得到图B就简单了，直接扫描，只要值出现变化，就选变化后的那个值

            如果这么做的话，需要将每一个点看作是一个区间，
            例如 1 变成[1,1] , 2变成[2,2] 
            从:
                .  .  .  . 
                1  2  3  4
            变成：
                .   .   .   .   .
                  1   2   3   4
            
            非区间化的 [l,r] 就是区间化后的[l,r-1] （看上面的例子就理解了
            因此，我们在进行区间更新最大值操作的时候，不再是[l,r]而是[l,r-1]
            然后就可以了。
            

             ___3___   
            |    ___|__2__
            |   |   |     |
            |   |   |     |
            |___|___|_____|
            1   2   3    4 
            对于这样的图形，我们要保存的是 [ [1,3], [3,2], [4,0] ] 
            对于3这个点，又有2 又有3， 因此以点为单位很难做
            
            区间化后，就变成了
             ___3___   
            |    ___|__2__
            |   |   |     |
            |   |   |     |
            |___|___|_____|____
              1   2    3    4 
            
            很清楚的能看出[1,3],[3,2],[4,0]的变化结果.

        本题踩的坑在后面的代码中标出，都是线段树实现上的逻辑错误...    
*/                  
typedef struct{
    int l,r,maxi,lazy;    
}nodes;
class Solution {
public:
    vector<nodes> tree;
    
    void build( int i, int left, int right ){
        if ( left==right ){
            tree[i].l=tree[i].r=left;
            tree[i].lazy = 0;
            tree[i].maxi = 0;
            return ;
        }
        int mid = (left+right)/2;
        build(i<<1, left, mid);
        build(i<<1|1, mid+1, right);
        tree[i].l = left; tree[i].r=right;
        tree[i].maxi = max(tree[i<<1].maxi, tree[i<<1|1].maxi);
        tree[i].lazy=0;
    }
    
    void push_down( int i ){
        if ( !tree[i].lazy || tree[i].l==tree[i].r ) return ;
        int val = tree[i].lazy;
        // 这里对子节点的处理，要跟update那块核心代码保持一致
        tree[i<<1].maxi = max( tree[i<<1].maxi, val );
        tree[i<<1].lazy = max( tree[i<<1].lazy, val);
        tree[i<<1|1].maxi = max( tree[i<<1|1].maxi, val );
        tree[i<<1|1].lazy = max( tree[i<<1|1].lazy, val);
        tree[i].maxi = max(tree[i<<1].maxi, tree[i<<1|1].maxi);
        tree[i].lazy = 0;
    }
    
    void range_update( int i, int left,int right, int val ){
        if ( left>right ) return ;
        // 这部分很容易出错
        if ( left<=tree[i].l && tree[i].r<=right ){
            // 一定要想清楚对lazy节点的处理！！！
            // 因为要考虑多次更新但却没有向下传递时的情况
            // 这里对lazy节点的处理就是 取最大的那个
            tree[i].maxi = max( tree[i].maxi, val );
            tree[i].lazy = max(tree[i].lazy,val);
            return ;
        }
        push_down(i);
        int mid = (tree[i].l+tree[i].r)/2;
        if ( right<=mid  ) range_update( i<<1, left, right, val );
        else if ( left>mid ) range_update(i<<1|1, left, right, val);
        else{
            range_update(i<<1,left, mid, val);
            range_update(i<<1|1, mid+1, right,val);
        }
        tree[i].maxi = max(tree[i<<1].maxi, tree[i<<1|1].maxi);
    }
    
    
    int query(int i,int idx){
        if ( idx==tree[i].l && tree[i].r==idx ) return tree[i].maxi;
        int mid = (tree[i].l+tree[i].r)/2;
        push_down(i);
        if ( idx<=mid ) return query(i<<1,idx);
        return query(i<<1|1, idx);
    }
    
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        if ( buildings.size()==0 ) return {};
        // 区间更新，单点查询
        // 离散化处理
        unordered_map<int,int> encode;
        unordered_map<int,int> decode;
        set<int> tmp;
        for ( auto e:buildings ){
            tmp.insert(e[0]);
            tmp.insert(e[1]);
        }
        int idx=1;
        for ( auto e:tmp ){
            encode[e] = idx;
            decode[idx] = e;
            ++idx;
        }
        for ( int i=0; i<buildings.size(); ++i ){
            buildings[i][0] = encode[buildings[i][0]];
            buildings[i][1] = encode[buildings[i][1]];
        }
        // 离散化结束


        int n=0;
        vector<vector<int>> res;
        vector<vector<int>> ans;
        // 确定n大小
        for( auto e:buildings )
            if ( e[1]>n ) n = e[1];
        tree.resize(n*4);
        // 初始化树
        build( 1, 1,n+1 );
        // 对[l,r-1]更新最大值
        for ( auto e:buildings )
            range_update( 1, e[0], e[1]-1, e[2] );
        // 最后遍历一遍，只要出现变化，就选变化后的那个值
        int pre = -1;
        for ( int i=1; i<idx; ++i ){
            int h = query(1,i);
            if ( h!=pre ){
                pre = h;
                ans.push_back({decode[i], h});
            }
        }
        return ans;
    }
};
