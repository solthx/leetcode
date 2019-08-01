/*
    问题描述：
        编写一个高效的算法来搜索 m x n 矩阵 matrix 中的一个目标值 target。该矩阵具有以下特性：
        每行的元素从左到右升序排列。
        每列的元素从上到下升序排列。
        示例:

        现有矩阵 matrix 如下：
        [
            [1,   4,  7, 11, 15],
            [2,   5,  8, 12, 19],
            [3,   6,  9, 16, 22],
            [10, 13, 14, 17, 24],
            [18, 21, 23, 26, 30]
        ]

    问题分析：
        方法一：
            O(M*logN) 如果第t+1行的第一个元素大于了target，第t行第一个元素小于等于target
            就对前t行用一次二分， 这个方法比较好想，但复杂度较高。

        方法二：
            
            ▶▶▶这个矩阵的特性是 对于任意一个元素matrix[i][j]，
            在(i,j)坐标的正右方，正下方，右下方的所有元素都要比这个位置的元素大，
            因此可以通过缩小矩阵来做。

            先从行上下手，在c_lower行上找到首个比target大的元素，
            然后包括这个元素在内的正下方正右方以及右下方的所有元素都可以不考虑了。

            再从列上下手，在r_upper列上找到首个比target大的元素，
            该元素所在行的上面的每一行的最大元素都比target小，也不用考虑了。

*/


// O(N) 写法简洁， 不用二分的去前进
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if ( matrix.size()==0 || matrix[0].size()==0 ) return false;
        int i=0, j=matrix[0].size()-1;
        while( i<matrix.size() && j>=0 ){
            if (matrix[i][j]>target) --j;
            else if (matrix[i][j]<target) ++i;
            else return true;
        }
        return false;
    }
};

// O(logN) 所有的搜索都用二分来搜
class Solution2 {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if ( matrix.size()==0 || matrix[0].size()==0 ) return false;
        int val, mid, i, j, r_upper = matrix[0].size()-1, c_lower=0;
        while( r_upper>=0 && c_lower<matrix.size() ){
            // 缩小列范围
            i=0;
            j=r_upper;
            while( i<=j ){
                mid = (i+j)/2;
                val = matrix[c_lower][mid];
                if (val>target) j = mid-1;
                else if ( val<target ) i = mid+1;
                else return true;
            }
            r_upper = i-1;
            if ( r_upper<0 ) return false;
            // 缩小行范围
            i=c_lower;
            j=matrix.size()-1;
            while( i<=j ){
                mid = (i+j)/2;
                val = matrix[mid][r_upper];
                if (val>target) j = mid-1;
                else if ( val<target ) i = mid+1;
                else return true;
            }
            c_lower = i;
            if ( c_lower>=matrix.size() ) return false;
        }
        return false;
    }
};


// O(mlogn)
class Solution3 {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if ( matrix.size()==0 || matrix[0].size()==0 ) return false;
        int val, mid, i=0, j=matrix.size()-1;
        while( i<=j ){
            mid = (i+j)/2;
            val = matrix[mid][0];
            if (val>target) j = mid-1;
            else if ( val<target ) i = mid+1;
            else return true;
        }
        for ( int t=0; t<i; ++t ){
            int left=0, right=matrix[0].size()-1;
            while( left<=right ){
                mid = (left+right)/2;
                val = matrix[t][mid];
                if ( val>target )
                    right = mid-1;
                else if ( val<target )
                    left = mid+1;
                else return true;
            }
        }
        return false;
    }
};