/*
    问题描述:
        给出一个字符串 S，考虑其所有重复子串（S 的连续子串，出现两次或多次，可能会有重叠）。
        返回任何具有最长可能长度的重复子串。（如果 S 不含重复子串，那么答案为 ""。）

        示例 1：

            输入："banana"
            输出："ana"
        示例 2：

            输入："abcd"
            输出：""

        提示：
            2 <= S.length <= 10^5
            S 由小写英文字母组成。

    问题分析:
        后缀数组这种数据结构属于，用的不多，但长期不用就会忘的数据结构，所以这里并没有使用后缀数组来写。
        而是用一种更好理解的方式解决。。 二分+滚动哈希

        在对字符串预处理之后，滚动哈希能在O(1)的复杂度下判断两个字符串是否相同。
        
        最长重复字串的长度为k， 那么一定存在长度为k-1的重复子串，利用这一点，可以做二分操作。

        也就是对长度进行二分，然后check这个长度是否满足，如果满足，则去找更大的长度，如果不满足则尝试把长度缩小看看是否存在满足的重复子串

        check的复杂度在引入滚动哈希之后，可以在O(N)的复杂度下找出是否存在重复子串(就是遍历所有长度为len的字符串，看是否有重复的hashcode)

        总复杂度为O(NlogN)
*/

# define ull unsigned long long 
# define BASE 37
class Solution {
public:
    ull f[100010]={0};
    ull offset[100010]={0};
    string longestDupSubstring(string S) {
        offset[0]=1;
        for(int i=1; i<=S.size(); ++i){
            f[i] = f[i-1]*BASE + S[i-1]-'a';
            offset[i] = offset[i-1]*BASE;
        }
        int mid, l=1, r=(int)S.size()-1;
        string cur;
        string res;
        while(l<=r){
            mid = l+(r-l)/2;
            cur = check(S, mid);
            if ( cur.size()<=0 )
                r = mid - 1;
            else{
                l = mid + 1;
            }
            if (cur.size()>res.size())
                res = cur;
        }
        return res;
    }
    
    // 返回长度为len的重复子串
    string check(string S, int len){
        if (len==0) return "";
        unordered_set<ull> st;
        ull cur;
        for(int i=0; i<=S.size(); ++i){
            // (i, i+len]
            if (i+len>S.size()) break;
            cur = (f[i+len]-f[i]*offset[len]);
            if (st.count(cur))
                return S.substr(i, len);
            st.insert(cur);
        }
        return "";
    }
};