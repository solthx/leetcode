/*
	题目描述：
		设计一个找到数据流中第K大元素的类（class）。注意是排序后的第K大元素，不是第K个不同的元素。

		你的 KthLargest 类需要一个同时接收整数 k 和整数数组nums 的构造器，它包含数据流中的初始元素。
		每次调用 KthLargest.add，返回当前数据流中第K大的元素。
		
	题目分析：
		维护一个最小堆，堆的元素个数为常量 k，新加入一个元素和堆顶比较，
		如果比堆顶元素小，丢弃，否则删除堆顶元素，插入新元素。
*/

class KthLargest {
public:
    KthLargest(int k, vector<int>& nums) {
        K=k;
        for ( auto e:nums ){
            if ( q.empty() || q.size()<k ) q.push(e);
            else if ( e>q.top() ){
                q.pop();
                q.push(e);
            }
        }
    }
    
    int add(int val) {
        if ( q.empty() || q.size()<K ) q.push(val);
        else if ( val>q.top() ){
            q.pop();
            q.push(val);
        }
        return q.top();
    }
    priority_queue<int,vector<int>,greater<int>> q;
    int K;
};
    static const int _ = [](){
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
        return 0;
    }();

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */