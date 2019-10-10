/*
    问题描述:
        给定一个整数数组 a，其中1 ≤ a[i] ≤ n （n为数组长度）, 其中有些元素出现两次而其他元素出现一次。

        找到所有出现两次的元素。

        你可以不用到任何额外空间并在O(n)时间复杂度内解决这个问题吗？

        示例：

        输入:
        [4,3,2,7,8,2,3,1]

        输出:
        [2,3]

    问题分析:

        方法一: 
            看到 1 ≤ a[i] ≤ n ， 整数变下标，正负号来作为visited没跑了

            第一遍遍历，把 abs(a[i])-1 下标的 元素 取个反

            最后，
                若e出现了一次， 那么nums[e-1] < 0
                若e出现了两次和0次， 那么nums[e-1] > 0

            排除出现0次的方法就是，不再以下标作为判断，而是以nums[e-1]来作为判断,
            就是，如果 
                nums[ abs(nums[i]) ] < 0 , 那么nums[i]一定出现在了第i个位置上，即必不是出现了0次，那么就是出现了两次..
        
        方法二: 
            和方法一思想差不多，不过这个方法是一次遍历,
            如果 遇到 nums[nums[i]-1]是正的，那第一次遇到nums[i],， 那么就对nums[nums[i]-1] 取反
            如果 遇到 nums[nums[i]-1]是负的， 那肯定不是第一次遇到，就知道push_back(nums[i])就行了
                
*/

class Solution1 {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        for ( auto e:nums )
            nums[abs(e)-1] = - 1 * nums[abs(e)-1] ;
        vector<int> res;
        for ( auto e:nums )
            if ( nums[abs(e)-1]>0 ){
                res.push_back(abs(e));
                nums[abs(e)-1]*=-1;
            }
        return res;
    }
};


class Solution2 {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        vector<int> res;
        for ( auto e:nums )
            if ( nums[abs(e)-1]<0 ) res.push_back(abs(e));
            else nums[abs(e)-1]*=-1;
        return res;
    }
};
