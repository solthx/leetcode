/*
    一、 最短单词距离I:
        问题描述:
            给定一个单词列表和两个单词 word1 和 word2，返回列表中这两个单词之间的最短距离。

            示例:
            假设 words = ["practice", "makes", "perfect", "coding", "makes"]

            输入: word1 = “coding”, word2 = “practice”
            输出: 3
            输入: word1 = "makes", word2 = "coding"
            输出: 1
        
        问题分析:
            方法一: 暴力O(N^2) 
                vector<int> a和b 分别保存word1和word2出现的位置, 然后N^2来取min( abs(a[i]-b[j] ))   

            方法二: 双指针，两次遍历O(N)
                因为在把位置装入a和b的时候是有序的，所以可以用双指针来做， 
                 while( i<a.size() && j<b.size() ){
                    res = min( res, abs(a[i]-b[j]) );
                    if ( a[i]<b[j] ) ++i;
                    else ++j;
                }
            
            方法三: 一次遍历法 O(N)
                最近的word1和word2的位置一定是相邻或相同的，
                所以p1保存到当前位置word1的位置，
                    p2保存到当前位置word2的位置
                然后在每个位置上取 res = min(res, abs(p1-p2));

        二、 最短单词距离II 的解决思路就是用hashmap来保存映射就行了.( unordered_map<string, vector<int>> mp; )
        三、 最短单词距离III 的解决思路就是排除重复位置，
            对于方法一和方法二，加个a[i]!=b[j]就行了
            对于方法三, 对word1==word2时，加一个特殊判断就行了，就是p1和p2不会指向同一个位置的判断
                for ( int i=0; i<words.size(); ++i ){
                    if ( words[i]==word1 ) p1 = (word1!=word2)?i:p2;
                    if ( words[i]==word2 ) p2 = i;
                    res = min( res, abs(p1-p2) );
                }
*/

class Solution1 {
public:
    // 暴力
    int shortestDistance(vector<string>& words, string word1, string word2) {
        int n = words.size();
        unordered_map<string, vector<int>> mp;
        for ( int i=0; i<words.size(); ++i ){
            mp[words[i]].push_back(i);
        }
        int res=INT_MAX;
        for ( auto a : mp[word1] )
            for ( auto b : mp[word2] )
                res = min( abs(a-b),res );
        return res;
    }
};

class Solution2 {
public:
    //双指针
    int shortestDistance(vector<string>& words, string word1, string word2) {
        int n = words.size();
        unordered_map<string, vector<int>> mp;
        for ( int i=0; i<words.size(); ++i )
            mp[words[i]].push_back(i);
        vector<int> a = mp[word1], b = mp[word2];
        int i=0,j=0, res=INT_MAX, m1=a.size(), m2=b.size();
        while( i<m1 && j<m2 ){
            res = min( res, abs(a[i]-b[j]) );
            if ( a[i]<b[j] ) ++i;
            else ++j;
        }
        return res;
    }
};

class Solution3 {
public:
    // 一次遍历法
    int shortestDistance(vector<string>& words, string word1, string word2) {
        int p1=-words.size(), p2=words.size(), res=INT_MAX;
        for ( int i=0; i<words.size(); ++i ){
            if ( words[i]==word1 ) p1 =i;
            if ( words[i]==word2 ) p2 = i;
            res = min( res, abs(p1-p2) );
        }
        return res;
    }
};