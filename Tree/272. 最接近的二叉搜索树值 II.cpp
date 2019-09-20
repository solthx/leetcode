/*
    问题描述：
        给定一个不为空的二叉搜索树和一个目标值 target，请在该二叉搜索树中找到最接近目标值 target 的 k 个值。
        注意：
            给定的目标值 target 是一个浮点数
            你可以默认 k 值永远是有效的，即 k ≤ 总结点数
            题目保证该二叉搜索树中只会存在一种 k 个值集合最接近目标值
        示例：

            输入: root = [4,2,5,1,3]，目标值 = 3.714286，且 k = 2

             4
            / \
           2   5
          / \
         1   3

        输出: [4,3]
        拓展：
            假设该二叉搜索树是平衡的，请问您是否能在小于 O(n)（n 为总结点数）的时间复杂度内解决该问题呢？

    问题分析:
        方法一:  中序遍历+双端队列
            维护一个大小为k的window,  中序遍历保证了访问顺序是递增的,
            因为每次在窗口的末尾处添加元素，因此， 窗口中的元素也是递增的, 
            
            窗口的首个元素就是最小的元素，

            所以，对于新来的元素，如果 abs(target-窗口的最小元素) > abs(target-新来的元素)
            那就把那个最小元素给丢掉，然后新来的元素加进来

            最终，这个window里的所有元素就是答案.
        
        方法二： 栈 O(logn)
            拓展里要求我们要用小于O(N)的解法, 这里的思想比较棒!!!
            
            先说一下核心思路:
                1. 先找到最接近target的两个数（一个大一个小）, 例如:
                             4
                            / \
                           2   5
                          / \   \
                         1   3   6
                这个例子中，target=3.7, 那么两个数就是3和4.

                2. bst的中序遍历 得到的是递增的序列, 所以在这个递增序列里，
                我们从得到的这两个数，向两边扫描,
                即序列为： 1  2  3  4  5  6
                               ^  ^
                然后向两边扩展:   1  2  3  4  5  6 
                                   ^  ^  ^  ^  
                3. 直到扩展满k个元素， 就可以返回了.
            
            实现上，我们虽然我们可以先前序遍历，得到一个升序序列，然后再来做，但这么做的话，复杂度就变成O(N)了

            如果想变成logN的话，我们就需要利用到bst的性质了.

            在这里，在bst中实现这个的思路就是用两个栈pred和succ
            pred里保存所有小于target的元素，
            succ里保存所有大于target的元素,
            
            我们从根开始，寻找和target最接近的两个数,
            while root!=null :
                if root->val > target :
                    succ.push(root); 
                    root = root->left;  // root的左子树中可能有更接近target的
                else 
                    pred.push(root);
                    root = root->right; // root的右子树中可能有更接近target的
            
            出了循环以后，pred和succ的栈顶的两个元素，就是最接近target的两个元素了

            在同一个栈中，每次push进去的元素接近target的的程度，都要比上一次push进去的元素要更接近target
            这是因为，遍历的顺序就是不断的寻找更加接近target的的过程.

            得到了最接近target的的两个数之后，接下来就是向两边扩展了，
            利用bst的中序遍历是有序的性质，我们可以通过找pred的栈顶元素的在中序遍历的前驱节点
            和 找succ的栈顶元素在中序遍历的后继节点，来进行向两边的扩展.

            但寻找前驱节点和后继节点的方法也比较秀，
            
            先来看 寻找R的前驱节点 ：
                1.  如果有R有左子树, 那么左子树的最右元素，就是R的前驱节点 (这个是中序遍历的性质，比较基础就不多说原因了)
                    这种情况属于: 前驱节点在当前节点的孩子中

                2. 如果R没有左子树，那么该怎么办呢?
                    来看一个情况:
                        4
                         \
                          6
                         / \
                        5   7
                    
                    当到位置5的时候，发现前驱节点是4， 那该怎么找4呢?
                    我们可以发现, 这种没有左子树的情况，就是“前驱节点在当前节点的祖先中”
                    
                    而这种情况，我们在构造pred的时候，其实就已经把这种节点给push进去了,

                    为什么呢?

                    因为中序遍历的前驱节点一定是比当前节点小的，
                    
                    然后就pred来看的话，向pred里push元素就是递增的过程，
                    
                    而当前节点R又是栈顶，
                    
                    所以，在栈中，栈顶的下一个元素，就是这个栈顶的这个子树的前一个元素！！！！

                    因此，当栈顶的节点不存在左子树的时候，那么这个节点的前驱节点就是栈顶的下一个元素！ 

                找后继节点的思想和找前驱一样，这里不多说了.. 
                
                再次总结一下找前驱节点的思想，
                    通过栈来保存了"前驱节点在祖先中的情况"，
                    然后通过找左子树的最右节点来找“前驱节点在子树中的情况”。
                
                后继节点同理
*/

class Solution1 {
private:
    deque<int> q;
    int k;
public:
    vector<int> closestKValues(TreeNode* root, double target, int k) {
        // 中序遍历+双端队列
        if ( !root ) return {};
        int i=0; this->k = k;
        helper( root, i, target );
        return vector<int>(q.begin(), q.end());
    }
    void helper(  TreeNode* r, int & idx, double target ){
        if ( !r ) return ;
        helper( r->left, idx, target );
        if ( q.size()<k || abs( (double)q.front() - target ) > abs( (double)r->val - target ) ){
            q.push_back(r->val);
            if ( q.size()>k ) q.pop_front();
        }
        helper(  r->right, idx, target );
    }
};


/*=================================Solution2==================================*/
class Solution2 {
public:
    // 双栈
    vector<int> closestKValues(TreeNode* root, double target, int k) {
        stack<TreeNode *> succ, pred;
        while( root ){
            if ( root->val>target ){
                succ.push(root);
                root = root->left;
            }else{
                pred.push(root);
                root = root->right;
            }
        }
        vector<int> res;
        while( k>0 && !succ.empty() && !pred.empty() ){
            if ( succ.top()->val-target < target - pred.top()->val ){
                res.push_back( succ.top()->val );
                getNext( succ );
            }else{
                res.push_back(pred.top()->val);
                getPre( pred );
            }
            --k;
        }
        while( k>0 && !succ.empty()  ){
            res.push_back( succ.top()->val );
            getNext( succ );
            --k;
        }
        while( k>0 &&  !pred.empty()  ){
            res.push_back(pred.top()->val);
            getPre( pred );
            --k;
        }
        return res;
    }
    
    void getPre( stack<TreeNode *> & st ){
        // 即左子树的最右节点
        // 若没有左子树，那么就没有前驱了
        TreeNode * sav = st.top(); st.pop();
        sav = sav->left;
        while( sav ){
            st.push(sav);
            sav = sav->right;
        }
    }
    
    void getNext( stack<TreeNode *> & st  ){
        // 即右子树的最左节点
        TreeNode * sav = st.top(); st.pop();
        sav = sav->right;
        while( sav ){
            st.push(sav);
            sav = sav->left;
        }
    }
};