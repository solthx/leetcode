/*
    问题描述：
        给定一个只包含数字的字符串，复原它并返回所有可能的 IP 地址格式。
        示例:
        输入: "25525511135"
        输出: ["255.255.11.135", "255.255.111.35"]

    问题分析：
        合理使用substr(), set, stoi, 就成了水题。。
        值得一题的是在字符串转换成数字的时候，
        001 ≠ 1，
        记得过滤掉以0开头的非0数字字符串。
 */

 class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        vector<string> res;
        helper( res, "", s, 0 );
        return res;
    }
    
    void helper( vector<string>& res, string cur, string s, int cnt ){
        if ( cnt>=4 && s.size()==0 ){
            //
            res.push_back(cur);
            return ;
        }
        if ( cnt>=4 ) return ;
        for ( int len=1; len<=3 && len<=s.size(); ++len ){
            string tmp = s.substr(0,len);
            // 记得过滤以0为开头的非0数字字符串
            if ( atoi(tmp.c_str())>255 || ( tmp[0]=='0' && tmp.size()>1  ) ) continue;
            if ( cur=="" )
                helper( res, tmp, s.substr(len), cnt+1 );
            else
                helper( res, cur+"."+tmp, s.substr(len), cnt+1 );
        }
        
    }
};