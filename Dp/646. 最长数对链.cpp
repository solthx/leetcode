/*
    问题描述:
        给出 n 个数对。 在每一个数对中，第一个数字总是比第二个数字小。
        现在，我们定义一种跟随关系，当且仅当 b < c 时，数对(c, d) 才可以跟在 (a, b) 后面。我们用这种形式来构造一个数对链。
        给定一个对数集合，找出能够形成的最长数对链的长度。你不需要用到所有的数对，你可以以任何顺序选择其中的一些数对来构造。

        示例 :
            输入: [[1,2], [2,3], [3,4]]
            输出: 2
            解释: 最长的数对链是 [1,2] -> [3,4]

    问题分析:
        方法一: 贪心排序
            决定能连多长的不是第一个元素，而是第二个元素，第二个元素越小，能连的就越多越长
            所以，按照第二个元素的大小排序，然后从后向前扫描，只要遇到比 pre_one[1] 大的cur_one[0]， 就用cur_one[i][1]更新pre_one[1]

        方法二: 动态规划
            解法同 最长上升子序列问题 一样
            dp[i]保存了长为i的序列的最后一个那个最大的元素.
            然后用二分去找首个大于等于 pairs[i][0] 的元素 然后更新就行了，跟 最长升上子序列那题处理方法几乎一样.
*/

class Solution1 {
public:
    int findLongestChain(vector<vector<int>>& pairs) {
        // 贪心
        if ( pairs.size()==0 ) return 0;
        int l,r,mid,len=0;
        auto cmp = [](vector<int>&a , vector<int>&b){
            return a[1]<b[1];
        };
        sort( pairs.begin(), pairs.end(),cmp );
        int res = 1, pre=pairs[0][1];
        for ( int i=1; i<pairs.size(); ++i ){
            if ( pairs[i][0]>pre ){
                pre = pairs[i][1];
                res++;
            }
        }
        return res;
    }
};

class Solution2 {
public:
    int findLongestChain(vector<vector<int>>& pairs) {
        vector<int> dp; //dp[i]为长为i的数对链的最后一个最大元素
        int l,r,mid,len=0;
        sort( pairs.begin(), pairs.end() );
        for ( auto e:pairs ){
            l=0; r=len-1;
            while( l<=r ){
                // 递增，找到首个比e[0]大的元素
                mid = (l+r)/2;
                if ( dp[mid]>=e[0] ) r = mid-1;
                else if ( dp[mid]<e[0] ) l = mid+1;
            }
            if ( l<len ){
                dp[l] = min( dp[l], e[1] );
            }else{
                ++len;
                dp.push_back( e[1] );
            }
        }
        return len;
    }
};