/*
	题目描述：
		如果连续数字之间的差严格地在正数和负数之间交替，则数字序列称为摆动序列。第一个差（如果存在的话）可能是正数或负数。少于两个元素的序列也是摆动序列。

		例如， [1,7,4,9,2,5] 是一个摆动序列，因为差值 (6,-3,5,-7,3) 是正负交替出现的。相反, [1,4,7,2,5] 和 [1,7,4,5,5] 不是摆动序列，第一个序列是因为它的前两个差值都是正数，第二个序列是因为它的最后一个差值为零。

		给定一个整数序列，返回作为摆动序列的最长子序列的长度。 通过从原始序列中删除一些（也可以不删除）元素来获得子序列，剩下的元素保持其原始顺序。

		示例 1:
		输入: [1,7,4,9,2,5]
		输出: 6 
		解释: 整个序列均为摆动序列。
		
		示例 2:
		输入: [1,17,5,10,13,15,10,5,16,8]
		输出: 7
		解释: 这个序列包含几个长度为 7 摆动序列，其中一个可为[1,17,10,13,10,16,8]。
		
		示例 3:
		输入: [1,2,3,4,5,6,7,8,9]
		输出: 2
		
	问题分析：
		方法一：
			最终个数 = 极值个数 + 第一个元素 + 最后一个元素 
			注意这里的极值的定义和数学上的不大一样，
			就是 1,2,2,2,1 中， 2也算一个极值，注意处理连续重复元素的情况
		
		方法二：
			动态规划：
				up[i]是在第i个位置上，处于上升时，所包含的摆动序列个数
				down[i]是在第i个位置上，处于上升时，所包含的摆动序列个数
				
				状态更新： 
					处于上升阶段的时候：
						up[i] = down[i-1] + 1  (当前是上升，给前i-1个下降时最大振荡个数+1
						down[i] = down[i-1]    (上一个最大下降个数传递不变
						
					处于下降阶段的时候：(同理)
						down[i] = up[i-1] + 1
						up[i] = up[i-1]    
						
			进一步对空间优化：
				上升时，down = up + 1
				下降时，up = down  + 1
		
*/

class Solution1 {
public:
    int wiggleMaxLength(vector<int>& nums) {
        int cnt=0;
        for ( int i=0; i<nums.size(); ++i ){
            //看第i个位置是不是极值
			if ( helper(nums,i,cnt) ){
                cnt++;
            }
        }
        return cnt;
    }
    
    bool helper(vector<int>& nums,int & t,int cnt){
        int i=t;
		// 第一个元素直接返回
        if ( i==0 ) return true;
		
		// 对于最后一个元素，要排除掉
		// a,a,a,a,a,a,a,a的情况 
		// 也就是如果第一个元素和最后一个元素一样，并且中间没有极值(cnt==1的第一个元素),那么就是这个情况
        if ( i==nums.size()-1 )
            return (cnt==1 && nums[0]==nums.back())?false:true;
        int l=i-1,r=i+1;
        
		//过滤左边相等
		while( l>=0 && nums[l]==nums[i] )
            l--;
		//过滤右边相等
        while( r<nums.size() && nums[r]==nums[i] ){
            t++;
            r++;
        }
		//当前是极大
        if ( r<nums.size() && l>=0 && nums[i]<nums[l] && nums[i]<nums[r] ) return true;
        //当前是极小
		if ( r<nums.size() && l>=0 && nums[i]>nums[l] && nums[i]>nums[r] ) return true;
        return false;
    }
};


class Solution2 {
public:
    int wiggleMaxLength(vector<int>& nums) {
        int n = nums.size();
        //up[i]是在第i个位置上，处于上升时，所包含的摆动序列个数
        vector<int> up(n,1);
        //down[i]是在第i个位置上，处于上升时，所包含的摆动序列个数
        vector<int> down(n,1);
        if ( n<2 ) return n;
        for ( int i=1; i<nums.size(); ++i ){
            if ( nums[i]>nums[i-1] ){
                // 处于上升
                up[i] = down[i-1] + 1;
                down[i] = down[i-1];
            }else if ( nums[i]<nums[i-1] ){
                //处于下降
                down[i] = up[i-1]+1;
                up[i] = up[i-1];
            }else{
                up[i] = up[i-1];
                down[i] = down[i-1];
            }
        }
        return max(down[n-1],up[n-1]);
    }
};

class Solution2_优化 {
public:
    int wiggleMaxLength(vector<int>& nums) {
        int n = nums.size();
        int up=1,down=1;
        if ( n<2 ) return n;
        for ( int i=1; i<nums.size(); ++i ){
            if ( nums[i]>nums[i-1] ) up = down + 1;
            else if ( nums[i]<nums[i-1] ) down = up + 1;
        }
        return max(down,up);
    }
};