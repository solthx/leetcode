/*
	题目大意：
		跳跃游戏1数组每一个元素代表可走步数，返回能否从0出发抵达最后一个元素
		在此基础上又加了一个要求，就是输出最少步数。

	题目分析：
		解法一就是在跳跃游戏1的基础上的暴力，果然在最后一个样例超时了QAQ
		
		解法二是看了题解才会的。 换了一个思路，那就是维护一个区间，就是
		在第i跳可以跳到的最近距离和最远距离（之所以需要最近距离，是因为
		在更新第i+1跳的最远距离时，需要用到第i跳的最近距离，因为有可能在第i
		跳的最近距离可以跳的位置超级远，然后一下跳到最远），最近距离很好维护，
		第i跳最近能跳到i（每次跳一步，虽然存在跳0的情况，但跳0的是不可能抵达终点的
		，并且题目说每次都能够跳到最后，所以在这里不影响），若cnt超过了reach_most，那么
		肯定就挑不到终点了。
		
		最后，只要most_reach覆盖到最后一个位置，那就立马返回跳数。
*/

class Solution {
public:
    int jump(vector<int>& nums) {
        /* 
            解法一 （超时）
        int last = nums.size()-1,cnt=0;
        for ( int i=0; i<nums.size() && last>0 ; ++i ){
            for ( int j=0; j<last; ++j ){
                if ( j+nums[j]>=last ) {
                    last = j;
                    cnt++;
                    break;
                }
            }
        }
        return cnt;
        */
        /*
            解法二：维护一个most_reach，即当前跳所能抵达的最远位置
            每次都跳最远，当跳到last idx时，一定就是最小跳数
        */
        //过滤非法情况，，
        if ( nums.size()<2 ) return 0; 
        int n,start=0,cnt=1,most_reach=nums[0];
        while( most_reach<nums.size()-1 ){
            //第cnt次跳跃，
            //最近的位置是 前面都每次跳一步，位置与cnt一样
            //最远的位置就是most_reach，是我们主要更新的变量
            n = most_reach; 
            //所以第cnt次可以跳到的范围就是[cnt, most_reach]
            //下面的循环是更新第cnt+1次的most_reach
            for ( int i=cnt; i <= n ; ++i ){
                if ( most_reach< i + nums[i] ) most_reach = i+nums[i];
            }
            cnt++;
			if ( cnt>most_reach ) return -1; // 跳不到最后。
        }
        
        return cnt;
    }
};

