/*
	问题描述：
		给定一组非负整数，重新排列它们的顺序使之组成一个最大的整数。

		示例 1:

		输入: [10,2]
		输出: 210
		示例 2:

		输入: [3,30,34,5,9]
		输出: 9534330

	问题分析：
		排序，注意，这解释一下cmp
		bool cmp(string a,string b)
			return a+b>b+a;
		的意思是，如果a和b的顺序是: ..,a,b,.. 那么一定是a+b>b+a 
		
		然后善用字符串比较吧。。
		
		注意排除全0的情况
*/

class Solution {
public:
    string largestNumber(vector<int>& nums) {
        if ( only_zero(nums) )
            return "0";
        sort(nums.begin(),nums.end(),cmp);
        string res = "";
        for ( auto e:nums )
            res = res + to_string(e);
        return res;
    }
    
    static bool only_zero(vector<int>& s){
        for ( int i=0; i<s.size(); ++i )
            if ( s[i]!=0 )
                return false;
        return true;
    }
    
    static bool cmp(int a,int b){
        string sa = to_string(a);
        string sb = to_string(b);
        return sa+sb > sb+sa;
    }
};
