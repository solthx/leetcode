/*
	问题描述：
		给你一个字符串 S、一个字符串 T，请在字符串 S 里面找出：包含 T 所有字母的最小子串。
		
		示例：
		输入: S = "ADOBECODEBANC", T = "ABC"
		输出: "BANC"
		                                               
		说明：
		如果 S 中不存这样的子串，则返回空字符串 ""。
		如果 S 中存在这样的子串，我们保证它是唯一的答案。


	问题分析：
		维护一个window 用left和right来确定这个区间范围，
		while（ right没到结尾 ）:
			1. 先移动right， 直到区间内满足了包含所有的字符串t中的字符
			2. 再移动left， 直到区间内到可以满足上面要求的最小区间
			3. 更新最小区间长度
		
		实现时，用need[c]来记录在t中的字符c的出现次数（也可以理解成在window中对字符c的需求个数）
		cnt表示已经包含的字符串t中的字符个数（当cnt==t.size()的时候，就说明满足条件了）
*/

class Solution {
public:
    string minWindow(string s, string t) {
        int need[256] = {0};
        string res="";
        int left=0, minlen=INT_MAX, right=0, pos=0;
        int cnt=0;
        char ch;
        for ( auto c:t )
            ++need[c];  //字符c需要的个数
        while( right<s.size() ){
            ch = s[right];
            if ( --need[ch]>=0 ) //收录进一个字符c，那么字符c的需求数就减1
                ++cnt;  //如果原本需求是大于0的，那么减去1后就是大于等于0，也就是说解决掉了字符串t中的一个字符
            while ( cnt>=t.size() && left<=right ){  // 开始更新左边界
                if ( minlen >= right-left+1 ){       //更新最小区间
                    minlen = right-left+1;
                    pos = left;
                }
                if ( ++need[s[left]]>0 )  //缩小window，左边字符弹出的时候，对应的该字符的需求数+1  ，同理，如果是t中的字符的话，要更新cnt
                    --cnt;
                ++left;
            }
            ++right;
        }
        //过滤非法情况 ，也就是说从未更新过minlen，则返回“”
        return minlen==INT_MAX?"":s.substr(pos, minlen);
    }
};