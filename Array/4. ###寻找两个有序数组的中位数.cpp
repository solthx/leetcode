/*
	题目描述：
		给两个有序的数组，求：把这两个数组合成一个数组以后的那个中位数
		
	限制：
		时间复杂度为O(log(m+n))
	
	题目分析：
		加上限制以后。。这题就变难了。。（边界条件比较烦
		
		
		为了方便说明，设第一个序列为nums1 , 第二个序列为nums2
		然后nums3就是 由nums1和nums2组成的那个递增序列。
		
		首先，对中位数的理解是： 从中位数位置切下去后，
		两个子序列满足的条件：
			1. 分成的两个子序列的数量相同
			2. 左边子序列的最大值小于等于右边子序列的最小值
		
		所以我们的目标就是，从nums1和nums2里分别取出一些元素，
		这些元素的个数是nums3的一半，且取出的这些元素的最大值
		要小于剩下的那一半元素里的最小值。
		
		那么该怎么取呢？
		
		因为取出元素的个数是固定(nums3的一半)的，所以我们把关注焦点就放在nums1上，
		（nums2取出的元素个数，用总长度减去Nums1取出的个数就行了），这样，数量这一
		个情况就可以满足了，然后来看怎么满足第二个条件。
		
		第二个条件是左边子序列的最大值小于等于右边子序列的最小值，
	
		下面看一个例子：
		
		nums1:  1 3 5 7  
		nums2:  2 4 6 8 10 12
		
		一、条件分析：
			1、左边子序列：
				
				假如在nums1中选2个元素，在nums2中选5-2=3个元素
				作为左边子序列：
				nums1:  {1 3} 5 7  
				nums2:  {2 4 6} 8 10 12
				
				这个时候就会发现，左边子序列的最大值将会是在
				nums1选出的元素的最大值和nums2选出元素的最大值里选，
				又因为是递增顺序，也就是：
				
					nums1取出的元素：{.., L1}
					nums2取出的元素：{...., L2} 
				
			
			2、右边子序列
				
				也就是nums1剩下的元素和nums2剩下的元素组成的
				nums1:  1 3 {5 7}  
				nums2:  2 4 6 {8 10 12}
				
				而右边序列的最小值则同理
				
					nums1剩下的元素：{R1,..}
					nums2剩下的元素：{R2,.....}
			
			3、左边子序列的最大值小于右边子序列的最小值：
				
				只要满足：
					L1<R1 L1<R2
					L2<R1 L2<R2
				那么就可以满足“左边子序列的最大值小于右边子序列的最小值”
				
				又因为序列本来有序，也就是L1<R1,L2<R2是天然存在的
				所以只要满足：
					
					L1<R2, L2<R1即可！
			
			总结:
				从nums1里选出i个元素，nums2选出j个元素，满足：
					1. i+j = len/2
					2. L1<R2, L2<R1
				
		二、落实到代码：
			
			1. 在编程时，因为数组是从0计数，我们又习惯从1开始，为了把这层关系弄得而更清晰一些，
			我们引入一个变量cut1，和cut2 这个变量的含义就是从nums1和nums2中取出元素的个数
			
			举个例子：
				nums1： 1 3 5 7 9 11
				如果我们要从nums1里取3个数，
				nums1:  {1 3 5} 7 9 11
				那么cut1就是3 ， 说明在第3个元素的后面切了一刀，拿走这一刀前面的元素(这里是{1 3 5})
			
			2. 实现的时候，还要考虑奇偶情况
				
				(len是nums3的长度)
				
				2.1 奇数的时候，中位数是第((len+1)/2)个，从0开始计，idx是(len/2)
				2.2 偶数的时候，中位数是第(len/2)个元素和第(len/2)+1个元素的均值，对应idx分别为(len-1)/2和(len/2)
				2.3 (len-1)/2是左边子序列的最大值，也就是max(L1,L2)
					    len/2是右边子序列的最小值，也就是min(R1,R2)						
				
				这时候，我们可以发现：
					我们的目标就是找出满足：
						1. i+j = len/2
						2. L1<R2, L2<R1
					的L1,L2,R1,R2
					
					最后，如果是奇数的话，中位数就是min(R1,R2)
						  如果是偶数的话，中位数就是 {max(L1,L2)+min(R1,R2)}/2
					
					接下来找L1,L2,R1,R2就行了~~
					
			3. 最后一步 ———— 确定cut1位置和L1,L2,R1,R2
			
				我们依然把关注点放在nums1上，nums1处理好了，nums2也好了
				
				3.1 我们的目标是：L1<R2, L2<R1
				
					 但如果L1>R2呢？
						那需要让L1小一些，因为nums1是递增顺序，L1是{}的最后一个，这就需要
						让cut1小一些，这样L1会小一些，同时R2也会大一些，直到L1<R2 
					
					 如果L2>R1呢？
						根上一个情况同理，那就让R1大一些，也就是让cut1大一些，这样R1就会变大
						同时L2也会跟着变小，知道L2<R2
					
					 前两个情况都不满足，就是L1<R2, L2<R1了！
					然后分奇偶来讨论再返回就行了。
				
				3.2 根据3.1的情况，用二分的方法来确定cut1,
					因为cut1是从nums1中取走的元素数量，
					所以cut1的取值范围是0~nums1.size() 
					故初始化一个 cutL = 0, cutR = nums1.size()
					然后根据3.1的情况，来进行二分。
					
			4. 最后的细节处理：
				边界情况：
					当cut1为0的时候，从nums1取出0个数，那L1是多少呢 
					例如：nums1: {} 4 5 
						  nums2: {1 2} 3
					这种时候，我们就不去更新cut1了，也就是把它设成100%能满足的情况：
						L1 ：-∞ ，R2：+∞
					
					同理，当cut1为nums1.size()的时候，nums1剩下0个，停止更新cut1
					更新L1 ：-∞ ，R2：+∞
					
					cut2同理。
				
				特殊情况：
					我们上面的所有操作，都是把焦点放在了nums1上，这里需要nums1的长度小于nums2
					否则可能乎产生越界错误。 
					因为我们的所有操作都是，先在nums1上取i个数，然后再在nums2上取j个数，
					如果这个i很小，那么j就会很大，当nums1比较大的时候，nums2机会相对比较小，j很大的话可能会越界
					
					下面举个例子：
					
					例如：nums1 ： 2 3 4 5 6 7 
						  nums2 :  1
						  
						k  = 8/2 = 4
						当cut1取到2的时候，cut2则应该取4-2 = 2，
						但是nums2的总长度才是1，取2时显然就越界了。
						
					但是如果nums1的长度小于了nums2的长度，那么无论i取的多小，
					取cut2时，都不会越界，这一点可以体会一下，还是很好理解的。
			
			
		
*/

