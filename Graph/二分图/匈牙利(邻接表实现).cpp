/*
    问题描述:
        RPG girls今天和大家一起去游乐场玩，终于可以坐上梦寐以求的过山车了。
        可是，过山车的每一排只有两个座位，而且还有条不成文的规矩，就是每个女生必须找个个男生做partner和她同坐。
        但是，每个女孩都有各自的想法，举个例子把，Rabbit只愿意和XHD或PQK做partner，
        Grass只愿意和linle或LL做partner，PrincessSnow愿意和水域浪子或伪酷儿做partner。
        考虑到经费问题，boss刘决定只让找到partner的人去坐过山车，其他的人，
        嘿嘿，就站在下面看着吧。聪明的Acmer，你可以帮忙算算最多有多少对组合可以坐上过山车吗？
 

        Input
            输入数据的第一行是三个整数K , M , N，分别表示可能的组合数目，女生的人数，男生的人数。0<K<=1000
            1<=N 和M<=500.接下来的K行，每行有两个数，分别表示女生Ai愿意和男生Bj做partner。最后一个0结束输入。
        Output
            对于每组数据，输出一个整数，表示可以坐上过山车的最多组合数。
    
    问题分析:
        二分图就是，所有顶点被分为两个集合A,B，
        集合内的顶点之间没有边相连，
        边的两端的顶点一个属于集合A, 一个属于集合B。 这样的图就是二分图。

        一条边<a,b> 就是一个匹配
        现在要求:
            一个点只能存于一条边中， 找出最大匹配数量, 也就是最多的这样的边的数量. 即二分图的最大匹配问题.
        
        解决最大匹配问题的算法就是匈牙利算法，
        它的实现步骤为：
            1. 首先从一个未匹配的点 u 开始, 从点u的边中，任意选择一条边( u->v ) 开始配对.
            如果此时v没有被配对，那么直接配对成功. 更新match数组
            如果此时v已经被配对了, 那就要尝试 能不能让和v配对的那条边，再换一个点配对，这样的话v就空出来了
                如果和v配对的点还可以和其他点配对，那就让它和其他点配对，把v空出来
                否则，说明v无法和当前点拆散，说明<u->v>不可行，应该换下条边进行尝试
            2. 找到了点u的配对点后， 依次遍历所有的点.
            3. 得到配对数
        
        这里多解释一下，v被配对时，如何去尝试 能不能让v裴迪哦的那条边再换一个点配对.
        dfs(i) 这个函数的作用是 尝试为 节点i匹配，如果匹配成功，那么返回true, 失败返回false
        在尝试匹配的时候，会扫描i的所有邻接点.
        假设 v 此时的配对点为 w ，
        如果我们把 v 标记为不可访问，然后dfs(w)返回了true， 那就说明，w可以找到除了v之外的另一个配对点，v就可以腾出来了

        所以，dfs里要有match数组和visited数组，用于保存 已配对节点的配对节点编号 和 该节点能否被访问
        match初始化为0 
        dfs伪代码：

        bool  dfs(cur): 
                for cur 的每一个邻接点v: 
                    if ( !visited[v] ):
                        visited[v] = true
                        if ( !match[v] || dfs( mathc[v] ) ):
                            // 配对成功
                            match[cur]=v
                            match[v]=cur
        for i from 1 to n:
            memset(visited, false);
            if ( !match[i] && dfs(i) ) 
                sum+=1;
        sum 就是最大匹配数

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
const int N=2000;
const int M=2*2000;
using namespace std;

int k,boy,girl,n;
bool visited[N];
int match[N];

typedef struct{
    int v;
    int next;
}Node;

int head[N];
Node edge[M];
int idx=0;

void Init(){
    for ( int i=0; i<=n; ++i ) head[i]=-1;
    idx=0;
    mem(match,0);
}

bool dfs( int cur ){
    int v;
    for ( int i=head[cur]; i>=0; i = edge[i].next ){
        v = edge[i].v;
        if ( !visited[v] ){
            visited[v] = true;
            if (  !match[v] || dfs(match[v])  ){
                match[v] = cur;
                match[cur] = v;
                return true;
            }
        }
    }
    return false;
}

void add_edge( int u,int v ){
    edge[idx].v = v;
    edge[idx].next = head[u];
    head[u] = idx++;
}

int main(void){
    int u,v;
    while( ~scanf("%d",&k) && k!=0 ){
        scanf("%d%d", &girl, &boy);
        // 前girl个是女生，之后是男生
        n = boy+girl;
        Init();
        for ( int i=1; i<=k; ++i ){
            scanf("%d%d",&u,&v);
            v += girl;
            add_edge(u,v);
            add_edge(v,u);
        }
        int sum=0;
        for ( int i=1; i<=n; ++i ){
            mem(visited, false);
            if ( !match[i] && dfs(i) ) sum+=1;
        }
        cout<<sum<<endl;
    }
    return 0;
}