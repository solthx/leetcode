/*
    问题描述:
        给定二维空间中四点的坐标，返回四点是否可以构造一个正方形。

        一个点的坐标（x，y）由一个有两个整数的整数数组表示。

        示例:

        输入: p1 = [0,0], p2 = [1,1], p3 = [1,0], p4 = [0,1]
        输出: True
         

        注意:

        所有输入整数都在 [-10000，10000] 范围内。
        一个有效的正方形有四个等长的正长和四个等角（90度角）。
        输入点没有顺序。

    问题分析:
        证明四条边的距离相等就行。 

        两个比较好的思想:
            1. 因为存在垂直，所以点的距离可以用平方表示， 可以用勾股定理来做( 即向量模的平方 )
            2. 任意两个点做差， 可以得到6个向量( 其中两个是对角线一定比边长 )， 因此，计算出所有情况后，排序，前4个元素最小的就是四条边.
            这就是穷举的思想, 即穷举出所有情况，然后利用不同情况之间的关系来做区分.  适合于所有情况可以穷举出来的情况.
        
        记得排除点重叠的情况
*/

class Solution {
    public boolean validSquare(int[] p1, int[] p2, int[] p3, int[] p4) {
        int []arr = new int[6];
        arr[0] = getDistance( p1, p2 );
        arr[1] = getDistance( p1, p3 );
        arr[2] = getDistance( p1, p4 );
        arr[3] = getDistance( p2, p3 ); 
        arr[4] = getDistance( p2, p4 );
        arr[5] = getDistance( p3, p4 );
        Arrays.sort(arr);
        //return arr[0]!=0 && arr[1]==arr[2] && arr[2]==arr[3] && arr[0]==arr[1] && arr[4]>arr[0] && arr[5]>arr[0];
        return arr[0]!=0 && arr[0]==arr[3] && arr[4]==arr[5] && arr[3]!=arr[4];  // 更少的判断条件
    }
    

    // 计算两点距离
    private int getDistance( int [] a, int[] b ){
        a = vecSub(a,b);
        return a[0]*a[0] + a[1]*a[1];
    }
    
    private int [] vecSub( int [] a, int [] b ){
        return new int[]{ b[0]-a[0], b[1]-a[1] };
    }
    
}