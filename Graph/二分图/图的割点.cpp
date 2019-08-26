/*
    问题描述：
        给一个图， 如果把第i个节点删除后，图会变成两个图，那么称该点为“关键点”
        输出有多少个这样的“关键点”， 并输出这些关键点的序号（从1开始记）。

        输入格式:
           第一行:     n(节点个数) m(边的个数) 
           之后m行:    u v  (表示u和v之间有边)

        输出格式:
          第一行: 关键点的个数k
          第二行: k个点的序号
      
    问题分析:
        该问题属于“图的割点”的问题.
        解决方法就是：
          1. 选取一个root ，然后以该root为起点做dfs，在dfs的过程中，按照访问顺序为每一个节点建立“时间戳”
            例如:  2
                 /  \
                1    3  选取3作为root， dfs访问顺序为 3->2->1 
                                        时间戳对应为 1，2，3 ， 
                  设时间戳数组为nums,nums[i]为节点i的时间戳,  就得到nums[3]=1, nums[2]=2, nums[1]=1
            建立这样的“时间戳”的目的是，让图有一种层序关系， 
            1.1 祖先节点:
              我们假设:  “时间戳小的节点”是“时间戳大的节点”的祖先节点 ( 时间戳越小，访问的越早 )
            1.2 父节点:
              我们假设： 如果第i个节点的时间戳为t，第j个节点的时间戳为t+1, 那么第i个节点就是第j个节点 父节点


          2. 在dfs的过程中，不断更新lows数组。
             lows[i]表示第i个节点能够抵达的最小时间戳的节点, 
             且这个节点不能是父节点. ps: 其实是父节点也可以.. 这个无所谓的, 但不是父节点能更快一点
             且这个节点要和自己相邻
             并且这个节点可以是自己

          3. 具体的dfs伪代码:
              // cur为当前节点， father为父节点
              dfs( cur, father ) :
                  // 第一步: 更新时间戳
                  nums[cur] = index
                  lows[cur] = index
                  index += 1 
                  
                  times = 0    // 用于记录cur节点发起的dfs次数
                  
                  // 第二步: 扫描邻接点
                  for cur 的每一个邻接点 v:
                    if v是cur的孩子节点 : // 若nums[v]==0，说明v在cur后面访问，是cur的孩子节点
                        dfs( v, cur )
                        times+=1      //发起次数+1
        
                        lows[cur] = min( lows[cur], lows[v] )  //因为v和cur相邻， 所以v能抵达的,cur也能， 因为在v做完dfs之后，也更新一下cur的lows，取最小
                        
                        // 如果 lows[v]>=nums[cur]，就说明，v所能够抵达的最远的距离，也不过是到cur, 不会到cur之前访问过的值
                        // 所以，如果cur没了, v就无法访问 在访问cur之前访问的那些节点
                        // 因此，如果 lows[v]>=nums[cur]，则可以判定cur为 “关键点”
                        // 但因为nums[root]一定是自己，所以root的情况要单独讨论
                        if ( root!=cur && lows[v] >= nums[cur] )  
                            flag[cur] = 1  // 打标记
                        
                        // 单独判断root的情况，只要确定能够从root发起几次dfs就行了
                        // 如果发起次数超过一次，说明把root摘掉，一定能分成两个图
                        // 这里的child就来记录发起dfs的次数
                        if ( root==cur && times == 2 )
                            flag[cur] = 1
                    else 
                        // 说明v是祖先节点
                        // 更新cur所能够访问的最小时间戳的祖先节点
                        lows[cur] = min( lows[cur], nums[v] )
          4. dfs( root,root ) 为开始,
             当遇到图不连通的时候，要对每一个连通分量使用一次dfs
              for i from 1 to n:
                  if nums[i]==0 :
                    root = i;
                    dfs(i,root);
      
      下面是具体的代码实现，使用邻接表的实现.
      模版题: https://www.luogu.org/record/23332876
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
  int u,v,w; //u和w没用， v为被指向的节点
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
  edge[e_cnt].v = v; 
  edge[e_cnt].w = w;
  edge[e_cnt].next = head[u];
  head[u] = e_cnt++;
}

void dfs( int cur, int father ){
  int child_cnt = 0;
  indx++;
  nums[cur] = indx;
  lows[cur] = indx;
  int e_idx = head[cur];
  int nxtv;
  for ( int i=head[cur]; i>0; i = edge[i].next ){
    nxtv = edge[i].v;
    if ( nums[nxtv] == 0 ){
      // 孩子
      ++child_cnt;
      dfs( nxtv, cur );
      lows[cur] = min( lows[cur], lows[nxtv] );
      if ( (cur!=root && nums[cur]<=lows[nxtv]) || (cur==root && child_cnt==2 ) )
        flag[cur] = 1;
    }else if ( nxtv!=father ){
      // 非父节点的 祖先节点
      lows[cur] = min( lows[cur], nums[nxtv] );
    }
  }
}

//  debug
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

  vector<int> res;
  for ( int i=1; i<=n; ++i ){
    if ( flag[i] )
      res.push_back( i );
  }

  cout<<res.size()<<endl;
  for ( int i=0; i<res.size(); ++i )
    cout<<res[i]<<" ";
  return 0;
}


/*
  邻接矩阵实现:
    啊哈算法p232 日后再补上
*/