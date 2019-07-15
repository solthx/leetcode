/**
 * 问题描述： 给定一个未排序的整数数组，找到最长递增子序列的个数。
 * 
 * 示例 1: 输入: [1,3,5,4,7] 输出: 2 解释: 有两个最长递增子序列，分别是 [1, 3, 4, 7] 和[1, 3, 5, 7]。
 * 
 * 示例 2: 输入: [2,2,2,2,2] 输出: 5 解释: 最长递增子序列的长度是1，并且存在5个子序列的长度为1，因此输出5。
 * 
 * 问题分析： 只记录长度的话，个数没法更新 只记录个数的话，长度也没法观察。。 所以本题的难点就是能不能想到用两个数组分别保存长度和对应个数的信息。
 * 
 * len[i]保存以第i个元素为结尾的最大递增子序列长度 cnt[i]保存对应len[i]的个数
 * 
 * 最后选出全局最大长度maxi，然后把长度为maxi的个数加起来就行了。
 */
class Solution {
    public int findNumberOfLIS(int[] nums) {
        // cnt[i]表示以第i个元素为结尾的最长距离的个数
        // len[i]表示以第i个元素为结尾的最长距离

        int[] cnt = new int[nums.length];
        int[] len = new int[nums.length];

        int res = 0;
        int maxi = 1, new_dis;
        Arrays.fill(cnt, 1);
        Arrays.fill(len, 1);
        for (int i = 0; i < nums.length; ++i) {
            for (int j = 0; j < i; ++j) {
                if (nums[i] > nums[j]) {
                    if (len[i] < len[j] + 1) {
                        len[i] = len[j] + 1;
                        cnt[i] = cnt[j];
                    } else if (len[i] == len[j] + 1) {
                        cnt[i] += cnt[j];
                    }
                }
            }
            maxi = Math.max(len[i], maxi);
        }
        for (int i = 0; i < nums.length; ++i)
            if (len[i] == maxi)
                res += cnt[i];
        return res;
    }
}
