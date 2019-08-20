/*
    问题描述：
        就是给一堆矩阵，求矩阵的并集面积. 
        矩阵的形式的左下角坐标(x1,y1)和右上角的坐标(x2,y2).

    问题分析:
        本题是很好的一道题, 考点: 扫描线, 离散化, 用线段树处理区间问题
        
        本题的核心就是考扫描线的.

        用网上某博客的师兄的话来比喻扫描线思想就是:
            一段公路上右很多区间要收不同的费用，区间的开始给一个标记，表示该段区间对答案有贡献，
            区间的结束拿走该标记，表示该段区间对答案的贡献结束。

        当要使用扫描线算法的时候，先确定一个方向，在本题中就假设是从下网上的扫描.

        而扫描线也顾名思义，本题的“线” 就是矩阵的上下两条边
        
        我们把“线”抽象成一个结构体, 它包括四个变量:
            x1: 线的左端点
            x2: 线的右端点
            y : 线的纵轴高度
            flag: -1表示矩阵的上边, 1表示是矩阵的下边
        
        每个矩阵都能提供两个上面这样的"线"节点

        先把这些得到的线，按照高度排序，

        然后在从下往上扫描的过程中，
        
        将在不同高度的“线” 都投影到同一个x轴上,
        
        从而围城的子矩形，子矩形的宽，就是y之间的差

        关键在于长的计算, 

        我们每次遇到一条线，就给对应区间[x1, x2]加flag

        子矩形的长就是当前x轴上大于0的区间长度.

        flag的1和-1 也是矩阵 "加入" 和 "离开" 的体现.

        另外，因为矩阵的区间非常大，所以我们要进行离散化处理,
        将
            [x0,x1,x2,x3...,xn] => [0,1,2,3,..n]
        然后计算区间长度的时候, 例如 "xn-xm" 的时候,我们再给还原回来
            [0,1,2,3,...,] => [x0,x1,x2,x3...,xn] 
        可以把[0,1,2,3,...,n]看成是 x在x数组中的下标（）.
        在进行区间操作的时候，实际操作的是坐标i，真正计算区间差的时候，用的是x[i]

        通用部分讲完以后，接下来就是实现的上方法了:
            方法一:
                暴力，开一个cnt数组来表示x轴， 每次进行区间的加减flag的时候，都遍历一遍区间进行操作
                然后再遍历一遍找 cnt[i]>0 的区间，并加上它的实际长度 ( 因为这里的操作是再离散化后的坐标上的 )

            方法二:
                使用线段树来进行区间操作:
                    1. 给指定区间加上flag
                    2. 查询大于0的区间长度
                
                为了实现这两个功能，
                区间保存的信息是:
                    1. cnt  : 表示当前节点区间目前累计的flag的值
                    2. cover: 表示当前区间内 cnt大于0的区间长度 (在进行值的更新时, 要将x转换成x[i])
                
                这里再补充一点:
                    正是因为线段树的区间节点之间，上层区间和下层的孩子区间有着关系，
                    在更新上层区间的时候会接连更新到下层区间，
                    而延迟标记就是 延迟 上层区间对下层区间更新的标记
                    
                    但是在本题中，每一个区间可以看成是一个单位,
                    例如 有一个  "对[x1,x2]加1(flag==1)" 操作，就一定会有一个"对[x1,x2]减1(flag==-1)"操作
                    不会出现 "对[x1,x2]加1(flag==1)" ，然后 "对[x1,x3]减1, x1<x3<x2"
                    
                    因此，每一个区间变成了一个单位，本题的区间操作的实质还是单点操作，不需要引入延迟标记

                    用单点处理的思想即可， 把每个区间当成一个节点，只存在自底向上的更新(push_up)

                再补充一点:
                    线段树在处理区间问题的时候，对区间更新不再是[l,r]而是[l,r-1],
                    具体详见 #850 那里有提
*/  

