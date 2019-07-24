/*
    问题描述：
        给定一个非空字符串 s 和一个包含非空单词列表的字典 wordDict，在字符串中增加空格来构建一个句子
        ，使得句子中所有的单词都在词典中。返回所有这些可能的句子。
        说明：

        分隔时可以重复使用字典中的单词。
        你可以假设字典中没有重复的单词。
        示例 1：

        输入:
        s = "catsanddog"
        wordDict = ["cat", "cats", "and", "sand", "dog"]
        输出:
        [
          "cats and dog",
          "cat sand dog"
        ]

    问题分析：
        本题分为两个步骤：
            1. 检测s能否根据wordDict来分割出来
            2. 如果可以分割，那么开始分割
        
        0. 可以事前先判断一次，若s中出现了wordDict中未出现的字符，那么一定不可被分割
        1. 用Dp来解决检测问题：
            dp[i]表示s前i个字符能否由wordDict分割
            状态转移公式为:
            for idx : [1, len(s)]
                for ( int len : wordDict中的所有长度 )
                    if ( idx-len>=0 && dp[idx-len]可以被表示 && s[idx-len : idx]在wordDict中  )
                        dp[idx] = true
        2. dfs来分割：
            分割就比较简单了，
            void helper(...){
            ...
            for ( auto len : wordDict中的所有长度 ){
                if ( len>s.size() ) return;
                string cur = s.substr(0,len);
                if ( cur在wordDict里 ){
                    helper( res, dic, lens, s.substr(len), str+" "+cur );
                }
            }
        }
 */

 class Solution {
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        set<string> dic;
        set<int> lens;
        vector<string> res;
        for ( auto s:wordDict ){
            dic.insert(s);
            lens.insert(s.size());
        }
        if ( !canBreak(s, dic, lens) ) return {};
        
        helper( res, dic, lens, s, "" );
        return res;
    }
    
    bool canBreak(string s, set<string> & dic, set<int>& lens){
        //dp[i] : 前i个元素是否可以被拆分
        bool dp[s.size()+1];
        memset(dp,false,sizeof(dp));
        dp[0] = true;
        // 正向dp会超时
        //queue<int> q;
        //q.push(0);
        // while( !q.empty() ){
        //     int idx = q.front(); q.pop();
        //     for ( auto len:lens ){  
        //         if ( idx+len<=s.size() ){
        //             string cur = s.substr(idx,len);
        //             if ( dp[idx]==true && dic.count(cur)>0 ){
        //                 dp[idx+len] = true;
        //                 q.push(idx+len);
        //             }
        //         }
        //     }
        // }
        
        for ( int idx=1; idx<=s.size(); ++idx ){
            for ( auto len:lens ){  
                if ( idx-len>=0 && dp[idx-len] && dic.count( s.substr(idx-len,len) )>0 ){
                    dp[idx] = true;
                    break;
                }
            }
        }
        
        return dp[s.size()];
    }
    
    void helper( vector<string>& res, set<string> & dic, set<int>& lens, string s, string str ){
        if ( s.size()==0 ){
            res.push_back(str.substr(1));
            return;
        }
        for ( auto len:lens ){
            if ( len>s.size() ) return;
            string cur = s.substr(0,len);
            if ( dic.count(cur) ){
                helper( res, dic, lens, s.substr(len), str+" "+cur );
            }
        }
    }
};