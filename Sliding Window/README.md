# 滑动窗口专题

模版:
```cpp
// l 和 r 为窗口的两个边界
for (int r = 0, l = 0; r < s.size(); r++) {
	// 窗口右端扩展，收录s[r], 更新条件
	while ( 移动l使得区间[l,r]合法 ) {
		// 执行操作 (例如和当前最优比较并保存)
		// 窗口左端移除s[i]，更新条件，i++
	}
    // 执行操作 ( 例如获取当前区间长度(r-l+1)然后尝试更新最长/短区间长度... )
}
```

上面的板子可以无脑切滑动窗口的medium题...

## 经典题目及思想:

<br>

## 1. 滑动窗口 + 数据接口(map / deque)
滑动窗口再进阶一下，可能会和其他数据结构结合，像`#239. 滑动窗口最大值` 

<br>

## 2. 维护两个滑动窗口 => 三指针
另外一个比较经典的思想就是通过维护两个滑动区间来构成`三指针`的解题思想.. 代表题目为: `#930. 和相同的二元子数组` 和 `#992. K 个不同整数的子数组` ..

维护的两个滑动窗口是： 都以r为右边界， 左边界一个是满足条件的最远情况lo , 一个是首个不满足的情况hi， 两个window为`[lo, r]`和 `[hi, r]` (lo<=hi) , 往往左边界在[lo,hi)之间都是合法的，通过滚动思想，在常数时间复杂度内来求合法的情况数.. 
