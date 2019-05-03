/*
	问题描述：
		给出一个无重叠的 ，按照区间起始端点排序的区间列表。

		在列表中插入一个新的区间，你需要确保列表中的区间仍然有序且不重叠（如果有必要的话，可以合并区间）。

		示例 1:

		输入: intervals = [[1,3],[6,9]], newInterval = [2,5]
		输出: [[1,5],[6,9]]
		示例 2:

		输入: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
		输出: [[1,2],[3,10],[12,16]]
		解释: 这是因为新的区间 [4,8] 与 [3,5],[6,7],[8,10] 重叠。
		
	题目分析：
		方法一：
			插入一个区间[l,r]
            分情况讨论：
                1. l在某一个区间i里，r在区间i后的某个区间的前面
                2. l在某一个区间i里，r在区间i后面的一个区间里面：
                3. l不在区间里，r在某个区间里
                4. l不在区间里，r也不在区间里
                5. l和r在最后
*/
class Solution1 {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        /*
            插入一个区间[l,r]
            分情况讨论：
                1. l在某一个区间i里，r在区间i后的某个区间的前面
                2. l在某一个区间i里，r在区间i后面的一个区间里面：
                3. l不在区间里，r在某个区间里
                4. l不在区间里，r也不在区间里
                5. l和r在最后
                
        */
        int l = newInterval[0],r = newInterval[1];
        vector<vector<int>> res;
        int i,j=intervals.size(),ist=0;
        
        if( intervals.size()<1 ){
            res.push_back(newInterval);
            return res;
        }
        
        for ( int i=0; i<intervals.size(); ++i ){
            if ( intervals[i][1]<l )
                res.push_back(intervals[i]);
            else{
                if( intervals[i][0]<=l ){
                    //情况1，2
                    j=i;
                    vector<int> t(2,0);
                    t[0] = min(intervals[i][0],l);
                    while( j<intervals.size() && intervals[j][1] < r ) 
                        j++;
                    //intervals[j][1]>=r
                    if ( j==intervals.size() || r<intervals[j][0] ){
                        t[1] = r; //情况1:  l在某一个区间i里，r在区间i后的区间j的前面
                    }
                    else{
                        t[1] = intervals[j][1];
                        j++;   //情况2: l在某一个区间i里，r在区间i后面的一个区间j里面
                    }
                    res.push_back(t);
                    break;
                }else{
                    //情况3，4
                    j=i;
                    vector<int> t(2,0);
                    t[0] = l;
                    while( j<intervals.size() && intervals[j][1] < r ) 
                        j++;
                    //intervals[j][1]>=r
                    if ( j==intervals.size() || r<intervals[j][0] ){
                        t[1] = r; //情况4: l不在区间里，r也不在区间里
                    }else{
                        t[1] = intervals[j][1]; //情况3 : l不在区间里，r在某个区间j里 
                        j++;
                    }
                    res.push_back(t);
                    break;
                } 
            }//else
        }//for
        
        //情况5 : l和r在最后
        if ( intervals.back()[1]<l )
            res.push_back(newInterval);
        
        for ( ; j<intervals.size(); ++j )
            res.push_back(intervals[j]);
        return res;
    }
};