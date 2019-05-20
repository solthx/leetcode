/*
	问题描述：
		给定两个字符串 s 和 t，判断它们是否是同构的。
		如果 s 中的字符可以被替换得到 t ，那么这两个字符串是同构的。
		所有出现的字符都必须用另一个字符替换，同时保留字符的顺序。两个字符不能映射到同一个字符上，但字符可以映射自己本身。

		示例 1:
		输入: s = "egg", t = "add"
		输出: true

	问题分析：
		方法一：
			以字符作为Key，然后这个字符在字符串中出现的序列位置是value
			若是同构，则出现的序列必定是相同的。。 
			然后按这个思路实现就行了。。
			这个方法不推荐， 实现起来相对比较烦( 因为还有更简单的办法。。就是方法二 )
			
		方法二：
			key是字符
			value是该字符在上一次出现的位置
			
			每次遇到s中的字符c1和t中的字符c2，
			就看c1和c2在上一次出现的位置是不是在同一个位置，
			若不是则肯定不是同构，
			若是，则进行更新，把位置更新成当前位置，
			这里要注意的是，
			给table初始化的时候，要记得初始成和位置不相干的一个值
			（下面的代码是初始成0，但位置从1开始计）
*/

class Solution1 {
public:
	//不推荐
    bool isIsomorphic(string s, string t) {
        int sz=128;
        int find_the_same=0,k;
        vector<vector<int>> st(sz);
        vector<vector<int>> tt(sz);
        for ( int i=0; i<s.size(); ++i )
            st[s[i]].push_back(i);
        for ( int i=0; i<t.size(); ++i )
            tt[t[i]].push_back(i);
        for ( int i=0; i<sz; ++i ){
            //当前字母存在一个序列
            if ( st[i].size()>0 ){
                find_the_same=0;
                //去tt中找是否存在相同序列
                for ( int j=0; j<sz; ++j ){
                    // 遍历tt每一个序列
                    if ( tt[j].size()>0 && tt[j][0]==st[i][0] ){
                        if ( tt[j].size()!=st[i].size() ) return false;
                        k=0;
                        while( k<tt[j].size() && tt[j][k]==st[i][k] )
                            k++;
                        if ( k==tt[j].size() )
                            find_the_same = 1;
                    }
                }
                if ( find_the_same==0 )
                    return false;
            }
        }
        return true;
    }
};


class Solution2 {
public:
    bool isIsomorphic(string s, string t) {
        int st[256]={0},tt[256]={0};
        for ( int i=0; i<s.size(); ++i ){
            if ( st[s[i]]!=tt[t[i]] )
                return false;
			//之所以是i+1而不是i，是因为
            st[s[i]] = i+1;
            tt[t[i]] = i+1;
        }
        return true;
    }
};