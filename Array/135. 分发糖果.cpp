/*
	题目描述：
		老师想给孩子们分发糖果，有 N 个孩子站成了一条直线，老师会根据每个孩子的表现，预先给他们评分。

		你需要按照以下要求，帮助老师给这些孩子分发糖果：

			1. 每个孩子至少分配到 1 个糖果。
			2. 相邻的孩子中，评分高的孩子必须获得更多的糖果。
			
	题目分析：
		方法一：
                时间O(N), 空间O(N)
                第一次遍历先找到极小值(比左右都小)，
                找到极小值以后：
                    1. 更新以当前元素为结尾的左边的严格单调减区间
                    2. 更新以当前元素为起始的右边的严格单调增区间
                
                第二次遍历更新极大值(比左右都大的元素)，取最大然后加一
                
        方法二：
            greedy 跟法一差不多，不过是正着来一遍，然后反着来一遍
*/


class Solution1 {
public:
    int candy(vector<int>& ratings) {
        /*
            方法一：
                时间O(N), 空间O(N)
                第一次遍历先找到极小值(比左右都小)，
                找到极小值以后：
                    1. 更新以当前元素为结尾的左边的严格单调减区间
                    2. 更新以当前元素为起始的右边的严格单调增区间
                
                第二次遍历更新极大值(比左右都大的元素)，取最大然后加一
        */
        if ( ratings.size()<1 ) return 0;
        if ( ratings.size()<2 ) return 1;
        vector<int> candy(ratings.size(),0);
        int n = ratings.size();
        
        int l,r;
        for ( int i=0; i<ratings.size(); ++i ){
            if (!candy[i] && (i==0 || ratings[i]<=ratings[i-1]) && (i==n-1 ||ratings[i]<=ratings[i+1] )){
                candy[i]=1; 
                //更新左边
                l=i-1;
                while( l>=0 && ratings[l]>ratings[l+1] ){
                    candy[l] = candy[l+1] + 1;
                    l--;
                }
                r = i+1;
                while( r<n && ratings[r]>ratings[r-1] ){
                    candy[r] = candy[r-1] + 1;
                    r++;
                }
            }
        }
        
        //第二轮更新极大值
        for ( int i=1; i<n-1; ++i ){
            if ( ratings[i]>ratings[i-1] && ratings[i]>ratings[i+1] )
                candy[i] = max(candy[i-1],candy[i+1])+1;
        }
        
        int res =0;
        for( int e:candy ){
            res+=e;
        }
        return res;
    }   
};




class Solution2 {
public:
    int candy(vector<int>& ratings) {
        /*
             
            方法二：
                greedy 跟法一差不多，不过是正着来一遍，然后反着来一遍
        */
        vector<int> candy(ratings.size(),1);
        for( int i=0; i<n-1; ++i )
            if ( ratings[i+1]>ratings[i] ) 
                candy[i+1] = candy[i]+1;
        for ( int i=n-1; i>0; --i )
            if ( ratings[i-1]>ratings[i] && candy[i-1] < candy[i]+1 )
                candy[i-1] = candy[i]+1;
        int res =0;
        for( int e:candy ){
            res+=e;
        }
        return res;
    }
    
    
};