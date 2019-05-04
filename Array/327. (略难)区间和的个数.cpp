/*
	题目描述：
		给定一个整数数组 nums，返回区间和在 [lower, upper] 之间的个数，包含 lower 和 upper。
		区间和 S(i, j) 表示在 nums 中，位置从 i 到 j 的元素之和，包含 i 和 j (i ≤ j)。

	
	
	题目分析：
		本题使用分治来解决，即｛左子序列的情况，右子序列的情况，中间的情况｝
		本题难点：
			1. 	看到区间和，要有使用sums[i]的意识
				sums[i]从1开始记
				sums[i] - sums[j] 是区间(i,j] 的和
				
			2. 	使用分治的时候，处理的区间使用左闭右开的形式：[l,r)
			3. 	使用了分治，大多是O(NlogN)复杂度了，有时可以在分治的过程中加一些操作，
				来使得处理中间情况的时候更加高效！！
			
				例如本题，就是在分治的过程中对左右子序列进行了排序，才使得中间情况处理的复杂度变成O(N)
				
		divide(l,r) : 返回区间[l,r)满足条件的子区间个数。
		左子区间和右子区间中，满足条件的子区间个数为 ： divide(l,mid) + divide(mid,r) 
		中间情况： 
			1. 	根据左右两边的情况来确定中间情况：
					1.1 左区间[l,mid) 不存在mid
					1.2 右区间[mid,r) 因为 sum[i]-sum[mid] 是表示(mid,i]，所以其实也不存在mid
				所以中间情况就是： x∈[l,mid]，y∈[mid,r) , 求区间[x,y]满足条件的个数
				也就是求(x-1,y]满足条件的个数 ， 
				
				如果使用暴力的话： 中间情况的处理是(N/2)^2 ，依旧还是N^2（最后的那个超时解法就是暴力凉了。。）
				
	############接下来就是本题最大难点了。。
				首先，我们要知道我们要的是什么：在所有包含了nums[mid]的满足条件区间，
				也就是所有满足了下面这个条件的区间之中：
				
					( 以[l,mid)中任意一个元素为起始 && 以[mid,r)中任意一个元素为结尾的区间 )
				
				，找出满足条件的区间。
				
				（这里解释一下，因为sums[i]-sums[j]是区间(i,j]的和，所以可能会有疑问为什么不是[l-1,mid), 
				因为sums是从1开始记的，而l是从0开始的，本身就比idx要少了1，所以不用减一，就是[l,mid)）
				
				所以只要保证区间不变，打乱了排列的顺序也没关系（就像以{1,2,3,4}顺序搜索和{4,1,3,2}顺序搜索最后的结果一样）
				
				所以，我们就可以在分治的过程中，对mid两边的区间的sums进行排序，然后搜索满足条件的区间，
				这个时候，问题就变成了：
					sums在[l,mid)区间内有序，在[mid,r)区间内有序
					找出x∈[l,mid)，y∈[mid,r) ，使得 sums[y]-sums[x] 的取值范围落在[lower,upper]中
					
				这个时候就可以使用虫取法了(就是two pointer)
				下面是伪代码：
				p1 = p2 = l ;
				for end from mid to r-1 :  //以idx为end的元素来当作区间的结尾位置
					//因为减数是从小到大的，所以差的顺序就从大变小了，先找出首个小于等于upper的
					while( p1<mid && 区间(p1,end]的和>upper ) p1++;
					//找到首个小于等于upper的以后，再找出首个小于lower的位置
					while( p2<mid && 区间(p2,end]的和>=lower ) p2++;
					cnt += (p2-p1);  // [p1,p2)这个区间之间的元素个数就是落在区间[lower,upper]的个数
					
					因为end是从mid到r-1，所以sums[end]也是逐渐变大的，
					因此，之后的p1,p2一定是在当前p1,p2的右边（实在不理解就找个例子写一下就明白了
					所以不必重新给p1,p2赋值！！
					（虽然重新赋值也可以过，但速度就慢下来了）
		
		
		
	本题总结&&收获：

		就我目前感觉，分治的难点在于：
			1. 如何处理中间情况
			2. 对于边界的处理
			
		对于难点1：
			只能多做题，去积累一些经验和灵感（比如这一题，我就没想到在分治的过程中也mergesort一下。。）
		对于难点2：
			想清楚再写程序！！！
			在写程序前，一定要定义好分治的那个递归函数处理的区间情况，建议还是用左闭右开的形式[l,r)。
			确定完以后，在此基础上再写程序，才不容易晕！！
			确定完区间，再确定返回情况。
			最后一定别忘记检查是否覆盖了所有的情况！！！
			
		另外补充C++的merge和inplace_merge的用法：
			1. merge比较快，但用起来比较麻烦，需要自己再引入一个结果数组
			2. inplace_merge稍微慢点，但用起来很方便。
			
		下面以合并nums的 [first,mid) 和 [mid,last)   (ps: last指向最后一个元素的后一个位置，你懂得)
			//merge(first,mid, mid, last, result);
			//result为结果数组
			merge( nums+first, nums+mid, nums+mid, nums+last, result);
			merge( nums.begin()+first,nums.begin()+ mid, nums.begin()+ mid,nums.begin()+ last, result.begin()  );

			//inplace_merge( first, mid , last );
			//合并[first,mid) 与 [mid,last) 
			inplace_merge( nums+first, nums+mid, nums+last );
			inplace_merge( nums.begin()+first, nums.begin()+mid, nums.begin()+last );
			
		
*/


