/*
    问题描述：
        给定一个 n x n 矩阵，其中每行和每列元素均按升序排序，找到矩阵中第k小的元素。
        请注意，它是排序后的第k小元素，而不是第k个元素。
        示例:
        matrix = [
            [ 1,  5,  9],
            [10, 11, 13],
            [12, 13, 15]
        ],
        k = 8,
        返回 13。

    问题分析：
        这题让我对二分法又有了进一步的理解。

        首先，二分法可以分为两种：
            1. 对索引二分 (index)
            2. 对值二分   (nums[index])


        本题找第k大的元素，
        即找一个位置，使得在这个位置的元素满足：
            小于该元素的元素个数又k-1个
            小于等于该元素的元素个数有k个

        本题的解决方法就是，对值进行二分，找到这个位置。
        而在找这个位置的时候，可以利用矩阵有序的这个特征来降低复杂度。

        记模版只管一时， 重要的是理解二分的边界处理，
        从而可以把二分应用于不同场景。
 */

class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int n=matrix.size(), m=matrix[0].size();
        long cnt, mid, left=matrix[0][0], right=matrix[n-1][m-1];
        while(left<=right){
            mid = (left+right)/2;
            cnt = get_cnt(matrix, mid);
            // 找出cnt大于等于k的最小的那个
            if ( cnt<k ) left = mid+1;
            else if ( cnt>=k ) right = mid-1;
        }
        return left;
    }
    
    int bineary_search_row(vector<vector<int>>& matrix, int k){
        // 找到每行第一个元素小于等于k的元素
        int left=0, mid, right=matrix.size()-1;
        int val;
        while( left<=right ){
            mid = (left+right)/2;
            val = matrix[mid][0];
            if ( val<=k ) left = mid+1;
            else if ( val>k ) right = mid-1;
        }
        return left;
    }
    
    int get_cnt( vector<vector<int>>& matrix, int k ){
        int left, right, mid, val, cnt=0;
        int len = bineary_search_row(matrix, k);
        for ( int i=0; i<len; ++i ){
            //cout<<i<<endl;
            left = 0;
            right = matrix[0].size()-1;
            // 找出这一行小于等于k的元素
            
            /* 暴力
            for ( int j=0; j<matrix[0].size(); ++j )
                if ( matrix[i][j]<=k )
                    ++cnt;
                else break;*/
            
            // 二分
            while( left<=right ){
                mid = (left+right)/2;
                val = matrix[i][mid];
                if ( val>k )
                    right = mid-1;
                else if ( val<=k )
                    left = mid+1;
            }
            cnt+= left;
        }
        return cnt;
    }
};