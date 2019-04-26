/*
	问题描述：
		每个位置的值是高度，
		现取两个高度，组成一个水缸，问水缸最大容积
	问题解决：
		双游标，矮那一边的游标移动，水题
*/

class Solution {
public:
    int maxArea(vector<int>& height) {
        int i=0,j=height.size()-1; 
        int h,w,res = 0;
        while( i<j ){
            w = j-i;
            h = min(height[i],height[j]);
            res = max(res,w*h);
            if ( height[i]<height[j] ) i++;
            else --j;
        }
        return res;
    }
};