/*
    问题描述：
        假设有打乱顺序的一群人站成一个队列。 每个人由一个整数对(h, k)表示，其中h是这个人的身高，k是排在这个人前面且身高大于或等于h的人数。 编写一个算法来重建这个队列。

        注意：
        总人数少于1100人。

        示例

        输入:
        [[7,0], [4,4], [7,1], [5,0], [6,1], [5,2]]

        输出:
        [[5,0], [7,0], [5,2], [6,1], [4,4], [7,1]]

    问题分析:
        想到了排序，但还是没做出来T_T
        
        这里用到的思想就是插入的思想，
        
        前面有k个数比自己大，可以这样插入来满足：
            就是从大到小，往数组里插入，当元素大小相同时，那么就按照rank大小升序排序，，
            
            当插到nums[i]的时候，
            
            那么nums[i+1~n]都要小于nums[i]，nums[0~i-1]都要大于等于nums[i]，且已经插入到数组里了

            此时，只要把nums[i]插入到合适位置就行了，因为nums[i]在当前最小，所以插入之后也不会改变数组结构

        知道了这个思想以后，可以用插入的方式来实现，也可以排序后原地交换来实现
*/

// 插入实现
class Solution1 {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        sort( people.begin(), people.end(), [](vector<int>& a, vector<int> &b){
            return a[0]>b[0] || a[0]==b[0] && a[1]<b[1];   
        });
        vector<vector<int>> res;
        for ( auto p:people )
            res.insert( res.begin()+p[1], p );
        return res;
    }
};

// 原地交换
class Solution2 {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        sort( people.begin(), people.end(), [](vector<int>& a, vector<int> &b){
            return a[0]>b[0] || a[0]==b[0] && a[1]<b[1];   
        });
        int r=0, n=people.size();
        while( r<n ){
            int l = r;
            while( l>0 && people[l][1]!=l ){
                swap( people[l], people[l-1]  );
                --l;
            }
            r++;
        } 
        return people;
    }
};

