/*
    问题描述：
        给定一个字符串s，返回所有回文排列(不重复)。如果没有回文排列，则返回空列表。
        Example
        样例1

        输入: s = "aabb"
        输出: ["abba","baab"]

    问题分析：
        如果“出现次数为奇数”的字符数超过1， 那么一定不存在回文排列
        若存在回文排列：
            1. 若不存在“出现次数为奇数的字符”：
                把每个字符出现次数除2， 然后列出所有排列组合，得到s，然后s+reversed(s)就是一种情况
            2. 如果存在“出现次数为奇数”的字符c：
                和1差不多，只不过变成了 s + c + reversed(s)
 */
 class Solution {
public:
    /**
     * @param s: the given string
     * @return: all the palindromic permutations (without duplicates) of it
     */
    vector<string> generatePalindromes(string &s) {
        // write your code here
        int pos=-1;
        int table[128] = {0};
        vector<string> res;
        string t;
        for ( auto c:s ) //记录字符次数
            ++table[c];
        for ( int i=0; i<128; ++i )
            if ( table[i]%2==1  ) 
                if ( pos==-1 ){  //pos为奇数字符
                    pos = i;
                    table[i] = (table[i]-1) /2 ;
                }
                else return res; //出现超过一次奇数次数字符 ，是不存在情况
            else table[i] /= 2;
        helper( res, table, pos, t );
        return res;
    }
    
    void helper( vector<string> & res,  int table[], int pos, string t ){
        char c;
        bool flag=true; //是否每个字符次数都列完了，得到了最终的s
        for ( char i='a'; i<='z'; ++i ){
            if ( table[i] > 0 ){
                flag=false;  // 只要存在table[c]大于0， 就肯定不是最终情况
                table[i]--;
                t = t + i;
                helper(res, table, pos, t);
                table[i]++; //回溯
                t.pop_back();
            }
        }
        if ( flag ){
            string rv = reversed(t);
            if ( pos!=-1 ){ //存在奇数字符的情况
                c = pos;
                t = t + c;
            }
            res.push_back( t + rv );
        }
    }
    
    string reversed(string s){
        int i=0, j=s.size()-1;
        while( i<j ) swap(s[i++],s[j--]);
        return s;
    }
};