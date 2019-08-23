/*
    问题描述：
        在一个 10^6 x 10^6 的网格中，每个网格块的坐标为 (x, y)，其中 0 <= x, y < 10^6。
        我们从源方格 source 开始出发，意图赶往目标方格 target。每次移动，我们都可以走到网格中在四个方向上相邻的方格，只要该方格不在给出的封锁列表 blocked 上。
        只有在可以通过一系列的移动到达目标方格时才返回 true。否则，返回 false。

        示例 1：
            输入：blocked = [[0,1],[1,0]], source = [0,0], target = [0,2]
            输出：false
            解释：
            从源方格无法到达目标方格，因为我们无法在网格中移动。
        
        示例 2：
            输入：blocked = [], source = [0,0], target = [999999,999999]
            输出：true
            解释：
            因为没有方格被封锁，所以一定可以到达目标方格。
             

        提示：
            0 <= blocked.length <= 200
            blocked[i].length == 2
            0 <= blocked[i][j] < 10^6
            source.length == target.length == 2
            0 <= source[i][j], target[i][j] < 10^6
            source != target

    问题分析:
        这题是真的秀！！
        开辟了另一种bfs的思路！！
        按区域块来扫描.
        因为block的个数，最多是200个，
        而当这200个斜着盖住grid的一角的时候，是能盖住的最大面积，
        此时的面积是 1+2+..+200 <20000
        而一个点，相等于是一个面积为1的正方形，
        所以只要从source遍历到20000的个点的时候，还能继续遍历，说明source没有被围死

        因此，只要source和target这两个点都没有被围死，
        那么他们就一定是连同的

*/

# define MAXI 1000000
class Solution {
public:
    bool isEscapePossible(vector<vector<int>>& blocked, vector<int>& source, vector<int>& target) {
        // 表示当前遍历的面积
        // 开始判断source点有没有被围死，flag1为true的时候说明source没有被围死
        int square=1;
        bool flag1=false,flag2=false;
        queue<pair<int,int>> q;
        int dir[4][2] = {{0,1},{1,0},{-1,0},{0,-1}};
        map<int, map<int,bool>> visited; // 记录该位置是否访问过
        
        q.push({source[0], source[1]});
        
        for ( auto e:blocked ) 
            visited[e[0]][e[1]]=true; // block位置，置成访问过的，不再访问
        
        visited[source[0]][source[1]] = true;
        
        while( !q.empty() ){
            pair<int,int> cor = q.front(); q.pop();
            for ( int k=0; k<4; ++k ){
                int y = cor.first + dir[k][0];
                int x = cor.second + dir[k][1];
                if ( x>=0 && y>=0 && x<MAXI && y<MAXI && !visited[y][x]   ){
                    if ( y==target[0] && x==target[1] ) return true;
                    visited[y][x] = true;
                    q.push({y,x});
                    ++square;
                }
            }
            // 面积超过20000还没被围死， 说明不会被围死了
            if ( square>=20000 ){
                flag1=true;
                break;
            }
        }
        

        // 开始判断target点有没有被围死，flag2为true的时候说明target没有被围死
        square=1;
        map<int, map<int,bool>> book;
        for ( auto e:blocked ) 
            book[e[0]][e[1]]=true;
        book[target[0]][target[1]] = true;
        queue<pair<int,int>> p;
        p.push({target[0], target[1]});
        while( !p.empty() ){
            pair<int,int> cor = p.front(); p.pop();
                   
            for ( int k=0; k<4; ++k ){
                int y = cor.first + dir[k][0];
                int x = cor.second + dir[k][1];
                if ( x>=0 && y>=0 && x<MAXI && y<MAXI && !book[y][x]   ){
                    if ( y==source[0] && x==source[1] ) return true;
                    book[y][x] = true;
                    p.push({y,x});
                    ++square;
                }
            }
            if ( square>=20000 ){
                flag2=true;
                break;
            }
        }
        // 当source和target都没被围死的时候，则一定连通
        return flag1&&flag2;
    }
};