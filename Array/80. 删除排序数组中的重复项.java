/*
    解决思路一：
        遍历Nums，每次和前两个元素比，若和前两个元素相同，则不放入nums中，负责就重新放入
        nums中，但这么做的话，对于某些情况，由于上一次的存入改变了数组，在当本次判断同前两
        个元素比较的时候会出现错误，因为就把数组的存入操作进行了延迟，也就是不立刻存入，而
        是先保存idx和val值，当下一次需要存入时就先把上一次的存入了，然后再把这一次要存入的数
        据记录下来
	
	方案评价：属于看到错误后打补丁的方案，不好 
*/
class Solution1 {
    public int removeDuplicates(int[] nums) {
        if (nums.length<=2) return nums.length;
        int last = 2, idx=0,val=nums[0],has=0;
        //has表示是否有延迟存入操作
        for ( int i=2; i<nums.length; ++i )
            if ( nums[i-1]==nums[i] && nums[i-2]==nums[i] ) continue;
            else{
                if ( has !=0 ){ //有延迟操作，先存，再更新idx,val
                    nums[idx] = val;
                    idx = last++;
                    val = nums[i];
                }else{ //无延迟操作说明是第一次，只更新参数
                    idx = last++;
                    val = nums[i];
                    has = 1;
                }
            }
        if (has==1) nums[idx] = val; //别忘记最后一个的延迟操作还要存入
        return last;
    }
}

/*
	解决思路二：
		本题虽然很显然是利用双游标，一个遍历一个赋值，但上题是利用遍历的那个
		游标来进行条件判断，然而在本题中，显然是利用赋值的那个游标来做判断更加合理
		i是遍历游标，cur是赋值游标，
		我们把(nums[i-1]==nums[i] && nums[i-2]==nums[i])这个条件改成
		(nums[i] == nums[cur-2] ) 因为cur是当前nums已经赋值元素的个数，
		nums[cur-1]是已经赋值了的最后一个元素，而最后一个元素和正在遍历的这个是否相等都
		无所谓，因为只要倒数第二个元素和当前元素相等，那么这两个元素之间的所有元素都会相等！
		因为本题是相同的元素是连续存放的，因此放散一下的话，如果把本题的两个改成三个，
		那么(nums[i] == nums[cur-2] ) 就可以改成 (nums[i] == nums[cur-3] ) 
*/

class Solution2 {
    public int removeDuplicates(int[] nums) {
        int i = 0;
        for (int n : nums)
            if (i < 2 || n > nums[i-2])
                nums[i++] = n;
        return i;
    }
}