/*
    问题描述:
        我们把无限数量 ∞ 的栈排成一行，按从左到右的次序从 0 开始编号。每个栈的的最大容量 capacity 都相同。

        实现一个叫「餐盘」的类 DinnerPlates：

        DinnerPlates(int capacity) - 给出栈的最大容量 capacity。
        void push(int val) - 将给出的正整数 val 推入 从左往右第一个 没有满的栈。
        int pop() - 返回 从右往左第一个 非空栈顶部的值，并将其从栈中删除；如果所有的栈都是空的，请返回 -1。
        int popAtStack(int index) - 返回编号 index 的栈顶部的值，并将其从栈中删除；如果编号 index 的栈是空的，请返回 -1。
        

        示例：

        输入： 
            ["DinnerPlates","push","push","push","push","push","popAtStack","push","push","popAtStack","popAtStack","pop","pop","pop","pop","pop"]
            [[2],[1],[2],[3],[4],[5],[0],[20],[21],[0],[2],[],[],[],[],[]]
        输出：
            [null,null,null,null,null,null,2,null,null,20,21,5,4,3,1,-1]

        解释：
            DinnerPlates D = DinnerPlates(2);  // 初始化，栈最大容量 capacity = 2
            D.push(1);
            D.push(2);
            D.push(3);
            D.push(4);
            D.push(5);         // 栈的现状为：    2  4
                                                1  3  5
                                                ﹈ ﹈ ﹈
            D.popAtStack(0);   // 返回 2。栈的现状为：    4
                                                    1  3  5
                                                    ﹈ ﹈ ﹈
            D.push(20);        // 栈的现状为：20 4
                                            1  3  5
                                            ﹈ ﹈ ﹈
            D.push(21);        // 栈的现状为：20 4  21
                                            1  3  5
                                            ﹈ ﹈ ﹈
            D.popAtStack(0);   // 返回 20。栈的现状为：       4 21
                                                        1  3  5
                                                        ﹈ ﹈ ﹈
            D.popAtStack(2);   // 返回 21。栈的现状为：       4
                                                        1  3  5
                                                        ﹈ ﹈ ﹈ 
            D.pop()            // 返回 5。栈的现状为：        4
                                                        1  3 
                                                        ﹈ ﹈  
            D.pop()            // 返回 4。栈的现状为：    1  3 
                                                       ﹈ ﹈   
            D.pop()            // 返回 3。栈的现状为：    1 
                                                       ﹈   
            D.pop()            // 返回 1。现在没有栈。
            D.pop()            // 返回 -1。仍然没有栈。
            

        提示：
            1 <= capacity <= 20000
            1 <= val <= 20000
            0 <= index <= 100000
            最多会对 push，pop，和 popAtStack 进行 200000 次调用。

        问题分析:
            难点在于，该如何找最小的未满的栈的index
                         和最大的非空的栈的index
            可以用最大堆和最小堆来解决
            最大堆， 用来存 非空栈的index
            最小堆， 用来存 未满栈的index

            然后对应实现就行了。
            值得注意的是，对于这个栈的集合，没必要一开始就开辟10^5的空间，
            这样会TLE，
            可以用unordered_map来保存栈集合, 这样就不用一开始就开辟那么大的空间了。
*/


class DinnerPlates {
public:
    unordered_map<int,stack<int>> vs; //栈集合 vs[idx]表示第idx个栈
    int len;
    priority_queue<int> q_maxi; //最大堆， 用来存 非空栈的index
    priority_queue<int, vector<int>, greater<int>> q_mini; //最小堆， 用来存 未满栈的index
    
    DinnerPlates(int capacity) {
        len = capacity;
        
        // 事先存入10^5个未满的index
        for ( int i=0; i<=100000; ++i )
             q_mini.push(i);
        // vs.resize(100001); 事先开辟会tle
    }
    
    void push(int val) {
        // 获取最小的未满栈
        int idx = q_mini.top();
        vs[idx].push( val );
        // 如果是第一个元素，那就更新 未满栈堆
        if ( vs[idx].size()==1 ){
            q_maxi.push(idx);
        }
        // 栈满了，把该节点从未满栈堆里 删除    
        if ( vs[idx].size()>=len ){
            q_mini.pop();
        }
    }
    
    int pop() {
        if ( q_maxi.size()==0 ) return -1;
        int idx = q_maxi.top();
        int res = vs[idx].top();
        vs[idx].pop();
        if ( vs[idx].size()==0 ){
            q_maxi.pop();
        }
        if ( vs[idx].size()==len-1 ){
            q_mini.push(idx);
        }
        return res;
    }
    
    int popAtStack(int index) {
        if ( vs[index].size()==0 ) return -1;
        int res = vs[index].top(); 
        vs[index].pop();
        if ( vs[index].size()==0 ){
            q_maxi.pop();
        }
        if ( vs[index].size()==len-1 ){
            q_mini.push(index);
        }
        return res;
    }
};

/**
 * Your DinnerPlates object will be instantiated and called as such:
 * DinnerPlates* obj = new DinnerPlates(capacity);
 * obj->push(val);
 * int param_2 = obj->pop();
 * int param_3 = obj->popAtStack(index);
 */