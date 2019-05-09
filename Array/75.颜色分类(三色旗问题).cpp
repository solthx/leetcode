/*
	问题描述：
		三色旗问题，不多说了，三项切分走起。
		
	问题分析：
		抽象一下问题，变成分类成  0，1，2
		维护i,j,k. 
		使得i之前的都是0，
		i到j之间的是1
		j右边的都是2
		
		i游标指向0的，j指向1的，k指向2的
		
		伪代码：
			while( j<=k ):
				while( j<=k && nums[j]不是2 )：
					如果j是1：
						j向后移动1个
					如果j是0:
						交换nums[i]和nums[j]
						i和j后移动
				while( j<=k && nums[k]是2 )：
					k前移动
				if ( j<=k )
					交换nums[j],nums[k]
					k前移一个
					
		注意：
			这里是j<=k而不是j<k
			如果是j<k，
			那么j==k的时候，
			如果nums[j]是2那还好，
			如果nums[j]是0，那么这时候需要和nums[i]交换，
			所以在j==k的时候，还是需要再判断一次的，
			否则可能会出现 0 0 0 1 1 1 0 2 2 2 2 
									   j
									   k
*/

class Solution {
public:
    void sortColors(vector<int>& nums) {
        int i=0,j=0,k=nums.size()-1;
        while( j<=k ){
            while( j<=k && nums[j]!=2 ){
                if ( nums[j]==0 ) swap(nums[i++],nums[j++]);
                else if ( nums[j]==1 ) j++;
            }
            while( j<=k && nums[k]==2 ) k--;
            if ( j<=k )
                swap(nums[j],nums[k--]);
        }
    }
};