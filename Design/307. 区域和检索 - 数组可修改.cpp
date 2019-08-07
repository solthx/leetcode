/*
    问题描述：
        给定一个整数数组  nums，求出数组从索引 i 到 j  (i ≤ j) 范围内元素的总和，包含 i,  j 两点。
        update(i, val) 函数可以通过将下标为 i 的数值更新为 val，从而对数列进行修改。

        示例:

        Given nums = [1, 3, 5]
        sumRange(0, 2) -> 9
        update(1, 2)
        sumRange(0, 2) -> 8

    问题分析:
        树状数组模版题...
 */

class NumArray {
private:
        vector<int> c;
        int lowbit( int k ){ return k&-k; }
        int n;
        int search( int x ){
            int res=0;
            while( x>0 ){
                res += c[x];
                x -= lowbit( x );
            }
            return res;
        }
        
        void add(int i, int val) {
            while( i<=n ){
                c[i] += val;
                i += lowbit(i);
            }
        }
    
    
public:
    NumArray(vector<int>& nums) {
        n = nums.size();
        c.resize(n+1,0);
        for ( int i=0; i<n; ++i )
            update(i, nums[i]);
    }
    
    void update(int i, int val) {
        i += 1;
        int addition = val - (search(i) - search(i-1));
        add( i, addition );
    }
    
    int sumRange(int i, int j) {
        return search( j+1 ) - search(i);
    }
};
