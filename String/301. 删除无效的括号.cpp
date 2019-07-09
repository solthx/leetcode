/*
    问题描述：
        删除最小数量的无效括号，使得输入的字符串有效，返回所有可能的结果。

        说明: 输入可能包含了除 ( 和 ) 以外的字符。
        示例 1:
        输入: "()())()"
        输出: ["()()()", "(())()"]
        
        示例 2:
        输入: "(a)())()"
        输出: ["(a)()()", "(a())()"]
        
        示例 3:
        输入: ")("
        输出: [""]

    问题分析：
        方法一：
            暴力BFS，初始化一个队列来保存string，首先是删去一个括号字符得到的所有情况，
            然后判断删掉两个的，然后三个。。
            直到首次发现一个满足回文的字符串，那么这个字符串就是最长长度，所有长度小于它的都不符合要求
            因为是按删除字符个数依次入队的，所以一旦发现回文串就直接不用再入队了(found变量来控制)
            在入队的过程，就是遍历当前删去了n个字符的字符串，一旦发现'('或‘)'就删除，入队删去了n+1个字符串
            最终把所有满足的回文串压入res中
        
        方法二：
            DFS，用cnt1和cnt2记录多余的左括号数和右括号数， 然后用DFS的方式，把cnt1和cnt2都
            变成0， 这一情况就可以把对应的字符串压入结果中。 
            在DFS函数中， 遍历当前cnt1和cnt2对应的字符串s的时候，
            if ( cnt1>0 && s[i]=='(' )
                helper( res, i, 删掉s[i]的s, cnt1-1, cnt2 );
            if ( cnt2>0 && s[i]==')' )
                helper( res, i, 删除s[i]的s, cnt1, cnt2-1 );
    
        方法三：
            二刷再更
 */

 class Solution1 {
public:
    vector<string> removeInvalidParentheses(string s) {
        queue<string> q;
        string t;
        vector<string> res;
        unordered_set<string> sets{{s}};
        bool found=false;   //首次发现满足条件的回文串
        q.push(s);
        while( !q.empty() ){
            t = q.front(); q.pop();
            if ( isValid(t) ){
                res.push_back(t);
                found = true;
            }
            if ( found ) continue;
            for ( int i=0; i<t.size(); ++i ){  // 把删去n+1个括号的字符串压入队列
                if ( t[i]=='(' || s[i]==')' ){
                    string st = t.substr(0,i) + t.substr(i+1);
                    if ( !sets.count(st)   ){
                        q.push(st);
                        sets.insert(st);
                    }
                }
            }
        }
        return res;
    }
    
    bool isValid(string s){
        int cnt=0, i=0;
        while( i<s.size() ){
            if ( s[i]=='(' ) ++cnt;
            else if ( s[i]==')' && --cnt<0 ) return false;
            ++i;
        }
        return cnt==0;
    }
        
};


class Solution2 {
public:
    vector<string> removeInvalidParentheses(string s) {
        // 使用两个变量来分别记录左右括号的多余的数量也是一个不错的思路
        int cnt1=0, cnt2=0;
        for ( int i=0; i<s.size(); ++i )
            if ( s[i]==')' && --cnt1<0 ){
                cnt2++;
                cnt1=0;
            }
            else if (s[i]=='(') ++cnt1;
        vector<string> res;
        // 直到cnt1和cnt2都为0的时候，再把其压入res
        helper(res, 0, s, cnt1, cnt2);
        return res;
    }
    
    void helper( vector<string> & res, int start, string s, int cnt1, int cnt2){
        if ( cnt1==0 && cnt2==0  ){
            if ( isValid(s) )
                res.push_back(s);
            return ;
        }
        for ( int i=start; i<s.size(); ++i ){
            if ( i==start || s[i]!=s[i-1] ){
                if ( cnt1>0 && s[i]=='(' )
                    helper( res, i, s.substr(0, i) + s.substr(i+1), cnt1-1, cnt2 );
                if ( cnt2>0 && s[i]==')' )
                    helper( res, i, s.substr(0, i) + s.substr(i+1), cnt1, cnt2-1 );
            }
        }
    }
    bool isValid(string t) {
        int cnt = 0;
        for (int i = 0; i < t.size(); ++i) {
            if (t[i] == '(') ++cnt;
            else if (t[i] == ')' && --cnt < 0) return false;
        }
        return cnt == 0;
    }
};