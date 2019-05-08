/*
	题目描述：
		中位数是有序列表中间的数。如果列表长度是偶数，中位数则是中间两个数的平均值。

		例如，

		[2,3,4] 的中位数是 3

		[2,3] 的中位数是 (2 + 3) / 2 = 2.5

		设计一个支持以下两种操作的数据结构：

		void addNum(int num) - 从数据流中添加一个整数到数据结构中。
		double findMedian() - 返回目前所有元素的中位数。
		示例：

		addNum(1)
		addNum(2)
		findMedian() -> 1.5
		addNum(3) 
		findMedian() -> 2
		
	题目分析：
		构建两个堆，一个最大堆，一个最小堆，最大堆的最大元素小于等于最小堆的最小元素
		两个堆的size差始终维护在1以内，
		
		当最小堆的size和最大堆的size相等时，返回最小和最大的和 * 1/2
		不等时，返回size较大的那个堆的堆顶。
		
	最后：
		
    static const int _ = [](){
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
        return 0;
    }();
	加了这段代码，速度直接起飞了。。
*/



class MedianFinder {
public:
    /** initialize your data structure here. */
    MedianFinder() {
        
    }
    
    void addNum(int num) {
		//根据size的情况来分类讨论
        if ( small_top.empty() ) small_top.push(num);
        else if ( small_top.size()==big_top.size() ){
            if ( num<=big_top.top() ){
                big_top.push(num);
            }else
                small_top.push(num);
        /*
            小顶堆少一个：
            大:1 2 3
            小:5 6 
         */  
        }else if ( small_top.size()+1==big_top.size() ){
            //小顶堆缺一个
            if ( num>=big_top.top() ){
                //假如插入3 or 4
                small_top.push(num);
            }else{ //假如插入0
                small_top.push(big_top.top());
                big_top.pop();
                big_top.push(num);
            }
        /*
            大顶堆比小顶堆多一个
            大: 1 2
            小: 3 4 5
        */
        }else if ( small_top.size()==big_top.size()+1 ){
            //大顶堆缺一个
            if ( num<=small_top.top() ){
                //插入0
                big_top.push(num);
            }else{
                //插入6
                big_top.push(small_top.top());
                small_top.pop();
                small_top.push(num);
            }
        }
    }
    
    double findMedian() {
        int n = small_top.size()+big_top.size();
        if (n%2==0){
            return (small_top.top() * 1.0 + big_top.top()*1.0)/2.0;
        }else 
            return (small_top.size()>big_top.size())?small_top.top():big_top.top();
    }
    
private:
    priority_queue<int,vector<int>,greater<int>> small_top;
    priority_queue<int,vector<int>,less<int>> big_top;
};

    static const int _ = [](){
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
        return 0;
    }();

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */