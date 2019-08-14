/*
    问题描述:
        给定一个二叉树，返回其结点 垂直方向（从上到下，逐列）遍历的值。
        如果两个结点在同一行和列，那么顺序则为 从左到右。
        示例 1：
        输入: [3,9,20,null,null,15,7]

            3
            /\
           /  \
          9   20
               /\
              /  \
             15   7 

        输出:
            [
                [9],
                [3,15],
                [20],
                [7]
            ]

        示例 2:
        输入: [3,9,8,4,0,1,7]

           3
           /\
          /  \
         9    8
         /\   /\
        /  \ /  \
       4   0 1   7 

        输出:
        [
            [4],
            [9],
            [3,0,1],
            [8],
            [7]
        ]
        
        示例 3:
        输入: [3,9,8,4,0,1,7,null,null,null,2,5]（注意：0 的右侧子节点为 2，1 的左侧子节点为 5）

            3
            /\
           /  \
           9   8
          /\  /\
         /  \/  \
         4  01   7
            /\
           /  \
           5   2

        输出:
        [
            [4],
            [9,5],
            [3,0,1],
            [8,2],
            [7]
        ]

    问题分析：
        仔细观察以后发现， 只要向左走， idx就减1， 向右走idx就加1
        因为这样的话 最中间是0， 向左idx回小于0， 所以用map先暂时来记录， 最后再一起放进vector里
        因为内部vector是从上到下的顺序， 所以应该用层序遍历
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
    int idx=-1;
    vector<vector<int>> verticalOrder(TreeNode* root) {
        /*
            1. 先找到最左边的节点
            2. 向右移动( 不管是向右回溯还是右下走 都算向右移动 )
               的时候，idx+1
            3. 向左移动, idx-1
        */
        if ( !root ) return {};
        queue<pair<int,TreeNode*>> q;
        q.push({0,root});
        map<int,vector<int>> sav;
        vector<vector<int>> res;
        int idx=0;
        while( !q.empty() ){
            pair<int,TreeNode*> p = q.front(); q.pop();
            sav[p.first].push_back(p.second->val);
            if ( p.second->left!=NULL )
                q.push({p.first-1, p.second->left});
            if ( p.second->right!=NULL )
                q.push({p.first+1, p.second->right});
        }
        for ( auto e:sav )
            res.push_back(e.second);
        return res;
    }
    
};
