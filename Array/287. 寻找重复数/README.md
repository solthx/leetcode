## 在本题的方法二中，可以把问题抽象成，在下面这个含有环的线性表中，找出点A的位置，即环开始的位置。



![此处输入图片的描述][1]


    可以使用快慢指针，fast每次走两步，slow每次走一步，如果是真的存在环的话，fast和slow必定在环内的某个地方相遇，这里假设在B处相遇。  
    
    假设每圈周长为C，在slow转了k1圈，fast转了k2圈后在B点相遇
    
    我们先看slow走的路程：
        L1 = a + k1 * C + x;
    再来看fast走的路程：
        L2 = a + k2 * C + x;
    
    又有L2 = L1*2
    所以：
        a + k2 * C + x = 2 * （a + k1 * C + x）
    
    化简后得到：
        x+a = (k2-2*k1) * C
    又 C = x+b
    
    => a = (k2 - 2*k1 - 1)*C +C -x
    => a = (k2 - 2*k1 - 1)*C + x + b - x
    => a = (k2 - 2*k1 - 1)*C + b
    => a = T*C + b  (T = (k2 - 2*k1 - 1)）

也就是说，当fast和slow在B处相遇后， a和b的长度是一样的。

知道这个结论就好办多了，只要发现他们相遇，就让slow从头开始，fast从B开始也是每次只走一步
当他们再次相遇的时候，那个位置就是A。

  [1]: https://raw.githubusercontent.com/solthx/leetcode/master/Array/287.%20%E5%AF%BB%E6%89%BE%E9%87%8D%E5%A4%8D%E6%95%B0/%23287%E6%96%B9%E6%B3%95%E4%BA%8C.png