/*
    问题描述:
        给定正整数 N ，我们按任何顺序（包括原始顺序）将数字重新排序，注意其前导数字不能为零。
        如果我们可以通过上述方式得到 2 的幂，返回 true；否则，返回 false。
        示例 1：

        输入：1
        输出：true
        示例 2：

        输入：10
        输出：false
        示例 3：

        输入：16
        输出：true
        示例 4：

        输入：24
        输出：false
        示例 5：

        输入：46
        输出：true
        
        提示：

        1 <= N <= 10^9
    
    问题分析:
        方法一:
            递归遍历每一种组合，然后判断 复杂度( O(9!*9) )
            TLE

        方法二:
            仔细分析可以发现，小于1e9的 2的幂次数 个数也不多，
            
            这是个很好的思路， 就是在一个很大的范围里，发现
            目标的情况数其实很少， 就可以从这一点入手（之前遇到的一个bfs区域太大不能表示 也有点像这个思想

            因此，就先列出来1e9里，所有的2的幂次的数，
            
            把N变成string，设其为s

            然后把每一个2的幂次的数，也变成string,
            凡是和s的长度相同的，作为候选，放入vector里，这个vector设其为vs

            然后遍历vs里的每一个元素，和s进行匹配，
            如果出现的字符集一样，那么就可以组合成
*/

class Solution {
public:
    bool reorderedPowerOf2(int N) {
        long MAX=1e9;
        string s = to_string(N);
        long d = 1;
        vector<string> vs;
        while( d<MAX ){
            string tp = to_string(d);
            if ( tp.size()==s.size() ) vs.push_back( tp );
            else if ( tp.size()>s.size() ) break;
            d*=2;
        }
        for ( auto t:vs ){
            if ( OK(t, s) ) return true;
        }
        return false;
    }
    
    bool OK(string a, string b){
        int cnt1[26]={0}, cnt2[26]={0};
        for ( int i=0; i<a.size(); ++i ){
            cnt1[a[i]-'0']++;
            cnt2[b[i]-'0']++;
        }
        for ( int i=0; i<26; ++i )
            if ( cnt1[i]!=cnt2[i] ) return false;
        return true;
    }
};