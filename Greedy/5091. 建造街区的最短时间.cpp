/*
    问题描述:
        你是个城市规划工作者，手里负责管辖一系列的街区。在这个街区列表中 blocks[i] = t 意味着第  i 个街区需要 t 个单位的时间来建造。

        由于一个街区只能由一个工人来完成建造。

        所以，一个工人要么需要再召唤一个工人（工人数增加 1）；要么建造完一个街区后回家。这两个决定都需要花费一定的时间。

        一个工人再召唤一个工人所花费的时间由整数 split 给出。

        注意：如果两个工人同时召唤别的工人，那么他们的行为是并行的，所以时间花费仍然是 split。

        最开始的时候只有 一个 工人，请你最后输出建造完所有街区所需要的最少时间。

        

        示例 1：

        输入：blocks = [1], split = 1
        输出：1
        解释：我们使用 1 个工人在 1 个时间单位内来建完 1 个街区。
        示例 2：

        输入：blocks = [1,2], split = 5
        输出：7
        解释：我们用 5 个时间单位将这个工人分裂为 2 个工人，然后指派每个工人分别去建造街区，从而时间花费为 5 + max(1, 2) = 7
        示例 3：

        输入：blocks = [1,2,3], split = 1
        输出：4
        解释：
        将 1 个工人分裂为 2 个工人，然后指派第一个工人去建造最后一个街区，并将第二个工人分裂为 2 个工人。
        然后，用这两个未分派的工人分别去建造前两个街区。
        时间花费为 1 + max(3, 1 + max(1, 2)) = 4
        

        提示：

        1 <= blocks.length <= 1000
        1 <= blocks[i] <= 10^5
        1 <= split <= 100
    
    问题分析:
        看到这道题解法的时候，真是被秀到了。。
        记录一下从这题得到的收货吧.

        这里只记录贪心的方法.

        把完成一个街区的建造看成是完成一个任务，

        那么， 观察本题可以知道，一个人只能完成一个任务，一个任务只能被一个人完成，
        
        然后一个人又可以分裂成两个人， 

        可以画出下面这个对应关系:
        
        一个工人  一个工人
           |       |
        一个任务  一个工人

        而因为一开始只有一个人， 所以构建的模型其实是一个人最终分裂出多个人，然后对应多个任务，
        例如 三个任务 一个人的情况:
                    工人A           (1)
                    /    \
                工人A   工人B        (2)
                /  \     | 
            工人A  工人C 任务3        (3)
             |     |
            任务1  任务2             (4)

        我们最终是要计算，在只有一个工人A的情况下，花费的最少时间
        
        上面的这颗树， 每个节点，要么分裂， 要么去完成任务. 

        若节点分裂，则这个节点的花费时间就是 split + 分裂的两个工作最久的时间 (分裂花费的时间也算这里的工作时间) )

        最终完成所有任务的时间，就是 最长的带权路径和 (这里的权重就是花费的时间) .

        然后我们要的结果是，所有这种 最长的带权路径和中， 最短的那条.

        因为每分裂一次，都要花费split, 所以我们想要的是，花费时间小的任务放在下层，花费时间大的任务放在上层
        (因为越往下面就是越是放在后面做的，而前面的时间久的可以并行，所以我们当然是想优先做长作业了)
        
        然后根据哈夫曼的思想，求出 （最长的带权路径和 (这里的权重就是花费的时间)）的最短的那条就行了
*/

class Solution {
public:
    int minBuildTime(vector<int>& blocks, int split) {
        priority_queue<int,vector<int>, greater<int>> q;
        for ( auto e:blocks ) q.push(e);
        while( q.size()>1 ){
            q.pop();
            int res = q.top(); q.pop();
            q.push(res+split);
        }
        return q.top();
    }
};