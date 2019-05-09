/*
	题目描述：
		给定一个排序整数数组，其中元素的取值范围为[lower，upper] (包括边界)，返回其缺少的范围。
		Example
		样例1
		输入：
		nums = [0, 1, 3, 50, 75], lower = 0 and upper = 99
		输出：
		["2", "4->49", "51->74", "76->99"]
		解释：
		在区间[0,99]中，缺失的区间有：[2,2]，[4,49]，[51,74]和[76,99]
	
		样例2
		输入：
		nums = [0, 1, 2, 3, 7], lower = 0 and upper = 7
		输出：
		["4->6"]
		解释：
		在区间[0,7]中，缺失的区间有：[4,6]

	题目分析：
		方法一：
			把lower-1和upper+1插进原数组（因为有个样例是在边界处，所以写程序的时候拿出来了，
			（***）的位置处），从头开始判断是否连续，若不连续再看是缺一个数还是缺一个区间，
			分别处理。
		
*/

class Solution {
public:
    vector<string> findMissingRanges(vector<int> &nums, int lower, int upper) {
        // write your code here
        int idx=-1;
        vector<string> res;
        if ( upper<lower ) return res;
        // size是0的情况,单独处理
        string elem;
        long l,r;
        //把边界插进首尾
        nums.insert(nums.begin(),lower);
        nums.insert(nums.end(),upper);
        for ( int i=1; i<nums.size(); ++i ){
            l = nums[i-1];
            r = nums[i];
            /*
                可以给l减一，给r加一，
                1. 如果边界存在，就会变成l-1,l,..,r,r+1
                2. 如果边界不存在，就会有l-1, a(<l),.., b(<r),r+1
                    后面的程序会自动加上l和r
            */
            if ( i==nums.size()-1 ) r++;
            if ( i== 1 ) l--;
            if ( r>l+1 ){
                //只缺了一个值
                if ( r==2+l ){
                    res.push_back(to_string(r-1));
                }else{
                    //缺少两个值及以上
                    elem = to_string(l+1) + "->" + to_string(r-1);
                    res.push_back(elem);
                }
            }
        }
        return res;
    }
};