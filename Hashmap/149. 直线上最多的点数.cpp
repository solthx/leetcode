/*
    问题描述:
        给定一个二维平面，平面上有 n 个点，求最多有多少个点在同一条直线上。
        示例 1:

        输入: [[1,1],[2,2],[3,3]]
        输出: 3
        解释:
            ^
            |
            |        o
            |     o
            |  o  
            +------------->
            0  1  2  3  4
        示例 2:

        输入: [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]
        输出: 4
        解释:
            ^
            |
            |  o
            |     o        o
            |        o
            |  o        o
            +------------------->
            0  1  2  3  4  5  6

    问题分析:
        O(N^2)的思路主要是这样的:
            确定一个点(假设这个点为<X,Y>)之后：
                假设所有的点和<X,Y>构成的斜率集为{k1,k2,...}
                
                那么就看当斜率为多少时， 这条线上的点是最多的.
                
                mp[k]表示 过<X,Y>斜率为k的线上，有多少个点(这个点的个数不包括自己, 因为可能会出现重复，所以自己的情况单独讨论，后面会说)  .

                res = max( res, max(mp[k]) )
        
            本题的两个坑在于:
                1. 因为浮点数的精度问题，斜率不好保存，
                这里用pair来保存， 并用gcd来对斜率进行化简.
                例如: {a, b}表示 a/b ， 3/9和 2/6斜率都是 1/3， 我们计算a和b的最大共约数d, 然后 a/=d, b/=d;
                最终用化简后的{ a, b } 来代替a/b=k.

                在这里，水平和垂直的情况, 可以进行单独的讨论. 

                2. 点可能会出现重叠的情况，要预先做处理. 
                这里用的处理方式是, 先计算出每个坐标上有多少个重复点,
                cnt[{a,b}] 记录了在坐标<a,b>上有多少个点

                然后 当确定一个点<X,Y>之后，再遍历其他点的时候，如果遇到<X,Y>那就直接continue了，
                最终， 过<X,Y>,斜率为a/b的直线上 拥有点数量 = mp[{a,b}] + cnt[{a,b}] 
                
            方法二和方法一思想一样，
            不同的是方法二不需要在编码的时候讨论了，
            原因在于gcd实现的不同:
                来看看下面两种gcd的实现:

                int gcd1( int x, int y ){
                    return x%y==0 ? y :  gcd( y,x%y );
                }
                
                int gcd2(int x, int y) {
                    return (y == 0) ? x : gcd(y, x%y);
                }
            显然，当y为0的时候，gcd1会出bug, 所以写gcd的时候，应该写gcd2的这种，
            在y==0的时候返回！
*/

class Solution1 {
public:
    int maxPoints(vector<vector<int>>& points) {
        // y=kx+b
        map<pair<int,int>, int> cnt;
        int res=0;
        for ( auto p:points )
            res = max(res, ++cnt[make_pair(p[0],p[1])]);
        if ( points.size()==0  ) return 0;
        int n = points.size();
        for ( int i=0; i<n; ++i ){
            int x = points[i][0]; // 当前坐标
            int y = points[i][1];
            int addition = cnt[make_pair(x,y)]; // 重复点的个数
            map<pair<int,int>, int> mp;
            for ( int j=i+1; j<n; ++j ){
                int nx = points[j][0];
                int ny = points[j][1];
                if ( x==nx && y==ny ) continue;
                int dh = y - ny;
                int dw = x - nx;
                //编码
                if ( (dh>0 && dw<0) || (dw>0 && dh<0) ){
                    dh = -abs(dh);
                    dw = abs(dw);
                }else{
                    dh = abs(dh);
                    dw = abs(dw);
                }
                if ( dh==0 && dw!=0 ){
                    //水平
                    dw=1;
                }else if ( dw==0 && dh!=0 ){
                    //垂直
                    dh = 1;
                }else{
                    int k = gcd(dh,dw);
                    dh /= k;
                    dw /= k;
                }
                res = max( res , ++mp[make_pair(dh,dw)] + addition );
            }
        }
        return max(1, res);
    }

    int gcd(int a, int b) {
        return (b == 0) ? a : gcd(b, a % b);
    }
};



class Solution2 {
public:
    int maxPoints(vector<vector<int>>& points) {
        // y=kx+b
        map<pair<int,int>, int> cnt;
        int res=0;
        for ( auto p:points )
            res = max(res, ++cnt[make_pair(p[0],p[1])]);
        if ( points.size()==0  ) return 0;
        int n = points.size();
        for ( int i=0; i<n; ++i ){
            int x = points[i][0];
            int y = points[i][1];
            int addition = cnt[make_pair(x,y)];
            map<pair<int,int>, int> mp;
            for ( int j=i+1; j<n; ++j ){
                int nx = points[j][0];
                int ny = points[j][1];
                if ( x==nx && y==ny ) continue;
                int dh = y - ny;
                int dw = x - nx;
                // 编码 不再需要讨论
                // 因为 x-xn和y-yn不会同时为0 
                int k = gcd(dh,dw);
                dh /= k;
                dw /= k;
                res = max( res , ++mp[make_pair(dh,dw)] + addition );
            }
        }
        return max(1, res);
    }
    
    int gcd(int a, int b) {
        return (b == 0) ? a : gcd(b, a % b);
    }
    
};