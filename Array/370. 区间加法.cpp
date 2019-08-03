/*
    问题分析：
        假设你有一个长度为 n 的数组，初始情况下所有的数字均为 0，
        你将会被给出 k​​​​​​​ 个更新的操作。

        每个更新操作都是一个三元组( start, end, inc )
        对数组的[start,end]这个区间上的元素加inc，
        返回最终结果数组。


    问题分析:
        对 [start, end]区间内的每个元素加inc，
        可以转换成：
                先对 [start,n) 的每个值加上inc
                再对 [end+1,n) 的每个值减去inc
        
        先对nums这个初始为0的数组进行标记，
        标记的意义就是: 当nums[i]不为0时，就表示对[i,n)的每个元素都加上nums[i]
        
        标记完之后，再实施上面的这个"标记意义"、、
 */

class Solution {
public:
    vector<int> getModifiedArray(int length, vector<vector<int>>& updates) {
        vector<int> res(length, 0);
        for ( auto v:updates ){
            res[v[0]] += v[2];
            if ( v[1]<length-1 )
                res[v[1]+1] -= v[2];
        }
        for ( int i=1; i<length; ++i ){
            res[i] += res[i-1];
        }
            
        /*int addition = 0, sav;
        for ( int i=0; i<length; ++i ){
            if ( res[i]!=0 ){
                sav = res[i];
                res[i] += addition;
                addition += sav;
            }else res[i] += addition;
        }*/
        
        return res;
    }
    
};
