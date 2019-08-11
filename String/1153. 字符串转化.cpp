/*
    问题描述:
        给出两个长度相同的字符串，分别是 str1 和 str2。请你帮忙判断字符串 str1 能不能在 零次 或 多次 转化后变成字符串 str2。
        每一次转化时，将会一次性将 str1 中出现的 所有 相同字母变成其他 任何 小写英文字母（见示例）。
        只有在字符串 str1 能够通过上述方式顺利转化为字符串 str2 时才能返回 True，否则返回 False。​​

        
        示例 1：
        输入：str1 = "aabcc", str2 = "ccdee"
        输出：true
        解释：将 'c' 变成 'e'，然后把 'b' 变成 'd'，接着再把 'a' 变成 'c'。注意，转化的顺序也很重要。
        
        示例 2：
        输入：str1 = "leetcode", str2 = "codeleet"
        输出：false
        解释：我们没有办法能够把 str1 转化为 str2。
        
        提示：
        1 <= str1.length == str2.length <= 10^4
        str1 和 str2 中都只会出现 小写英文字母
    
    问题分析:
        一开始想错了。。
        看两个字符串是否模式相同 ( 是否形如AABBCC之类的 )
        与 Str1可以通过字符映射变为Str2 是两个不同的问题。。
        模式相同可以映射过去， 但可以映射过去不一定模式相同，
        例如 aabc 可以映射到ccdd , a->c, b->d, c->d
        
        本题的解决方法就是建一个 str1到str2的字符映射， 一旦出现二义性直接返回false，
        然后，如果str2的出现字符有26种（a-z），且 str1!=str2，
        那么这种情况，要么会出现二义性， 要么就是一个大环，是无法转换的情况，故排除。
        其他情况都是true
 */

class Solution {
public:
    bool canConvert(string str1, string str2) {
        if ( str1==str2 ) return true;  //相同直接返回
        unordered_map<char, char> mp;
        set<char> sts;
        string s;
        for ( int i=0; i<str1.size(); ++i ){
            if ( mp.count(str1[i])>0 ){
                if ( mp[str1[i]] != str2[i] ) 
                    // 出现二义性
                    return false;
            }else{
                mp[str1[i]] = str2[i];
            }
            sts.insert(str2[i]);
        }
        // 前面已经保证了str1!=str2
        if ( sts.size()==26 )
            return false;
        return true;
    }
};