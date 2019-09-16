/*
    问题描述:
        给定一个字符串，对该字符串可以进行 “移位” 的操作，也就是将字符串中每个字母都变为其在字母表中后续的字母，比如："abc" -> "bcd"。这样，我们可以持续进行 “移位” 操作，从而生成如下移位序列：

        "abc" -> "bcd" -> ... -> "xyz"
        给定一个包含仅小写字母字符串的列表，将该列表中所有满足 “移位” 操作规律的组合进行分组并返回。

        示例：
            输入: 
                ["abc", "bcd", "acef", "xyz", "az", "ba", "a", "z"]
            输出: 
                [
                    ["abc","bcd","xyz"],
                    ["az","ba"],
                    ["acef"],
                    ["a","z"]
                ]

            输入:
                ["ac","bd"]
            输出:
                [["ac","bd"]]
    问题分析:
        方法一: 暴力+剪枝 O(N^2)
            只要两个单词长度相同，并且对于任意 i<word1.size() 都满足: word1[i]-word1[i-1] == word2[i] - word2[i-1] 
            那么这两个单词可以放到一起.
            然后每个单词只能放到一个vector里， 所以已经被放入的单词可以不用访问了，用visited来保存单词是否已被放入
        
        方法二: 重新对单词进行编码+hashmap
            只要word1,word2满足：
                1. word1.size() == word2.size()
                2. 对于任意 i<word1.size() 都满足: word1[i]-word1[i-1] == word2[i] - word2[i-1] 
            那么word1和word2可以在一个组里

            同时这里也具有传递性，
            也就是上面的条件可以改成:
                1. word1.size() == word2.size()
                2. 对于任意 i<word1.size() 都满足: word1[i]-word1[0] == word2[i] - word2[0] 
            即 所有的字母到 首字母的距离都相同的话，那就可以在同一组
            
            然后根据这个特性，对单词进行编码，得到一个新的字符串，这个字符串上的每一位都代表了这个位置上的字符到首字符的距离
*/

class Solution1 {
public:
    // 暴力+剪枝
    vector<vector<string>> groupStrings(vector<string>& strings) {
        vector<bool> visited( strings.size(), false );
        vector<vector<string>> res;
        for ( int i=0; i<strings.size(); ++i ){
            if ( !visited[i] ){
                vector<string> cur{{strings[i]}};
                visited[i] = true;
                for ( int j=i+1; j<strings.size(); ++j ){
                    if ( !visited[j] && strings[j].size()==strings[i].size() ){
                        int t=1, n = strings[j].size(),diff1, diff2;
                        while( t<n ){
                            diff1 = (strings[j][t]-strings[j][t-1] +26)%26;
                            diff2 = (strings[i][t]-strings[i][t-1] +26)%26;
                            if ( diff1!=diff2 ) break;
                            else ++t;
                        }
                        if ( t>=n ){
                            cur.push_back( strings[j] );
                            visited[j] = true;
                        }
                    }
                }
                res.push_back(cur);
            }
        }
        return res;
    }
};

class Solution2 {
public:
    // 重编码+hashmap
    vector<vector<string>> groupStrings(vector<string>& strings) {
        unordered_map<string, vector<string>> mp;
        for ( auto & s:strings ){
            string cur = "";
            char c = s[0];
            for ( int i=0; i<s.size(); ++i )
                cur += ( (s[i]-c +26 )%26 +'a'); // 到首字符的距离 'a'加不加都无所谓的.
            mp[cur].push_back(s);
        }
        vector<vector<string>> res;
        for ( auto it:mp )
            res.push_back(it.second);
        return res;
    }
};