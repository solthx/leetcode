/*
    题目描述：
        给定一个字符串 s 和一些长度相同的单词 words。找出 s 中恰好可以由 words 中所有单词串联形成的子串的起始位置。

        注意子串要与 words 中的单词完全匹配，中间不能有其他字符，但不需要考虑 words 中单词串联的顺序。

        示例 1：
        输入：
        s = "barfoothefoobarman",
        words = ["foo","bar"]
        输出：[0,9]
        解释：
        从索引 0 和 9 开始的子串分别是 "barfoor" 和 "foobar" 。
        输出的顺序不重要, [9,0] 也是有效答案。
        
        示例 2：
        输入：
        s = "wordgoodgoodgoodbestword",
        words = ["word","good","best","word"]
        输出：[]

    问题分析：
        一开始没看到每个单词长度相同了。。
        说说单词长度不同也可以容忍的做法：

        window大小为固定的（所有字符加起来的长度。。）
        每次都看window是否由words组成match_in_win函数，
        match_in_win的实现方式为暴力实现。。
        
 */

 class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        int j=0;
        int i=0;
        int winlen = 0;
        vector<int> res;
        if ( words.size()==0 ) return res;
        for ( auto s:words )
            winlen += s.size();
        while( i+winlen<=s.size() ){ 
            if ( match_in_win(s.substr(i,winlen), words ) ){
                res.push_back( i );
             //   i += winlen;
            }
            i += 1;
        }
        return res;
    }
    
    //匹配看s是否由words组成，返回失败的位置
    bool match_in_win( string s, vector<string>& words ){
       // cout<<s<<" : "<<endl;
        int len = words.size()-1;
        int si = 0, j=0;
        bool flag;
        while( si<s.size() ){
            flag = false;
            for ( int i=0; i<=len; ++i ){
                if ( words[i][0]==s[si] ){
                    // 开始匹配
                    j = 0;
                    while( j<words[i].size() && s[si+j]==words[i][j] ){
                        ++j;
                    }
                    if ( j==words[i].size() ){
                        //匹配成功
                        flag = true;
                        swap(words[i],words[len]);
                        --len;
                        break;
                    }
                }
            }
            if ( flag ) si += j;
            else{
                //cout<<"在"<<si<<"失败"<<endl<<endl;;
                return false;
            } 
        }
        return true;
    }
    
};