/*
    问题描述:
        给定在 xy 平面上的一组点，确定由这些点组成的矩形的最小面积，其中矩形的边平行于 x 轴和 y 轴。

        如果没有任何矩形，就返回 0。

        示例 1：

        输入：[[1,1],[1,3],[3,1],[3,3],[2,2]]
        输出：4
        示例 2：

        输入：[[1,1],[1,3],[3,1],[3,3],[4,1],[4,3]]
        输出：2
         

        提示：

        1 <= points.length <= 500
        0 <= points[i][0] <= 40000
        0 <= points[i][1] <= 40000
        所有的点都是不同的。

    问题分析:
        方法一: 扫描线
            先对点集合按照高从低到高排序..
            map[h]记录高为h的横坐标集合.. 
            
            对于高为h的情况, 遍历高小于h的每一个情况, 得到高度差
            然后扫描横坐标，  找到满足条件的横坐标，得到了水平的差， 于是可以得到矩形的高和宽，然后计算面积..

        方法二: 对角线扫描的思想
            这个思想简直太棒了.. 
            
            一个矩形的确定，其实只要确定四个点就行了， 而对角的两个点的位置却包含了四个点的位置信息，

            例如 一个矩形 只要知道了左上角(a,b) 和右下角(c,d) , 那么右上角和左下角也知道了，分别为(a,d) (c,b)

            所以，我们就枚举所有两个点的组合，然后看另外两个点是否存在。。如果存在的话，说明就可以组成矩形，然后计算面积就行了..

            判断点是否存在就用集合就可以了.. （可以对坐标进行编码 变一维
*/

class Solution1 {
public:
    int minAreaRect(vector<vector<int>>& points) {
        // 扫描线
        map<int, vector<int>> mp; // mp[h]为高度为h的点的集合
        if (points.size()==0 ) return 0;
        sort( points.begin(), points.end(), [](vector<int>&a, vector<int>&b){
            return a[1]<b[1] || (a[1]==b[1] && a[0]<b[0]);
        } );    
        vector<int> pre;
        int pre_h=INT_MIN, h=points[0][1], i=0, res=INT_MAX;
        while( i<points.size() ){
            vector<int> cur; // 记录高为h的点的横坐标情况    
            h = points[i][1];
            while( i<points.size() && points[i][1]==h ){
                cur.push_back(points[i][0]);
                ++i;
            }
            for ( auto e:mp ){
                // 计算两层之间的情况
                int a=0, b=0;
                auto pre = e.second;
                while( a<pre.size() && b<cur.size() ){
                    if ( pre[a]<cur[b] ) ++a;
                    else if ( pre[a]>cur[b] ) ++b;
                    else{
                        int ra=a+1;
                        int rb=b+1;
                        while( ra<pre.size() && rb<cur.size() ){
                            if( pre[ra]>cur[rb] ) ++rb;
                            else if ( pre[ra]<cur[rb] ) ++ra;
                            else{
                                res = min( res, (h-e.first)*(pre[ra]-pre[a]) );
                                break;
                            }
                        }
                        ++a;
                        ++b;
                    }
                }
            }
            mp[h] = cur;
        }
        return res==INT_MAX?0:res;
    }
};


class Solution2 {
public:
    int minAreaRect(vector<vector<int>>& points) {
        int res = INT_MAX;
        unordered_set<int> st;
        for ( auto p:points )
            st.insert( encode(p[0], p[1]) );
        for ( int i=0; i<points.size(); ++i ){
            for ( int j=i+1; j<points.size(); ++j ){
                if ( points[i][0]==points[j][0] || points[i][1]==points[j][1] )
                    continue;
                if ( st.count(encode(points[i][0], points[j][1])) && st.count(encode(points[j][0], points[i][1])) )
                    res = min( res, abs(points[i][0]-points[j][0])*abs(points[i][1]-points[j][1]));
            }
        }
        return res==INT_MAX?0:res;
    }

    inline int encode( int x,int y ){
        return x*40010+y;
    }
};