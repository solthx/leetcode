/*
    问题描述:
        用栈来实现队列操作.

    问题分析:
        用栈实现队列， 要求出队，入队，取队首节点的复杂度均为O(1)

        用两个栈实现，
        第一个栈的作用是用于存储 自从上次pop之后，push进去的所有的元素。
        第二个栈的作用是 当进行pop时，把第一个栈中的所有元素都push到第二个栈中，
        进行两次栈操作，序列就变成FIFO了，此时栈顶就是队首. 

        因此, 第一个栈服务于push， 第二个栈服务于pop操作

        对于stack.top()的操作，如果第二个栈不空，那队首就是第二个栈的栈顶，
        如果第二栈空了，那就是第一个栈的栈底.
*/

class MyQueue {
public:
    int front;
    stack<int> st1;
    stack<int> st2;
    /** Initialize your data structure here. */
    MyQueue() {
        
    }
    
    /** Push element x to the back of queue. */
    void push(int x) {
        if ( st1.empty() )
            front = x;
        st1.push(x);
    }
    
    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        int res;
        if ( this->empty() ) return -1;
        if ( st2.empty() ){
            while( !st1.empty() ){
                st2.push(st1.top());
                st1.pop();
            }    
        }
        res = st2.top();
        st2.pop();
        return res;
    }
    
    /** Get the front element. */
    int peek() {
        if ( st2.size()==0 ) return front;
        return st2.top();
    }
    
    /** Returns whether the queue is empty. */
    bool empty() {
        return st1.empty() && st2.empty();
    }
};
