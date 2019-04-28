/*
	题目描述：
		给一个数组，找出这个数组中在"有序"的情况下，相邻两个元素之间的最大差值
		
	问题分析：
		方法一：
			先排序，再遍历的找。。不过这是道hard题，这肯定不是最优解
			
		方法二：
			桶排序O(N)
			
			以下是个人对桶排序的理解：
				使用桶排序时，我们首先要决定两个事情：
					1. 桶的index的含义
					2. 桶里存什么
				
				以最简单的桶排序为例： 我们把元素的值当作index，然后
				在桶里存这个值的出现次数，最后按序输出。
				
				而本题如果用最原始的桶排序，那将并不是O(N),而是O(max(N,K)),K是nums[i]的取值范围
				显然当N很小，K很大时，很不划算（比如[999999999,999999999999]）
				
				这时候我们就要对取值范围进行缩放，这个缩放方法就是一个难点（不然怎么是hard
				
				数组里遇到这种求什么什么的最值的时候，可以注意一下这个最值的【取值范围】
				本题中，这个差最大的情况就是最大值maxi和最小值的mini差，此时n=2
				最小值则一定不会小于 avg = ceil((maxi-mini)/(n)) （用反证法很好证明）
				
				然后看这个取值范围(maxi-mini)内能分成几个这样的avg， 个数就是桶的大小。
				
				把大区间(maxi-mini)变成了 多个小区间avg，
				而最大的差值肯定被存在两个相邻的桶之间(不包括空桶)
				
				所以：
					桶的index就是对应的第几个avg，可以通过 (nums[i]-mini)/(avg) 来得到
					第i个桶里存的东西，就是所有落在在第i个小区间avg内的最小值与最大值
					
					假如q桶是p桶后面一个非空的桶(p在前,q在后，pq相邻(不包括空桶·的相邻))
					那么 max( q.min-p.max ) 就是最大的差值了。。
					
				写程序的时候，可以使用pair<int,int >来记录第i个avg区间(也就是第i个桶)内的
				最大最小值
				
				first 存最大，
				second 存最小
				
				注意，还要处理一些特殊情况，例如 所有数全是相同的数，这个时候avg就是0
				
*/
class Solution1 {
public:
    int maximumGap(vector<int>& nums) {
        /*
			先排序，再找O(NlogN)
		*/
		if ( nums.size()<2 ) return 0;
        sort(nums.begin(),nums.end());
        int res=0;
        for ( int i=1; i<nums.size(); ++i )
            res = max( nums[i]-nums[i-1],res );
        return res;
        
    }
};

class Solution2 {
public:
    int maximumGap(vector<int>& nums) {
        //桶排序O(N)
        if ( nums.size()<2 ) return 0; 
        int maxi,mini,n=nums.size();
        maxi=mini=nums[0];
        for(int e:nums){
            if (e<mini) mini=e;
            else if(e>maxi) maxi =e;
        }
        int where,  avg = (maxi-mini)/n;
		//所有数都相同，avg区间最小为1
        if ( avg==0 ) avg++;
        int bucket_size = (maxi-mini)/avg +1 ;
        if ( bucket_size==0 ) return 0;
        //pair<最大，最小>
        vector<bool> visited(bucket_size,false);
        vector<pair<int,int>> bucket(bucket_size,make_pair(0,0));
        for ( int e:nums ){
            where = (e-mini)/avg;
            if ( visited[where] ){ //非首次访问
                if ( e>bucket[where].first )
                    bucket[where].first = e;
                else if ( e<bucket[where].second )
                    bucket[where].second = e;
            }else{
                bucket[where].first = bucket[where].second = e;
                visited[where] = true;
            }
        }
        int res=0,pre=0;
        for ( int i=1; i<bucket_size; ++i ){
            if ( visited[i] ){
                res = max( bucket[i].second - bucket[pre].first, res );
                pre = i;
            }
        }
        return res;
    }
};