/*
    问题描述:
        给你一个 有序的 不相交区间列表 intervals 和一个要删除的区间 toBeRemoved， intervals 中的每一个区间 intervals[i] = [a, b] 都表示满足 a <= x < b 的所有实数  x 的集合。
        我们将 intervals 中任意区间与 toBeRemoved 有交集的部分都删除。
        返回删除所有交集区间后， intervals 剩余部分的 有序 列表。

        示例 1：

        输入：intervals = [[0,2],[3,4],[5,7]], toBeRemoved = [1,6]
        输出：[[0,1],[6,7]]
        示例 2：

        输入：intervals = [[0,5]], toBeRemoved = [2,3]
        输出：[[0,2],[3,5]]
         

        提示：

        1 <= intervals.length <= 10^4
        -10^9 <= intervals[i][0] < intervals[i][1] <= 10^9

    问题分析:
        
        这题其实并不难，分类讨论，把每个区间的情况往里套就行了.. 

        但却做了很久，原因就是没想清楚，图速度，就直接coding了，然后不停debug.. 消耗了时间。

        要知道，如果一开始用的方法就是不好的，那么后面debug的成本要高的多！！！！！

        这题就是再一次的血泪教训！！！

        一定！！！要想清楚后！！！再coding！！！！ 不差那一点思考的时间！！
*/

class Solution {
public:
    vector<vector<int>> removeInterval(vector<vector<int>>& interval, vector<int>& toB) {
        auto cmp = [](vector<int>&a,vector<int>&b ){
            if ( a[1]!=b[1] ) return a[1]<b[1];
            return a[0]<b[0];
        };
        sort( interval.begin(), interval.end(), cmp );
        int i=0;
        vector<vector<int>> res;
        bool found = false;
        while( i<interval.size() ){
            // 不在删除区间里，直接加入
            if ( interval[i][1]<toB[0] || interval[i][0]>=toB[1] ) res.push_back(interval[i++]);
            // 删除区间在当前区间内的情况，当前区间被分成了两个区间
            else if ( interval[i][0]<toB[0] && interval[i][1]>toB[1]  ){
                res.push_back( {interval[i][0], toB[0]} );
                res.push_back( {toB[1], interval[i][1]} );
                ++i;
            // 当前区间完全在删除区间里，直接无视了
            }else if ( toB[0]<=interval[i][0] && toB[1]>=interval[i][1] ) ++i;
            // 删除区间的左端点，落在了当前区间内，进行"截取"
            else if ( toB[0]<interval[i][1] && toB[0]>interval[i][0] ){
                res.push_back({interval[i][0],toB[0]});
                ++i;
            // 删除区间的右断电，落在了当前区间内，进行“截取”
            }else if ( toB[1]>interval[i][0] && toB[1] < interval[i][1] ){
                res.push_back({toB[1], interval[i][1]});
                ++i;
            // 其他情况（其实不会发生
            }else ++i;
        }
        return res;
    }
};
