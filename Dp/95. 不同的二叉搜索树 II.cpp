/*
    问题描述:   
        给定一个整数 n，生成所有由 1 ... n 为节点所组成的二叉搜索树。

        示例:

        输入: 3
        输出:
        [
          [1,null,3,2],
          [3,2,null,1],
          [3,1,null,null,2],
          [2,1,3],
          [1,null,2,null,3]
        ]
        解释:
        以上的输出对应以下 5 种不同结构的二叉搜索树：
           1         3     3      2      1
            \       /     /      / \      \
             3     2     1      1   3      2
            /     /       \                 \
           2     1         2                 3

    问题分析：
        方法一:
            分治，helper(1,n) 返回 val的取值范围为1~n的所有情况的二叉搜索树的树根
 
        方法二：
            分治+记忆化， 在方法一的基础上加个memo数组，曾经计算过的就不用重复计算了

        方法三:
            动态规划.
            dp[i]保存取值范围为[1,i]的所有树的情况的树根的情况
        
            根为i的话，
            左子树直接是dp[i-1]
            而右子树[i+1,n]的情况，可以转换成 [1,n-i] 然后对每一个值加上i ，
            就是对dp[n-i]里的每一颗树的所有值都加上i  
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

class Solution2{
public:
    vector<TreeNode*> generateTrees(int n) {
        // 记忆化
        vector<vector<vector<TreeNode*>>> memo(n+2, vector<vector<TreeNode*>>(n+2));
        if ( n==0 )
            return {};
        else 
            // 返回取值范围为[1,n] 之间的所有情况
            return helper( 1, n, memo ) ;
    }
    
    vector<TreeNode*> helper( int start, int end, vector<vector<vector<TreeNode*>>>& memo ){
        if ( memo[start][end].size()>0 ) return memo[start][end];
        if ( start>end ){
            memo[start][end].push_back(NULL);
            return memo[start][end];
        }
        
        for ( int i=start; i<=end; ++i ){
            auto left = helper( start, i-1 , memo );
            auto right = helper( i+1, end , memo );
            for ( auto l:left )
                for ( auto r:right ){
                    TreeNode*node = new TreeNode(i);
                    node->left = l;
                    node->right = r;
                    memo[start][end].push_back(node);
                }
        }
        return memo[start][end];
    }
};



class Solution3{
public:
    vector<TreeNode*> generateTrees(int n) {
        if ( n==0 ) return {};
        vector<vector<TreeNode*>> dp( n+1 );
        dp[1].push_back(new TreeNode(1));
        dp[0].push_back(NULL);
        for ( int i=2; i<=n; ++i ){
            // 选root
            for ( int root=1; root<=i; ++root ){
                // 填充右子树
                for ( int r=0; r<dp[i-root].size(); ++r ){
                    TreeNode * tmp_right = Plus( dp[i-root][r], root );
                    for ( int l=0; l<dp[root-1].size(); ++l ){
                        TreeNode *rt = new TreeNode(root);
                        rt->right = tmp_right;
                        rt->left = dp[root-1][l];
                        dp[i].push_back(rt);
                    }
                }
            }
        }
        return dp[n];
    }
    
    TreeNode * Plus( TreeNode* rt, int addition ){
        if ( !rt ) return NULL;
        TreeNode * node = new TreeNode(rt->val + addition);
        node->left = Plus(rt->left, addition);
        node->right = Plus(rt->right, addition);
        return node;
    }
};