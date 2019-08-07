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
            树状数组。
            对于求逆序对的个数问题，也可以使用树状数组来做。。
            主要思想就是：
                1. 通过i从大到小遍历的顺序来满足i<j, 也就是当前遍历到的nums[i]
            是在 "nums[i]<nums[j]"中的更小的那个元素。
                2. 通过一个count数组，来保存已经遍历过的元素的个数(也就是nums[j])，
            因为是逆向遍历，j属于(i,n) ， 然后遍历到nums[i]的时候， count数组里的nums[i]
            的前缀和就是 在nums[i]右边的比nums[i]小的元素的个数.


            而树状数组主要就是用于 "单点修改, 区间查询" 正好满足本题条件，
            用树状数组的思想来建立前面说到的count数组  
 */

class Solution1 {
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




class Solution2 {
private:
    vector<int> tree_arr;   
    int lowbit(int x){ return x&(-x); }   
    void add(int idx, int val){
        int n=tree_arr.size();
        while( idx<tree_arr.size() ){
            tree_arr[idx] += val;
            idx += lowbit(idx);
        }
    }  
    int pre_sum( int idx ){
        int res=0;
        while( idx>0 ){
            res += tree_arr[idx];
            idx -= lowbit(idx);
        }
        return res;
    }   
public:
    vector<int> countSmaller(vector<int>& nums) {
        // 树状数组
        if ( nums.size()<=0 ) return {};
        int maxi = nums[0], mini = nums[0];
        for ( auto e:nums )
            if ( e>maxi ) maxi = e;
            else if ( e<mini ) mini = e;
        int n = maxi - mini + 2;  //个数是maxi-mini+1 , 又因为要从0开始，所以再+1
        tree_arr.resize(n,0);
        vector<int> res(nums.size());
        for ( int i=nums.size()-1 ; i>=0; --i ){
            //cout<<i<<endl;
            res[i] = pre_sum( nums[i] - mini );
            add( nums[i] - mini + 1, 1 );
        }
        
        return res;
    }
};
