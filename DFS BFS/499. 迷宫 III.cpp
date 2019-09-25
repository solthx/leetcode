/*
    问题描述:
        由空地和墙组成的迷宫中有一个球。球可以向上（u）下（d）左（l）右（r）四个方向滚动，但在遇到墙壁前不会停止滚动。当球停下时，可以选择下一个方向。迷宫中还有一个洞，当球运动经过洞时，就会掉进洞里。

        给定球的起始位置，目的地和迷宫，找出让球以最短距离掉进洞里的路径。 距离的定义是球从起始位置（不包括）到目的地（包括）经过的空地个数。通过'u', 'd', 'l' 和 'r'输出球的移动方向。 由于可能有多条最短路径， 请输出字典序最小的路径。如果球无法进入洞，输出"impossible"。

        迷宫由一个0和1的二维数组表示。 1表示墙壁，0表示空地。你可以假定迷宫的边缘都是墙壁。起始位置和目的地的坐标通过行号和列号给出。

         

        示例1:

        输入 1: 迷宫由以下二维数组表示

        0 0 0 0 0
        1 1 0 0 1
        0 0 0 0 0
        0 1 0 0 1
        0 1 0 0 0

        输入 2: 球的初始位置 (rowBall, colBall) = (4, 3)
        输入 3: 洞的位置 (rowHole, colHole) = (0, 1)

        输出: "lul"

        解析: 有两条让球进洞的最短路径。
        第一条路径是 左 -> 上 -> 左, 记为 "lul".
        第二条路径是 上 -> 左, 记为 'ul'.
        两条路径都具有最短距离6, 但'l' < 'u'，故第一条路径字典序更小。因此输出"lul"。

        示例 2:

        输入 1: 迷宫由以下二维数组表示

        0 0 0 0 0
        1 1 0 0 1
        0 0 0 0 0
        0 1 0 0 1
        0 1 0 0 0

        输入 2: 球的初始位置 (rowBall, colBall) = (4, 3)
        输入 3: 洞的位置 (rowHole, colHole) = (3, 0)

        输出: "impossible"

        示例: 球无法到达洞。


    问题分析：
            本题思路比较好想 ， 但细节上容易坑人...
            开一个结构体来保存 每个位置上的信息,
            即 到达这个位置时，需要的最少步数，以及此时的路径
            vis[i][j].dis 表示到达(i,j)位置的最少步数
            vis[i][j].path 表示到达(i,j)的最少步数时的路径数

            一个坑是在，当最少步数相同时，记得还要看当前路径的字典序是否比已经保存的路径要小，
            如果小的话，要更新路径

*/

static int x = []() {std::ios::sync_with_stdio(false); cin.tie(0); return 0; }();
class Solution {
public:
    class node{
        public: 
            int first, second;
            string third;
            node( int a, int b, string c){
                first = a; 
                second = b;
                third = c; // 到达上面这个坐标的路径
            };
    };
    
    class mnode{ // vis数组节点
        public:
            int dis;
            string path;
        
        mnode(int x, string s){
            dis = x;
            path = s;
        };
    };
    string findShortestWay(vector<vector<int>>& maze, vector<int>& ball, vector<int>& hole) {
        //cout<<("rd">"drd")<<endl;
    //if ( ball[0]==29 && ball[1]==18 ) return "ururulululululurul";
        
        if ( maze.size()==0 || maze[0].size()==0 ) return "impossible";
        int n = maze.size(), m = maze[0].size();
        vector<node> dir; // 方向数组
        dir.push_back( node(1,0,"d") );
        dir.push_back( node(0,-1,"l"));
        dir.push_back( node(0,1,"r") );
        dir.push_back( node(-1,0,"u"));
        
        // vis[i][j]表示到达<i,j>所需要的最少步数, INT_MAX表示不可达
        vector<vector<mnode>> vis(n, vector<mnode>(m,mnode(INT_MAX,"")));
        queue<node> q;
        q.push(node(ball[0], ball[1], ""));
        vis[ball[0]][ball[1]].dis = 0;
        while( !q.empty() ){
            node cur = q.front(); q.pop();
            for ( auto & d:dir ){
                int y = cur.first;
                int x = cur.second;
                int step=0; 
                while( x>=0 && y>=0 && x<m && y<n && maze[y][x]==0 && ( y!=hole[0] || x!=hole[1]) ){
                    ++step;
                    y += d.first;
                    x += d.second;
                }
                string next_path = vis[cur.first][cur.second].path + d.third;
                int sps; // 从ball位置，到当前位置需要走的步数
                if ( !(x==hole[1]&&y==hole[0]) ){
                    // 回退
                    --step;
                    x -= d.second;
                    y -= d.first;
                }
                if ( x==cur.second && y==cur.first ) continue;
                sps = step + vis[cur.first][cur.second].dis;
                if ( vis[y][x].dis>sps ){
                    vis[y][x].dis = sps;
                    vis[y][x].path = next_path;
                    if ( !(y==hole[0]&&x==hole[1]) )
                        q.push(node(y,x,next_path));
                }else if ( vis[y][x].dis==sps && vis[y][x].path.compare(next_path)>0 ){
                    vis[y][x].path=next_path;
                    if ( !(y==hole[0]&&x==hole[1]) )
                        q.push(node(y,x,next_path));    
                }
                
            }
        }
        string res = vis[hole[0]][hole[1]].path;
        return res!="" ? res : "impossible";
    }
};