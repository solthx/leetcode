/*
    问题描述:
        这题看图比较好理解: https://leetcode-cn.com/problems/perfect-rectangle/
    
    问题分析:
        方法一： 
            扫描线+暴力 TLE
            把每一个矩形拆成上边和下边的两条line = { x1, y, x2, val }
            
            然后按照y坐标排序， 自底向上扫描，

            上边的val是1 ， 下边的val是-1,

            每遇到一条线，就给[x1,x2]加val

            每次次操作，就把所有相同y 的线，进行操作，
            操作完之后， 如果最左区间和最右区间 一直保持是1的话， 那么就说明这一个高度没有重叠，也没有缺失，

            ps: 尽管可以用线段树来做区间维护操作，，但太麻烦了，，不想再写线段树了。。下次再补上把

            如果每一个高度都这样，那么就返回true， 否则false

        方法二:
            方法一扫描线的思想是对的，但是需要优化.

            依然是把矩形抽象成每一条线,

            这次，对于线的操作，不再模拟模拟区间，
            而是用set来保存每一个区间，用pair类型来存，

            把线按照一定规则拍完序之后， 

            遇到上边，删除区间，
            遇到下边，就插入，
                插入之前，先判断插入之后会不会有重叠  
                用lower_bound找到首个大于等于当前区间的 区间，

                假设找到的这个位置是it ， 

                所以，当前区间就插入到 (it-1) 和 it 之间的这个位置， 只要判断是否有重叠就行了.

            对于缺失的情况，
            可以把每一个子矩阵的面积加起来， 然后再计算并之后的矩阵（  (rx-lx)*(ry-ly) ）

            如果两者面积不相等，那么就说明有缺失或重叠 

            pps: 
                直接用面积来判断是不可以的， 不信你随便就能举个反例出来。 我就不举了。

*/

// 扫描线+模拟区间  TLE
class Solution1 {
public:
    bool isRectangleCover(vector<vector<int>>& rect) {
        // 7:05
        auto cmp = []( vector<int>& a, vector<int>&b ){
            return a[1]<b[1];
        };
        vector<vector<int>> lines;
        int l=INT_MAX,r=INT_MIN;
        int pre = INT_MAX;
        for ( auto mat:rect ){
            l = min(l,mat[0]);
            r = max(r,mat[2]);
            pre = min(pre, mat[1]);
            lines.push_back( {mat[0], mat[1], mat[2], 1} );
            lines.push_back( {mat[0], mat[3], mat[2], -1} );
        }
        sort( lines.begin(), lines.end(), cmp );
        int i=0;
        unordered_map<int,int> mp;
        while( i<lines.size() ){
            while( i<lines.size() && lines[i][1]==pre ){
                for ( int t=lines[i][0]; t<lines[i][2]; ++t )
                    mp[t] += lines[i][3];
                ++i;
            }
            if ( i<lines.size() )
                pre = lines[i][1];
            if ( i<lines.size() )
                for ( int x = l; x<r; ++x )
                    if ( mp[x]!=1 ){
                        return false;
                    }
        }
        return true;
    }
};



// 扫描线 + set检测区间重合
class Solution {
public:
    bool isRectangleCover(vector<vector<int>>& rect) {
        auto cmp = []( vector<int>& a, vector<int>&b ){
            if ( a[1]!=b[1] )
                return a[1]<b[1];
            else{
                if ( a[3]!=b[3] ) return a[3]<b[3];
                return a[0]<b[0];
            }
        };
        vector<vector<int>> lines;
        int lx=INT_MAX,rx=INT_MIN,ly=INT_MAX,ry=INT_MIN;
        int pre = INT_MAX;
        int sums=0;
        for ( auto mat:rect ){
            lx = min(lx,mat[0]);
            rx = max(rx,mat[2]);
            ly = min(ly,mat[1]);
            ry = max(ry,mat[3]);
            sums += ( mat[2]-mat[0] )*(mat[3]-mat[1]);
            lines.push_back( {mat[0], mat[1], mat[2], 1} );
            lines.push_back( {mat[0], mat[3], mat[2], -1} );
        }
        if ( sums!= (rx-lx)*(ry-ly) ) return false; //过滤掉缺失的情况，后面判断重叠情况
        sort( lines.begin(), lines.end(), cmp );
        int i=0;
        set<pair<int,int>> st;
        while( i<lines.size()  ){
            pair<int,int> p = {lines[i][0], lines[i][2]};
            if ( lines[i][3]>0 ){
                auto it = st.lower_bound(p);
                if ( it!=st.end() && it->first<lines[i][2] ) return false; // 判断是否 和插入位置的右边的区间有重叠
                if ( it!=st.begin() && (--it)->second>lines[i][0] ) return false; // 判断是否 和插入位置的左边的区间有重叠
                st.insert(p); // 都没重合就插入
            }else
                st.erase( st.find( p ) );
            ++i;
        }
        return true;
    }
};