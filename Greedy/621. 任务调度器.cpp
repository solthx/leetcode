/*
    问题描述:
        给定一个用字符数组表示的 CPU 需要执行的任务列表。其中包含使用大写的 A - Z 字母表示的26 种不同种类的任务。任务可以以任意顺序执行，并且每个任务都可以在 1 个单位时间内执行完。CPU 在任何一个单位时间内都可以执行一个任务，或者在待命状态。
        然而，两个相同种类的任务之间必须有长度为 n 的冷却时间，因此至少有连续 n 个单位时间内 CPU 在执行不同的任务，或者在待命状态。
        你需要计算完成所有任务所需要的最短时间。

    示例 1：
        输入: tasks = ["A","A","A","B","B","B"], n = 2
        输出: 8
        执行顺序: A -> B -> (待命) -> A -> B -> (待命) -> A -> B.

    注
        任务的总个数为 [1, 10000]。
        n 的取值范围为 [0, 100]。

    问题分析:
        方法一:
            可以用 堆+滑动窗口 来做，用hashmap记录每个字符的出现次数，
            然后在长度为n+1的窗口里，不停的取出出现次数最多的，当前可以用的字符，
            复杂度为O(NlogN) ， 但实际操作的时候，并不需要返回序列的样子，所以
            pop的过程就是模拟的过程， 下一个方法就是根据规律直接计算了。
        
        方法二:
            先计算字符最多的出现次数maxi， 再计算有多少个字符出现了maxi次，即maxi_cnt,
            因为中间要等待n秒，
            所以，如果一个字符出现了maxi次， 那么至少 (maxi-1)*(n+1) 是需要等待的。
            如果这样的话，在最后一个区间里，就只剩下 出现次数为maxi的字符们了，所以再加上maxi_cnt;
            故，结果就是 （maxi-1)*(n+1) + maxi_cnt;

            但还有个特殊情况，就是区间内可以使用的字符数大于区间长度，
            所以返回的结果是 max( tasks.size(), maxi-1)*(n+1) + maxi_cnt ) 
*/

class Solution1 {
public:
    int leastInterval(vector<char>& tasks, int n) {
        // 用堆+hashmap+滑动窗口 来模拟
        auto cmp = []( pair<int,int>& a, pair<int,int>& b ){
            if (a.second!=b.second) 
                return a.second<b.second;  
            return a.first<b.first;
        };
        unordered_map<int, int> mp;
        for ( auto e:tasks )
            mp[e-'a'] += 1;
        priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(cmp)> q(cmp);
        for ( auto e:mp )
            q.push(e);
        int res=0,i;
        while( !q.empty() ){
            vector<pair<int,int>> tmp;
            for ( i=0; i<=n && !q.empty(); ++i ){
                pair<int,int> cur = q.top();
                res+=1;
                q.pop();
                if ( --cur.second>0 )
                    tmp.push_back(cur);
            }
            if ( i<=n && tmp.size()>0 ) res+=(n-i+1);
            for ( auto & e:tmp ) 
                q.push(e);
        }
        return res;
    }
};

class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        int res=0;
        int maxi = 0;
        int maxi_cnt=0;
        int cnt[26]={0};
        for ( auto e:tasks )
            ++cnt[e-'A'];
        for ( int i=0; i<26; ++i )
            if ( maxi<cnt[i] ){
                maxi = cnt[i];
                maxi_cnt = 1;
            }else if ( maxi==cnt[i] ) ++maxi_cnt;
        res = (n+1)*(maxi-1)+maxi_cnt;
        return max( (int)tasks.size(), (maxi-1)*(n+1) + maxi_cnt ) ;
    }
};