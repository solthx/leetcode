/*
    问题描述：
        给定一个整数数组  nums 和一个正整数 k，找出是否有可能把这个数组分成 k 个非空子集，其总和都相等。
        示例 1：

        输入： nums = [4, 3, 2, 3, 5, 2, 1], k = 4
        输出： True
        说明： 有可能将其分成 4 个子集（5），（1,4），（2,3），（2,3）等于总和。

    问题分析：
        先判断是否“不存在”，也就是nums的和能否被k整除
        若可能存在，再去，然后再DFS去搜素。
        搜索的时候要注意，
        确定下来的集合也有可能被推翻重来，
        例如：10，10，10，7，7，7，7，7，7，6，6，6，k=3
        target = 30
        如果先取了10 10 10 ，那么后面一定无法组合
        但这却是可以组合的（(10,7,7,6)*3）
*/

class Solution {
    public boolean canPartitionKSubsets(int[] nums, int k) {
        int acc = 0;
        /*
         * #####
         */
        int target;
        boolean[] visited = new boolean[nums.length + 1];
        for (int e : nums)
            acc += e;
        if (acc % k != 0)
            return false;
        target = acc / k;
        return helper(nums, visited, k, target, 0, 0);
    }

    // helper 返回能否将nums划分为k个一样大的子集
    // 目标是把待划分子集数减到1
    private boolean helper(int[] nums, boolean[] visited, int k, int target, int start, int cur) {
        // k只剩一个的时候，肯定可以划分，因为前面判断过了
        if (k == 1)
            return true;
        // 当前和已经超过每个子集的大小，剪枝返回
        if (cur > target)
            return false;
        // 如果当前和正好等于了target，那么也不能说
        // 是一定可以，例如：10，10，10，7，7，7，7，7，7，6，6，6
        // 即子集数减1，从头再来
        else if (cur == target) {
            return helper(nums, visited, k - 1, target, 0, 0);
        }
        for (int i = start; i < nums.length; ++i) {
            if (visited[i] == false) {
                // 加入当前元素到当前子集
                visited[i] = true;
                // 如果已经可以划分了，那么直接返回就可以了
                if (helper(nums, visited, k, target, i + 1, cur + nums[i]) == true)
                    return true;
                // 不能划分说明当前元素不能加入当前子集
                visited[i] = false;
            }
        }
        return false;
    }
}