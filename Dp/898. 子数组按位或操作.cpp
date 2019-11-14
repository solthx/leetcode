/*
    问题描述:
        我们有一个非负整数数组 A。
        对于每个（连续的）子数组 B = [A[i], A[i+1], ..., A[j]] （ i <= j），我们对 B 中的每个元素进行按位或操作，获得结果 A[i] | A[i+1] | ... | A[j]。
        返回可能结果的数量。 （多次出现的结果在最终答案中仅计算一次。）

        示例 1：

            输入：[0]
            输出：1
        解释：
            只有一个可能的结果 0 。
        示例 2：

            输入：[1,1,2]
            输出：3
        解释：
            可能的子数组为 [1]，[1]，[2]，[1, 1]，[1, 2]，[1, 1, 2]。
            产生的结果为 1，1，2，1，3，3 。
            有三个唯一值，所以答案是 3 。
        示例 3：
            输入：[1,2,4]
            输出：6
        
        解释：
            可能的结果是 1，2，3，4，6，以及 7 。
         

        提示：
            1 <= A.length <= 50000
            0 <= A[i] <= 10^9

    问题分析：
        当没有思路的时候，可以考虑从暴力来优化。

        方法零: 两层循环来暴力枚举所有情况， 复杂度为O(N^2)
        
        方法一: 
            上面的暴力枚举，是对每一个区间的枚举，即对每一个区间的或的枚举，
            
            但这些 不同区间 的 或 的结果，会有很多重复的

            那么，里面一定有很多重复的情况，这个时候，可以用unordered_set来过滤掉每一种重复的情况。

            一个set用来保存以第i个元素为结尾的前缀区间或 的结果集，
            伪代码:
            for i from 1 to n:
                for auto d:dp[i-1]:
                    dp[i].insert( d|A[i] )             
            一个set用来保存结果.

        方法二:
            利用到了一个新的性质:
              ( a | b ) >= a
              ( a | b ) >= b
            
            显然，当等号不成立的时候，就说明出现了新的情况。
            把这个性质应用上去，就可以不用set来保存了。

            核心伪代码:
            for i from 1 to n:
                int tmp, pre_or = A[i] 
                for auto d:dp[i-1]:
                    tmp = pre_or | d 
                    if tmp>pre_or:  说明出现了新的情况
                        pre_or = tmp    更新这个前缀
                        dp[i].push_back( pre_or ) 

            tmp 是指 以第i个元素为结尾的区间的 区间的元素的或\

            ( pre_or 的起使为A[i] ， dp[i-1]里的每一个元素都是以第i-1的元素为结尾的xxxx
            
            所以 进行或就得到了 以第i个元素为结尾的xxxxx, 但是pre_or虽然起使是A[i]， 但如果发现了新的或的结果以后，需要进行更新，即 pre_or = pre_or | d, 这也就是tmp了，
            
            含义是把刚才那个新的情况也纳入到结果里。。 这一块有点绕，实在想不清楚，可以画几种情况来看  )

*/

// unordere_map的暴力
class Solution1 {
public:
    int subarrayBitwiseORs(vector<int>& A) {
        unordered_set<int> res, pre;
        for ( auto d:A ){
            unordered_set<int> nxt;
            for ( auto e:pre )
                nxt.insert( e|d );
            nxt.insert(d);
            pre = nxt;
            for ( auto e:pre )
                res.insert(e);
        }
        return res.size();
    }
};

// 运用性质
class Solution2 {
public:
    int subarrayBitwiseORs(vector<int>& A) {
        unordered_set<int> res;
        vector<int> pre;
        for ( auto d:A ){
            vector<int> nxt_pre={d};  
            int pre_or = d;
            for ( auto e:pre ){
                int tmp = pre_or | e;
                if ( tmp>pre_or ){
                    nxt_pre.push_back(tmp);
                    pre_or = tmp;
                }
            }
            pre = nxt_pre;
            for ( auto e:pre )
                res.insert( e);
        }
        return res.size();
    }
};