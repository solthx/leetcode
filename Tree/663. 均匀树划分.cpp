/*
    问题描述:
        给定一棵有 n 个结点的二叉树，你的任务是检查是否可以通过去掉树上的一条边将树分成两棵，且这两棵树结点之和相等。

        样例 1:

        输入:     
             5
            / \
           10 10
          /  \
          2   3

        输出: True
        解释: 
            5
           / 
          10
            
        和: 15

              10
             /  \
            2    3

        和: 15
         

        样例 2:

        输入:     
            1
           / \
          2  10
            /  \
            2   20

        输出: False
        解释: 无法通过移除一条树边将这棵树划分成结点之和相等的两棵子树。
         

        注释 :
            树上结点的权值范围 [-100000, 100000]。
            1 <= n <= 10000

    问题分析:
        切一刀一定是被分成两棵树， 那么就一个子树一个子树的来找， 即后序遍历的应用。。

        先遍历一遍，找到sum， 如果sum不是偶数 直接返回false。

        如果是偶数，在用后续遍历一个子树一个子树的找，直到找到和为sum/2的子树。。

        这里要注意的是，sum如果为0的话， 要排除掉根节点的情况。
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode * fb=NULL; // 记录一下根节点
    bool checkEqualTree(TreeNode* root) {
        int Sums = 0;
        fb = root;
        dfs( Sums, root ); // 求和
        if ( Sums%2 != 0 ) return false; // 和不是偶数的情况
        Sums /= 2;
        bool found = false;  
        helper( Sums, root, found );
        return found;
    }

    int helper( int & Sums, TreeNode * rt, bool & found ){
        if ( !rt ) return 0;
        int l = helper( Sums, rt->left, found );
        int r = helper( Sums, rt->right, found );
        int cur = l+r+rt->val;
        if ( cur == Sums && fb !=rt ){ // 排除掉根节点的情况
            found = true;
        }
        return cur;
    }

    void dfs( int &sums, TreeNode* rt){
        if ( !rt ) return ;
        sums += rt->val;
        dfs(sums, rt->left);
        dfs(sums, rt->right);
    }
};