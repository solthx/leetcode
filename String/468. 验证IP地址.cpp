/*
    问题描述:
        编写一个函数来验证输入的字符串是否是有效的 IPv4 或 IPv6 地址。
        IPv4 地址由十进制数和点来表示，每个地址包含4个十进制数，其范围为 0 - 255， 用(".")分割。比如，172.16.254.1；
        同时，IPv4 地址内的数不会以 0 开头。比如，地址 172.16.254.01 是不合法的。
        IPv6 地址由8组16进制的数字来表示，每组表示 16 比特。这些组数字通过 (":")分割。比如,  2001:0db8:85a3:0000:0000:8a2e:0370:7334 是一个有效的地址。而且，我们可以加入一些以 0 开头的数字，字母可以使用大写，也可以是小写。所以， 2001:db8:85a3:0:0:8A2E:0370:7334 也是一个有效的 IPv6 address地址 (即，忽略 0 开头，忽略大小写)。
        然而，我们不能因为某个组的值为 0，而使用一个空的组，以至于出现 (::) 的情况。 比如， 2001:0db8:85a3::8A2E:0370:7334 是无效的 IPv6 地址。
        同时，在 IPv6 地址中，多余的 0 也是不被允许的。比如， 02001:0db8:85a3:0000:0000:8a2e:0370:7334 是无效的。
        说明: 你可以认为给定的字符串里没有空格或者其他特殊字符。

        示例 1:

        输入: "172.16.254.1"

        输出: "IPv4"

        解释: 这是一个有效的 IPv4 地址, 所以返回 "IPv4"。
        示例 2:

        输入: "2001:0db8:85a3:0:0:8A2E:0370:7334"

        输出: "IPv6"

        解释: 这是一个有效的 IPv6 地址, 所以返回 "IPv6"。
        示例 3:

        输入: "256.256.256.256"

        输出: "Neither"

        解释: 这个地址既不是 IPv4 也不是 IPv6 地址。

    问题分析：
        先列情况，再写代码，
        这种字符串的题，不想清楚直接写 = GG
        ipv4:
            1. 四个字段
            2. 每个字段不能以0开头， 但可以是0
            3. 取值范围为[0,255]
            
        ipv6:
            1. 每组4个16进制数
            2. 8组
            3. : 分开
            4. 可以以0开头，但不可以有多余的0 例如:0000
        
        除了要满足上面的，也要考虑 xxx.xxx.xx.xx. 这样的情况

        （这题考的感觉不是coding能力  而是 测试能力（边界考虑的全不全

        另外 学到了一个c++版本的 split模版，

        注释部分是自己写的。。 

        后来用优雅的split来替代了
*/

class Solution {
public:
    vector<string> split( string ip, char c ){
        if ( ip.back()==c ) return {"z"};
        istringstream  iss(ip);
        vector<string> res;
        string tmp;
        while( getline(iss, tmp, c) ){
            res.push_back(tmp);
        }
        return res;
    }
    
    bool isIpv4( string ip ){
        if ( ip.size()>15 ) return false;
        int cnt=0;
        // for ( auto&c:ip){
        //     if ( c=='.' ){
        //         c=' '; 
        //         if ( ++cnt>3 ) return false;
        //     }
        // }
        // stringstream input(ip);
        // vector<string> sv(4);
        // input>>sv[0]>>sv[1]>>sv[2]>>sv[3];
        vector<string> sv = split(ip,'.');
        if ( sv.size()!=4 ) return false; 
        for ( auto s:sv ){
            if ( s.size()>3 || s.size()==0 ) return false;
            for ( auto c:s ) if ( c>'9'||c<'0' ) return false;
            int d = stoi(s);
            if ( s[0]=='0' && ( s.size()>1 )) return false;
            if ( d>255 ) return false;
        }
        return true;
    }
    
    bool isIpv6(string ip){
        if ( ip.size()>=40 ) return false;
        int cnt=0;
        // for ( auto&c:ip){
        //     if ( c==':' ){
        //         c=' '; 
        //         if ( ++cnt>7 ) return false;
        //     }
        // }
        // stringstream input(ip);
        // vector<string> sv(8);
        // input>>sv[0]>>sv[1]>>sv[2]>>sv[3]>>sv[4]>>sv[5]>>sv[6]>>sv[7];
        vector<string> sv = split(ip,':');
        if ( sv.size()!=8 ) return false;
        for ( auto s:sv ){
            if ( s.size()>=5 || s.size()==0 ) return false;
            for ( auto c:s ) 
                if ( c<'0' || c>'9' && c<'A' || c>'F' && c<'a' || c>'f' ) return false;
            
        }
        return true;
    }
    
    string validIPAddress(string IP) {
        /* ipv4:
              1. 四个字段
              2. 每个字段不能以0开头， 但可以是0
              3. 取值范围为[0,255]
             
            ipv6:
                1. 每组4个16进制数
                2. 8组
                3. : 分开
                4. 可以以0开头，但不可以有多余的0 例如:0000
        */
        // 看是否是Ipv4
        if ( isIpv4(IP) )
            return "IPv4";
        // 看是否是Ipv6
        else if ( isIpv6(IP) )
            return "IPv6";
        return "Neither"; // 都不是
    }
};