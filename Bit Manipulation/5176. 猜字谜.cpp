/*
    问题描述:
        外国友人仿照中国字谜设计了一个英文版猜字谜小游戏，请你来猜猜看吧。
        字谜的迷面 puzzle 按字符串形式给出，如果一个单词 word 符合下面两个条件，那么它就可以算作谜底：
        单词 word 中包含谜面 puzzle 的第一个字母。
        单词 word 中的每一个字母都可以在谜面 puzzle 中找到。
        例如，如果字谜的谜面是 "abcdefg"，那么可以作为谜底的单词有 "faced", "cabbage", 和 "baggage"；而 "beefed"（不含字母 "a"）以及 "based"（其中的 "s" 没有出现在谜面中）。
        返回一个答案数组 answer，数组中的每个元素 answer[i] 是在给出的单词列表 words 中可以作为字谜迷面 puzzles[i] 所对应的谜底的单词数目。

        示例：

        输入：
            words = ["aaaa","asas","able","ability","actt","actor","access"], 
            puzzles = ["aboveyz","abrodyz","abslute","absoryz","actresz","gaswxyz"]
        
        输出：[1,1,3,2,4,0]
        
        解释：
            1 个单词可以作为 "aboveyz" 的谜底 : "aaaa" 
            1 个单词可以作为 "abrodyz" 的谜底 : "aaaa"
            3 个单词可以作为 "abslute" 的谜底 : "aaaa", "asas", "able"
            2 个单词可以作为 "absoryz" 的谜底 : "aaaa", "asas"
            4 个单词可以作为 "actresz" 的谜底 : "aaaa", "asas", "actt", "access"
            没有单词可以作为 "gaswxyz" 的谜底，因为列表中的单词都不含字母 'g'。
         
        提示：
            1 <= words.length <= 10^5
            4 <= words[i].length <= 50
            1 <= puzzles.length <= 10^4
            puzzles[i].length == 7
            words[i][j], puzzles[i][j] 都是小写英文字母。
            每个 puzzles[i] 所包含的字符都不重复。


    问题分析：
        对于每一个puzzle, 找到满足以下条件的word个数:
            1. 单词 word 中包含谜面 puzzle 的第一个字母 
            2. 单词 word 中的每一个字母都可以在谜面 puzzle 中找到
        
        翻一下，就是满足下面两个条件的word个数:
            word中包括 puzzle[0] 
            word[0~n] 都在puzzle中

        因为字母一共就26个，所以可以用一个整数来对字符串编码
        把一个单词编码word成一个整数code， 前26位表示对应'a'-'z'是否出现
        cnt是个哈希表
        cnt[code]记录code这个单词的个数

        然后对于每一个puzzle, 我们只要看有哪些code满足，然后加上对应的cnt[code]就可以了.

        code是对word的编码， 关于找code的环节:
            code = 0
            第一个环节: word中包括 puzzle[0] 
                code |= 1 << ( puzzle[0]-'a')  
            
            第二个环节: word[0~n] 都在puzzle中
                我们可以知道，puzzle一共有7位，其中第一位一定存在于word中，
                所以只要puzzle的第2～7位的0/1组合全排列，就是当前puzzle的所有情况
                因为 如果code是 2～7位的所有01排列的子集， 那么word出现的单词一定是puzzle出现的单词的子集

                这里的一个迭代实现技巧就是，利用mask来实现:
                    首先 2～7位的排列组合， 一共有 2^6种， 而他们的二进制，就是所有的情况！！！！
                    所以不妨 for mask from 0 to 2^6， 然后把低6位的二进制作为 puzzle单词后6个字母的mask !!
                    
                    核心伪代码:
                    
                    for j from 0 to puzzles.size():
                        puzzle = puzzles[j] 
                        for mask from 0 to 2^6:
                            code |= 1 << ( puzzle[0]-'a')  
                            for i from 1 to 6: //表示mask的1～6位的情况 （第一位是0
                                if ( (mask & (1<<(i-1)) !=0  )  // 说明mask的第i位不是0！
                                    code |=  1<< ( puzzle[i]-'a' )  // mask第i位对应位为1，那么第i位的字符就可以选！
                            res[j] += cnt[code]

*/

class Solution {
public:
    vector<int> findNumOfValidWords(vector<string>& words, vector<string>& puzzles) {
        int nn = words.size();
        vector<int> res(puzzles.size());
        unordered_map<int,int> cnt;
        for ( auto s:words ){
            int mask = 0;
            for ( auto c:s )
                mask |= ( 1<<(c-'a') );
            ++cnt[mask];
        }
        
        int idx=0;
        for ( auto s:puzzles ){
            int sums=0;
            int n = s.size();
            // 找所有满足的words, puzzle的子集，且
            for ( int mask=0; mask < (1 << n-1); ++mask ){  // 开始搞后n-1位
                int code = (1<<(s[0]-'a')); // 第一位必须在
                for ( int i=1; i<n; ++i ){ // 后n-1位，只要是子集就行
                    if ( mask & (1<<(i-1)) )
                        code |= (1<<(s[i]-'a'));
                    
                }
                res[idx] += cnt[code];
            }
            ++idx;
        }
        return res;
    }
    
};