class Solution {
public:
    int lo;
    int hi;
    vector<long> sums;
    vector<long> tmp;
    
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        sums.resize(nums.size()+2);
        tmp.resize(nums.size()+2);
        for ( int i=0; i<nums.size(); ++i )
            sums[i+1] = sums[i] + nums[i];
        lo = lower;
        hi = upper;
        //sums[i]表示前i个元素的和，从1开始记
        //divide处理区间为[l,r), 因为要处理[0,len]<=>[0,len+1)
        return divide(0,nums.size()+1); 
    }
    
    //处理区间为[l,r)
    int divide(int l,int r){
        if ( l+1>=r ) return 0;
        int mid = (l+r)/2;
        //[l,mid) + [mid,r)
        int lr_cnt = divide(l,mid) + divide(mid,r);
        int t1=l,t2=l; 
        int cnt=0;
        //以位置i为结尾
        for ( int i=mid; i<r; ++i ){
            //sum[i]-sum[t] => 区间(t,i]的和
            //t1=t2=l;
            //从小到大排好序
            while( t1<mid && sums[i]-sums[t1]>=(long)lo ) t1++;
            while( t2<mid && sums[i]-sums[t2]>(long)hi ) t2++;
            cnt += ( t1-t2 );
        }
        //下面两条语句是等价的，但还是merge比较快。。。
        //inplace_merge(sums.begin()+l,sums.begin()+mid,sums.begin()+r);
        merge(sums.begin()+l,sums.begin()+mid,sums.begin()+mid,sums.begin()+r,tmp.begin()+l);
        for ( int z=l; z<r; ++z )
            sums[z] = tmp[z];
        return cnt + lr_cnt;
    }
};

/*==============================================================================================*/

/*		
	虽然超时了，但还是记录一下- -...
	超时分治（分治完还是O(N^2) 55555
	但是从中对分治以及写分治的程序，得到一些经验：
	分治是先分左中右三个情况，这三种情况的并集一定要覆盖到所有情况！！！（废话
	所以在写程序前，{{{先定义好分治函数的定义！！！！以及处理的区间的开闭！！！}}}	
		以本题为例：
			1. divide就是处理[l,r)的情况！！
		****2. 并集为： [l,mid) + mid + [mid+1,r)  ([l,r)挺好的，可以多用用)
			3. 中间的情况就是覆盖到mid的情况,在本题中就是：
					以[l,mid]的每一个元素为开始，以[mid,r)的每一个元素为结尾！！
					（不同的情况，这里也有所不同，这是本题是这样）
					
	最重要的还是，先想清楚每个函数的定义以及所处理的区间，然后再动手！！！！！！

*/



class Solution {
public:
	/*
		超时分治（分治完还是O(N^2) 55555
		但是从中对分治以及写分治的程序，得到一些经验：
			分治是先分左中右三个情况，这三种情况的并集一定要覆盖到所有情况！！！（废话
			所以在写程序前，{{{先定义好分治函数的定义！！！！以及处理的区间的开闭！！！}}}	
				以本题为例：
					1. divide就是处理[l,r)的情况！！
				****2. 并集为： [l,mid) + mid + [mid+1,r)  ([l,r)挺好的，可以多用用)
					3. 中间的情况就是覆盖到mid的情况,在本题中就是：
							以[l,mid]的每一个元素为开始，以[mid,r)的每一个元素为结尾！！
							（不同的情况，这里也有所不同，这是本题是这样）
							
		最重要的还是，先想清楚每个函数的定义以及所处理的区间，然后再动手！！！！！！
	*/
    int lo,hi;
    long sums[10000];
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        lo = lower;
        hi = upper;
        long acc=0,cnt=0;
        for ( int i=0; i<nums.size(); ++i ){
            acc += nums[i];
            sums[i] = acc;
        }
        //[l,r)
        return divide(nums,0,nums.size());
    }
    
    //[l,mid) + mid + [mid+1,r) 的mid
    int divide(vector<int> & nums,int l,int r){
        if ( l>=r ) return 0;
        if ( l+1==r ){
            if ( lo<=nums[l] && nums[l]<=hi )
                return 1;
            else 
                return 0;
        }
        
        int mid = (l+r)/2;
        long cur=0,cnt=0;
        
        for ( int i=l; i<=mid; ++i ){ // 开始
            for ( int j=mid; j<r; ++j ){ //结束
                cur = sums[j]-sums[i]+nums[i];
                if ( lo<=cur && cur<=hi ){
                    cnt++;
                }
            }
        }
        return cnt + divide(nums,l,mid) + divide(nums,mid+1,r);
    }
};