/*
	题目描述：
		给定一个无序的数组 nums，将它重新排列成 nums[0] < nums[1] > nums[2] < nums[3]... 的顺序。
		
		示例 1:
		输入: nums = [1, 5, 1, 1, 6, 4]
		输出: 一个可能的答案是 [1, 4, 1, 5, 1, 6]
		
		示例 2:
		输入: nums = [1, 3, 2, 2, 3, 1]
		输出: 一个可能的答案是 [2, 3, 1, 3, 1, 2]

	题目分析：
		方法一：
			比摆动排序(一)更难的地方就是加了一个限制，相邻元素不能够相等，
			这样的话，如果还是按照摆动排序(一)就会出错。
			
			这里的想法是分为三个步骤：
				1. 确定中位数medium 
				2. 元素聚集， 使得所有和medium的元素都相邻！  （如： 1 3 2 4 4 4 4 9 10 5 7 , 4是中位数）
				3. 插回原数组， 因为medium的确定已经分出了两堆，
					考虑到medium的重复，经过元素聚集之后，medium在右区间中就是最小值，在左区间中就是最大值
					所以为了防止相同元素的相邻，插入的时候，尽量让medium在两边，
					
					令小于m的数同一看作为l, 大于m的的统一看作为r， m是medium
					（注意，l和r是一个标识，而不是具体的数）
					
		经过1和2处理后的数组： l l l m m m m m m m r r r r 
					
					插入： 	  r   r   r   r   m   m   m  
							m   m   m   m   l   l   l
					
					最后：  m r m r m r m r l m l m l m  
		
		方法二：
			排序后按照上面的插入方法插入。
			
*/

class Solution1 {
public:
    void wiggleSort(vector<int>& nums) {
        /*
            用快排思想找到中位数，
            再把中位数右边的每一个数插入到左边
        */
        int i,j,n=nums.size();
        int mid = (n-1)/2;
        if ( nums.size()<2 ) return ;
        vector<int> tmp(nums.begin(),nums.end());
     
        //找中位数
        Kth_element(tmp, mid+1, 0, n-1);
        
        //元素聚集，若存在多个和中位数相同的元素，就把它们聚集到中位数旁边
        gather_medium(tmp,mid);
    
        //策略，相同的放两边
        i = n-1;
        for ( j=1; i>mid && j<nums.size(); --i ,j+=2 )
            nums[j] = tmp[i];
        for ( j=0,i=mid; i>=0 && j<nums.size() ; j+=2, i-- )
            nums[j] = tmp[i];
       
    }
    
private:
    int Kth_element(vector<int>& nums, int k,int lo,int hi){
        swap(nums[lo],nums[(lo+hi)/2]);
        int key = nums[lo];
        int rank;
        int l=lo,r = hi;
        while( l<r ){
            while( l<r && nums[r]>key ) r--;
            if ( l<r ) swap(nums[l++],nums[r]);
            while( l<r && nums[l]<=key ) l++;
            if ( l<r ) swap(nums[l],nums[r--]);
        } 
        nums[l] = key;
        rank = l-lo+1;
        if ( rank == k ) return key;
        else if ( rank<k ) return Kth_element(nums, k-rank, l+1,hi);
        else return Kth_element(nums, k, lo, l-1);
    }
    
    void gather_medium(vector<int>& nums,int mid){
        int l,r,medium = nums[mid];
        l = 0;
        r = mid-1;
        while( l<r && nums[r]==medium ) r--;
        while( l<r ){
            if ( nums[l]==medium ) swap(nums[l++],nums[r--]);
            else l++;
        }
        l = mid+1;
        r = nums.size()-1;
        while( l<r && nums[l]==medium ) l++;
        while( l<r ){
            if ( nums[r]==medium ) swap(nums[r--],nums[l++]);
            else r--;
        }
    }
};


class Solution2 {
public:
    void wiggleSort(vector<int>& nums) {
        vector<int> tmp(nums.begin(),nums.end());
        sort(tmp.begin(),tmp.end());
        int i=1,j=nums.size()-1;
        for ( ;i<nums.size(); i+=2 )
            nums[i] = tmp[j--];
        for ( i=0; i<nums.size(); i+=2 )
            nums[i] = tmp[j--];
    }
};