/*
    问题描述:
        给定一个数组 nums ，如果 i < j 且
        nums[i] > 2*nums[j] 我们就将 (i, j) 称作一个重要翻转对。

        你需要返回给定数组中的重要翻转对的数量。

    问题分析:
        其实还是求逆序对问题， 只不过 nums[i]<nums[j] 变成了 2*nums[i]<nums[j]。
        而求逆序对的个数是 分治，归并的重要应用。

        这里稍微多讲一下吧。

        使用分治解决问题的时候，主要难度在于处理中间情况,
        我们不希望用太高的复杂度来处理中间情况，
        
        归并排序可以使得左右区间变得有序( 但是要牺牲原所在数组的相对顺序， 尽管可以用pair来记录，不过那是后话了 )
        
        有序的左右区间可以使我们更快的处理中间情况。

        举个最常见的例子( 本题也属于这个例子 )
        就是当遇到关于 “连续区间和”的“值” 怎么怎么样的时候， 一般都是可以用分治归并。
        ( 一定要是值，而不能是长度，这个问题具体见 #1124 )

        因为连续区间的值，我们可以用前缀和来表示，
        然后对前缀和进行归并的话，我们可以在线性时间内处理中间情况，
        
        更具体的例子就是本题 和 #327

        顺便补充一点
        inplace_merge( sums.begin()+l, ..+mid, ..+r );
        处理的区间是 [l,mid), [mid,r)

        再有，自己手动实现归并的时候， 一开始就把临时数组tmp创建好作为参数，
        而不要每次都创建，这样能大幅度减少时间。

 */


 class Solution {
public:
    // 归并求解逆序对
    int reversePairs(vector<int>& nums) {
        vector<int> tmp( nums.size() ) ;
        return helper( 0, nums.size()-1, nums, tmp );
    }
    
    int helper( int l, int r, vector<int> & nums, vector<int> & tmp ){
        if ( l<0 || r>=nums.size() || l>=r ) return 0;
        int mid = (r+l)/2;
        int lr_cnt = helper( l, mid, nums, tmp ) + helper( mid+1, r, nums, tmp );
        int cnt=0, start,end;
        int j=l;
        // [l,mid] (mi,r]
        for ( int end=mid+1; end<=r; ++end ){
            while( j<=mid && nums[j]<= 2*(long long)nums[end] ) ++j;    
            if ( j<=mid && (long long)nums[j]>2*(long long)nums[end] ){
                cnt += ( mid-j+1 );
            }
        }
        // 704ms
        //inplace_merge( nums.begin()+l, nums.begin()+mid+1, nums.begin()+r+1 );
        // 1340ms
        //sort( nums.begin()+l, nums.begin()+r+1  );
        // TLE 每次都创建临时数组
        //Merge( l, mid, r, nums );
        
        // 208ms beats 100%
        int k=0, a=l, b=mid+1;
        while( a<=mid && b<=r ){
            if ( nums[a]<=nums[b] )
                tmp[k++] = nums[a++];
            else tmp[k++] = nums[b++];
        }
        while( a<=mid )
            tmp[k++] = nums[a++];
        while( b<=r )
            tmp[k++] = nums[b++];
        for ( int t=0; t<k; ++t )
            nums[t+l] = tmp[t];
        
        return cnt+lr_cnt;
    }
    
    /*void Merge( int l, int mid, int r, vector<int> & nums ){
        vector<int> tmp( nums.size() ) ;
        int k=0, i=l, j=mid+1;
        while( i<=mid && j<=r ){
            if ( nums[i]<=nums[j] )
                tmp[k++] = nums[i++];
            else tmp[k++] = nums[j++];
        }
        while( i<=mid )
            tmp[k++] = nums[i++];
        while( j<=r )
            tmp[k++] = nums[j++];
        for ( int t=0; t<k; ++t )
            nums[t+l] = tmp[t];
    }*/
    
    
};