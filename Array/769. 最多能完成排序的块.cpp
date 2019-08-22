/*
    问题描述:
        给定数组中的元素可以重复，输入数组最大长度为2000，其中的元素最大为10**8。
        arr是一个可能包含重复元素的整数数组，我们将这个数组分割成几个“块”，并将这些块分别进行排序。之后再连接起来，使得连接的结果和按升序排序后的原数组相同。
        我们最多能将数组分成多少块？
        
        示例 1:
            输入: arr = [5,4,3,2,1]
            输出: 1
            解释:
            将数组分成2块或者更多块，都无法得到所需的结果。
            例如，分成 [5, 4], [3, 2, 1] 的结果是 [4, 5, 1, 2, 3]，这不是有序的数组。 
        
        示例 2:
            输入: arr = [2,1,3,4,4]
            输出: 4
            解释:
            我们可以把它分成两块，例如 [2, 1], [3, 4, 4]。
            然而，分成 [2, 1], [3], [4], [4] 可以得到最多的块数。 
            注意:

            arr的长度在[1, 2000]之间。
            arr[i]的大小在[0, 10**8]之间。

    问题分析：
        方法一:
            观察每个分组，可以知道， 同一个分组内虽然是乱序的，
            但是只要把该分组内的元素排序后，他们都可以归到正确的位置，
            例如:
                1,2,[4,3,5],6
                虽然 [4,3,5] 是无序的， 但是只要把他们排序后 就可以变成[3,4,5]
                且3正好是第3大，4正好是第4大，5正好是第5大，这个样子.
                只要区间满足这样的状态，就可以分个组了.

                但怎么找呢? 可以想成，这个区间内的元素和，和排序后这个区间内的元素和 相同的话，就可以分组了

                同时，前面分完组的区间和都是相同的， 所以 可以把区间和等价转换成前缀和,
                只要 原数组 和 排序后的数组 在第i个位置前缀和相同， 那么就可以分出一个组.
        
        方法二:
            另一个思路， 遍历到第i个元素的时候， 只要满足 max{nums[0~i]}<= max{nums[i+1,n)} 
            那么就可以在当前位置分组，
            所以我们可以提前保存 左区间的最大值和右区间的最小值， 然后扫描判断，复杂度为O(N)
            
*/

class Solution1 {
public:
    int maxChunksToSorted(vector<int>& arr) {
        long long sumsA=0, sumsB=0, res=0;
        vector<int> nums( arr.begin(), arr.end() );
        sort( nums.begin(), nums.end() );
        for ( int i=0; i<arr.size(); ++i ){
            sumsA += arr[i];
            sumsB += nums[i];
            res += ( sumsA==sumsB );
        }
        return res;
    }
};

class Solution2 {
public:
    int maxChunksToSorted(vector<int>& arr) {
        int n = arr.size(), res=0;
        // 只要[0,i]的最大值 小于等于 [i+1,n]的最小值， 就🉑️ 分一个
        vector<int> left_max(n+1,INT_MIN);
        vector<int> right_min(n+2,INT_MAX);
        for ( int i=1; i<=n; ++i ){
            left_max[i] = max( arr[i-1], left_max[i-1] );
            right_min[n-i+1] = min( right_min[n-i+2], arr[n-i] );
        }
        
        for ( int i=1; i<=n; ++i ){
            if ( left_max[i]<=right_min[i+1] )
                res++;
        }
        return res;
    }
};
