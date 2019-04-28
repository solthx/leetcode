
/*
	题目描述：
		数组长度为n+1, 每个元素的取值范围为1~n ，必有一个重复数
		找出这个重复的数
	
	限制：
		空间复杂度O(1)
		时间复杂度小于O(N^2)
	
	问题分析：
		这里只说说满足了限制的算法：
		
		方法一：二分 O(NlogN)
			二分查找虽说是一般用于有序数组，但本题就是在无序数组里用了二分，
			即在二分的时候，不再以下标idx来作为基准，而是以值的大小来作为基准
			
			l初始为1，r初始为n （长度为n+1)
			mid = （l+r）/2
			每次找小于mid的元素个数，
			若个数小于mid，则说明重复元素要么是mid，要么是大于mid
			若个数大于mid，则说明重复元素肯定小于mid
			
			因为找小于mid的元素个数需要遍历数组，然后找logN次
			故复杂度就变成了O(NlogN) 
			
		方法二：
			这个方法很妙。。把问题抽象成了找一个线性表中有一个环，
			而那个环开始的位置就是重复元素
			
			例如：
			idx:  0 1 2 3 4 
			val:  3 1 3 4 2
			从0开始，val就是下一个元素的idx
			[0,3]->[3,4]->[4,2]->[2,3]->
				   [3,4]->[4,2]->[2,3]->
				   [3,4]->[4,2]->[2,3]->
			就出现环了
		
			而重复的数就是进入环的那个点，
			如何找到这个点，将在markdown里说明			
*/

class Solution1 {
public:
    int findDuplicate(vector<int>& nums) {
        
        // 方法一：
        //     二分查找，看小于mid的数量是否为mid，
        //     若大于mid，则重复数取值范围为1~mid
        //     小于mid，则在mid~n，
        
        int l=1,r = nums.size()-1;
        int cnt1=0,cnt2=0,mid;
        bool res = false;
        while( l<r ){
            mid = (l+r)/2;
            cnt1=0; // 记录小于mid的元素个数
            cnt2=0; // 记录等于mid的个数
            for ( int e:nums ){
                if ( e<mid ) cnt1++;
                else if ( e==mid )
                    if ( ++cnt2>1 ) return e; //等于mid 直接返回
            }
            if ( cnt1<mid ) l = mid+1;
            else r = mid - 1;
        }
        return l;
    }
};

class Solution2 {
public:
    int findDuplicate(vector<int>& nums) {
        /*
            方法二：
                这个方法很妙。。把问题抽象成了找一个线性表中有一个环，
                而那个环开始的位置就是重复元素
                
                例如：
                idx:  0 1 2 3 4 
                val:  3 1 3 4 2
                从0开始，val就是下一个元素的idx
                [0,3]->[3,4]->[4,2]->[2,3]->
                       [3,4]->[4,2]->[2,3]->
                       [3,4]->[4,2]->[2,3]->
                就出现环了
            
                而重复的数就是进入环的那个点，
                如何找到这个点，后面再做说明
        */
        if ( nums.size()==0 ) return -1;
        if ( nums.size()<3 ) return nums[0];
        int fast=nums[0],slow=nums[nums[0]];
        while( fast!=slow ){
            fast = nums[fast];
            slow = nums[nums[slow]];
        }
        slow = 0;
        while( fast!=slow ){
            fast = nums[fast];
            slow = nums[slow];
        }
        return fast;
    }
};
