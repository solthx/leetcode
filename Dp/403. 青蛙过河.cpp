/*
    问题描述:
        一只青蛙想要过河。 假定河流被等分为 x 个单元格，并且在每一个单元格内都有可能放有一石子（也有可能没有）。 青蛙可以跳上石头，但是不可以跳入水中。
        给定石子的位置列表（用单元格序号升序表示）， 请判定青蛙能否成功过河（即能否在最后一步跳至最后一个石子上）。 开始时， 青蛙默认已站在第一个石子上，并可以假定它第一步只能跳跃一个单位（即只能从单元格1跳至单元格2）。
        如果青蛙上一步跳跃了 k 个单位，那么它接下来的跳跃距离只能选择为 k - 1、k 或 k + 1个单位。 另请注意，青蛙只能向前方（终点的方向）跳跃。

        请注意：
            石子的数量 ≥ 2 且 < 1100；
            每一个石子的位置序号都是一个非负整数，且其 < 231；
            第一个石子的位置永远是0。
        示例 1:
            [0,1,3,5,6,8,12,17]

            总共有8个石子。
            第一个石子处于序号为0的单元格的位置, 第二个石子处于序号为1的单元格的位置,
            第三个石子在序号为3的单元格的位置， 以此定义整个数组...
            最后一个石子处于序号为17的单元格的位置。

            返回 true。即青蛙可以成功过河，按照如下方案跳跃： 
            跳1个单位到第2块石子, 然后跳2个单位到第3块石子, 接着 
            跳2个单位到第4块石子, 然后跳3个单位到第6块石子, 
            跳4个单位到第7块石子, 最后，跳5个单位到第8个石子（即最后一块石子）。

    问题分析:
        方法一:
            一看就是Dp, 
            dp[i]保存了到达第stones[i]块石头的前一跳跳数的集合.. (之所以用集合是因为会有重复的
            如果这个集合的个数是0，说明这块石头不可达。。

            然后在第stones[i]块石头上的时候，对后面的时候进行更新...

        方法二:
            dfs+记忆化搜索+二分查找
            helper( stones, index, jump_size, memo ) 返回 跳了jump_size后，
            抵达到第index个石头上 之后能否跳到最后一块石头上.

            因为会有很多重复计算，所以用memo[index][jump_size]来保存已经计算过的情况
            即memo[index][jump_size]就是表示 跳了jump_size后，
            抵达到第index个石头上 之后能否跳到最后一块石头上 1表示可以，0表示不可以，-1表示还没更新

            因为石头序号是递增有序的，因此在找首个大于等于jump_size-1的石头的时候，可以使用二分查找来找.

            总体复杂度为O(N^2 * logN)
 */

class Solution1 {
public:
    //Dp
    bool canCross(vector<int>& stones) {
        int stone_idx, n=stones.size();
        if ( n==0 || n>1 && stones[1]==0 ) return false;
        unordered_map<int, set<int>> mp;
        for ( auto e:stones )
            mp[e] = {};
        mp[1].insert(1);
        for ( int i=1; i<n-1; ++i ){
            stone_idx = stones[i];
            for ( auto pre_step : mp[stone_idx] ){
                for ( int step=pre_step-1; step<=pre_step+1; ++step ){
                    if ( mp.count(stone_idx+step)>0 ){
                        mp[stone_idx + step].insert( step );
                    }
                } 
            }
        }
        return mp[stones.back()].size()>0 ;
    }
};


class Solution2 {
public:
    bool canCross(vector<int>& stones) {
        int n=stones.size();
        vector<vector<int>> memo( n, vector<int>(n, -1 ) ); //memo[index][jumpsize]
        return helper( stones, 0, 0 , memo)==1;
    }
    
    //返回从第idx个位置开始跳，上一次跳过来的jump_size是jsize，能否跳到最后一个石头
    int helper( vector<int> & stones, int idx, int jsize, vector<vector<int>>& memo ){
        int res=0;
        if ( idx==stones.size()-1 )
            return 1;
        if ( memo[idx][jsize]>=0 ){
            return memo[idx][jsize];
        }
        int i=idx+1;
        int mid, l=idx+1, r=stones.size()-1;
        
        // 找首个stones[j] - stones[idx]>=jsize-1 的那个j
        while( l<=r ){
            mid = (l+r)/2;
            if ( stones[mid] - stones[idx] < jsize-1 ) l = mid + 1;
            else  r = mid -1 ;
        }
        // 找到了那个j就是这里的l
        // 因为是stones是递增的，所以stones[i] - stones[idx]>jsize+1的话，
        // 那么stones[i～n] - stones[idx]>jsize+1 都成立
        while ( l<stones.size() && stones[l] - stones[idx]<=jsize+1 ){
            if ( helper( stones, l, stones[l]-stones[idx], memo )==1 )
                return 1;
            l++;
        }

        /* 暴力
        while( i<stones.size()  )
        {
            int gap =  stones[i]-stones[idx]; 
            if ( gap>jsize+1 ) break; 
            if ( gap<=jsize+1 && gap>=jsize-1 &&  helper( stones, i, stones[i]-stones[idx], memo )==1 )
                return 1;
            ++i;
        }*/
        memo[idx][jsize] = 0;
        return memo[idx][jsize];
    }
    
};