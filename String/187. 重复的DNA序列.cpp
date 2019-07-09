/*
    问题描述：
        所有 DNA 由一系列缩写为 A，C，G 和 T 的核苷酸组成，例如：“ACGAATTCCG”。在研究 DNA 时，识别 DNA 中的重复序列有时会对研究非常有帮助。

        编写一个函数来查找 DNA 分子中所有出现超多一次的10个字母长的序列（子串）。

        示例:

        输入: s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"

        输出: ["AAAAACCCCC", "CCCCCAAAAA"]

    问题分析：
        方法一：
            hashmap ，简单快捷，缺点是空间开销大。
        
        方法二：
            Bit Manipulation， 位运算，每一个字符用三位数字编码，
            （之所以不用两位是因为0不能用作编码，不然AA和A都没差了）
            每一个window长度为10，故30位小于32位，故int足矣。
 */
class Solution1 {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        string window;
        vector<string> res;
        unordered_map<string, int> mp;
        for ( int i=0; i<s.size(); ++i ){
            window = s.substr(i,10);
            if ( ++mp[window]==2 ) 
                res.push_back(window);
        }
        return res;
    }
};


class Solution2 {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        // 'A':1 , 'C':2 , 'G':3 , 'T':4
        int table[26];
        vector<string> res;
        table['A'-'A'] = 1;
        table['C'-'A'] = 2;
        table['G'-'A'] = 3;
        table['T'-'A'] = 4;
        unordered_map<int, int> mp;
        string window;
        int key;
        for ( int i=0; i<s.size(); ++i ){
            window = s.substr(i,10);
            key = 0;
            for ( auto c:window )
                key = ((key<<2) + table[c-'A']);
         
            if ( ++mp[key] == 2 ){
                res.push_back(window);
            }
        }
        return res;
    }
};