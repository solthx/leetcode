/*
    问题描述:
        给你一个整数数组 nums 和一个整数 k。
        如果某个 连续 子数组中恰好有 k 个奇数数字，我们就认为这个子数组是「优美子数组」。
        请返回这个数组中「优美子数组」的数目。

        示例 1：

        输入：nums = [1,1,2,1,1], k = 3
        输出：2
        解释：包含 3 个奇数的子数组是 [1,1,2,1] 和 [1,2,1,1] 。
        示例 2：

        输入：nums = [2,4,6], k = 1
        输出：0
        解释：数列中不包含任何奇数，所以不存在优美子数组。
        示例 3：

        输入：nums = [2,2,2,1,2,2,1,2,2,2], k = 2
        输出：16
         

        提示：

        1 <= nums.length <= 50000
        1 <= nums[i] <= 10^5
        1 <= k <= nums.length

    问题分析:
        一般求子数组满足xxx的问题，大概率可以用以下几种思路：
            1. 分治 或 分治+归并
            2. hashmap + 前缀和 
            3. 滑动窗口（双指针）

        方法一: 滑动窗口 + deque
            比赛期间用的滑动窗口做的。。 
            思路为:
                l和r维护一个窗口：
                    1. 移动r，直到奇数个数等于k
                    2. 移动l，直到最后一个满足条件的位置 
                    3. 计算l左边的连续偶数个数lc， 计算r右边的连续偶数个数rc (此时l和r的位置应该都是奇数，因此个数至少均为1)
                    4. lc*rc就是当前这个窗口的满足条件的个数
                    5. 继续移动r，开始计算下一个窗口的满足条件的个数
                    6. 最终返回和。
        
        方法二: hashmap+前缀和
            对于这种奇偶个数问题，也可以考虑前缀和( 因为偶数%2就是0， 奇数%2就是1， 前缀和的大小就是奇数的个数 )
            因此，问题就变成了：
                给一个01数组，求和为k的子区间个数, 妥妥的hashmap走起。

            这里做一个延伸:
                其他求子数组里xx个数的问题，也可以尝试往这里转移，例如，给一个 -1，1数组，求区间内-1的个数为k的区间个数，
                这个时候，可以把所有的-1变成1， 所有的1变成0， 然后又变成01数组了，

                因此，当一个数组里只有两种情况，且要求某一个情况的个数时， 可以考虑转换成01数组，然后hashmap+前缀和。
*/

class Solution1 {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        // 滑动窗口
        deque<int> q;
        int l=0,r=0, cur=0;
        int res = 0;
        while( r<nums.size() ){
            while( r<nums.size() && cur<k ){
                if ( nums[r]%2==1 ){
                    ++cur;
                    q.push_back(r); // 记录所有奇数的位置
                }
                ++r;
            }
            if ( r>=nums.size() && cur<k ) break;
            int left=q.front()-1; // front为最左边奇数的位置
            int right = q.back()+1; // back为最右边奇数的位置
            int lc=1, rc=1; // 计算lc和rc
            while( left>=0 && nums[left]%2==0 ){
                --left; ++lc;
            }
            while( right<nums.size() && nums[right]%2==0 ){
                ++right; ++rc;
            }
            res += ( lc*rc ); // 加上当前区间的个数
            r = right;  
            l = q.front()+1; q.pop_front();
            cur--; // cur为当前区间内的奇数的个数，因为把左边的给pop出去了，因此减1
        }
        return res;
    }
};



class Solution2 {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        for ( auto &e:nums )
            e = e%2;
        unordered_map<int,int> mp; // mp[cur]为前缀和为cur的个数
        mp[0] = 1;
        int cur = 0;
        int res = 0;
        for ( int i=0; i<nums.size(); ++i ){
            cur += nums[i];
            res += mp[cur-k];
            mp[cur]++;
        }
        return res;
    }
};