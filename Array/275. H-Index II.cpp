/*
	题目描述：
		题目花里胡哨，最终就是让你求一个最大的h满足：
		数组大小为N，
		有N-h个元素小于等于h， 
		h个元素大于等于h
		
	解决思路：
		先排序，然后从小到大遍历数组，
		然后找出第一个nums[i]<=h (ps:h=len-i)
		然后返回这样的h
		
	优化：
		因为已经排过序了，又是找第一个满足nums[i]<=h的，所以可以
		用二分，
		如果h大于nums[mid]，说明右边的元素太多（h是右边的元素），那么h应该是在区间右边
		如果h小于nums[mid], 说明右边的元素太少，那么应该在左区间
		值得一提的是，
		下面的这个二分板子，如果应用在升序数组里找某一个数，那么lo会落在
		首个大于等于目标元素的位置，
		因此lo会落在nums[lo]等于h的位置或者是大于h的位置，
		又因为如果是nums[lo]等于h, 那么已经在循环中返回了，
		因此lo是落在大于h的位置，
		这说明nums[lo]>h
		这个时候，h就是区间[lo,N-1]的元素数,
		h = N-1 - lo +1 = N-lo
		返回h即可
*/
class Solution {
public:
    int hIndex(vector<int>& citations) {
        int mid,h;
        //大于h的有h个
        int lo=0,hi=citations.size()-1;
        while( lo<=hi ){
            mid = (lo+hi)/2;
            h =  citations.size()- mid  ;
            if ( citations[mid]==h ) return h;
            else if ( citations[mid]>h ) hi = mid-1;
            else lo = mid +1;
        }
        return citations.size()-1 - (lo-1);
    }   
};