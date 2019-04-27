
/*
	题目描述：
		heights[]的每一个元素表示石头高度，下了一场雨之后，坑中水的体积为多少。（打开网页来看图更好理解）
	
	问题分析：
		方法一：
			暴力层序遍历，一层一层来看有多少是水，多少是石头，O(N*K) K为最大高度，超时T_T
		
		方法二：
			不再从区间考虑，而是从单个柱状单元考虑，
			在第i个位置上，如果左边的最高值和右边的最高值都比当前
			柱状单元要高，那么当前单元肯定是可以积水的，积水体积为
			min(left_highest, right_highest) - cur_height 
			因此我们开两个数组，分别记录每个单元的左右边的最高值
        
		方法三：
			核心思想和方法二一样，利用双指针，从空间上进行了优化
    
		方法四：
			核心思想变化不大，维护一个非递减栈主要栈空或者当前元素
            小于等于栈顶元素就入栈。当当前元素大于栈顶元素时，
            若站内元素大于一个，那么就把栈顶元素当作“坑”，
            倒数第二个元素为左边界（因为是非递减，倒数第二个大于等于倒数第一个）
            这里的计算方法还有些不同，那就是算的是面积(宽可能会大于1)而不是单个单元（宽固定为1）
*/


class Solution1 {
public:
    int trap(vector<int>& height) {
        //超时解法O(N*H)
		//层序遍历
        if ( height.size()<2 ) return 0;
        int left,cnt=0,right,l,max_height = height[0];
        for ( int e:height )
            max_height = max(max_height,e);
        
        int res=0;
        for ( int h=1; h<=max_height; ++h ){
            left = -1;
            right=-1;
            cnt=0;
            for ( int i=0; i<height.size(); ++i ){
                if ( height[i]>=h ){
                    if ( left<0 ) left = i;
                    cnt++;
                    right = i;
                }
            }
            if ( left!=right )
                res += ( right-left+1-cnt );
        }
        return res;
};

class Solution2 {
public:
    int trap(vector<int>& height) {
		
        if ( height.size()<2 ) return 0;
        /*法二：不再从区间考虑，而是从单个柱状单元考虑，
          在第i个位置上，如果左边的最高值和右边的最高值都比当前
          柱状单元要高，那么当前单元肯定是可以积水的，积水体积为
          min(left_highest, right_highest) - cur_height 
          因此我们开两个数组，分别记录每个单元的左右边的最高值
        */
        int l,r,res = 0,h,maxi=-1,n = height.size(); 
        vector<int> left_highest(n,0);
        vector<int> right_highest(n,0);
        for ( int i=0; i<n; ++i ){
            left_highest[i] = maxi;
            maxi = max( maxi, height[i] );
        }
        maxi = -1;
        for ( int i=0; i<n; ++i ){
            right_highest[i] = maxi;
            maxi = max( maxi, height[n-i-1] );
        }
        for ( int i=0; i<n; ++i ){
            l = left_highest[i];
            r = right_highest[n-i-1];
            h = min(l,r);
            if ( h>height[i] ) res += ( h-height[i] );
        }
        return res;
      
};

class Solution3 {
public:
    int trap(vector<int>& height) {
		
        if ( height.size()<2 ) return 0;
        /*
            方法三：
                核心思想和方法二一样，利用双指针，从空间上进行了优化
        */
        int mini,res=0,l=0,r=height.size()-1;
        while( l<r ){
            mini = min( height[l],height[r] );
            if ( height[l]<height[r] ){
                l++;
                while( l<r && height[l]<mini ) 
                    res += ( mini-height[l++] );
            }else{
                r--;
                while( l<r && height[r]<mini )
                    res += (mini-height[r--]);
            }
        }
        return res;
};

class Solution4 {
public:
    int trap(vector<int>& height) {
        /*
            方法四：核心思想变化不大，维护一个非递减栈主要栈空或者当前元素
            小于等于栈顶元素就入栈。当当前元素大于栈顶元素时，
            若站内元素大于一个，那么就把栈顶元素当作“坑”，
            倒数第二个元素为左边界（因为是非递减，倒数第二个大于等于倒数第一个）
            
            这里的计算方法还有些不同，那就是算的是面积(宽可能会大于1)而不是单个单元（宽固定为1）
        */
        stack<int> s;
        int i=0,pit,res=0,h;
        while( i<height.size() ){
            while( s.size()>0 && height[s.top()]<height[i] ){
                pit = s.top();
                s.pop();
                if ( s.size()==0 ) break;
                h = min(height[i],height[s.top()]); 
                res += ( (h-height[pit])*(i-s.top()-1) );
            }
            
            s.push(i++);
        }
        return res;
    }
};