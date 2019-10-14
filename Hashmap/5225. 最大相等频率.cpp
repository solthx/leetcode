/*
    问题描述:
        给出一个正整数数组 nums，请你帮忙从该数组中找出能满足下面要求的 最长 前缀，并返回其长度：
        从前缀中 删除一个 元素后，使得所剩下的每个数字的出现次数相同。
        如果删除这个元素后没有剩余元素存在，仍可认为每个数字都具有相同的出现次数（也就是 0 次）。

        示例 1：

        输入：nums = [2,2,1,1,5,3,3,5]
        输出：7
        解释：对于长度为 7 的子数组 [2,2,1,1,5,3,3]，如果我们从中删去 nums[4]=5，就可以得到 [2,2,1,1,3,3]，里面每个数字都出现了两次。
        示例 2：

        输入：nums = [1,1,1,2,2,2,3,3,3,4,4,4,5]
        输出：13
        示例 3：

        输入：nums = [1,1,1,2,2,2]
        输出：5
        示例 4：

        输入：nums = [10,2,8,9,3,8,1,5,2,3,7,6]
        输出：8
         

        提示：

        2 <= nums.length <= 10^5
        1 <= nums[i] <= 10^5

    问题分析:
        哈希表 + 分类讨论...
        
        赛后补了下这题，其实并不难， 不要被hard吓到，这是第一个收获！！！
        
        第二个收获是，把所有情况都列出来，是分析题目的一个重要且有效的手段！！
*/

class Solution {
public:
    /*
        分为三种情况:
            1. 有i-1个元素出现了k次， 1个元素出现了1次
            2. 有i-1个元素出现了k次， 1个元素出现了k+1次
            3. 所有元素均只出现1次.
    */
    int maxEqualFreq(vector<int>& nums) {
        unordered_map<int,int> times; // times[i]为i出现的次数
        unordered_map<int,int> cnt; // cnt[i]为出现了次数为i个 数字个数
        unordered_set<int> st; //st记录当前出现元素个数
        int res = 0;
        for ( int i=0; i<nums.size(); ++i ){
            // 更新map
            int e = nums[i];
            if ( cnt[times[e]]>0 ) cnt[times[e]]--;
            times[e]++;
            cnt[times[e]]++;
            st.insert(e);
            if (  ((st.size()>1) && i%(st.size()-1)==0) ){
                // 情况1: 一个元素出现了1次,
                int k = i/(st.size()-1); // 每个元素出现了k次
                // 若其余元素出现了k次
                if ( cnt[k]==st.size()-1 )
                    res = max(res ,i+1);
            }
            if ( i%(st.size())==0 ){
                // 情况2: 有一个元素出现了k+1
                int k = i/st.size();
                // 若其余元素出现了k次
                if ( cnt[k]==st.size()-1 )
                    res = max(res, i+1);
            }
        }
        // 情况3: 所有元素都出现了一次
        if ( nums.size()==st.size() ) return nums.size();
        return res;
    }
};