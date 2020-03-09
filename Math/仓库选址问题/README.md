# 仓库选址问题

仓库选址问题：

    在数轴上找一点使得该点到所有其他点的距离之和最小。

也就是说:

    给定x0, x1, .. xn, 找到一个点k , dis = |x0-k| + |x1-k| + ... +|xn-k|
    使得dis最小。

这个点很显然是所有点排序后的中位数的那个位置... [证明在这](https://www.cnblogs.com/LLTYYC/p/9537677.html)

这类题的变种往往是给另一个场景，然后通过建模推导之后，能得出类似公式，下面来看一个.

## 题目1

1. 在数轴上给定[x0, x1, ... xn] (可xi和xj可以相等，例如[1,9,9,3, ...]), 这n个点可以左移或右移，每移动1步开销为1，现要将这n个点排成一排连续直线，求最小的移动开销.

- 分析: 
    如果是枚举每个区间的话，那么复杂度就是n^2了，这个复杂度并不是让人满意... 我们的目的是将[x0, x1, ..., xn] 放入 [a, a+1, a+2, .. a+n-1] 之后
    开销最小，但长度我们知道，所以实际就是确定a点的位置!  不妨将问题
    转换成数学语言：
        最有解a点位置满足:
            min{ |x0-a| + |x1-(a+1)| + ... + |xn-(a+n-1)| }
        <=> min{ |x0-a| + |x1-1-a }| + ... + |xn-(n-1) - a| }
        
        令zi = xi - (i+1)

        => min{ |z0-a| + |z1-a| + ... + |zn-a| }

    又变成了仓库选址问题了！

[练手题目](https://www.nowcoder.com/questionTerminal/64d35e4069574412a1a654d53c9a1710?orderByHotValue=0&mutiTagIds=1194&page=1&onlyReference=false&toCommentId=5408308)

cpp solution
```
# include<iostream>
# include<cstring>
# include<map>
# include<algorithm>
# include<vector>
# include<cmath>
#include <sstream>
using namespace std;

int n,m;
int x[10010], y[10010], z[10010];
 
int main(void){
    while(cin>>n){
        for(int i=0; i<n; ++i)
            cin>>x[i]>>y[i];
        sort(y, y+n);
        sort(x, x+n);
        int mid=n/2, y_ans = 0, x_ans = 0;
        for(int i=0; i<n; ++i)
            y_ans += abs(y[i]-y[mid]);
        for(int i=0; i<n; ++i)
            z[i] = x[i] - i;
        int a = z[mid];
        for(int i=0; i<n; ++i)
            x_ans += (abs(x[i]-(a+i)));
        cout<<x_ans+y_ans<<endl;
    }
    return 0;
}
```



## 题目2

    好吧，并没有什么题目2，只是提一下，对于加整数正权的情况，也是可以取中位数来做的.
    即: min{ wi*|xi-k| } 这种