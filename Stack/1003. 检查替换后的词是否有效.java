/*
    问题描述:
        给定有效字符串 "abc"。
        对于任何有效的字符串 V，我们可以将 V 分成两个部分 X 和 Y，使得 X + Y（X 与 Y 连接）等于 V。（X 或 Y 可以为空。）那么，X + "abc" + Y 也同样是有效的。
        例如，如果 S = "abc"，则有效字符串的示例是："abc"，"aabcbc"，"abcabc"，"abcabcababcc"。无效字符串的示例是："abccba"，"ab"，"cababc"，"bac"。
        如果给定字符串 S 有效，则返回 true；否则，返回 false。
         
        示例 1：

        输入："aabcbc"
        输出：true
        解释：
        从有效字符串 "abc" 开始。
        然后我们可以在 "a" 和 "bc" 之间插入另一个 "abc"，产生 "a" + "abc" + "bc"，即 "aabcbc"。
        示例 2：

        输入："abcabcababcc"
        输出：true
        解释：
        "abcabcabc" 是有效的，它可以视作在原串后连续插入 "abc"。
        然后我们可以在最后一个字母之前插入 "abc"，产生 "abcabcab" + "abc" + "c"，即 "abcabcababcc"。
        示例 3：

        输入："abccba"
        输出：false
        示例 4：

        输入："cababc"
        输出：false
         

        提示：

        1 <= S.length <= 20000
        S[i] 为 'a'、'b'、或 'c'

    问题分析:
        本题的第一大难点就读懂题意。。好吧开玩笑的。。

        本题的题意其实就是想让你不断的在字符串里删除"abc"， 如果最后能删成空串，那么就返回true，否则返回false
        
        用递归来做的方法很简单，就不赘述了。。

        另一个方法是用栈来做， 每次吧字符丢到栈里，然后扫描到目标字符串的最后一个字符时，就开始pop，如果连续的pop出来的字符串正好是目标字符串的逆序，那么就继续扫描。。

        扫描结束后，如果栈是空的，那么就说明是可以删完的，返回true，否则返回false。
*/

class Solution {
    public boolean isValid(String S) {
        Deque<Character> q = new ArrayDeque<>();
        for (char c : S.toCharArray()) {
            if (c != 'c')
                q.offerLast(c);
            else {
                if (q.isEmpty() || q.pollLast() != 'b')
                    return false;
                if (q.isEmpty() || q.pollLast() != 'a')
                    return false;
            }
        }
        return q.isEmpty();
    }
}