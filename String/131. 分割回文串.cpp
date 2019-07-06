/*
    问题描述：
        给定一个字符串 s，将 s 分割成一些子串，使每个子串都是回文串。

        返回 s 所有可能的分割方案。

        示例:

        输入: "aab"
        输出:
        [
        ["aa","b"],
        ["a","a","b"]
        ]

    问题分析：
        递归回溯。
        返回条件，递归函数helper的当前起始位置start到达n(n为s的长度)
        没什么好说的。。水题
 */

class Solution {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> res;
        vector<string> t;
        helper( res, t, 0, s );
        return res;
    }
    
    //返回res， t是res的元素，start为起始位置
    void helper( vector<vector<string>>& res, vector<string> &t, int start, string s ){
        // 返回情况
        if ( start>=(int)s.size() ){
            res.push_back(t);
            return;
        }
        for ( int i=start; i<s.size(); ++i ){
            if ( isValid( s.substr(start, i-start+1) ) ){
                t.push_back(s.substr(start, i-start+1));
                helper( res, t, i+1, s );
                t.pop_back(); //回溯
            }
        }
    }
    //判断是否为回文
    bool isValid(string s){
        int i=0,j=s.size()-1;
        while( i<j && s[i]==s[j] ){
            i++;
            j--;
        } 
        return i>=j;
    }
};
