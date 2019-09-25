/*
    问题描述:
        给定一个以字符串表示的非负整数 num，移除这个数中的 k 位数字，使得剩下的数字最小。

        注意:

        num 的长度小于 10002 且 ≥ k。
        num 不会包含任何前导零。
        示例 1 :

        输入: num = "1432219", k = 3
        输出: "1219"
        解释: 移除掉三个数字 4, 3, 和 2 形成一个新的最小的数字 1219。
        示例 2 :

        输入: num = "10200", k = 1
        输出: "200"
        解释: 移掉首位的 1 剩下的数字为 200. 注意输出不能有任何前导零。
        示例 3 :

        输入: num = "10", k = 2
        输出: "0"
        解释: 从原数字移除所有的数字，剩余为空就是0。

    问题分析:
        单调栈 + 贪心
        
        我们希望高位上的数字尽量的小， 高位如果大了，低位再小也没用..
        所以，在从左向右扫描的过程，就是从高到低扫描的过程，
        如果发现高位(扫描过的元素)，比低位(当前正在扫描的元素) 还要大的话，
        那就尽量把高位的数字都删掉,

        因此维护一个单调递增栈， 栈内就是可以保留的元素. 


        举个例子， 如果k=1,
        1324

        1                   o
        1 3                 o
        1 3 2               x 2比3大，删掉3 变成 1, 2
        1 2 4

        最终124 
*/

class Solution {
public:
    string removeKdigits(string num, int k) {
        stack<char> st;
        int i = 0;
        while( i<num.size() ){
            if ( st.empty() || st.top()<=num[i] || k<=0 )
                st.push(num[i]);
            else {
                while( st.size()>0  && st.top()>num[i] && k>0 ){
                    --k;
                    st.pop();
                }
                st.push(num[i]);
            }
            ++i;
        }
        string res="";
        while( !st.empty() ){
            if ( k>0 ) --k;
            else res+=st.top();
            st.pop();
        }
        reverse(res.begin(), res.end());
        int t = 0;
        while( t<res.size() && res[t]=='0' ) ++t;
        res =  res.substr( t );
        return res=="" ? "0" : res;
    }
};