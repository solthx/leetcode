/*
    问题描述:
        有图不大好说，自己看题吧: https://leetcode-cn.com/problems/path-with-maximum-minimum-value/
    
    问题分析:
        方法一: 最大堆
            一个很直观的且是错误的贪心方法就是，进行dfs然后每次都选周围最大的那个那个数，
            直到走到右下角为止.
            这个很容易举出反例,
            3 9 9
            2 1 1  
            2 2 2  这种情况，就会出错.

            但可以进行改进，也就是，当访问到9的时候， 周围是1了，我们就不继续往下走了，因为可以回到2继续走，2>1，
            我们可以维护一个最大堆，堆里存放下一步可以走的所有为止的值，
            然后每次取最大的那个，然后再遍历最大的那个点的上下左右可以走的位置，并将其放入堆中。
            直到遇到右下角，之后，到目前位置所遇到的最小的值就是结果了.

        方法二: 二分查找+bfs
            另一个很秀的思路就是对值来进行二分查找，
            我们知道，结果一定是在区间[0, min( A[0][0], A[n-1][m-1]) ]里面
            所以，可以对这个区间进行二分，
           
            函数helper():
                对于mid值，如果能找到一条从(0,0)到(n-1,m-1)的路径，使得路径上的每个点都大于等于mid
            那么就返回true，找不到就返回false
            
            l = 0 , r=min( A[0][0], A[n-1][m-1])
            while l<=r:
                mid = (l+r)/2
                if  helper( A, mid )==True: 
                    l = mid+1
                else:
                    r = mid-1
            return r; 
*/

class Solution1 {
public:
    int maximumMinimumPath(vector<vector<int>>& A) {
        // 最大堆
        if ( A.size()==0 || A[0].size()==0 ) return 0;
        int n = A.size(), m=A[0].size(); 
        auto cmp = [](vector<int> & a, vector<int>& b){
            return a[2]<b[2];  
        };
        int dir[4][2] = {{-1,0},{0,-1},{1,0},{0,1}};
        //元素为{i,j,A[i][j]} vector类型
        priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> q(cmp);
        vector<vector<bool>> visited(n, vector<bool>(m,false));
        q.push({0,0,A[0][0]});
        visited[0][0] = true;
        int maxi = INT_MAX;
        while( !q.empty() ){
            vector<int> cur = q.top(); q.pop();
            maxi = min( maxi, cur[2] );
            for ( int k=0; k<4; ++k ){
                int y=cur[0]+dir[k][0];
                int x=cur[1]+dir[k][1];
                if ( x<0 || y<0 || x>=m || y>=n ||visited[y][x] ) continue;
                visited[y][x] = true;
                q.push({y,x,A[y][x]});
                if ( y==n-1 && x==m-1 ){
                    return min( maxi, A[y][x] );
                }
                
            }
        }
        return -1;
    }
};


//=======================Solution2====================================
class Solution2{
public:
    int maximumMinimumPath(vector<vector<int>>& A) {
        // 二分+bfs
        if ( A.size()==0 || A[0].size()==0 ) return 0;
        int n = A.size(), m=A[0].size(); 
        int mid, l = 0 , r = min( A[n-1][m-1], A[0][0] );
        while( l<=r ){
            mid = (l+r)/2;
            if ( helper( A, mid ) ){
                l = mid+1;
            }else r = mid-1;
        }
        return r;
    }
    
    bool helper( vector<vector<int>>& A, int val ){
        int dir[4][2] = {{-1,0},{0,-1},{1,0},{0,1}};
        int n = A.size(), m=A[0].size(); 
        vector<vector<bool>> visited( n, vector<bool>(m,false));
        visited[0][0] = true;
        queue<pair<int,int>> q;
        q.push({0,0});
        while( !q.empty() ){
            pair<int,int> cur = q.front();q.pop();
            for ( int k=0; k<4; ++k ){
                int y = cur.first+dir[k][0];
                int x = cur.second + dir[k][1];
                if ( x<0 || y<0 || x>=m || y>=n || visited[y][x] || A[y][x]<val ) continue;
                visited[y][x] = true;
                q.push( {y,x} );
            }
        }
        return visited[n-1][m-1];
    }
    
};