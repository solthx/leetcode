/*
    问题描述：
        给定一个有相同值的二叉搜索树（BST），找出 BST 中的所有众数（出现频率最高的元素）。

        假定 BST 有如下定义：

        结点左子树中所含结点的值小于等于当前结点的值
        结点右子树中所含结点的值大于等于当前结点的值
        左子树和右子树都是二叉搜索树
        例如：
        给定 BST [1,null,2,2],

           1
            \
             2
            /
           2
        返回[2].

        提示：如果众数超过1个，不需考虑输出顺序

        进阶：你可以不使用额外的空间吗？（假设由递归产生的隐式调用栈的开销不被计算在内）

    问题分析:
        直接说进阶解法，利用bst的中序遍历有序的特性，
        cnt记录当前个数，
        pre记录前一个数字，
        maxi记录同一个数字出现的最多个数

        然后中序遍历，更新res

        只要题目说了bst 就一定要用到"有序" 这个特性。
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
    vector<int> res;
    int maxi=0;
    int cnt=0;
    int pre=0;
    vector<int> findMode(TreeNode* root) {
        if ( root ){
            findMode(root->left);
            if ( maxi==0 ){
                cnt=1;
                maxi = 1; 
                pre=root->val;
                res.push_back(root->val);
            }else if ( pre==root->val ){
                ++cnt;
                if ( cnt>maxi ){
                    maxi = cnt;
                    res.clear();
                    res.push_back(pre);
                }else if ( cnt==maxi ){
                    res.push_back(root->val);
                }
            }else{
                cnt=1;
                pre = root->val;
                if ( maxi<=1 ){
                    maxi = 1;
                    res.push_back(root->val);
                }
            }
            findMode(root->right);
        }
        return res;
    }
};
