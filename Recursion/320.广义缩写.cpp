/*
    问题描述：
        请完成一个能够给出 wordword 的所有“缩写”的函数（给出任意一种排列即可）
        
        Example
        例1:
        输入: 
        word = "word", 
        输出: 
        ["word", "1ord", "w1rd", "wo1d", "wor1", "2rd", "w2d", "wo2", "1o1d", "1or1", "w1r1", "1o2", "2r1", "3d", "w3", "4"]
        
        例2:
        输入:
        word = "today"
        输出:
        ["1o1a1","1o1ay","1o2y","1o3","1od1y","1od2","1oda1","1oday","2d1y","2d2",
        "2da1","2day","3a1","3ay","4y","5","t1d1y","t1d2","t1da1","t1day","t2a1",
        "t2ay","t3y","t4","to1a1","to1ay","to2y","to3","tod1y","tod2","toda1","today"]

    问题分析：
        这题真的是看样例猜题意- -， 
        朴素dfs暴力就可以过，
        值得注意的是，数字+'0' 是可以变成字符数字的，但是，如果数字大于了10记得好好转换成字符串（查这个bug查半天T_T

        dfs时：
            1. 思路框架：
                [0,i) [i,i+len-1] [i+len, n)
                前缀  i开始长为len的字符串变为数字字符串 后缀
            2. 因为数字不能连续，所以真正的是:
                [0,i)前缀 [i,i+len-1]数字字符串 [i+len]字符 （i+len, n)后缀,交给下一次dfs来加
 */

 class Solution {
public:
    vector<string> generateAbbreviations(string &word) {
        // Write your code here
        vector<string> res;
        helper( res, word, "" );;
        return res;
    }
    void helper( vector<string> & res, string word, string cur ){
        //在第i个位置，替换长为len
        if ( word=="" ){
            res.push_back(cur);
            return ;
        }
        res.push_back(cur+word);
        for ( int i=0; i<word.size(); ++i )
            for ( int len=1; len<=word.size()-i; ++len ){
                //[0,i) [i,i+len-1] [i+len, n)
                if ( i+len<word.size() )
                    helper( res, word.substr(i+len+1), cur + word.substr(0,i) +  to_string(len) + word[i+len] );
                else
                    helper( res, "", cur + word.substr(0,i) +  to_string(len)  );
            }
    }
};

 class Solution {
public:
    vector<string> generateAbbreviations(string &word) {
        // Write your code here
        vector<string> res;
        helper( res, word, "" );;
        return res;
    }
    void helper( vector<string> & res, string word, string cur ){
        //在第i个位置，替换长为len
        if ( word=="" ){
            res.push_back(cur);
            return ;
        }
        res.push_back(cur+word);
        for ( int i=0; i<word.size(); ++i )
            for ( int len=1; len<=word.size()-i; ++len ){
                //[0,i) [i,i+len-1] [i+len, n)
                if ( i+len<word.size() )
                    helper( res, word.substr(i+len+1), cur + word.substr(0,i) +  to_string(len) + word[i+len] );
                else
                    helper( res, "", cur + word.substr(0,i) +  to_string(len)  );
            }
    }
};