"""
    问题描述:
        在二维平面上计算出两个由直线构成的矩形重叠后形成的总面积。
        每个矩形由其左下顶点和右上顶点坐标表示，如图所示。

        示例:

            输入: -3, 0, 3, 4, 0, -1, 9, 2
            输出: 45
            说明: 假设矩形面积不会超出 int 的范围。

    问题分析:
        虽然可以先离散坐标然后用扫描线来做。。但有些小题大做。。
        这里只介绍计算两个矩形的并面积。。 扫描线的方法可以参考: https://github.com/solthx/leetcode/blob/master/Tree/Segment%20Tree/850.%20%E7%9F%A9%E5%BD%A2%E9%9D%A2%E7%A7%AF%20II.cpp

        计算出两个矩形的面积然后减去重合的部分的面积就可以了.
        本题介绍了计算iou的方法 (就是矩形重合的那个部分)
        
        计算重合部分的方法就是:
            1. 重合面积的宽:
                max( 0 , 两个矩形的右竖边的横左边最小值 - 两个矩形左竖边的横坐标最大值 )

            2. 重合面积的高:
                max( 0, 两个矩形上横边的最小纵坐标 - 两个矩形下横边的最大纵坐标 )

            3. 宽 X 高
"""
class Solution(object):
    def computeArea(self, A, B, C, D, E, F, G, H):
        a = (C-A)*(D-B)
        b = (G-E)*(H-F)
        x = max(0,min(C,G)-max(A,E))
        y = max(0,min(D,H)-max(B,F))
        area = a+b-x*y
        return area