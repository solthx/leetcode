/*
    问题描述:
        假设我们在一条水平数轴上，列表 stations 来表示各个加油站的位置，加油站分别在 stations[0], stations[1], ..., stations[N-1] 的位置上，其中 N = stations.length。

        现在我们希望增加 K 个新的加油站，使得相邻两个加油站的距离 D 尽可能的最小，请你返回 D 可能的最小值。

        示例：

            输入：stations = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], K = 9
            输出：0.500000
        注：
            1. stations.length 是在范围 [10, 2000] 内的整数
            2. stations[i] 是在范围 [0, 10^8] 内的整数
            3. K 是在范围 [1, 10^6] 内的整数
            4. 在 10^-6 以内的正确值会被视为正确的答案

    问题分析:
        （其实看到“注”里的4，基本就可以断定用二分了...

        最大最小值问题，妥妥的二分..

        即确定一个值以后，通过编写check函数来缩小区间..

        就本题来说，可以通过二分最小距离D, check函数的逻辑日下:
            
            确定完最大距离的最小值mid之后，就开始计算，如果要满足最大距离的最小值为mid
            的话，需要插入多少个值.. 假设需要 x个:
                1. 如果 x>K 说明 这个 mid 太小了.. 需要让mid大一些，就更新左边界 l = mid
                2. 如果 x<=K 说明 或许存在更小的mid 满足条件， 就尝试让mid更小一些, 就调整右边界 r=mid 
*/

class Solution {
public:
    double minmaxGasDist(vector<int>& stations, int K) {
        if ( stations.size()<=1 ) return 0;
        double l = 0;
        double r=l;
        for ( int i=1; i<stations.size(); ++i ){
            l = min( l , (double)(stations[i],stations[i-1]));
            r = max( r, (double)(stations[i],stations[i-1]));
        }
        while( r-l>1e-6 ){
            double mid = (r+l)/2;
            if ( check(stations, K, mid) ) 
                l =  mid;
            else r = mid;
        }
        return l;
    }
    
    bool check( vector<int>& stations, int K, double m ){
        double diff;
        for ( int i=1; i<stations.size(); ++i ){
            if ( (diff = stations[i]-stations[i-1])>m ){
                int cnt =(diff/m);
                K -= cnt;
                if ( K<0 ) return true; 
            }
        }
        return false;
    }
};