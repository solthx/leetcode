/*
	题目描述：
		920. 会议室
			给定一系列的会议时间间隔，包括起始和结束时间[[s1,e1]，[s2,e2]，…(si < ei)，确定一个人是否可以参加所有会议。
	题目解析：
		先排序，再判断，水题。。
*/

/**
 * Definition of Interval:
 * classs Interval {
 *     int start, end;
 *     Interval(int start, int end) {
 *         this->start = start;
 *         this->end = end;
 *     }
 * }
 */

class Solution {
public:
    /**
     * @param intervals: an array of meeting time intervals
     * @return: if a person could attend all meetings
     */
    bool canAttendMeetings(vector<Interval> &intervals) {
        // Write your code here
        if ( intervals.size()<1 ) return true;
        sort(intervals.begin(),intervals.end(),cmp);
        for ( int i=0; i<intervals.size()-1; ++i ){
            if ( intervals[i].end>intervals[i+1].start )
                return false;
        }
        return true;
        
    }
    
    static bool cmp(Interval a,Interval b){
        if ( a.start!=b.start ) return a.start<b.start;
        return a.end<b.end;
    }
};