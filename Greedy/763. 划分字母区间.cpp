/*
    问题描述：
        字符串 S 由小写字母组成。我们要把这个字符串划分为尽可能多的片段，同一个字母只会出现在其中的一个片段。返回一个表示每个字符串片段的长度的列表。
        示例 1:

        输入: S = "ababcbacadefegdehijhklij"
        输出: [9,7,8]
        解释:
        划分结果为 "ababcbaca", "defegde", "hijhklij"。
        每个字母最多出现在一个片段中。
        像 "ababcbacadefegde", "hijhklij" 的划分是错误的，因为划分的片段数较少。
        注意:

        S的长度在[1, 500]之间。
        S只包含小写字母'a'到'z'。

    问题分析:
        方法一: 扫描线
            1. 先得到字母c出现的最左的位置和最右的位置。
            2.  cur = 0
                for i from 0 to s.size():
                    如果s[i]出现的最左位置==i:
                        if cur==0 :
                            l = i // 记录进入开始位置
                        ++cur 
                    如果s[i]出现的最右位置==i:
                        --cur
                        if cur==0:
                            res.push_back( i-l+1 )
        
        方法二: 贪心
            mp[c]保存该字符c出现的最右位置，
            r 当前的字符集中，最靠近右边的位置
            l 当前的字符集中，最靠近左边的位置
            for i from 0 to s.size():
                r = max( r, i )
                if r==i :    // 如果当前位置i就是当前出现的所有字符里最靠右的位置，
                    res.add( r-l+1 )
                    l = r+1            
*/


// C++实现方法一
class Solution1 {
public:
    vector<int> partitionLabels(string S) {
        vector<pair<int,int>> mp(26, {INT_MAX,INT_MIN});
        for ( int i=0; i<S.size(); ++i ){
            int d = S[i]-'a';
            mp[d].first = min( mp[d].first, i );
            mp[d].second = max( mp[d].second, i );
        }
        int n = S.size();
        int cur = 0;
        vector<int> res;
        int l,r;
        for ( int i=0; i<S.size(); ++i ){
            /*if ( mp[S[i]-'a'].first == mp[S[i]-'a'].second && mp[S[i]-'a'].second!=INT_MIN ){
                cout<<S[i]<<" "<<i<<endl;
                res.push_back(1);
                continue;
            }*/
            if ( i==mp[S[i]-'a'].first ){
                // 进入左区间
                if (cur++ == 0) 
                    l = i;
            }
            if ( i==mp[S[i]-'a'].second ){
                if ( --cur==0 )
                    res.push_back( i - l + 1 );
            }
        }
        return res;
    }
};


// Java实现方法2
class Solution2 {
    public List<Integer> partitionLabels(String S) {
        List<Integer> res = new ArrayList<>();
        int [] mp = new int[26];
        for( int i=0; i<S.length(); ++i )
            mp[S.charAt(i)-'a']=i;    
        int l=0,r=0;
        for ( int i=0; i<S.length(); ++i ){
            r = Integer.max( r, mp[S.charAt(i)-'a'] );
            if ( i==r ){
                res.add( r-l+1 );
                l = r+1;
            }
        }
        
        return res;
    }
}