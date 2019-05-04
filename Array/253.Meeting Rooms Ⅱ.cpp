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
		方法一：
			N^2
			先对区间按start升序排序，
			last数组记录了最后一个区间的结束时间
			len记录了last的长度
			每次遍历last:
				找到首个last[i]小于等于当前区间的start（说明可以接在这个队列后面），更新last
				找不到就说明要重新开一个会议室了
			最后返回len
			
			最后不明白为什么O(N^2)击败了100%
			
		方法二：
			NlogN
			对方法一的优化，在方法一中，找首个小于等于elem.start的元素时，使用的
			是暴力遍历，这里使用的是最小堆，弹出最小的会议结束时间（即最小的end）
			然后用当前的来进行更新（因为已经对start进行升序排序了，所以不会出现
			很早的会议结束接上很晚的会议开始的情况）
		
		方法三：
			NlogN
			使用有序的map，该方法脑洞比较大，来举个例子说明
			如果有一个会议时间的区间是[50,100]，
			那么:
				m[50] = m[50] + 1  //说明从50这个时刻开始要占用一个会议室
				m[100] = m[100] - 1 //说明在100这个时刻释放一个会议室
			所以，我们的目标就是找出同时使用的会议室的最大值！
			这么一想就简单多啦！
			
		方法四：
			NlogN
			脑洞也挺大，
			按开始和结束的时间排序，
			完全模拟会议的持续过程
			
			starts保存了所有会议起始时间
			ends保存了所有会议的结束时间
			使用双指针，starts用i， ends用endpos，
			
			i指向下一个要开的会议的起始时间，
			endpos指向正在开的会议的结束时间
			
			遍历starts:
				如果starts[i]>=ends[endpos]：
					例如：
						starts[i]==50，ends[endpos]==40
					也就是说，下一个要开的会议在50时刻开始，当前这个会议在40时刻结束，不冲突，
					所以不用加房间
					
				如果starts[i]<ends[endpos]， 
					例如：
						starts[i]==50，ends[endpos]==60
					也就是说，下一个要开的会议在50时刻开始，当前这个会议在60时刻结束，冲突，
					需要再加一个房间来满足下次的会议。
						
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

class Solution1 {
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


class Solution3 {
public:

    int minMeetingRooms(vector<Interval> &intervals) {
        // Write your code here
        if ( intervals.size()<1 ) return true;
        //sort(intervals.begin(),intervals.end(),cmp);
        int len=0,rooms=0,i;
        map<int,int> m;
        for( auto e:intervals ){
            ++m[e.start];
            --m[e.end];
        }
        for ( auto e:m ){
            //len是最大的同时使用的会议室数量
            //rooms是当前使用的会议室数量
            len = max(len,rooms+=e.second);
        }
        return len;
    }
    
    static bool cmp(Interval a,Interval b){
        if ( a.start!=b.start ) return a.start<b.start;
        return a.end<b.end;
    }
};

class Solution4 {
public:
    int minMeetingRooms(vector<Interval>& intervals) {
        vector<int> starts, ends;
        int res = 0, endpos = 0;
        for (auto a : intervals) {
            starts.push_back(a.start);
            ends.push_back(a.end);
        }
        sort(starts.begin(), starts.end());
        sort(ends.begin(), ends.end());
        for (int i = 0; i < intervals.size(); ++i) {
			/*
				如果starts[i]<ends[endpos]， 
				例如：
					starts[i]==50，ends[endpos]==60
				也就是说，下一个要开的会议在50时刻开始，当前这个会议在60时刻结束，冲突，
				需要再加一个房间来满足下次的会议。
			*/
            if (starts[i] < ends[endpos])	
				++res;
            else ++endpos;
			/*
				如果starts[i]>=ends[endpos]：
				例如：
					starts[i]==50，ends[endpos]==40
				也就是说，下一个要开的会议在50时刻开始，当前这个会议在40时刻结束，不冲突，
				所以不用加房间
			*/				
				
        }
        return res;
    }
};
