/*
    问题描述：
        给定一个整数数组 nums，按要求返回一个新数组 counts。数组 counts 
        有该性质： 
            counts[i] 的值是  nums[i] 右侧小于 nums[i] 的元素的数量。

    问题分析:
        方法一:
            分治归并，因为在排序的过程中会打乱相对顺序，故用pair来保存前缀和的值和
            其对应的最开始的位置，这样就可以把 sums[i]计算得到的个数放到原先未被打乱顺序的最开始的的位置上.
            尽管用这个方法写过去了。。但感觉这个办法还是不够优雅。。

        方法二:
            感觉单调栈+树状数组也可以做。。下次再写吧。。
 */

 class Solution {
public:
    vector<int> countSmaller(vector<int>& num) {
        vector<pair<int,int>> tmp(num.size());
        vector<int> res(num.size(),0);
        
        vector<pair<int,int>> nums(num.size(),{0,0});
        for ( int i=0; i<nums.size(); ++i ){
            nums[i].first = i;
            nums[i].second = num[i];
        }
        
        helper( res, 0, nums.size()-1, nums, tmp );
        return res;
    }
    
    void helper( vector<int> & res, int l, int r, vector<pair<int,int>> & nums, vector<pair<int,int>> & tmp ){
        if ( l<0 || r>=nums.size() || l>=r ) return ;
        int mid = (r+l)/2;
        helper( res, l, mid, nums, tmp );
        helper( res, mid+1, r, nums, tmp );
        int start,end=r;
        // [l,mid] (mi,r]
        // 计算大于xx的个数
        for ( start=mid; start>=l; --start ){
            while( end>mid && nums[end].second>=nums[start].second ) --end;
            // 放到合适位置
            if ( end>mid && nums[end].second<nums[start].second )
                res[nums[start].first] += ( end-mid );
        }
        // 归并
        int k=0, a=l, b=mid+1;
        while( a<=mid && b<=r ){
            if ( nums[a].second<=nums[b].second )
                tmp[k++] = nums[a++];
            else tmp[k++] = nums[b++];
        }
        while( a<=mid )
            tmp[k++] = nums[a++];
        while( b<=r )
            tmp[k++] = nums[b++];
        for ( int t=0; t<k; ++t )
            nums[t+l] = tmp[t];
    }

};

