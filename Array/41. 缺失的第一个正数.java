/*
    题目描述：
        给一个数组，输出这个数组里缺失的最小正数。
        示例 1:
        输入: [1,2,0]
        输出: 3

        示例 2:
        输入: [3,4,-1,1]
        输出: 2

        示例 3:
        输入: [7,8,9,11,12]
        输出: 1
*/

/*
    没做出来，正确的思路是：
        首先，这个正数的范围肯定是1~数组大小，所以就先遍历数组，
        对于小于0的和大于数组大小的元素就不考虑了，
        在[1,数组大小]区间内的元素，开一个数组table来记录这个元素是否出现过，
        例如table[i]==0就是没出现，table[i]==1就是出现（初始化table所有元素都为0）
        最后再遍历这个table，找到首个table[i]==0的位置，i就是首个没出现的正数
        若table的所有元素都是1（就是1~数组大小的元素都出现了），那么首个没出现的正数就是‘数组大小+1’

        最后，记得考虑边界情况
*/

class Solution {
    public int firstMissingPositive(int[] nums) {
        int i,cur=0;
        if (nums.length==0) return 1; //边界情况
        int [] table = new int[nums.length+1]; //初始化table
        for (  i=0; i<nums.length; ++i ){
            if ( nums[i]>0 && nums[i]<=nums.length )
                table[nums[i]] = 1;
        }
        for ( i=1; i<=nums.length; ++i )
            if ( table[i]==0 ) return i;
        return i;
    }
} 

/*
    本题收获： 最重要的就是，对于首次未出现的正数，那么这个正数的大小的取值区间就是[1,数组大小]
              ，也就是说对于小于0的和大于数组大小的元素就不考虑了，这个条件要能看出来。 
              然后没要求空间复杂度，就打表吧。
*/