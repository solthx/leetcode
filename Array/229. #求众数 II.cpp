/*
	问题描述：
		一个数组长为n，返回所有出现了超过⌊ n/3 ⌋ 次的元素
		
	解决思路：
		是“返回出现了超过⌊ n/2 ⌋次的元素”（摩尔投票）的变种。
		解决方法是：
			一. 先找出两个候选人A和B
			二. 扫描数组：
					2.1 若和A相等，则A的票数+1
				    2.2 若和B相等，则B的票数+1
				    2.3 若和A，B都不相等：
						存在票数为0的人，当前的人替换掉票数为0的人，
						不存在票数为0的人，当前候选人A和B的票数均减一；
		
			三、得到了出现次数最多的两个人
			四、从头再遍历一遍数组，找出这两个人的出现次数，若大于n/3则
				选中
			五、返回选中结果。
			
	总结： 
			发散一下来看此类问题，
			找出出现次数超过n/2的元素，是选出一个候选人
			找出出现次数超过n/3的元素，是选出两个候选人
			...
			找出出现次数超过n/k的元素，则是选出K-1个候选人
			
			然后后面的方法都一样，
			就是相同就加，
			不同就能替换候选人就替换候选人，替换不了就减票数，
			最后找出得票最多的人，
			然后再遍历一次数组，找出最多次数为多少
	
	PS： 	需要注意的是，更新的时候把票数更新成1而不是0
*/



class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        vector<int> res;
        if (!nums.size() ) return res;
		//pair(候选人，票数)
        vector<pair<int,int>> candi;
		//选出两个候选人（票数是0那么是谁都无所谓了
        candi.push_back(make_pair(0,0));
        candi.push_back(make_pair(0,0));
        for ( int e : nums ){
			//和A相同，A的票数加一
            if ( e==candi[0].first ){
                candi[0].second++;
            }else if ( e==candi[1].first ){
                candi[1].second++; //B同理
            }else{
				//是否有能替换掉的候选人
                if ( candi[0].second<=0 ){
                    candi[0].first=e;
                    candi[0].second=1;
                }else if ( candi[1].second<=0 ){
                    candi[1].first=e;
                    candi[1].second=1;
                }else{//没有能替换的掉的，那就减票数
                    candi[0].second--;
                    candi[1].second--;
                }
            }
        }
        int cnt[2]={0}; //cnt[0]是A出现次数，cnt[1]是B出现次数
        for ( int e:nums ){
            if ( e==candi[0].first &&  0<candi[0].second  ) 
                cnt[0]++;
            else if ( e==candi[1].first && candi[1].second>0 ) 
                cnt[1]++;
        }
        //存入结果并返回
        if ( cnt[0]>nums.size()/3 ) res.push_back(candi[0].first);
        if ( cnt[1]>nums.size()/3 ) res.push_back(candi[1].first);
        return res;
    }
};