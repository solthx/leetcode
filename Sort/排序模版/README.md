# 排序

堆排，快排是面试常爱考的，这里就记录一下吧... 练手题目 ![leetcode 912](https://leetcode-cn.com/problems/sort-an-array/)

## 一、堆排序

```cpp
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        HeapSort(nums);
        return nums;
    }
    
    void HeapSort(vector<int>&nums){
        int n = nums.size();
        for(int i=n/2; i>=0; --i)
            push_down(nums, i, n);
        for(int i=n-1; i>=0; --i){
            swap(nums[0], nums[i]);  
            push_down(nums, 0, i); // 下标天然比长度少1，直接利用i就行了
        }
    }
    
    void push_down(vector<int>&nums, int i, int n){
        int l = (i+1)*2-1, r = (i+1)*2;  // 先转成个数，再减1变成下标
        int pos = i; // 注意，这里是只能交换一次！
        if ( l<n && nums[pos]<nums[l] )
            pos = l;
        if (r<n && nums[pos]<nums[r])
            pos = r;
        if (i!=pos){  // 注意，这里是push_down交换过的位置
            swap(nums[i], nums[pos]);
            push_down(nums,pos,n);
        }
    }
};
```

## 二、快速排序

### 2.1 快速排序 + 三项切分 (递归版)

```cpp
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        quickSort(nums, 0, (int)nums.size()-1);
        return nums;
    }
    
    void quickSort(vector<int>&nums, int l, int r){
        if (l>=r) return ;
        random_choose(nums, l, r); // 三项切分 
        int pivot = partition(nums, l, r);  // 对nums[l]就位，然后返回其就位后的位子
        quickSort(nums, l, pivot-1);
        quickSort(nums, pivot+1, r);
    }
    
    void random_choose(vector<int>&nums, int l, int r){
        int mid = l + (r-l)/2;
        if ( nums[l]>nums[mid] )
            swap(nums[l], nums[mid]);
        if (nums[mid]>nums[r])
            swap(nums[mid],nums[r]);
        swap(nums[mid], nums[l]);
    }
    
    int partition(vector<int>&nums, int l, int r){
        int sav = nums[l];
        int lo = l, hi = r;
        while( lo<hi ){   // 注意，这里是< 而不是<=， 是因为lo和hi其中一个一定是等待填坑的位置，另一个是正在扫描的位置，当这两个位置收敛到同一个位置时，就说明这个位置需要放最初的那个值
            while(lo<hi && nums[hi]>=sav) --hi;
            if (lo<hi) 
                nums[lo++] = nums[hi];
            while(lo<hi && nums[lo]<=sav) ++lo;
            if (lo<hi)
                nums[hi--] = nums[lo];
        }
        nums[lo] = sav;
        return lo;
    }
};
```

### 2.2 快速排序 + 三项切分 (非递归版)

将上面这种架构的递归版的程序改成非递归版是非常容易的，就是l和r不再用递归的形式存，而用栈来存，还是很简单的。

```cpp
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        quickSort(nums, 0, (int)nums.size()-1);
        return nums;
    }
    
    void quickSort(vector<int>&nums, int l, int r){
        if (l>=r) return;
        stack<int> st;
        st.push(l);
        st.push(r);
        while(st.size()>0){
            r = st.top(); st.pop();
            l = st.top(); st.pop();
            random_choose(nums, l, r);
            int pivot = partition(nums, l, r);
            if (pivot-1>l){
                st.push(l);
                st.push(pivot-1);
            }
            if (pivot+1<r){
                st.push(pivot+1);
                st.push(r);
            }
        }
    //     if (l>=r) return ;
    //     random_choose(nums, l, r);
    //     int pivot = partition(nums, l, r);
    //     quickSort(nums, l, pivot-1);
    //     quickSort(nums, pivot+1, r);
    }
    
    void random_choose(vector<int>&nums, int l, int r){
        int mid = l + (r-l)/2;
        if ( nums[l]>nums[mid] )
            swap(nums[l], nums[mid]);
        if (nums[mid]>nums[r])
            swap(nums[mid],nums[r]);
        swap(nums[mid], nums[l]);
    }
    
    int partition(vector<int>&nums, int l, int r){
        int sav = nums[l];
        int lo = l, hi = r;
        while( lo<hi ){
            while(lo<hi && nums[hi]>=sav) --hi;
            if (lo<hi) 
                nums[lo++] = nums[hi];
            while(lo<hi && nums[lo]<=sav) ++lo;
            if (lo<hi)
                nums[hi--] = nums[lo];
        }
        nums[lo] = sav;
        return lo;
    }
};
```

### 3. 插入排序

```cpp
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        // 插入排序
        for(int i=0; i<nums.size(); ++i){
            int sav = nums[i], j;
            for( j=i-1; j>=0 && nums[j]>sav; --j)
                nums[j+1] = nums[j];
            nums[j+1] = sav;
        }
        return nums;
    }
};
```