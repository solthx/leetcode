/*
    问题描述:
        给定一个长度为 n 的非空整数数组，找到让数组所有元素相等的最小移动次数。每次移动可以使 n - 1 个元素增加 1。
        示例:

        输入:
        [1,2,3]

        输出:
        3

        解释:
        只需要3次移动（注意每次移动会增加两个元素的值）：

        [1,2,3]  =>  [2,3,3]  =>  [3,4,3]  =>  [4,4,4]

    问题分析:
        能不能a掉这题的一个关键思路就在于，问题的转化。

        因为本题关注的是相对的变化， 因此，对n-1个元素+1， 就相当于对1个元素-1，

        因此， 本题就可以转换为，每次对1个元素-1， 问多少次操作使得所有值相同。

        这样问题一下就变成easy水平了。
*/

class Solution {
public:
    int minMoves(vector<int>& nums) {
        int mini = *min_element(nums.begin(), nums.end());
        int n = nums.size();
        int res = 0;
        for ( auto &e:nums )
            res += e-mini;
        return res;
    }
};