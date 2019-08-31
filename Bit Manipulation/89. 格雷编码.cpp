/*
    问题描述:
        实现格雷编码， 就是相邻两个数的二进制的严格只能有一位不同, 即距离为1
    
    问题分析:
        方法一: mirrors方法
            假设已经得到了长为n-1的格雷编码的序列为S,
            那么 0 + S 就是长为n的格雷编码的前1/2
                1 + S 就是长为n的各类编码的后1/2
            对于顺序的选择，
              0 + 01 = 001
              0 + 11 = 011
              0 + 10 = 010
              1 + ?? = 1??
            因为S内部，相邻元素的二进制距离已经是严格为1了，

            在前缀从0变成1的这一个边界，
            前缀发生了改变，因此，后缀必须相等，
            也就是后1/2个序列的第一个元素，和前1/2个序列的最后一个元素必须距离为0，也就是相等，
            即使:
                ...
                0+10=010
                1+10=110
                ...
            所以长为n的格雷编码可以根据长为n-1的格雷编码生成，
            即:
                0 + S[0]
                0 + S[1]
                ...
                0 + S[n-1]
                1 + S[n-1]
                1 + S[n-2]
                ...
                1 + S[0]

        方法二:
            公式生成:
                for i from 0 to 2^n:
                    res.push_back( i ^ (i>>1) )
*/

class Solution1 {
public:
    //mirror方法
    vector<int> grayCode(int n) {
        if ( n==0 ) return {0};
        vector<int> res{{0,1}};
        for ( int i=2; i<=n; ++i ){
            int tag = 1<<(i-1);
            int j=res.size()-1;
            while( j>=0 ){
                res.push_back( res[j]+tag );
                --j;
            }
        }
        return res;
    }
};

class Solution2 {
public:
    // 公式法
    vector<int> grayCode(int n) {
        vector<int> res;
        for ( int i=0; i<(1<<n); ++i )
            res.push_back( i^(i>>1) );
        return res;
    }
};2
