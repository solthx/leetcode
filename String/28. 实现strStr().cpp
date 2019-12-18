/*
	问题描述：
		实现字符串匹配算法，就是KMp吧
		
	问题分析：
		跳转到https://github.com/solthx/Old-code/blob/master/SA_code/string/kmp.cpp
		
		注意：
			每次生成next数组的时候，是每次更新下一个元素 next[++i] = ++j;
*/


// 二刷，补充C++版
class Solution {
public:
    int strStr(string haystack, string needle) {
        if ( needle.size()==0 )
            return 0;
        if ( haystack.size()==0  ) return -1;
        vector<int> next = get_next( needle );
        int i=0, j=0;
        while( i<haystack.size() ){
            if ( j<0 || haystack[i]==needle[j] ){
                ++i;
                ++j;
            }else j = next[j];
            if ( j==needle.size() ) return i-j;
        }
        return -1;
    }

    vector<int> get_next( string pat ){
        int n=pat.size();
        vector<int> next(n+1,0);
        int i=0, j=-1;
        next[0] = -1;
        while( i<pat.size() ){
            if ( j<0 || pat[i]==pat[j] ){
                next[++i] = ++j;
            }else j=next[j];
        }
        return next;
    }
};

// C语言版
class Solution {
public:
    int strStr(string haystack, string needle) {
        int n=haystack.size(), m = needle.size();
        if ( !m && !n ) return 0;
        if ( !m ) return 0;
        if ( !n ) return -1;
        int * next = get_next(needle);
        int res = Strstr(next,haystack,needle);
        return res;
    }
    
    int * get_next(string needle){
        int n = needle.size();
        int * next = new int[n+1];
        int i=0,j=-1;
        next[0] = -1;
        while( i<n ){
            if ( j<0 || needle[i]==needle[j] )
                next[++i] = ++j;
            else j = next[j];
        }
        return next;
    }
    
    int Strstr(int next[], string text,string pat){
        int n = text.size(),m = pat.size();
        int i=0,j=0;
        while( i<n ){
            if ( j<0 || text[i]==pat[j] ){
                i++;
                j++;
            }else j = next[j];
            if ( j==m ) return i-j;  //说明匹配到了
        }
        return -1;
    }
};