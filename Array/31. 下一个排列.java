/*
    问题分析：
        实现获取下一个排列的函数，
        算法需要将给定数字序列重新排列成字典序中下一个更大的排列。
        如果不存在下一个更大的排列，则将数字重新排列成最小的排列（即升序排列）。
        必须原地修改，只允许使用额外常数空间。
        以下是一些例子，输入位于左侧列，其相应输出位于右侧列。
        1,2,3 → 1,3,2
        3,2,1 → 1,2,3
        1,1,5 → 1,5,1

    问题分析：
        看了题解以后，知道了寻找到下一个排列的规律，
        即：
            例子：1 3 5,4,2
            1.  反向(从右向左)找到递增的最后一个元素a(5)，此位置为idx，
            2.  在元素a的右侧，找到元素b，其满足：b>a 且 abs(b-a)最小，这里元素b未找到
                若未找到，说明a为右侧最大，那么就选a左边一个位置，idx -= 1 ， a变成了3，找到b为4
                若a左边没元素了，说明排列是5 4 3 2 1，直接全部翻转
            
            3. 找到b后，交换元素a,b  （1，4，5，3，2）
            4. 翻转idx右侧的所有元素(未交换前元素a的右侧所有元素) (1,4,2,3,5) 
 */

class Solution {
    public void nextPermutation(int[] nums) {
        if ( nums.length<=1 ) return;
        int i=nums.length-2;
        // 第i个位置元素是左侧递增的峰值，元素a
        while( i>=0 && nums[i]>=nums[i+1] ) --i;
        
        // 去找元素b (nums[j])
        int j=i, k=-1, tmp;
        while( j>=0 && k<0 ){
            // 找到右侧小于nums[i]且最接近nums[i]的元素位置
            k = find_first_low(nums, j+1);
            if ( k<0 ){
                // 说明没找到
                j--;
            }else{
                //找到了
                Swap(nums, j, k);
                Reverse(nums, j+1, nums.length-1);
                return ;
            }
        }
        Reverse(nums,0, nums.length-1);
    }
    
    
    int find_first_low(int [] nums, int start){
        int val = nums[start-1];
        if ( start>=nums.length ) return -1;
        int idx=-1, mini=Integer.MAX_VALUE;
        for ( int i=start; i<nums.length;++i ){
            if ( nums[i]>val && nums[i]<=mini ){
                mini = nums[i];
                idx = i;
            }  
        }
        return idx;
    }
    
    void Swap(int [] nums, int i, int j){
        int tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
    }
    
    void Reverse( int [] nums, int l, int r ){
        while( l<r ){
            Swap(nums, l++,r--);
        }
    }
    
    
}
