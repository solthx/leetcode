一、 STL: 自定义堆
    // 1.堆的常用操作
    priority_queue<int> q;
    q.push(1);
    q.pop();
    q.top(); //堆顶

    // 2.1 构建大顶堆 ( 默认情况 )
    priority_queue<int> q;

    // 2.2 构建小顶堆 ( 模版自带 )
    // 这三个参数分别是 元素类型，容器类型，compare类
    priority_queue<int, vector<int>, greater<int>> q; 

    // 2.3 自定义堆 
    // 例如: 想把vector<ListNode*> v， 根据node->val的大小来进行构造堆

    // lambda表达式写cmp 因为lambda表达式的函数类型是根据return来推的，所以用auto来"接着" 
    auto cmp = []( ListNode* a, ListNode* b ){
        return a->val > b->val;   // (a,b)可以理解成从下到上, 上面的(b)小，就是小顶，反之大顶
    };
    // decltype(..)是自动获取..的类型，因为cmp是用auto接住的，所以这里很难表示出来，直接用auto + decltype来帮我屏蔽掉比较函数的类型了
    // 不要忘记把cmp作为构造函数参数 ，即:  ... q(cmp); 
    priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> q(cmp); 


二、使用流来实现split
    已知：
        string s = "1,abc,55"
    把s按','分开

    1. 把','换成' '
    2. stringstream input(s)
    3. input>>first>>second>>third
        first : 1
        second: abc
        third : 55
