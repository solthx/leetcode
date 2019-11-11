/*
    问题描述:
        你将会得到一份单词表 words，一个字母表 letters （可能会有重复字母），以及每个字母对应的得分情况表 score。
        请你帮忙计算玩家在单词拼写游戏中所能获得的「最高得分」：能够由 letters 里的字母拼写出的 任意 属于 words 单词子集中，分数最高的单词集合的得分。
        单词拼写游戏的规则概述如下：
        玩家需要用字母表 letters 里的字母来拼写单词表 words 中的单词。
        可以只使用字母表 letters 中的部分字母，但是每个字母最多被使用一次。
        单词表 words 中每个单词只能计分（使用）一次。
        根据字母得分情况表score，字母 'a', 'b', 'c', ... , 'z' 对应的得分分别为 score[0], score[1], ..., score[25]。
        本场游戏的「得分」是指：玩家所拼写出的单词集合里包含的所有字母的得分之和。
         

        示例 1：

            输入：words = ["dog","cat","dad","good"], letters = ["a","a","c","d","d","d","g","o","o"], score = [1,0,9,5,0,0,3,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0]
            输出：23
        解释：
            字母得分为  a=1, c=9, d=5, g=3, o=2
            使用给定的字母表 letters，我们可以拼写单词 "dad" (5+1+5)和 "good" (3+2+2+5)，得分为 23 。
            而单词 "dad" 和 "dog" 只能得到 21 分。
        
        示例 2：
            输入：words = ["xxxz","ax","bx","cx"], letters = ["z","a","b","c","x","x","x"], score = [4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,10]
            输出：27
        解释：
            字母得分为  a=4, b=4, c=4, x=5, z=10
            使用给定的字母表 letters，我们可以组成单词 "ax" (4+5)， "bx" (4+5) 和 "cx" (4+5) ，总得分为 27 。
            单词 "xxxz" 的得分仅为 25 。
        
        示例 3：

            输入：words = ["leetcode"], letters = ["l","e","t","c","o","d"], score = [0,0,1,1,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,0,0,0,0]
        输出：0
            解释：
            字母 "e" 在字母表 letters 中只出现了一次，所以无法组成单词表 words 中的单词。

        提示：
            1 <= words.length <= 14
            1 <= words[i].length <= 15
            1 <= letters.length <= 100
            letters[i].length == 1
            score.length == 26
            0 <= score[i] <= 10
            words[i] 和 letters[i] 只包含小写的英文字母。

    问题分析:
        数据量很小，完全可以枚举所有情况. 
        
        方法一: DFS
            用深搜来遍历每一种情况。 

            要强调的是: 进行DFS遍历每一种个情况的时候， 一定要覆盖到每种情况！！！！
            以本题为例， 每个元素分为取和不取 两种情况，
            因此， 在计算完取的情况以后，一定别漏了不取的情况啊！！！

        方法二:
            位运算枚举。

            这种二分一样的情况(取or不取)， 可以通过位运算来做.
            
            本题长度最长为15 ， 即枚举所有情况就是 2^15 

            而每一种情况对应 0~2^15，里的一个数字， 这个数字的二进制的低15位，0代表不取，1代表取，

            以此来枚举所有情况。
*/


// 位运算枚举
class Solution {
public:
    int maxScoreWords(vector<string>& words, vector<char>& letters, vector<int>& score) {
        int cnt[26]={0}, res=0;
        for ( auto c:letters )
            ++cnt[c-'a'];
        int n = 1<<(words.size()); // 所有情况数
        for ( int i=1; i<n; ++i ){ // 枚举情况[1,n)
            int cur[26]={0};
            bool ok = true; 
            for ( int j=0; j<words.size() && ok; ++j ){
                if ( ((1<<j)&i)!=0 ){ // 如果i的二进制的第j位是1， 那么就可以取第j个单词
                    for ( auto c:words[j] )
                        if ( ++cur[c-'a']>cnt[c-'a'] ) { // 如果取了第j个单词 超过了可用单词数，那么就不ok了
                            ok = false;
                            break;
                        }
                }
            }
            if ( ok ){ // 依然ok的话 就可以取
                int tmp=0;
                for ( int i=0; i<26; ++i )
                    tmp += score[i]*cur[i];
                res = max(res, tmp);
            }
        }
        return res;
    }
};