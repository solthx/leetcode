/*
    问题描述：
        回忆一下祖玛游戏。现在桌上有一串球，颜色有红色(R)，黄色(Y)，蓝色(B)，绿色(G)，还有白色(W)。 现在你手里也有几个球。
        每一次，你可以从手里的球选一个，然后把这个球插入到一串球中的某个位置上（包括最左端，最右端）。接着，如果有出现三个或者三个以上颜色相同的球相连的话，就把它们移除掉。重复这一步骤直到桌上所有的球都被移除。
        找到插入并可以移除掉桌上所有球所需的最少的球数。如果不能移除桌上所有的球，输出 -1 。

        示例:
        输入: "WRRBBW", "RB" 
        输出: -1 
        解释: WRRBBW -> WRR[R]BBW -> WBBW -> WBB[B]W -> WW （翻译者标注：手上球已经用完，桌上还剩两个球无法消除，返回-1）

        输入: "WWRRBBWW", "WRBRW" 
        输出: 2 
        解释: WWRRBBWW -> WWRR[R]BBWW -> WWBBWW -> WWBB[B]WW -> WWWW -> empty

        输入:"G", "GGGGG" 
        输出: 2 
        解释: G -> G[G] -> GG[G] -> empty 

        输入: "RBYYBBRRB", "YRBGB" 
        输出: 3 
        解释: RBYYBBRRB -> RBYY[Y]BBRRB -> RBBBRRB -> RRRB -> B -> B[B] -> BB[B] -> empty 
        标注:

        你可以假设桌上一开始的球中，不会有三个及三个以上颜色相同且连着的球。
        桌上的球不会超过20个，输入的数据中代表这些球的字符串的名字是 "board" 。
        你手中的球不会超过5个，输入的数据中代表这些球的字符串的名字是 "hand"。
        输入的两个字符串均为非空字符串，且只包含字符 'R','Y','B','G','W'。


    问题分析：
        这题的数据量很小，可以直接dfs暴力！！！！

        map来记录字符个数，
        然后看当前字符缺不缺，缺的话够不够。。每一次都对每一个情况试一遍。。 复杂度应该高上天了。。但数据量比较小。。所以没关系= =..
*/

class Solution {
public:
    unordered_map<char, int> mp;
    int findMinStep(string board, string hand) {
        for ( auto c:hand )
            mp[c]++;
        int res = INT_MAX, cur = 0;
        helper( res, board, cur );
        return res == INT_MAX?-1:res;
    }
    
    void helper( int &res, string s, int cnt ){
        removeDup( s );// 删除连续三个出现字符
        int r,l=0;
        if ( s.size()==0 ){
            res = min(res, cnt);
            return ;
        }
        while( l<s.size() ){
            r = l+1;
            while( r<s.size() && s[r]==s[l] )
                ++r;
            int need = 3 - (r-l);
            if ( mp[s[l]]>=need ){
                mp[s[l]] -= need;
                helper( res, s.substr(0,l) + s.substr(r), cnt+need );
                mp[s[l]] += need;
            }
            l = r;
        }
    }
    
    void removeDup( string & s ){
        int r=0, l=0;
        while( l<s.size() ){
            r = l+1;
            while( r<s.size() && s[r]==s[l] ) ++r;
            if ( r-l>=3 ){
                s = s.substr(0, l) + s.substr(r);
                removeDup(s);
                return ; 
            }
            l = r;
        }
    }
};