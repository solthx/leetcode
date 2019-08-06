/*
    问题描述:
        给一个'0' '1'矩阵，只有一块区域是全'1'，
        现给出x,y 满足 matrix[x][y]=='1'
        返回能够完全套住这块区域的最小矩阵面积。

    问题分析:
        其实就是求x_max, x_min, y_max, y_min
        
        方法一:
            直接暴力 O(M*N) 
        
        方法二：
            BFS or DFS 
            最坏情况还是O(M*N)

        方法三:
            二分法.
            以寻找y_min来举例。
            ps : 个人习惯把y看成行， x看成列
            y_min一定在[0,y-1] 这个行区间里
            不妨把每一行抽象成一个bool， false表示不存在'1'， true表示存在'1'
            而我们知道，对于y上面的行来说，
            只要第t行是true，那么[y,t]行一定都是true 
            所以我们就利用这个性质来进行二分，
            而具体怎么知道这一行是不是存在1 (是不是true)，
            直接暴力就好了。
            所以复杂度为O( N*logM + M*logN )

            寻找x_min, x_max, y_max道理是一样的。
            但细节情况的不同，还是要分4次不同的二分。

            因为4个不同的二分函数有很多重复的地方，所以
            也可以用两个bool值来控制当前是那种情况，
            然后对4个二分函数进行合并。。
            
            这样做的好处是代码变短了。。
            坏处是可读性有点差了。。。
 */

class Solution3 {
public:
    int minArea(vector<vector<char>>& image, int x, int y) {
        //int y_min = bs_row_up( image, 0, x-1 );
        int y_min = binary_search( image, 0, x-1, true, true );
        //int y_max = bs_row_down( image, x+1, image.size()-1 );
        int y_max = binary_search( image, x+1, image.size()-1,false, true );
        //int x_min = bs_col_left( image, 0 ,y-1 );
        int x_min = binary_search( image, 0 ,y-1, true, false );
        //int x_max = bs_col_right( image, y+1 ,image[0].size()-1 );
        int x_max = binary_search( image, y+1 ,image[0].size()-1,false, false );
        return ( y_max-y_min+1 ) * (x_max-x_min+1);
        //cout<<x_min<<" "<<x_max<<endl;
        //return 0;
    }
    
    // 把4个二分函数组成了一个，kind和row两个布尔值 控制了4个不同的情况/
    int binary_search( vector<vector<char>>&image, int l, int r, bool kind, bool isRow ){
        int mid = (l+r)/2;
        bool black = false;
        if ( isRow ){
            for ( int i=0; i<image[0].size(); ++i )
            if ( image[mid][i]=='1' ){
                black = true;
                break;
            }
        }else{
            for ( int i=0; i<image.size(); ++i )
            if ( image[i][mid]=='1' ){
                black = true;
                break;
            }
        }
        if ( l>r ) return kind?l:r;
        if ( kind )
            return black? binary_search(image, l, mid-1, kind, isRow): binary_search(image, mid+1, r, kind, isRow);
        else
            return  black==false? binary_search(image, l, mid-1, kind, isRow): binary_search(image, mid+1, r, kind, isRow);
    }
    
    
    /*  4个二分函数

    int bs_row_up( vector<vector<char>>&image, int l, int r ){
        int mid = (l+r)/2;
        bool black = false;
        for ( int i=0; i<image[0].size(); ++i )
            if ( image[mid][i]=='1' ){
                black = true;
                break;
            }
        if ( l>r )
            return l;    
        return black==true ? bs_row_up(image,l,mid-1) : bs_row_up(image,mid+1,r);
    }
    
    int bs_row_down( vector<vector<char>>&image, int l, int r ){
        int mid = (l+r)/2;
        bool black = false;
        for ( int i=0; i<image[0].size(); ++i )
            if ( image[mid][i]=='1' ){
                black = true;
                break;
            }
        if ( l>r )
            return r;    
        return black==false ? bs_row_down(image,l,mid-1) : bs_row_down(image,mid+1,r);
    }
    
    int bs_col_left( vector<vector<char>>&image, int l, int r ){
        //cout<<"left: "<<l<<" "<<r<<endl;
        int mid = (l+r)/2;
        bool black=false;
        for ( int i=0; i<image.size(); ++i )
            if ( image[i][mid]=='1' ){
                black = true;
                break;
            }
        if ( l>r )
            return l;
        return black==true? bs_col_left(image, l,mid-1): bs_col_left(image,mid+1, r);
    }
    
    int bs_col_right( vector<vector<char>>&image, int l, int r ){
        //cout<<"right: "<<l<<" "<<r<<endl;
        int mid = (l+r)/2;
        bool black=false;
        for ( int i=0; i<image.size(); ++i )
            if ( image[i][mid]=='1' ){
                black = true;
                break;
            }
        if ( l>r )
            return r;
        return black==false? bs_col_right(image, l,mid-1): bs_col_right(image,mid+1, r);
    }
    */
};

// BFS
class Solution2 {
public:
    int minArea(vector<vector<char>>& image, int x, int y) {
        //bfs
        if ( image.size()==0 || image[0].size()==0 ) return 0;
        int i,j, n = image.size(), m = image[0].size();
        queue<pair<int,int>> q;
        int x_min=INT_MAX, x_max=INT_MIN, y_min=INT_MAX, y_max=INT_MIN;
        vector<vector<bool>> visited(n, vector<bool>(m,0));
        visited[x][y] = true;
        q.push({x,y});
        int dir[4][2] = {{1,0},{0,1},{0,-1},{-1,0}};
        while( !q.empty() ){
            i = q.front().first;
            j = q.front().second; q.pop();
            x_min = min(x_min, j);
            x_max = max(x_max, j);
            y_min = min(y_min, i);
            y_max = max(y_max, i);
            for ( int k=0; k<4; ++k ){
                y = i + dir[k][0];
                x = j + dir[k][1];
                if ( x<m && y<n && x>=0 && y>=0 && !visited[y][x] && image[y][x]=='1' ){
                    visited[y][x]=true;
                    q.push({y,x});
                }
            }
        }
        //cout<<x_max<<" "<<x_min<<" "<<y_max<<" "<<y_min<<endl;
        return (x_max-x_min+1)*(y_max-y_min+1);
    }
};
