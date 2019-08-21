/*
    问题描述:
        给定一个字符串数组 words，找到 length(word[i]) * length(word[j]) 的最大值，并且这两个单词不含有公共字母。你可以认为每个单词只包含小写字母。如果不存在这样的两个单词，返回 0。
        示例 1:
        输入: ["abcw","baz","foo","bar","xtfn","abcdef"]
        输出: 16 
        解释: 这两个单词为 "abcw", "xtfn"。
        
        示例 2:
        输入: ["a","ab","abc","d","cd","bcd","abcd"]
        输出: 4 
        解释: 这两个单词为 "ab", "cd"。
        
        示例 3:
        输入: ["a","aa","aaa","aaaa"]
        输出: 0 
        解释: 不存在这样的两个单词。

    问题分析:
        思路很简单，N^2暴力，找到两个不存在公共元素的字符串，然后算出所有这些字符串中，长度乘积最大的那两个.

        关键点在于，如何快速判断两个字符串是否存在公共元素.

        用O(N)就会TLE

        因为本题的集合是所有小写字母，集合大小<=26，

        所以可以用位运算来做. 
        
        即int的32位可以作为map， 
        每一位代表一种， 这里只用前26位就行了，每一位代表一个字母

        把两个字符串编码成两个数字， 然后两个数字的与操作，如果是0，那么就说明没有公共元素

        本题核心在于int的32位可以作为map.！！！！

        另外一个:
            位操作的优先级 极低！！！！
            只要用位操作， 就加括号！！！！！！！！！！！
*/

class Solution {
public:
    int maxProduct(vector<string>& words) {
        int i=0, maxi = 0, n=words.size();
        vector<int> mask(n,0);
        for( i=0; i<words.size(); ++i ){
            for ( auto c:words[i] ){
                mask[i] |= (1<<(c-'a'+1));
            }
        }
        
        for ( int i=0; i<words.size(); ++i ){
            for ( int j=i+1; j<words.size(); ++j ){
                if ( (mask[i] & mask[j]) == 0 ){ // 用到位运算符，就一定加括号！！！！！！
                    maxi = max( maxi, (int)words[i].size()*(int)words[j].size());
                    //cout<<"S"<<endl;
                }
            }
        }
        return maxi;
    }
    
    
};