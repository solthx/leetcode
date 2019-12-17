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

//=====================二刷=========================

/*
    note 1. 判断循环里的条件是小于还是小于等于的时候，一定要考虑指针l或r是代表已经
    判断过的位置，还是下一个要判断的或者要操作的位置！！！

    像本题的三向切分， 是指向下一个需要操作的位置，因此，当l和r相遇时，都是代表的下一个需要操作的位置，
    如果是<的话，这种情况就会丢失，因此应该是<=..  所以在写边界条件的时候，一定要想清楚!!! 而不是凭感觉!! 毕竟面试
    手撕代码的时候， 目标是一次bug free!!!!

    note 2. 同时，在while循环体里，也并不是每个地方都是安全的， 每次动完while里的游标位置，都一定要考虑会不会出界！ 要不要出界！！
*/
class Solution2 {
public:
    void sortColors(vector<int>& nums) {
        int r = 0,  w = 0, b = (int)nums.size()-1;
        // note 1
        while( w<=b ){
            while( w<=b && nums[b] == 2 ) --b;
            while( w<=b && nums[w] == 1 ) ++w;
            if ( w>b ) break; // note 2
            if ( nums[w]==0 )
                swap(nums[r++],nums[w++]);
            else if ( nums[w]==2 ){
                swap(nums[w],nums[b--]);
            }
        }
    }
};