# define mod 1000000007
class Solution1 {
public:
    int rectangleArea(vector<vector<int>>& rectangles) {
        if ( rectangles.size()==0 ) return 0;
        // O(N^2)的扫描线
        // 暴力
        // 离散化一下
        set<int> st;
        unordered_map<int,int> encode;
        vector<vector<int>> lines;
        vector<int> unique_sorted_x;
        
        int n = 0;
        for ( auto e:rectangles ){
            st.insert(e[0]);
            st.insert(e[2]);
        }
        int idx = 0;
        for ( auto e:st ){
            encode[e] = idx++;
            unique_sorted_x.push_back(e);
        }
        // 离散化结束
        for ( auto e:rectangles ){
            lines.push_back( {e[3], e[0], e[2], -1} ); //上边界
            lines.push_back( {e[1], e[0], e[2], 1} ); //下边界
        }
        sort( lines.begin(), lines.end() );
        int x1,x2,y, res=0;
        long height, width=0, pre_y=0,sig;
        vector<int> count( idx, 0 );
        for ( auto line: lines ){
            y = line[0];   sig = line[3]; 
            x1 = line[1];  x2=line[2];
            
            height = y-pre_y;
            pre_y = y;
            res = ( res + height * width )%mod;
            
            for ( int i = encode[x1]; i<encode[x2]; ++i )
                count[i] += sig;
            width = 0;
            for ( int j = 0; j<unique_sorted_x.size()-1; ++j ){
                if ( count[j]>0 )
                    width += ( unique_sorted_x[j+1]-unique_sorted_x[j] );
            }
        }
        return res;
    }
};


//=================解法二: 线段树==========================
# define mod 1000000007

typedef struct{
    int l,r,cnt;    
    int covered;
    bool isLeaf;
}nodes;

class Solution2 {
public:
    vector<int> unique_sorted_x;
    vector<nodes> tree;
    int  idx;
    
    void build( int i, int left, int right ){
        if ( left>=right ){
            tree[i].l = tree[i].r = left;
            tree[i].cnt = 0;
            tree[i].covered = 0;
            tree[i].isLeaf = true;
            return ;
        }
        int mid = ( left+right )/2;
        build( i<<1, left, mid );
        build( i<<1|1, mid+1, right);
        tree[i].l=left; tree[i].r=right;
        tree[i].cnt = 0;
        tree[i].covered = 0;
        tree[i].isLeaf = false;
    }
    
    void push_up(int i){  //更新当前cover
       if ( tree[i].cnt>0 ){
            tree[i].covered = unique_sorted_x[tree[i].r+1] -  unique_sorted_x[tree[i].l];
        }else if ( tree[i].isLeaf ) tree[i].covered = 0;
        else tree[i].covered = tree[i<<1].covered + tree[i<<1|1].covered;
    }
    
    void update( int i , int left ,int right, int val ){
        if ( left<=tree[i].l && tree[i].r<=right ){
            tree[i].cnt += val;
            push_up(i);
            return ;
        }
        int mid = (tree[i].l+tree[i].r)/2;
        if ( right<=mid ) update(i<<1, left, right, val);
        else if ( left>mid ) update( i<<1|1, left, right,val );
        else{
            update( i<<1,left,mid,val );
            update( i<<1|1, mid+1, right,val);
        }
        push_up(i);
    }
    
    int rectangleArea(vector<vector<int>>& rectangles) {
        if ( rectangles.size()==0 ) return 0;
        // O(NLogN)的扫描线
        // 线段树维护区间
        // 离散化一下
        set<int> st;
        unordered_map<int,int> encode;
        vector<vector<int>> lines;
        
        int n = 0;
        for ( auto e:rectangles ){
            st.insert(e[0]);
            st.insert(e[2]);
        }
        idx = 0;
        for ( auto e:st ){
            encode[e] = idx++;
            unique_sorted_x.push_back(e);
        }
        // 离散化结束
        for ( auto e:rectangles ){
            lines.push_back( {e[3], e[0], e[2], -1} ); //上边界
            lines.push_back( {e[1], e[0], e[2], 1} ); //下边界
        }
        sort( lines.begin(), lines.end() );
        tree.resize(idx*4);
        build( 1, 0, idx );
        int x1,x2,y, res=0;
        long height, width=0, pre_y=0,sig;
        int wt;
        vector<int> count( idx, 0 );
        for ( auto line: lines ){
            y = line[0];   sig = line[3]; 
            x1 = line[1];  x2=line[2];
        
            height = y-pre_y;
            pre_y = y;
            res = ( res + height * width )%mod;
            // 用线段树来进行区间维护
            update( 1, encode[x1], encode[x2]-1, sig );
            width = tree[1].covered;
        }
        return res;
    }
};
