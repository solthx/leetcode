/*
    问题描述:
        我们有一个由平面上的点组成的列表 points。需要从中找出 K 个距离原点 (0, 0) 最近的点。

        （这里，平面上两点之间的距离是欧几里德距离。）

        你可以按任何顺序返回答案。除了点坐标的顺序之外，答案确保是唯一的。

         

        示例 1：

        输入：points = [[1,3],[-2,2]], K = 1
        输出：[[-2,2]]
        解释： 
        (1, 3) 和原点之间的距离为 sqrt(10)，
        (-2, 2) 和原点之间的距离为 sqrt(8)，
        由于 sqrt(8) < sqrt(10)，(-2, 2) 离原点更近。
        我们只需要距离原点最近的 K = 1 个点，所以答案就是 [[-2,2]]。
        示例 2：

        输入：points = [[3,3],[5,-1],[-2,4]], K = 2
        输出：[[3,3],[-2,4]]
        （答案 [[-2,4],[3,3]] 也会被接受。）
         

        提示：

        1 <= K <= points.length <= 10000
        -10000 < points[i][0] < 10000
        -10000 < points[i][1] < 10000
    
    问题分析:
        方法一:
            排序 or 堆
            复杂度稳定O(NlogN)
                打包正三元组， 计算每一个点到远点的距离的平方。
            然后用排序，或者堆， 取前K小的元素就行了。

        方法二:
            复杂度O(N)
                用快排分治+二分的思想， 每次都定位一个值，使得左边的都比这个值小，右边的都比这个值大，
            当定位到第k个位置的时候，就停止， 这个时候，前面K个元素就是前K小的了。
*/

// 排序
class Solution1 {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
        vector<vector<int>> nums;
        for ( auto point:points )
            nums.push_back({point[0], point[1], point[0]*point[0]+point[1]*point[1]});
        sort( nums.begin(), nums.end(), [](vector<int>&a, vector<int>&b){
            return a[2]<b[2];
        } );
        vector<vector<int>> res;
        for ( int i=0; i<nums.size() && K--; ++i )
            res.push_back({nums[i][0],nums[i][1]});
        return res;
    }
};

// 快排思想+二分
class Solution2 {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
        vector<vector<int>> nums;
        vector<vector<int>> res;
        for ( auto point:points )
            nums.push_back({point[0], point[1], point[0]*point[0]+point[1]*point[1]});
        divide( nums, 0, nums.size()-1, K-1 );
        for ( int i=0; i<nums.size() && K--; ++i )
            res.push_back({nums[i][0],nums[i][1]});
        return res;
    }
    
    void divide( vector<vector<int>>& nums, int l, int r, int k ){
        if ( l>=r ) return ;
        int val = nums[l].back();
        int lo=l, hi=r;
        while( lo<hi ){
            while( lo<hi && nums[hi].back()>=val ) --hi;  
            while( lo<hi && nums[lo].back()<=val ) ++lo;
            if ( lo<hi )
                swap( nums[lo], nums[hi] );
        }
        swap( nums[l],nums[lo] );
        if ( k==lo ) return ;
        if ( k>lo ) divide( nums, lo+1, r, k );
        else divide(nums, l, lo-1, k);
    }
};