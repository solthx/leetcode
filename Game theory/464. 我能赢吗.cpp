/*
    问题描述:
        题目太长了，我简化一下，
        A和B玩游戏，一个一次从 1～n里选一个数 加入序列中，
        一个数只能被选一次， 如果当前轮到A，A选了一个数放入序列使得序列总和超过m
        那么A胜，同理，如果B选了一个数使得序列总和超过m，那么B胜。

        现给定n和m， 问先手能否必胜?

    问题分析:
        第一次遇到博弈论的题目应该是 #1140 石子游戏II 那题，
        这种类似的博弈题可以用 记忆化数组+dfs(+min_max)  来做。
        
        本题在做dfs的时候会TLE, 因此要用memo数组来保存中间状态减少重复计算。
        但是该保存什么，这是个问题。
        因为当前状态是根据前面的选择来决定的，也就是说，当前的visited数组(用来记录哪些数被选过，之后就不能选了)
        所以，要保存的状态就是visited数组，但这个很不好保存。。
        
        这里一个很nice的办法，就是用mask来代替visited数组，
        这个方法的弊端就是 visited数组长度不能超过 sizeof(long long)
        不过本题的数组最大长度是20，所以int就够了，
        int的每一位代表数组的0/1状态，也就是选还是没选的状态，
        然后保存这个int就好啦。

         dfs逻辑就是:
            for i from 1 to n:
                如果i可以选:
                    把i个选了
                    如果 (i>=m || 选了i之后, 下一个player必输) :
                        直接返回true，说明当前player选了i 就赢了
    
            出了循环说明不管当前选1～n的哪一个数都不能必赢
            那就返回false
*/
class Solution {
public:
    bool canIWin(int maxChoosableInteger, int desiredTotal) {
        int mask = 0;
        // 事先判断几种特殊情况 直接返回了
        if (maxChoosableInteger >= desiredTotal) return true;
        if ( (maxChoosableInteger+1)*maxChoosableInteger/2<desiredTotal ) return false;
        if ( desiredTotal<=0 ) return true;
        map<int,bool> memo;
        return helper( maxChoosableInteger, desiredTotal, mask, memo );
    }

    bool helper( int length, int upper, int mask, map<int,bool>& memo ){
        if ( memo.count(mask)>0 ) return memo[mask];
        int cur;
        int j=0;
        for ( int i=1; i<=length; ++i ){
            cur = (1 << (i-1));
            if ( (cur & mask) == 0  ){
                if ( i>=upper || !helper( length, upper-i, mask | cur, memo  ) ){
                    memo[mask] = true;
                    return true;
                }
            }
        }
        memo[mask]=false;
        return false;
    }
};

/*
class Solution {
public:
    TLE
    bool canIWin(int maxChoosableInteger, int desiredTotal) {
        int cur = 0;
        int a = maxChoosableInteger, b = desiredTotal;
        if ( a*(a+1)/2 <b ) return false;
        vector<bool> visited(maxChoosableInteger+1,false);    
        return dfs(maxChoosableInteger, visited, desiredTotal, 0 ); 
    }
    
    // 当前选择的palyer能否必赢
    bool dfs( int length, vector<bool> & visited, int target, int player ){
        for ( int i=length; i>=1; --i ){
            if ( !visited[i] ){
                // 没被选就选择i
                visited[i] = true;   
                // 如果加上i，直接超过target, 那么则当前必赢
                if ( i>=target || !dfs(length , visited, target-i, (player+1)%2) ){
                    visited[i]=false;
                    return true;
                }
                visited[i] = false;
            }
        }
        return false;
    }
    
};

*/
