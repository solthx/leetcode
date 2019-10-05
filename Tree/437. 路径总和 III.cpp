/*
    问题描述:
        给定一个二叉树，它的每个结点都存放着一个整数值。

        找出路径和等于给定数值的路径总数。

        路径不需要从根节点开始，也不需要在叶子节点结束，但是路径方向必须是向下的（只能从父节点到子节点）。

        二叉树不超过1000个节点，且节点数值范围是 [-1000000,1000000] 的整数。

        示例：

        root = [10,5,-3,3,2,null,11,3,-2,null,1], sum = 8

                10
               /  \
              5   -3
             / \    \
            3   2   11
           / \   \
          3  -2   1

        返回 3。和等于 8 的路径有:

        1.  5 -> 3
        2.  5 -> 2 -> 1
        3.  -3 -> 11

    问题分析:
        N^2的解法就不说了..

        看到这种 连续元素的和为k ， 应该条件反射的想到hashmap (还有分治)
        
        (其实说到hashmap.. 我想你应该知道该怎么做了...)
*/

class Solution {
public:
    unordered_map<int,int> mp;
    int pathSum(TreeNode* root, int sum) {
        mp[0]=1;
        int res=0;
        dfs( root, res, sum, 0 );
        return res;
    }
    
    void dfs( TreeNode * rt, int &res, int sum, int cur ){
        if ( !rt ) return ;
        cur += rt->val;
        res += mp[cur-sum];
        mp[cur]++;
        dfs( rt->left, res, sum, cur );
        dfs( rt->right, res, sum, cur );
        mp[cur]--;
    }
};