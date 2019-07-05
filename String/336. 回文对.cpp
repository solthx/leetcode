/*
    题目描述：
        给定一组唯一的单词， 找出所有不同 的索引对(i, j)，使得列表中的两个单词， words[i] + words[j] ，可拼接成回文串。

        示例 1:

        输入: ["abcd","dcba","lls","s","sssll"]
        输出: [[0,1],[1,0],[3,2],[2,4]] 
        解释: 可拼接成的回文串为 ["dcbaabcd","abcddcba","slls","llssssll"]
        示例 2:

        输入: ["bat","tab","cat"]
        输出: [[0,1],[1,0]] 
        解释: 可拼接成的回文串为 ["battab","tabbat"]

    题目分析：
        暴力不可行。
        仔细考虑后可以归结为以下情况：
            1. "" 和 回文串的组合
            2. 类 "abc"和"cba"的组合 (相反)
            3. 字符串拆成 左侧回文串a+右侧字符串b 的形式 (例如 aaabc 拆成 aaa+bc)
                然后若存在reversed(右侧字符串b) (例如上面的bc翻转为cb),
                那么就可以组合成 (cbaaabc) 
            4. 与情况三同理，只不过变成右侧是回文串
        
        具体实现：
            实现的时候，可以把1，2都变成第3种情况
            例如:
                aba被拆成 "" + "aba" 且 ""作为回文判断，寻找"reverse(aba)"时，就变成了情况2
                aba被拆成 "" + "aba" 且 "aba"作为回文判断，寻找""时，就变成了情况1 
            还要防止匹配到自己的情况
            下面时具体实现。
*/

class Solution {
public:
    vector<vector<int>> palindromePairs(vector<string>& words) {
        vector<vector<int>> res;
        unordered_map<string, int> mp; //记录字符串的位置
        int cut,len;
        string left,right;
        for ( int i=0; i<words.size(); ++i )
            mp[words[i]]=i+1; //初始为0 ，位置从1开始记，为0则视为不存在 （其实可以使用mp.count(key)也可以，效果都一样//
        for ( int i=0; i<words.size(); ++i ){
            len = words[i].size();
            //回文的倒转还是回文，不影响，所以可以先整体倒转，后面search就不用倒转了
            reversed(words[i]);
            for ( cut=0; cut<=len; ++cut ){
                // left长为cut，right长为len-cut
                left = words[i].substr(0, cut); 
                right = words[i].substr(cut);
                // 左侧是回文， 且能够找到右侧的倒转，并且找到的不是自己，就可以组合
                if ( ispal(left) && mp[right]>0 && mp[right]!=i+1  ){
                    res.push_back({ i, mp[right]-1});    
                }
                // 和上面同理
                // 不过要过滤掉重复情况：
                // cut为0时，上面的情况  和 cut为len时，下面的情况 产生了重复
                // 所以过滤掉一个就可以， 这里选择的时过滤掉下面的cut==len的情况
                // 多说一句，重复的情况就是 判断""是否为回文，然后找reversed(words[i])
                if ( ispal(right) && mp[left]>0 && mp[left]!=i+1 && cut!=len ){
                    res.push_back({ mp[left]-1, i});        
                }
            }
        }
        return res;
    }
    
    void reversed(string & s){
        int i=0,j=s.size()-1;
        while( i<j )
            swap(s[i++],s[j--]);
    }

    //判断是否是回文
    bool ispal(string s){
        int i=0, j=s.size()-1;
        while( i<j && s[i]==s[j] ){
            i++;j--;
        }
        return i>=j;
    }
};