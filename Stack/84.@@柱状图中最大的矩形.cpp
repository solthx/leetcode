/**
    问题描述：
        给定 n 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。

        求在该柱状图中，能够勾勒出来的矩形的最大面积。
        
        输入: [2,1,5,6,2,3]
        输出: 10

    问题分析：
        方法一：
            从左向右遍历，当nums[i]>nums[i+1]的时候(遇到递减)，
            就以i为起点向左遍历，试图更新最大矩形面积。

            为什么要遇到递减的时候，才向左去寻找更新最大矩形面积呢？
            举个例子  1 4 5 3
            在
                1
                1 4 
            的时候，不必去更新，因为4的下一个数字5比4大，
            从比自己大的那个数字开始向左寻找时，遇到的所有情况 包括了当前自身
            向左寻找的所有情况。
            
            理解不了就记住规则，然后手动模拟去体会。

            到最后一个元素的时候，再次从当前位置向左去寻找更新的最大矩形面积。

        方法二：
            思想和方法一类似，使用了递增栈，
            
            遍历数组，
            1. 递增时入栈，
            2. 遇到递减时，当前元素小于前一个元素(nums[i]<nums[i-1])时：
                不断取top()作为左边的那一边, 并pop, 直到栈顶元素小于nums[i]，
                nums[i]作为右边的那一边，
                这在pop的过程中保证了nums[i]是最小的那个边，
                在这个过程中来更新最大矩形面积。
            
            ps: 矩形的边取左右两边的最小，长的话不好弄，这里的办法是入栈的时候
            栈元素不是nums[i]而是i， 从而可以计算得到长度(i-top+1)
 */


class Solution1 {
public:
    int largestRectangleArea(vector<int>& heights) {
        if ( heights.size()==0 ) return 0;
        int i=0;
        long long maximum = heights[0];
        while( i<heights.size() ){
            if ( i==heights.size()-1 || heights[i]>heights[i+1] ){
                long long mi=heights[i];
                int j=i;
                while( j>=0 ){
                    mi = min(mi, (long long)heights[j]);
                    maximum = max( maximum, mi*(i-j+1));
                    --j;
                }
            }
            ++i;
        }
        return maximum;
        
    }
};


class Solution2 {
public:
    int largestRectangleArea(vector<int>& heights) {
        int res = 0;
        stack<int> st;
        heights.push_back(0);
        for (int i = 0; i < heights.size(); ++i) {
            while (!st.empty() && heights[st.top()] >= heights[i]) {
                int cur = st.top(); st.pop();
                res = max(res, heights[cur] * (st.empty() ? i : (i - st.top() - 1)));
            }
            st.push(i);
        }
        return res;
    }
};
