/*
	����������
		��һ������nums��Ŀ��ֵk���ҵ���������������飬ʹ���е�Ԫ�غ�Ϊk�����û�У��򷵻�0��
		����1
		
		����: nums = [1, -1, 5, -2, 3], k = 3
		���: 4
		����:
		������[1, -1, 5, -2]�ĺ�Ϊ3���ҳ������ 
		
	��Ŀ������
		sum[i] Ϊnums��ǰi��Ԫ�صĺ� 
		unordered_map�������ǣ� {sum[i] : i } 
		
		��HashMap, Keyָi��֮ǰԪ�ص��ܺͣ�valueָ��ǰindex��
		
		����ÿ��i��������鵱ǰsum��ҲҪ���(currentSum - previousSum)�������Ƿ���k��ȡ���map.containsKey(sum - k) �������һ���ص㣺
		
		����˵����
		
			K=3
			
			Index : 0,1,2,3,4,5....
			
			Value : 2,0,2,1,1,1....
			
			Sum: 2,2,4,5,6,7
			
			Sum-K: 4
			
			map.containsKey(sum - k) : The index is 2
			
			��index0~2���ܺ���4�ˣ���0~5���ܺ���7�ˣ���ô��3~5���ܺ��ǲ��Ǿ���������Ҫ��3��
			
			3~5��size��ô�����أ� ===>> i - map.get(sum - k)��������������5-2
		
*/ 

class Solution {
public:
    /**
     * @param nums: an array
     * @param k: a target value
     * @return: the maximum length of a subarray that sums to k
     */
    int maxSubArrayLen(vector<int> &nums, int k) {
        if ( nums.size()<1 ) return 0;
        unordered_map<int,int> m;
        vector<int> sum(nums.size(),0);
        unordered_map<int,int> :: iterator it;
        //m[sum] = index;
        int idx;
        int res=0;
        sum[0]=nums[0];
        m[sum[0]] = 0;
        if ( sum[0]==k ) res = 1;
        for ( int i=1; i<nums.size(); ++i ){
            sum[i] = sum[i-1] + nums[i];
            //��ΪҪ����ģ����Ե�sum��ͬʱ������ȡi��С���Ǹ������������ľ������
			//��ˣ�ֻ�е�m��û�е�ǰsum��ʱ�����ǲŽ������ 
            if ( m.count(sum[i])==0 )
                m[sum[i]] = i;
            if ( sum[i]==k ) res = i+1;
        }
        
        for ( int i=0; i<nums.size(); ++i ){
            // sum[i] - x = k 
            // x = sum[i]-k
            it = m.find(sum[i]-k);
            if ( it!=m.end() && (*it).second<=i ){
                res = max(res, i-(*it).second);
            }
        }
        return res;
    }
};

/*                      map
  idx  0  1  2  3  4  (value)
  val  1 -1  5 -2  3  
  sum  1  0  5  3  6  (key)
*/


// �ռ��Ż�
 