# define inf 0x3f3f3f3f

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int len = (nums1.size()+nums2.size());
        //保证nums1比较短
		if ( nums1.size()>nums2.size() )
            return findMedianSortedArrays(nums2,nums1);
		int L1,L2,R1,R2; 
        //cut1位置左边的元素个数和cut2位置左边的元素个数
		int cut1=0,cut2=0; //分别代表从nums1和nums2中取出的元素个数
        
		//二分法找cut1的位置
		int cutR=nums1.size(),cutL=0;
		
		//有时，相等的情况是返回的情况。
		/*
			例如nums1: 1 2
			    nums2: 3 4 
			最后一步是cutL==cutR==2,cut1=2，此时返回结果，而不应该是跳出
			所以这里是要带等号的
		*/
        while( cutL<=cutR ){
            cut1=(cutR+cutL)/2;
            cut2=(len/2)-cut1;
            L1 = (cut1==0)?-inf:nums1[cut1-1];
            L2 = (cut2==0)?-inf:nums2[cut2-1];
            R1 = (cut1==nums1.size())?inf:nums1[cut1];
            R2 = (cut2==nums2.size())?inf:nums2[cut2];
            if ( L1>R2 ){
                cutR = cut1-1;
            }else if ( L2>R1 ){
                cutL = cut1+1;
            }else{
                if ( len%2==0 ){
                    L1 = max(L1,L2);
                    R1 = min(R1,R2);
                    return (R1+L1)/2.0;
                }else{
                    R1 = min(R1,R2);
                    return (1.0*R1);
                }
            }
        }
        return -1;
    }
};