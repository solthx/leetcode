/*
    题目描述：
        给定一个字符串 s，你可以通过在字符串前面添加字符将其转换为回文串。找到并返回可以用这种方式转换的最短回文串。
        示例 1:

        输入: "aacecaaa"
        输出: "aaacecaaa"
        示例 2:

        输入: "abcd"
        输出: "dcbabcd"

    题目分析：
        感觉有点像贪心。
        问题的本质是找到回文的中心，
        因为只能在字符串左边加前缀，
        所以中心点要么在0位置，要么在0～n的中的一个，
        0位置一定是回文的边缘。
        所以就寻找以位置0为边缘的回文串，
        0~r是回文串，那么前缀就是reverse(s.substr(r,n-r))
 */

class Solution {
public:
    string shortestPalindrome(string s) {
        if ( s.size()<=1 ) return s;
        int l=0, r=s.size()-1;
        int i,j,pos=-1;
        while( r>0 ){
            while( r>0 && s[r]!=s[0] )
                --r;
            i=0;j=r;
            while( i<j && s[i]==s[j] ){
                i++;j--;
            }
            if ( i>=j ){
                pos = r+1;
                break;
            }else r = min(j+1, r-1);
        }    
        // s[pos~n]的倒置是前缀
        return reversed(s.substr(pos,(int)s.size()-pos)) + s;
        
    }
    string reversed(string s){
        int i=0, j=s.size()-1;
        while( i<j ) swap(s[i++],s[j--]);
        return s;
    }
};