/*
	问题描述：
		给出一个区间的集合，请合并所有重叠的区间。
		
	题目分析：
		先给区间排序，
		然后核心思想就是每次都push进一个elem，让elem的右边界一定比后面元素的左边界小！
		
		伪代码：
			res是返回向量
			遍历intervals,设第i个区间为itvl:
				每次push一个区间elem
				elem的左边界设为第i个区间的左边界
				elem的右边界设为第i个区间的右边界
				
				while( elem的右边界 >= 第i+1个区间的左边界 )： //说明还可以合并
					找到首个区间j的右边界比elem[1]大  //说明落在了区间j里或者区间j的左边
					if ( 落在了区间j里面 ):
						右边界大小更新为第j个区间的右边界
						j += 1
				elem元素push进res中
			返回res
  
*/



class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {        
        int i=0,j=intervals.size();
		//给区间排序
        sort(intervals.begin(),intervals.end(),cmp);
        vector<vector<int>> res;
        if (  intervals.size()<1 ) return res;
        while( i<intervals.size() ){
			//每次push一个区间elem
            vector<int> elem(2,0);
            elem[0] = intervals[i][0];
            elem[1] = intervals[i][1];
            j=i+1;
			//判断是否还可以合并
            while( j<intervals.size() && elem[1]>=intervals[j][0] ){
				//找到首个区间j的右边界比elem[1]大
                while( j<intervals.size() && elem[1]>intervals[j][1] )
                    j++;
                if ( j<intervals.size() && elem[1]>=intervals[j][0] ){
					//说明落在了区间j里面
                    elem[1] = intervals[j][1];
                    j++;
                }
            }
            res.push_back(elem);
            i = j;
        }
        
        return res;
    }
    static bool cmp(vector<int>& a, vector<int> & b){
        return (a[0]!=b[0])?a[0]<b[0]:a[1]<b[1];
    }
};