/*
    题目描述：
        按大小顺序列出所有排列情况，并一一标记，当 n = 3 时, 所有排列如下：
            "123"
            "132"
            "213"
            "231"
            "312"
            "321"
        给定 n 和 k，返回第 k 个排列。
    
    题目分析：
        每次确定当前位置应该放几，
        从{1,2,3,4,5,6,7,8,9}这个集合里选，
        选到一个删除一个，
        选的时候根据k的大小来选，
        len为当前排列的剩余长度 (初始为n)
        i = k / (len-1)!
        选中第i个元素后，删除第i个元素
        ，然后确定下一个位置应该放几
 */


class Solution {
    public String getPermutation(int n, int k) {
        int [] book = new int[10];
        for ( int i=0; i<=9; ++i )
            book[i] = i;
        return helper( n, k, book );
    }
    
    private String helper( int n, int k, int [] book ){
        if ( n==0 ) return "";
        int idx=1, val;
        int fac = Fac(n-1);
        while( k>fac ){
            k-=fac;
            idx++;
        }
        // k<=fac
        val = book[idx];
        return Integer.toString(val) + helper( n-1, k, Remove(book, idx) );
    }
    
    int [] Remove(int [] book, int idx){
        int i=0,j=0;
        int [] res = new int[book.length-1];
        while( j<book.length ){
            if ( j!=idx ){
                res[i++] = book[j++];
            }else ++j;
        }
        return res;
    }
    
    int Fac(int n){
        if ( n<=1 ) return 1;
        return Fac(n-1) * n;
    }
    
}