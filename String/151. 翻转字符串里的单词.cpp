/*
	题目描述：
		给定一个字符串，逐个翻转字符串中的每个单词。
		
		示例 1：
		输入: "   the sky is blue    "
		输出: "blue is sky the"
		
	说明：
		无空格字符构成一个单词。
		输入字符串可以在前面或者后面包含多余的空格，但是反转后的字符不能包括。
		如果两个单词间有多余的空格，将反转后单词间的空格减少到只含一个。

	方法一：
		O(N)
		O(N)
		把字符串放到一个字符串数组里，然后对数组进行reverse，最后再放回字符串里，
		然后在存的过程中，记得过滤空格。
		
	方法二：
		O(N)
		O(1)
		有点类似右移k个位置的那个思想，
		先对每个单词reverse
		最后再对整个字符串reverse
		记得过滤两边空格。
*/


class Solution1 {
public:
    string reverseWords(string s) {
        int i=0;
        string ans="";
        vector<string> res;
        while( i<s.size() ){
            string tmp="";
            while( i<s.size() && s[i]==' ' ) i++;
            while( i<s.size() && s[i]!=' ' )
                tmp = tmp + s[i++];
            if ( tmp!="" )
                res.push_back(tmp);
        }
        i=0;
        int j=res.size()-1;
        while( i<j ) swap(res[i++],res[j--]);
        for ( i=0; i<res.size(); ++i ){
            ans = ans + res[i];
            if ( i<res.size()-1 )
                ans = ans + " ";
        }
        return ans;
    }
};



# include <algorithm>
class Solution2 {
public:
    string reverseWords(string s) {
        int i=0,j,t;
		//trim一下字符串
        while( i<s.size() && s[i]==' ' ) i++;
        s.erase(0,i);
        j=s.size();
        while( j>0 && s[j-1]==' ' ) j--;
        s.erase(j,s.size());
        i=0;
		//开始反转每一个单词，并且去掉多余的空格
        while( i<s.size() ){
            //找到单词的首尾
			j=i+1;
            while( j<s.size() && s[j]!=' ' ) j++;
			//反转单词
            reverse(s.begin()+i, s.begin()+j);
            //判断空格数是否超过一个
			t = j+1;
            while( t<s.size() && s[t]==' ' ) t++;
            //若空格超出一个，则删掉多余的空格
			if ( t>j+1 )
                s.erase(s.begin()+j+1,s.begin() + t);
			//更新i
			i = j+1;
        }
		//反转整个字符串
        reverse(s.begin(),s.end());
        return s;
    }
};