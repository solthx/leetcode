/*
    问题描述：
        就是给一个数组，对数组进行调整，使得任意相邻的两个元素不相等。
    
    问题分析:
        记录每一个元素的出现次数，并根据次数进行降序排序，
        然后依次存入到结果数组中
        存入顺序为 0, 2, 4, 6,... n, 1,3,5,7, ...
*/

class Solution {
public:
    vector<int> rearrangeBarcodes(vector<int>& barcodes) {
        map<int,int> mp;
        int maxi=-1;
        int val;
        int n = barcodes.size();
        vector<int> res(n, -1);
        vector<pair<int,int>> nums;
        // mp[e]是数字e出现的次数
        for ( auto e:barcodes )
            ++mp[e];
        // 构造pair数组，对次数进行降序排序
        for ( auto e:mp ){
            nums.push_back( {e.first, e.second} );
        }
        // 降序排序
        sort( nums.begin(), nums.end(), cmp );
        int i=0; // 0 ， 2， 4，6，..
        for (  auto e:nums){
            int cnt=e.second;
            while( cnt-- ){
                res[i] = e.first;
                i+=2;
                if ( i>=n ) i=1;// 到末尾了，再从1开始，1，3，5，7
            }
        }
        return res;
    }
    
    static bool cmp( pair<int,int> &a, pair<int,int> &b ){
        return a.second>b.second;
    }
};