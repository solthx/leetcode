/*
    问题描述:
        给定一个嵌套的整型列表。设计一个迭代器，使其能够遍历这个整型列表中的所有整数。
        列表中的项或者为一个整数，或者是另一个列表。

        示例 1:

        输入: [[1,1],2,[1,1]]
        输出: [1,1,2,1,1]
        解释: 通过重复调用 next 直到 hasNext 返回false，next 返回的元素的顺序应该是: [1,1,2,1,1]。
        示例 2:

        输入: [1,[4,[6]]]
        输出: [1,4,6]
        解释: 通过重复调用 next 直到 hasNext 返回false，next 返回的元素的顺序应该是: [1,4,6]。

    问题分析:
        NestedInteger对象提供了三个接口，
        isInteger() 返回是否是整数
        getInteger() 返回整数
        getList() 返回 vector<NestedInteger>

        对于这种实现迭代器的题， 如果遇到了需要递归的情况，基本就应该用栈来实现..
        因为，当要进入下一层的时候，我们要保存当前层的信息，以遍下次继续，
        而因为每一层都被打包成了一个NestedInteger对象，所以我们不妨反着先存进入，
        然后依次处理栈顶的情况！

        这里处理栈顶的情况就是一层一层剥开，直到栈顶元素是Integer，就可以把它拿出来了
*/

class NestedIterator {
public:
    stack<NestedInteger> st;
    NestedIterator(vector<NestedInteger> &nestedList) {
        // 反着先入栈
        for ( int i=(int)nestedList.size() -1 ; i>=0 ; --i )
            st.push(nestedList[i]);
    }

    int next() {
        // hasNext()保证了栈顶如果存在元素，则一定是Integer
        if ( !hasNext() ) return INT_MIN;
        int res = st.top().getInteger();
        st.pop();
        return res;
    }

    bool hasNext() {
        // 开始剥栈顶， 如果栈顶元素不是Integer，那就开始剥
        while( !st.empty() && !st.top().isInteger() ){
            vector<NestedInteger> arr = st.top().getList();
            st.pop();
            // 同理，逆向入栈
            for ( int i=(int)arr.size()-1; i>=0; --i ){
                st.push(arr[i]);
            }
        }
        return !st.empty();
    }
};

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */
