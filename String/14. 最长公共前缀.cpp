/*
	问题描述：
		编写一个函数来查找字符串数组中的最长公共前缀。

		如果不存在公共前缀，返回空字符串 ""。

		示例 1:

		输入: ["flower","flow","flight"]
		输出: "fl"
		示例 2:

		输入: ["dog","racecar","car"]
		输出: ""
		解释: 输入不存在公共前缀。
		
	问题分析：
		x是当前过滤到的横坐标，再按行遍历的时候，如果x超过了某一行的长度，就返回当前保存的res
		每次遍历一列，如果都一样，那么把这一列的字符加入res中
		只要有一个字符不一样，就直接返回res
		
		正常写逻辑就行。。。
*/

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs){
        string res="";
        if ( strs.size()<=0 ) return res;
        int y=0,x=0,finish=0;
        char cur;
        while( !finish ){
            if ( x<strs[0].size() ){
                cur = strs[0][x];
            }else finish=1;
            for ( int i=1; i<strs.size(); ++i ){
                if ( x>=strs[i].size() || cur!=strs[i][x] ){
                    finish=1;
                    break;
                } 
            }
            if ( !finish ) res.push_back(cur);
            x++;
        }
        return res;
    }
};