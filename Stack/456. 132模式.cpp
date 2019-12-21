/*
    问题描述：
        给定一个整数序列：a1, a2, ..., an，一个132模式的子序列 ai, aj, ak 被定义为：当 i < j < k 时，ai < ak < aj。设计一个算法，当给定有 n 个数字的序列时，验证这个序列中是否含有132模式的子序列。

        注意：n 的值小于15000。

        示例1:

        输入: [1, 2, 3, 4]

        输出: False

        解释: 序列中不存在132模式的子序列。
        示例 2:

        输入: [3, 1, 4, 2]

        输出: True

        解释: 序列中有 1 个132模式的子序列： [1, 4, 2].
        示例 3:

        输入: [-1, 3, 2, 0]

        输出: True

        解释: 序列中有 3 个132模式的的子序列: [-1, 3, 2], [-1, 3, 0] 和 [-1, 2, 0].

    问题分析:
        即找出是否相对顺序为 a,b,c 且满足 a<c<b 这种。。

        可以看出：
            1. 最左边的一直是最小的. 
            2. 中间的一直是最大的.

        所以，如果第i个元素能作为a,b,c里的b所满足条件的话，那么一定满足:
            左区间的最小值 < nums[i]
            右区间存在c 满足:  c < nums[i] && c>左区间的最小值

        所以，我们可以用mini[i]来保存[0,i]区间内的最小值
    
        接下来的问题就是怎么找c

        c可以理解为：右区间内比nums[i]小的最大值. 
        
        看到这里，单调栈没跑了..
        
        用单调栈来获取右区间比nums[i]小的最大值的方法:
                从右往左，维护一个递减栈，一旦发现升序，那么就pop栈内元素，直到栈顶元素比当前元素大,
            上一次pop出去的值，就是 右区间比当前元素小的最大值了. 

        单调栈可以帮我获取：左/右 区间比当前元素 大/小 的 最小/大值
     前缀数组可以帮我们获取:左/右 区间比当前元素 的 最小/大值
        
        明白了上面的道理之后，就好办了。。
*/

class Solution {
public:
    bool find132pattern(vector<int>& nums) {
        // mini[i] 保存第i个元素左边的最小值, 
        int mini[15001]={0};
        int n = nums.size();
        if ( n<=2 ) return false;
        mini[0] = nums[0];
        for ( int i=1; i<nums.size(); ++i )
            mini[i] = min(mini[i-1], nums[i]);
        stack<int> st;
        for ( int i=(int)nums.size()-1; i>0; --i ){
            if ( st.empty() || nums[st.top()]>nums[i] )
                st.push(i);
            else if ( nums[st.top()]<nums[i] ){
                while( st.size()>0 && nums[st.top()]<=mini[i-1] )
                    st.pop();
                
                if ( st.empty() || nums[st.top()]>nums[i] )
                    st.push(i);
                else if ( nums[i]>nums[st.top()] )
                    return true;
            }
        }
        return false;
    }
};