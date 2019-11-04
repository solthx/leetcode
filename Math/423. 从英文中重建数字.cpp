/*
    问题描述:
        给定一个非空字符串，其中包含字母顺序打乱的英文单词表示的数字0-9。按升序输出原始的数字。
        注意:

        输入只包含小写英文字母。
        输入保证合法并可以转换为原始的数字，这意味着像 "abc" 或 "zerone" 的输入是不允许的。
        输入字符串的长度小于 50,000。
        示例 1:

        输入: "owoztneoer"

        输出: "012" (zeroonetwo)
        示例 2:

        输入: "fviefuro"

        输出: "45" (fourfive)

    问题分析：
        容斥原理。

        有五个数字有着唯一标示的字符:
            zero : z
            two  : w
            four : u
            six  : x
            eight: g 
        因此，可以确定上面五个数字的出现次数，
        然后以 seven为例子，只有six和seven出现了s字符，
        因此s字符的出现次数减去six的出现次数，就是seven的出现次数(容斥原理)
        其他几个数字同理。

        计算出每个数字出现次数，剩下的就好办了。
*/
class Solution {
public:
    string originalDigits(string s) {
        // 容斥原理
        int tb[200]={0};
        int count[200]={0};
        for ( auto c:s )
            tb[c]++;
        string res="";
        count['2'] = tb['w'];
        count['8'] = tb['g'];
        count['6'] = tb['x'];
        count['4'] = tb['u'];
        count['0'] = tb['z'];
        count['7'] = tb['s']-count['6'];
        count['1'] = tb['o'] - count['2']-count['0']-count['4'];
        count['3'] = tb['r'] - count['4']-count['0'];
        count['5'] = tb['f']-count['4']; 
        count['9'] = tb['i'] - count['5'] - count['6']-count['8'];
        for ( char c = '0'; c<='9'; ++c ){
            res += helper( c, count[c] );
        }
        return res;
    }
    string helper( char c, int cnt ){
        string res="";
        while(cnt--) res+=c;
        return res;
    }
};