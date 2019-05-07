
/*
		题目描述：
			给定一个非负整数的数据流输入 a1，a2，…，an，…，将到目前为止看到的数字总结为不相交的区间列表。

			例如，假设数据流中的整数为 1，3，7，2，6，…，每次的总结为：

			[1, 1]
			[1, 1], [3, 3]
			[1, 1], [3, 3], [7, 7]
			[1, 3], [7, 7]
			[1, 3], [6, 7]
			
			
		问题分析；
            [val,val]
            分以下几个情况来讨论：
                1. [..,val-1], [val,val],[val+1,..]
                   合并成 [..,..]，删
                2. [..,val-1],[val,val],[>val+1,..]
                   合并成[..,val],[>val+1,..]，
                3. [..,<val-1],[val,val],[val+1,..]
                   合并成[..,<val+1],[val,..]，
                4. [..,<val-1],[val,val],[>val+1,..]
                   不变
            首先找到首个比val大的区间,分合并情况和不合并情况讨论
            
			难点在于边界的处理，以及逻辑的安排，显然这点处理的不大好，
			因为刚做完的关系，再做难免会有些印象，
			这题建议过段时间再做一遍！
        */

class SummaryRanges {
public:
    /** Initialize your data structure here. */
    vector<vector<int>> nums;
    
    SummaryRanges() {
            
    }
    
    void addNum(int val) {
        int i=0;
        while( i<nums.size() && nums[i][1]<val ){
            ++i;
        }
        if ( i<nums.size() ){
            if ( nums[i][0]<=val )
                return ;
            else{ 
                if ( i==0 ){
                    if (nums[i][0]-1==val)
                        nums[i][0] = val;
                    else 
                        nums.insert(nums.begin()+i, vector<int>(2,val));
                    return;
                }
				if ( nums[i-1][1]+1==val && nums[i][0]-1==val ){
                    nums[i-1][1] = nums[i][1];
                    nums.erase(nums.begin()+i);
                }else if ( nums[i-1][1]+1==val )
                    nums[i-1][1] = val;
                else if ( nums[i][0]-1==val )
                    nums[i][0] = val;
                else{//不合并的情况
                    nums.insert(nums.begin()+i, vector<int>(2,val));
                }
            }
        }else{
            if ( i==0 ||  val>nums.back()[1]+1 )
                nums.push_back(vector<int>(2,val));
            else
                nums.back()[1] = val;
            
        }
    }
    
    vector<vector<int>> getIntervals() {
        return nums;
    }
};
