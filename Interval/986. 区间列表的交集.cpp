/*
    问题描述:
        给定两个由一些闭区间组成的列表，每个区间列表都是成对不相交的，并且已经排序。
        返回这两个区间列表的交集。
        （形式上，闭区间 [a, b]（其中 a <= b）表示实数 x 的集合，而 a <= x <= b。两个闭区间的交集是一组实数，要么为空集，要么为闭区间。例如，[1, 3] 和 [2, 4] 的交集为 [2, 3]。）
        示例：
            输入：A = [[0,2],[5,10],[13,23],[24,25]], B = [[1,5],[8,12],[15,24],[25,26]]
            输出：[[1,2],[5,5],[8,10],[15,23],[24,24],[25,25]]
            注意：输入和所需的输出都是区间对象组成的列表，而不是数组或列表。
         

        提示：
            0 <= A.length < 1000
            0 <= B.length < 1000
            0 <= A[i].start, A[i].end, B[i].start, B[i].end < 10^9
    
    问题分析:
        另一道比较好的区间的题: https://leetcode-cn.com/problems/maximum-profit-in-job-scheduling/
        
        排序+双指针

        对end排序， 然后分类讨论.
        
        1. 区间不重合: 两种情况

        2. 区间重合， 计算重合部分， 然后根据end来判断应该移动谁.

*/

class Solution {
public:
    vector<vector<int>> intervalIntersection(vector<vector<int>>& A, vector<vector<int>>& B) {
        auto cmp = []( vector<int>& a, vector<int>& b ){
            return a[1]<b[1] || a[1]==b[1]&& a[0]<b[0];
        };
        sort( A.begin() , A.end(), cmp );
        sort( B.begin(), B.end(), cmp );
        vector<vector<int>> res;
        int i=0, j=0;
        while( i<A.size() && j<B.size() ){
            if ( A[i][1]<B[j][0] ) ++i;
            else if ( B[j][1]<A[i][0] ) ++j;
            else{
                res.push_back( {max( A[i][0], B[j][0] ), min(A[i][1], B[j][1])} );
                if ( A[i][1]>B[j][1] ) ++j;
                else ++i;
            }
        }
        return res;
    }
};