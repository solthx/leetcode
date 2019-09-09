/*
    问题描述:
        给定两个整数，分别表示分数的分子 numerator 和分母 denominator，以字符串形式返回小数。
        如果小数部分为循环小数，则将循环的部分括在括号内。
        
        示例 1:
            输入: numerator = 1, denominator = 2
            输出: "0.5"
        
        示例 2:
            输入: numerator = 2, denominator = 1
            输出: "2"
        
        示例 3:
            输入: numerator = 2, denominator = 3
            输出: "0.(6)"

    问题分析:
        本题的需要考虑的点为以下几个:
            1. 什么情况下会出现循环
            2. 出现循环之后，如何找到循环的数
        
        本题容易错的地方:
            1. 数的表示，溢出问题. 
            2. 正负号的单独处理

        先说说考虑的点:
            1. 很容易可以知道，当 n/d == t了之后， 如果下次又遇到了n/d，
            那么可以判断，这个时候循环出现了！

            2. 在没遇到循环之前，我们是不知道会有循环的，因此，维护一个字符串last，
            时刻记录小数点后面的数. 并且用一个hashmap来保存"当前 string((n*10)/d) 在last中的出现位置"，
            当出现循环时，
            这个位置之后的所有数都是循环的，
            这个位置之前都不是循环的，
            因此有了位置之后可以用substr来得到循环的部分和非循环的部分.      
*/

class Solution {
public:
    string fractionToDecimal(long n, long d) {
        bool sg = (n*d>=0); // 符号单独处理
        n = abs(n); 
        d = abs(d);
        string res = to_string((n/d));
        if ( sg==false ) res = "-"+res;
        string last="";
        n = n%d;
        if ( !n ) return res;
        res += ".";
        int cur;
        vector<int> v;
        map<int,int> mp; // mp[n] = idx  
        vector<int> cnt(10);
        int mod,idx = 0;
        while( n ){
            n *= 10;
            if ( mp.count( n ) ){
                // 存在循环
                string loop = last.substr( mp[n] );
                return res + last.substr( 0, mp[n] ) + "("+loop+")";
            }
            idx = last.size(); // 记录位置
            last += to_string(n/d);
            mp[n] = idx;
            n = n%d;
        }
        return res + last;
    }
};