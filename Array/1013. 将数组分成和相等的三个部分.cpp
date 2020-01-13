/*
    问题描述:
        能否把数组分成三个和相同的子数组

    问题分析：
        方法一: O(N)
            哈希表+前缀和,  right[i]记录[i,n]的和， 然后从右往左记录左前缀和，
            if 左前缀和出现过 && 左前缀和/2 == 右前缀和 ：
                return true
        
        方法二: O(N)
            1. 如果sums%3!=0 return false
            2. k = sums/3;
            3. 开始寻找子数组和，如果等于k, 就给cnt加1
            4. 如果cnt>=3 就说明ok （之所以是大于等于不是等于，是因为[1,1,1,1,-1]这个情况
        
        方法三: O(2/3 * N)
            在方法二的基础上，从左往右找前缀和等于k的,游标为l，
            然后从右往左找前缀和等于k的，游标为r， 如果l<r 那么就说明可以分成三个和相等的子数组
*/

class Solution1 {
public:
    bool canThreePartsEqualSum(vector<int>& A) {
        int right[A.size()+1];
        right[A.size()] = 0;
        for ( int i=(int)A.size()-1; i>=0; --i )
            right[i] = right[i+1] + A[i];
        unordered_set<int> mp;
        int s=0;
        for ( int i=0; i<A.size(); ++i ){
            s += A[i];
            if ( mp.count(s/2)>0 && i+1<A.size() && s/2 == right[i+1] )
                return true;
            mp.insert( s );
        }
        return false;
    }
};

class Solution2 {
public:
    bool canThreePartsEqualSum(vector<int>& A) {
        int acc=0, c=0, sums = accumulate(A.begin(), A.end(), 0);
        if ( sums%3!=0 ) return false;
        sums /= 3;
        for ( auto& d:A )
            if ( (acc+=d)==sums ){
                ++c; acc=0;
            }
        return c>=3;
    }
};

class Solution3 {
public:
    bool canThreePartsEqualSum(vector<int>& A) {
        int acc=0, c=0, sums = accumulate(A.begin(), A.end(), 0);
        if ( sums%3!=0 ) return false;
        sums /= 3;
        int l=0, sl=0, sr=0, r=(int)A.size()-1;
        while( l<A.size() && sl!=sums )sl += A[l++];
        --l;
        while( r>=0 && sr!=sums ) sr += A[r--]; 
        ++r;
        return l<r;
    }
};