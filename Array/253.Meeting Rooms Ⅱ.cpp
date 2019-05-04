/*
	问题描述：
		给定一系列的会议时间间隔intervals，包括起始和结束时间[[s1,e1],[s2,e2],...] (si < ei)，找到所需的最小的会议室数量。

		样例1

			输入: intervals = [(0,30),(5,10),(15,20)]
			输出: 2
			解释:
			需要两个会议室
			会议室1:(0,30)
			会议室2:(5,10),(15,20)
	
		样例2

			输入: intervals = [(2,7)]
			输出: 1
			解释:
			只需要1个会议室就够了

	问题分析：
		先对区间按start升序排序，
		last数组记录了最后一个区间的结束时间
		len记录了last的长度
		每次遍历last:
			找到首个last[i]小于等于当前区间的start（说明可以接在这个队列后面），更新last
			找不到就说明要重新开一个会议室了
		最后返回len
		
		最后不明白为什么O(N^2)击败了100%
		
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
     * @return: the minimum number of conference rooms required
     */
    int minMeetingRooms(vector<Interval> &intervals) {
        // Write your code here
        if ( intervals.size()<1 ) return true;
        sort(intervals.begin(),intervals.end(),cmp);
        int len=0,i;
        int last[intervals.size()+1];
        for ( auto elem : intervals ){
            //O(N^2)
            for ( i=0; i<len; ++i ){
                if ( last[i]<=elem.start )
                    break;
            }
            if ( i<len ){
                last[i] = elem.end;
            }else{
                last[len++] = elem.end;
            }
        }
        return len;
    }
    
    static bool cmp(Interval a,Interval b){
        if ( a.start!=b.start ) return a.start<b.start;
        return a.end<b.end;
    }
};