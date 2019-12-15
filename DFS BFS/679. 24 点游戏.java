/*
    问题描述:
        你有 4 张写有 1 到 9 数字的牌。你需要判断是否能通过 *，/，+，-，(，) 的运算得到 24。
        示例 1:

        输入: [4, 1, 8, 7]
        输出: True
        解释: (8-4) * (7-1) = 24
        示例 2:

        输入: [1, 2, 1, 2]
        输出: False
        注意:

        除法运算符 / 表示实数除法，而不是整数除法。例如 4 / (1 - 2/3) = 12 。
        每个运算符对两个数进行运算。特别是我们不能用 - 作为一元运算符。例如，[1, 1, 1, 1] 作为输入时，表达式 -1 - 1 - 1 - 1 是不允许的。
        你不能将数字连接在一起。例如，输入为 [1, 2, 1, 2] 时，不能写成 12 + 12 。

    问题分析:
        方法一:
            全排列+分治: 复杂度O( N! * N^2 * logN )
            
            最直观的想法是使用分治的方法, 即计算 [0,i], [i+1, n) 这两个区间通过加减乘除所得到的所以情况，
            然后再根据这两堆结果计算[0,n)的所以情况.. 

            但这样的话，取牌的顺序就已经确定了... 所以，我们可以先得到这4张牌的全排列，然后对每一种情况都使用上面的方法来计算，
            
            如果在遍历了全排列的每一种情况的加减乘除组合，最终都不能得到24这个数字，那么就返回-1
            
        方法二:
            TO DO...

*/

class Solution {
    private boolean [] vis = null;
    private int [] sav = null;
    private int top = 0;
    public boolean judgePoint24(int[] nums) {
        vis = new boolean[nums.length];
        sav = new int[nums.length];
        return dfs( nums );
    }

    // 复杂度O( N! * N^2 * logN )
    private boolean dfs( int [] nums){
        if ( top>=nums.length ){
            List<Double> ans = helper( 0 , nums.length-1 );
            for ( double d : ans ) 
                if ( Math.abs(d-24.0)<=1e-6 )
                    return true;
            return false;
        }
        boolean found = false, res = false;
        for ( int i=0; i<nums.length; ++i ){
            if ( vis[i]==false ){
                vis[i] = true;
                sav[top++] = nums[i];
                if ( dfs( nums ) ) return true;
                --top;
                vis[i] = false;
            }
        }
        return false;
    }

    private List<Double> helper( int l, int r ){
        List<Double> res = new ArrayList<>();
        if ( l>=r ){
            res.add((double)sav[l]);
            return res;
        }
        for ( int i=l; i<=r-1; ++i  ){
            List<Double> lv = helper(l, i);
            List<Double> rv = helper(i+1, r);
            for ( double a:lv )
                for ( double b:rv ){
                    res.add( a+b );
                    res.add( a-b );
                    res.add( a*b );
                    if ( Math.abs(b)>1e-6 )
                        res.add( a/b );
                }
        }
        return res;
    }
}