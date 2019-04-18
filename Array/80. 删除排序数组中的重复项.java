/*
    解决思路：
        遍历Nums，每次和前两个元素比，若和前两个元素相同，则不放入nums中，负责就重新放入
        nums中，但这么做的话，对于某些情况，由于上一次的存入改变了数组，在当本次判断同前两
        个元素比较的时候会出现错误，因为就把数组的存入操作进行了延迟，也就是不立刻存入，而
        是先保存idx和val值，当下一次需要存入时就先把上一次的存入了，然后再把这一次要存入的数
        据记录下来
*/
class Solution {
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
