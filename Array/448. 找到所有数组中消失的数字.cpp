/*
    问题描述:
        给定一个范围在  1 ≤ a[i] ≤ n ( n = 数组大小 ) 的 整型数组，数组中的元素一些出现了两次，另一些只出现一次。

        找到所有在 [1, n] 范围之间没有出现在数组中的数字。

        您能在不使用额外空间且时间复杂度为O(n)的情况下完成这个任务吗? 你可以假定返回的数组不算在额外空间内。

        示例:

        输入:
        [4,3,2,7,8,2,3,1]

        输出:
        [5,6]

    问题分析:
        这里只说一下 时间复杂度O(N), 空间复杂度O(1) 的做法.

        一般这种 1 <= a[i] <= n  (n = 数组大小) 的话，就可以把值和坐标 联系起来考虑了，

        就本题来说， 坐标提供了 [1,n] 的visited数组， 每访问一次a[i], 
        就把a[a[i]]上的元素置成小于的数， 
        因此， a[i]大于0， 说明i没出现过, a[i]小于0，说明i出现过,
        
        因此，只要遍历数组两遍， 第一遍更新访问， 第二遍去找a[i]>0的元素,
        所有a[i]>0的元素，i就是没出现过的。

        本题的亮点:
            1. 数组的值和下标进行结合.
            2. 本题之所以选择 "把值弄成小于0的"，而不是把值弄成0， 来进行区别，是因为
            如果把a[a[i]]弄成0的话, 就会造成原本a[a[i]]的元素的丢失, 虽然可以dfs，
            但这样编程复杂度就上去(虽然也不难).. 总之意思就是，合理选择状态，来进行区别..  
*/

class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        for ( auto c:nums ){
            int t = abs(c);
            if ( t>0 && nums[t-1]>0 ) nums[t-1]*=-1; 
        }
        vector<int> res;
        for ( int i=0;i<nums.size(); ++i )
            if ( nums[i]>0 )
                res.push_back(i+1);
        return res;
    }
};