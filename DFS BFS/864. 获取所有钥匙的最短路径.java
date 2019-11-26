/*
    问题描述：
        给定一个二维网格 grid。 "." 代表一个空房间， "#" 代表一堵墙， "@" 是起点，（"a", "b", ...）代表钥匙，（"A", "B", ...）代表锁。
        我们从起点开始出发，一次移动是指向四个基本方向之一行走一个单位空间。我们不能在网格外面行走，也无法穿过一堵墙。如果途经一个钥匙，我们就把它捡起来。除非我们手里有对应的钥匙，否则无法通过锁。
        假设 K 为钥匙/锁的个数，且满足 1 <= K <= 6，字母表中的前 K 个字母在网格中都有自己对应的一个小写和一个大写字母。换言之，每个锁有唯一对应的钥匙，每个钥匙也有唯一对应的锁。另外，代表钥匙和锁的字母互为大小写并按字母顺序排列。
        返回获取所有钥匙所需要的移动的最少次数。如果无法获取所有钥匙，返回 -1 。
         
        示例 1：
            输入：["@.a.#","###.#","b.A.B"]
            输出：8
        示例 2：

        输入：["@..aA","..B#.","....b"]
        输出：6
         

        提示：

        1 <= grid.length <= 30
        1 <= grid[0].length <= 30
        grid[i][j] 只含有 '.', '#', '@', 'a'-'f' 以及 'A'-'F'
        钥匙的数目范围是 [1, 6]，每个钥匙都对应一个不同的字母，正好打开一个对应的锁。

    问题分析:
        方法一：bfs+位运算
            本题用bfs的变种也可以做。。 即保存的状态就是 ： 位置[i,j] 和 手中的钥匙的状态（即已经拿到了哪些钥匙）

            因为钥匙数量很少，且不会出现重复，所以就用一个int变量来记录钥匙状态，即 'a'对应第1位， 'b'对应第二位... 
            如果已经有了某个钥匙，那么对应的位上的数字就是1， 否则就是0；

            感觉本题的最大难点还是在于要想清楚状态的更新，hint如下:
                1. 最终要的是最少步数，这个用bfs来控制最少步数
                2. 结束情况:
                    2.1 不存在: 直到bfs队列为空，都没有找到全部钥匙
                    2.2 存在: 在某一个位置下，找到了全部钥匙; 是否找到了全部钥匙，可以用finish这个变量来记录所有的钥匙的状态，然后在bfs时，一旦发现有一个位置上的状态和finish状态相同，那么就说明搜索完毕
                3. 拿到钥匙之后，不会因为开门而消耗掉钥匙
                4. 在bfs的过程中， '@'和'.'的地位是一样的，不要漏掉'@'的情况
              <5>. 判断某一个位是否为1:
                        要么  (flag & 1<<(c-'a')) > 0
                        要么  (flag & 1<<(c-'a')) == 1<<(c-'a')
                    千万不要写成了:
                        (flag & 1<<(c-'a')) == 1 // 这是错误的！！！
                    （总感觉是第二次犯这种弱智错误了。。 总之，使用位运算的时候切记两点:
                        1. 小心仔细的写！ 写完再检查一遍！！
                        2. 多加括号！！ 不要怕括号多。。 位运算的优先级有点迷。。
        
        官方题解用到了dijkstra和枚举.... emmm...  下次再补吧..
*/

class Solution {
    public int shortestPathAllKeys(String[] grid) {
        if (grid.length == 0 || grid[0].length() == 0)
            return 0;
        Queue<int[]> q = new LinkedList<>();
        int n = grid.length, m = grid[0].length();
        int finish = 0;
        boolean[][][] vis = new boolean[31][31][128];
        int[] dy = new int[] { 1, 0, -1, 0 };
        int[] dx = new int[] { 0, 1, 0, -1 };
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                if (grid[i].charAt(j) == '@') {
                    q.offer(new int[] { i, j, 0 });
                    vis[i][j][0] = true;
                } else if (grid[i].charAt(j) >= 'a' && grid[i].charAt(j) <= 'z') {
                    char c = grid[i].charAt(j);
                    finish = (finish | (1 << (c - 'a')));
                }
        int step = 0; // 已经走了的步数
        int key_cnt = 0;
        while (!q.isEmpty()) {
            for (int c = q.size(); c > 0; --c) {
                int[] cor = q.poll();

                if (cor[2] == finish)
                    return step;
                for (int k = 0; k < 4; ++k) {
                    int y = cor[0] + dy[k];
                    int x = cor[1] + dx[k];
                    if (y >= 0 && x >= 0 && y < n && x < m && grid[y].charAt(x) != '#') {
                        // 下一个位置<y,x>可以抵达, 且从未抵达过
                        char state = grid[y].charAt(x);
                        if (state >= 'a' && state <= 'z') {
                            // 取钥匙
                            int nxt_state = (cor[2] | (1 << (state - 'a')));
                            if (!vis[y][x][nxt_state]) {
                                vis[y][x][nxt_state] = true;
                                q.offer(new int[] { y, x, nxt_state });
                            }
                        } else if (state >= 'A' && state <= 'Z' && (cor[2] & (1 << (state - 'A'))) > 0) {
                            // 开锁
                            int nxt_state = cor[2];
                            if (!vis[y][x][nxt_state]) {
                                vis[y][x][nxt_state] = true;
                                q.offer(new int[] { y, x, nxt_state });
                            }
                        } else if (state == '.' || state == '@') {
                            if (!vis[y][x][cor[2]]) {
                                vis[y][x][cor[2]] = true;
                                q.offer(new int[] { y, x, cor[2] });
                            }
                        }
                    }
                }
            }
            ++step;
        }
        return -1;
    }
}