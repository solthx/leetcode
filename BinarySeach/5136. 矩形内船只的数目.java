/*
    问题描述:
        (此题是 交互式问题 )

        在用笛卡尔坐标系表示的二维海平面上，有一些船。每一艘船都在一个整数点上，且每一个整数点最多只有 1 艘船。

        有一个函数 Sea.hasShips(topRight, bottomLeft) ，输入参数为右上角和左下角两个点的坐标，当且仅当这两个点所表示的矩形区域（包含边界）内至少有一艘船时，这个函数才返回 true ，否则返回 false 。

        给你矩形的右上角 topRight 和左下角 bottomLeft 的坐标，请你返回此矩形内船只的数目。题目保证矩形内 至多只有 10 艘船。

        调用函数 hasShips 超过400次 的提交将被判为 错误答案（Wrong Answer） 。同时，任何尝试绕过评测系统的行为都将被取消比赛资格。

         

        示例：

            有图:
                https://leetcode-cn.com/problems/number-of-ships-in-a-rectangle/

        输入：
        ships = [[1,1],[2,2],[3,3],[5,5]], topRight = [4,4], bottomLeft = [0,0]
        输出：3
        解释：在 [0,0] 到 [4,4] 的范围内总共有 3 艘船。
         

        提示：

        ships 数组只用于评测系统内部初始化。你无法得知 ships 的信息，所以只能通过调用 hasShips 接口来求解。
        0 <= bottomLeft[0] <= topRight[0] <= 1000
        0 <= bottomLeft[1] <= topRight[1] <= 1000

    问题分析:
        难度适中的二分查找的题, 虽然一次过, 但题目本身感觉不错。 时间充裕的话可以重写下本题. 
*/

/**
 * // This is Sea's API interface.
 * // You should not implement it, or speculate about its implementation
 * class Sea {
 *     public boolean hasShips(int[] topRight, int[] bottomLeft);
 * }
 */

class Solution {
    public int countShips(Sea sea, int[] topRight, int[] bottomLeft) {
        // 两次二分查找 logN * logN
        int l=bottomLeft[0], r=topRight[0];
        int down = bottomLeft[1], up = topRight[1];
        int res = 0;
        while( l<=r ){
            int mid,i=l,j=r;
            while( i<j ){
                mid = (i+j)/2;
                if ( sea.hasShips( new int[]{mid,up}, new int[]{i,down}) ){
                    // 说明这个区间里有
                    j = mid;
                }else i = mid+1; // 说明左边没有
            }
            int botm = down, top = up;
            while( botm<=top ){ 
                int lo = botm , hi = top;
                while( lo<hi ){
                    mid = (lo+hi)/2;
                    if ( sea.hasShips( new int[]{i,mid},new int[]{i,lo}) ){
                        // 在下面
                        hi = mid;
                    }else lo = mid+1;
                }
                if ( sea.hasShips( new int[]{i,lo},new int[]{i,hi}) )
                    ++res;
                botm = lo + 1;
                top = topRight[1];
            }
            l = i+1;
            r = topRight[0];
        }
        return res;
    }
}