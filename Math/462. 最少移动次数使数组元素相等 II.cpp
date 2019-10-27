/*
    问题描述:
        给定一个非空整数数组，找到使所有数组元素相等所需的最小移动数，其中每次移动可将选定的一个元素加1或减1。 您可以假设数组的长度最多为10000。
        例如:

        输入:
        [1,2,3]

        输出:
        2

        说明：
        只有两个动作是必要的（记得每一步仅可使其中一个元素加1或减1）： 

        [1,2,3]  =>  [2,2,3]  =>  [2,2,2]

    问题描述:
        和I一样，也是问题的转化。

        把每个位置的元素，投影到坐标轴上，可以知道，目的就是要找出所有元素到某一个点的距离的和最小。

        因此，如果是奇数个数就是最中心的那个点的位置，如果是偶数个数，就是最中心两个点之间的任何位置。

        当然，奇数偶数无所谓了，直接排序+双指针，来计算就可以了。
*/

class Solution {
public:
    int minMoves2(vector<int>& nums) {
        sort( nums.begin(), nums.end() );
        int res = 0;
        int i=0, j=nums.size()-1;
        while( i<j ){
            res += ( nums[j]-nums[i] );
            ++i;
            --j;
        }
        return res;
    }
};