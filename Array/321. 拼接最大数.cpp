/*
	题目描述：
		给定长度分别为 m 和 n 的两个数组，其元素由 0-9 构成，
		表示两个自然数各位上的数字。现在从这两个数组中选出 k (k <= m + n) 
		个数字拼接成一个新的数，要求从同一个数组中取出的数字保持其在原数组中的相对顺序。

		求满足该条件的最大数。结果返回一个表示该最大数的长度为 k 的数组。
	
	题目分析：
		和 #4 有点像，
		可以用分治来做。。把大问题化成子问题。。
		也就是
			1. 从nums1取出i个数，使得相对位置不变，且组成数最大
			2. 从nums2取出j个数，使得相对位置不变，且组成数最大
			3. i+j==k
			4. i个数和j个数合并起来，组成一个最大数
			5. 返回所有情况的最大的那个最大数。

		难点(具体在代码里说明)：
			1. 合并时要注意，相等的情况要详细讨论，而不是随机的选择。
			2. 子问题的解决:
				从nums1取出i个数，使得相对位置不变，且组成数最大
				
*/

class Solution {
public:
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        //分治
        vector<int> a;
        vector<int> b;
        vector<int> res;
        for( int v=0; v<=k; ++v ){
            if (v<=nums1.size() && k-v<=nums2.size()){
				//子问题
                a = helper(nums1,v);
                b = helper(nums2,k-v);
                //合并
				a = Merge(a,b);
                //更新最大
				res = Max_one(res,a);
            }
        }
        return res;
    }

    vector<int> Max_one(vector<int> a,vector<int> b){
        if ( a.size()!=b.size() ){
            return (a.size()>b.size())?a:b;
        }
        for ( int i=0; i<a.size(); ++i ){
            if ( a[i]>b[i] ) return a;
            else if ( a[i]<b[i] ) return b;
        }
        return a;
    }
    
    vector<int> helper(vector<int>& nums,int k){
        // nums中选k个元素组成一个最大数，相对位置不变
        if(k>=nums.size()) return nums;
		// res表示返回的vector，里面是当前组成的最大数，且在nums中的相对位置不变
        vector<int> res(k,0);
		// i是遍历Nums的游标， j是指向res的游标
        for ( int i=0,j=0; i<nums.size(); ++i ){
			/*
				①. 在接下来还有足够的数量的元素来存入res的情况下( k-j<nums.size()-1 来保证 )
				②. 每次都更新res，使得res里的前j个元素都是当前最优的(即长度为j时组成的元素是最大的)
				
				当遇到当前的nums[i], 就在满足①的条件下，把nums[i]放到合适的位置
				(res一定是递减的)，所以就从后向前比较，找到首个元素e比nums[i]大或相等的时候，就放到e的后面
			*/
            while( j>0 && k-j<nums.size()-i && res[j-1]<nums[i] ) j--;
            if ( j<k )  //如果当前j是满的，就不用放了。
                res[j++] = nums[i];
        }
        return res;
    }
    
	//合并
    vector<int> Merge(vector<int> &a, vector<int> & b){
        vector<int> res;
        int i=0,j=0;
        while( i<a.size() && j<b.size() ){
			/*
				看下面这个情况：
					nums1: 2 0
					nums2: 2 0 1
					
					当元素相等时，如果是随机选一个元素，那么会有两种情况：
					2 2 0 1 0
					2 2 0 0 1 
					
					显然前者才是最大的，但如果在相等的情况随机选的话，有可能会选到后者，
					所以要讨论元素相等情况，方便起见就写一个比较函数
					
					如果a>b即，greater(a,b)==true 时，就放入a，否则就放入b
			*/
            if ( greater(a,i,b,j) ){
                res.push_back(a[i++]);
            }else res.push_back(b[j++]);
        }
        while( i<a.size() )
            res.push_back(a[i++]);
        while( j<b.size() )
            res.push_back(b[j++]);
        return res;
    }
	
	
    /*
		看下面这个情况：
			nums1: 2 0
			nums2: 2 0 1
			
			当元素相等时，如果是随机选一个元素，那么会有两种情况：
			2 2 0 1 0
			2 2 0 0 1 
			
			显然前者才是最大的，但如果在相等的情况随机选的话，有可能会选到后者，
			所以要讨论元素相等情况，方便起见就写一个比较函数
			
			如果a>b即，greater(a,b)==true 时，就放入a，否则就放入b
	*/
    bool greater(vector<int>& a,int i, vector<int> &b,int j){
		//过滤掉所有相等情况
        while( i<a.size() && j<b.size() && a[i]==b[j] ){
            i++;
            j++;
        }
		/*
			两种情况下选a：
				1. i和j是因为不同而跳出循环，这个时候，如果a[i]比较大，那么就选a[i]
				（这个情况好理解就不举例子了）
				
				2. i和j是因为j先到头了才跳出循环的，这个时候b[j]已经不存在，那么就选a[i]
				还是刚才的例子：
					a: 2 0 1
					b: 2 0 
				当i和j都为2的时候， b[2]不存在，a[2]是1， 这个情况下我们希望得到22010，那么就要优先选a[i]
		
		*/
        return (j==b.size()) || (i<a.size() && a[i]>b[j]); 
    }
};