/*
	题目描述：
		给定一个字符串 s1，我们可以把它递归地分割成两个非空子字符串，从而将其表示为二叉树。

		下图是字符串 s1 = "great" 的一种可能的表示形式。

			great
		   /    \
		  gr    eat
		 / \    /  \
		g   r  e   at
				   / \
				  a   t
		在扰乱这个字符串的过程中，我们可以挑选任何一个非叶节点，然后交换它的两个子节点。

		例如，如果我们挑选非叶节点 "gr" ，交换它的两个子节点，将会产生扰乱字符串 "rgeat" 。

			rgeat
		   /    \
		  rg    eat
		 / \    /  \
		r   g  e   at
				   / \
				  a   t
		我们将 "rgeat” 称作 "great" 的一个扰乱字符串。

		同样地，如果我们继续将其节点 "eat" 和 "at" 进行交换，将会产生另一个新的扰乱字符串 "rgtae" 。

			rgtae
		   /    \
		  rg    tae
		 / \    /  \
		r   g  ta  e
			   / \
			  t   a
		我们将 "rgtae” 称作 "great" 的一个扰乱字符串。

		给出两个长度相等的字符串 s1 和 s2，判断 s2 是否是 s1 的扰乱字符串。

		示例 1:

		输入: s1 = "great", s2 = "rgeat"
		输出: true
		示例 2:

		输入: s1 = "abcde", s2 = "caebd"
		输出: false

	题目解析：
		方法一：
			DFS+回溯剪枝
			可以发现，对于字符串s1、s2， 如果：
				s1的前i个字符和s2的前i个字符是扰乱字符串 且 s1的后n-i个字符和s2的后n-i个字符是扰乱字符串  	  
				或
				s1的前i个字符和s2的后i个字符是扰乱字符串 且 s1的后n-i个字符和s2的前n-i个字符是扰乱字符串
			那么，s1和s2就是扰乱字符串。
			isScramble(s1,s2)是判断两个字符串是否为扰乱字符串，
			剪枝情况：
				1. s1和s2长度不同，一定不是扰乱字符串。
				2. s1和s2若相等，则一定是扰乱字符串
				3. s1和s2的字符构成不同，一定不是扰乱字符串
				
		方法二的Dp有点难，二刷的时候再更吧。
				
*/

class Solution1 {
public:
    bool isScramble(string s1, string s2) {
        //剪枝情况一：长度是否相同
		if ( s1.size()!=s2.size() )
            return false;
		//剪枝情况二：字符串是否相等
        //这一步也是DFS的返回情况
		if ( s1==s2 ) return true;
        //剪枝情况三：字符串构成是否相同
		if ( !same_chars(s1,s2))
            return false; 
        int n = s1.size(); 
        for( int i=1; i<s2.size(); ++i ){
            if ( isScramble( s1.substr(0,i) , s2.substr(0,i) ) && isScramble( s1.substr(i) , s2.substr(i) )|| isScramble( s1.substr(0,i) , s2.substr(n-i) ) && isScramble( s1.substr(i) , s2.substr(0, n-i) ) )
                return true;
        }
        return false;
    }
    
    bool same_chars(string s1, string s2){
        int t1[26]= {0};
        int t2[26] = {0};
        for ( auto e:s1 )
            t1[e-'a']++;
        for ( auto e:s2 )
            t2[e-'a']++;
        for ( int i=0; i<26; ++i )
            if ( t1[i]!=t2[i] )
                return false;
        return true;
    }
};

