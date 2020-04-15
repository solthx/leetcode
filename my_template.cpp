# include <iostream>
# include <cstring>
# include <map>
# include <algorithm>
# include <vector>
# include <cmath>
# include <sstream>
# include <unordered_map>
# define ull unsigned long long 
# define BASE 37
# define ll long long
using namespace std;

//===============tri_tree==========================

struct tri_node{
    tri_node * children[26];
    bool isOver;
    tri_node(){
        for ( int i=0; i<26; ++i )
            children[i] = nullptr;
        isOver = false;
    }
};

void insert( tri_node * rt, string s ){
    if ( !rt ) return;
    int i=0;
    while( i<s.size() ){
        if ( !rt->children[s[i]-'a'] )
            rt->children[s[i]-'a'] = new tri_node();
        rt = rt->children[s[i]-'a'];
        ++i;
    }
    rt->isOver = true; // 这个位置是否是一个单词的结尾
}

//=========================================

//===============滚动hash==========================
// 滚动哈希板子
ull hs[10010]={0};
ull offset[10010]={0};

// 初始化，s是字符串
void init(string s){
    offset[0]=1;
    for(int i=1; i<=s.size(); ++i){
        hs[i] = hs[i-1]*BASE + (s[i-1]-'a');
        offset[i] = offset[i-1]*BASE;
    }
}    

// 获取区间[l,r]的哈希编码, 哈希编码相同则表示字符串相同
ull get_code(int l, int r){
    int len = r-l+1;
    return hs[r]-hs[l-1]*offset[len];
}
//================================================


//============BIT============
unordered_map<int,int> mp;
// map 可以替换成 vector或者 数组
int lowbit(int x){return x&-x;}

// 获取坐标[0,x]上元素的和
int search(int x){
    int res = 0;
    while( x>0 ){
        res += mp[x];
        x -= lowbit(x);
    }
    return res;
}

// 对mp[x] 加val
void add( long x, int val ){
    // INT_MAX可以换成idx的最大值
    while( x<=INT_MAX ){
        mp[x] += val;
        x += lowbit(x);
    }
}

// 获取sum{mp[a,b]}的和:
// search(a) - search(b-1);
//=================================

vector<string> split(string s,string seprate){
    vector<string> ret;
    int seprate_len=seprate.length();
    int start=0;
    int index;
    while((index = s.find(seprate,start))!=-1){
        ret.push_back(s.substr(start,index-start));
        start = index+seprate_len;
    }
    if(start<s.length())
        ret.push_back(s.substr(start,s.length()-start));
    return ret;
}


int n,m;

int main(void){
    return 0;
}