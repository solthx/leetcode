/*
    问题描述:
        给定一个有 N 个结点的二叉树的根结点 root，树中的每个结点上都对应有 node.val 枚硬币，并且总共有 N 枚硬币。

        在一次移动中，我们可以选择两个相邻的结点，然后将一枚硬币从其中一个结点移动到另一个结点。(移动可以是从父结点到子结点，或者从子结点移动到父结点。)。

        返回使每个结点上只有一枚硬币所需的移动次数。

        本题有图:
            https://leetcode-cn.com/classic/problems/distribute-coins-in-binary-tree/description/


        示例 1：

        输入：[3,0,0]
        输出：2
        解释：从树的根结点开始，我们将一枚硬币移到它的左子结点上，一枚硬币移到它的右子结点上。
        示例 2：

        输入：[0,3,0]
        输出：3
        解释：从根结点的左子结点开始，我们将两枚硬币移到根结点上 [移动两次]。然后，我们把一枚硬币从根结点移到右子结点上。
        示例 3：

        输入：[1,0,2]
        输出：2
        示例 4：


        输入：[1,0,0,null,3]
        输出：4

        提示：

        1<= N <= 100
        0 <= node.val <= N

    问题分析:
        当当前树依赖左右子树的情况的时候，就可以考虑用后序遍历来搞了..

        比如,  左子树多了x个coin (x<0时表示少了x个coin
               右子树多了y个coin

        那么，无论是多了x个还是少了x个，或者多了y个少了y个，

        它们都需要进行移动，因此，可以提前把这部分的移动给加到res里。

        如果从叶子节点就使用这个策略来做的话，那么每次移动的距离，就是多余或缺少 的 coin的个数, 即使abs(x), abs(y)

        向上传递的过程中，返回值就是:
            x + y + (r->val-1)

        分别代表 左子树多余的个数，右子树多余的个数，和根多余的个数 ( 同样的，这个个数如果小于0，就是缺少的个数

        很有趣的一题，记录一下。

*/
class Solution {
public:
    int res = 0;
    int distributeCoins(TreeNode* root) {
        dfs( root );
        return res;
    }

    int dfs( TreeNode * rt ){
        if ( !rt ) return 0;
        int l = dfs( rt->left );
        int r = dfs( rt->right );
        res += (abs(l)+abs(r));
        int offset = rt->val - 1;
        return l+r+offset;
    }
};