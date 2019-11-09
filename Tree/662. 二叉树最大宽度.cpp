/*
    问题描述：
        给定一个二叉树，编写一个函数来获取这个树的最大宽度。树的宽度是所有层中的最大宽度。这个二叉树与满二叉树（full binary tree）结构相同，但一些节点为空。

        每一层的宽度被定义为两个端点（该层最左和最右的非空节点，两端点间的null节点也计入长度）之间的长度。

        示例 1:

        输入: 

                  1
                /   \
               3     2
              / \     \  
             5   3     9 

        输出: 4
        解释: 最大值出现在树的第 3 层，宽度为 4 (5,3,null,9)。
        示例 2:

        输入: 

                 1
                /  
               3    
              / \       
             5   3     

        输出: 2
        解释: 最大值出现在树的第 3 层，宽度为 2 (5,3)。
        示例 3:

        输入: 

                 1
                / \
               3   2 
              /        
             5      

        输出: 2
        解释: 最大值出现在树的第 2 层，宽度为 2 (3,2)。
        示例 4:

        输入: 

                 1
                / \
               3   2
              /     \  
             5       9 
            /         \
           6           7
        输出: 8
        解释: 最大值出现在树的第 4 层，宽度为 8 (6,null,null,null,null,null,null,7)。
        注意: 答案在32位有符号整数的表示范围内。


    问题分析:
        利用左孩子是2*i, 右孩子是2*i+1的这个特性来做。

        bfs就不多说了。
        dfs的做法就是，每一层维护一个pair， first保存当前层最左边的idx, second保存当前层最右边的idx，然后返回 max( 左子树的最大宽度，右子树的最大宽度, 当前层的最大宽度 )  
*/


// dfs
class Solution1 {
public:
    vector<vector<int>> lv;
    int widthOfBinaryTree(TreeNode* root) {
        return dfs( root, 0, 1 );
    }
    
    int dfs( TreeNode* rt, int depth, int id ){
        if ( !rt ) return 0;
        if ( lv.size()==depth ) lv.push_back({id,id});
        else lv[depth][1] = id;
        
        int lm=0, rm=0;
        if ( INT_MAX>=2*(long)id )
            lm = dfs(rt->left, depth+1, 2*id);
        if ( INT_MAX>=2*(long)id+1 )
            rm = dfs(rt->right, depth+1, 2*id+1);
        return max( lv[depth][1]-lv[depth][0]+1, max(lm, rm) );
    }
};



// bfs
class Solution2 {
public:
    unordered_map<TreeNode*,int> mp;
    int widthOfBinaryTree(TreeNode* root) {
        if ( !root ) return 0;
        deque<TreeNode*> q;
        q.push_back(root);
        mp[root] = 1;
        int res=1, cnt = 1;
        while( !q.empty() ){
            int mini = INT_MAX, maxi=INT_MIN;
            res = max(res, mp[q.back()] - mp[q.front()] + 1 );    
            for ( int j=q.size(); j>0; --j ){
                TreeNode * cur = q.front(); q.pop_front();
                if ( cur->left ){
                    q.push_back(cur->left);
                    mp[cur->left] = 2*mp[cur];
                }
                if ( cur->right ){
                    q.push_back(cur->right);
                    if ( INT_MAX>=2*(long)mp[cur]+1 )
                        mp[cur->right] = 2*(long)mp[cur]+1;
                }    
            }
        }
        return res;
    }
};