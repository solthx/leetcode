/*
    问题描述：
        给定一个非负整数 N，找出小于或等于 N 的最大的整数，同时这个整数需要满足其各个位数上的数字是单调递增。

        （当且仅当每个相邻位数上的数字 x 和 y 满足 x <= y 时，我们称这个整数是单调递增的。）

        示例 1:

        输入: N = 10
        输出: 9
        示例 2:

        输入: N = 1234
        输出: 1234
        示例 3:

        输入: N = 332
        输出: 299
        
        说明: N 是在 [0, 10^9] 范围内的一个整数。

    问题分析:
        方法一:
            枚举+二分. 这种递增的数的个数也就 10!个, 大概30W+? 
            全枚举出来以后再进行二分.. 

        方法二:
            贪心. 

            一旦存在 前一位比当前位大的情况 , 就对前一位-1， 然后记录下这一位的位置， 这一位之后的所有数用9来补充

            例1:
                790 -> 780 -> 780 , 记录的位置为第二位

                填充9， 第二位之后的所有元素都改成9 
                    -> 789 
            
            例2:
                332 -> 322 -> 222 , 记录位置为第一位
                填充9，第一位之后的所有元素都改成9
                    -> 299 √
*/


// 枚举出所有情况然后二分
class Solution1 {
    private ArrayList<Integer> arr = new ArrayList<>();
    public int monotoneIncreasingDigits(int N) {
        for ( int i=9; i>=1; --i )
            dfs( i );
        Collections.sort(arr);
        int l = 0, r=arr.size()-1,mid;
        while( l<=r ){
            mid = l + (r-l)/2;
            if ( arr.get(mid)>N ) r = mid -1;
            else if ( arr.get(mid)<N ) l = mid+1;
            else return N;
        }    
        return arr.get(r);
    }

    private void dfs( int d ){
        int pre = d%10;
        arr.add(d);
        for ( int t = pre; t<=9; ++t ){
            if ( d> (1000_000_000-t)/10 + (1000_000_000-t)%10 ) continue;
            dfs( d*10+t );
        }
    }
}

// 贪心
class Solution2 {
    public int monotoneIncreasingDigits(int N) {
        String s = String.valueOf(N);
        char [] ch = s.toCharArray();
        boolean res = true;
        int j=s.length();
        for ( int i=ch.length-1 ; i>0; --i  )
            if ( ch[i]<ch[i-1] ){
                ch[i-1]--;
                j = i;
            }
        for ( int i=j; i<s.length(); ++i )
            ch[i] = '9';
        return Integer.parseInt(new String(ch));
    }
}