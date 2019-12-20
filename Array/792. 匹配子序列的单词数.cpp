/*
    问题描述:
        给定字符串 S 和单词字典 words, 求 words[i] 中是 S 的子序列的单词个数。

        示例:
        输入:
        S = "abcde"
        words = ["a", "bb", "acd", "ace"]
        输出: 3
        解释: 有三个是 S 的子序列的单词: "a", "acd", "ace"。
        注意:

        所有在words和 S 里的单词都只由小写字母组成。
        S 的长度在 [1, 50000]。
        words 的长度在 [1, 5000]。
        words[i]的长度在[1, 50]。


    问题分析:
        方法一:
            暴力匹配, TLE

        方法二:
            因为S的长度为5*10^4 ，可以先根据S来把 匹配word时所感兴趣的信息先给保存起来..

            我们再扫描word时，以acd为例，扫描完a，我们想知道，如果在S里匹配到了a,那么 这个位置后面是否还有c?
            如果有的话，就返回下一个最近的c的位置，然后再看后面是否还有d? 依次类推

            所以dp[i][c]就保存 在S的[i,n)中，是否有字符c, 如果有的话，就返回这个字符c的位置，如果没有的话，就范围-2

            然后就好办了，先建dp, 再扫描word。。

            复杂度O( max(N*26, K*M) )  N为S的长度, K为words长度, M为word的长度

        方法三:
            看了官方题解的解法:

                因为 S 很长，所以寻找一种只需遍历一次 S 的方法，避免暴力解法的多次遍历。

                将所有单词根据首字母不同放入不同的桶中。例如当 words = ['dog', 'cat', 'cop']，根据首字母不同可以分为 'c' : ('cat', 'cop'), 'd' : ('dog',)。换句话说，每个桶中的单词就是该单词正在等待匹配的下一个字母。在遍历 S 的同时，将匹配到单词根据下一个需要匹配的字母移动到不同的桶中。

                例如，有字符串 S = 'dcaog'：

                初始化 heads = 'c' : ('cat', 'cop'), 'd' : ('dog',)；
                遍历 S[0] = 'd' 后，heads = 'c' : ('cat', 'cop'), 'o' : ('og',)；
                遍历 S[1] = 'c' 后，heads = 'a' : ('at',), 'o' : ('og', 'op')；
                遍历 S[2] = 'a' 后，heads = 'o' : ('og', 'op'), 't': ('t',) ;
                遍历 S[3] = 'o' 后，heads = 'g' : ('g',), 'p': ('p',), 't': ('t',)；
                遍历 S[0] = 'g' 后，heads = 'p': ('p',), 't': ('t',)。
                算法

                使用长度为 26 的数组 heads 做桶，每个字母对应一个桶。访问 S 中的每个字母时，将该字母对应桶中的所有单词，根据下一个等待匹配字母放入到不同的桶中。如果已经匹配到单词的最后一个字母，那么子序列单词数加 1。

            作者：LeetCode
            链接：https://leetcode-cn.com/problems/number-of-matching-subsequences/solution/pi-pei-zi-xu-lie-de-dan-ci-shu-by-leetcode/
            来源：力扣（LeetCode）

            复杂度O( max(N, M) )
*/

class Solution2 {
public:
    int numMatchingSubseq(string S, vector<string>& words) {
        // dp[i][c]表示在第i个位置上，下一个字符c的位置是多少, 如果为-1则说明不存在
        vector<vector<int>> dp( S.size()+1, vector<int>(26, -2) );
        for ( int i=S.size(); i>0; --i ){
            for ( int j=0; j<26; ++j ){
                if ( (char)('a'+j) == S[i-1] )
                    dp[i-1][j] = i-1;
                else dp[i-1][j] = dp[i][j];
            }
        }
        int res = 0;
        for ( auto word:words ){
            int i=0, j=-1;
            while( i<word.size() && j>=-1 ){
                j = dp[j+1][word[i]-'a'];
                if ( j>=-1 )
                    ++i;
            }
            if ( i>=word.size() )
                ++res;
        }
        return res;
    }
};

class Solution3 {
public:
    int numMatchingSubseq(string S, vector<string>& words) {
        unordered_map<char, vector<string>> mp;
        for ( auto word:words )
            mp[word[0]].push_back(word);
        int res = 0;
        for ( auto c:S ){
            vector<string> sav;
            for ( auto s:mp[c] ){
                if ( s.size()>1 )
                    sav.push_back(s.substr(1));
                else ++res;
            }
            mp.erase(c);
            for ( auto word:sav )
                mp[word[0]].push_back(word);
        }
        return res;
    }
};