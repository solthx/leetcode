/*
  问题描述:
    和 “图的割点类似”

    给一个图， 如果把第i个边删除后，图会变成两个图，那么称该点为“关键边”
    输出所有的关键边，'i-j'的形式输出

    输入格式:
        第一行:     n(节点个数) m(边的个数) 
        之后m行:    u v  (表示u和v之间有边)

  问题分析:
    和图的割点处理方法如出一辙，
    甚至都不用单独讨论root了
    因为lows[i]表示节点i所能访问的最小时间戳节点， 也就是按访问顺序来看，距离自己最远的祖先节点，
    且这个节点不能是节点i的父节点.

    所以只要把 lows[v] >= nums[cur] 改成 lows[v] > nums[cur] 就说明，除了 <cur,v>这条边，
     v能访问的最远节点也到不了cur， 如果把<cur,v>砍了，v就访问不到cur， 就会出现两个图了。
    因此 只要改成 lows[v] > nums[cur] 然后删掉对root的讨论，割点的代码就变成割边的代码了

    下面的代码是邻接表的实现

*/
#include <cstdio>
#include <cstring>
#include <cctype>
#include <stdlib.h>
#include <string>
#include <map>
#include <iostream>
#include <stack>
#include <cmath>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
#define inf 1000000
#define mem(a,b) memset(a,b,sizeof(a))
const int N=100000+7;
const int M=2*100000+20;
using namespace std;

typedef struct{
  int u,v,w;
  int next; // 指向下一个边号
}Edge;

int head[N];
Edge edge[M];
int e_cnt=0;
int indx=0;
int n,m;

int root;

int nums[N]={0};
int lows[N]={0};
int flag[N]={0};

void add_edge( int u , int v, int w ){
  edge[e_cnt].u = u;
  edge[e_cnt].v = v; //v是儿子
  edge[e_cnt].w = w;
  edge[e_cnt].next = head[u];
  head[u] = e_cnt++;
}

void dfs( int cur, int father ){
  indx++;
  nums[cur] = indx;
  lows[cur] = indx;
  int child_cnt=0;
  int nxtv;
  for ( int i=head[cur]; i>=0; i = edge[i].next ){
    nxtv = edge[i].v;
    if ( nums[nxtv] == 0 ){
      // 孩子
      dfs( nxtv, cur );
      lows[cur] = min( lows[cur], lows[nxtv] );
      if (  lows[nxtv]>nums[cur]  ) {
          cout<<cur<<"-"<<nxtv<<endl;
      }
      
    }else if( nxtv!=father ) {
      // 非父节点的 祖先节点
      lows[cur] = min( lows[cur], nums[nxtv] );
    }
  }
}


int main(void){
  int u,v,w;
  scanf("%d%d",&n,&m); // 定点数和边数
  for ( int i=0; i<=n; ++i ) head[i]=-1;
  for ( int i=1; i<=m; ++i ){
      scanf("%d%d",&u,&v);
      add_edge(u,v,1);
      add_edge(v,u,1);   
  }
  indx=0;
  for ( int i=1; i<=n; ++i ){
      if ( nums[i]==0 ){
        root = i;
        dfs(i,root);
      }
  }
  return 0;
}

// // debug
// void print(){
//   for ( int i=1; i<=n; ++i ){
//      cout<<nums[i]<<" ";
//   }
//   cout<<endl;
//   for ( int i=1; i<=n; ++i ){
//      cout<<lows[i]<<" ";
//   }
//   cout<<endl;
// }

/*
  邻接矩阵的日后在补
*/