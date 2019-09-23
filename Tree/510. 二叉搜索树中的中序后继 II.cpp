/*
    问题描述:
        给一个二叉树节点，返回在中序遍历中，这个节点的后继节点.
        class Node {
        public:
            int val;
            Node* left,right;
            Node* parent;
        };

    问题分析:
        可能做题顺序应该是先做这一题再做 #272的， 在#272题解的方法二中，已经详细介绍了
        如何找后继节点和前驱节点. 

        这里再进一步说明一下，

        找中序遍历的后继节点的时候，

        如果后继节点不在当前节点的子树里的话( 右子树为空 )

        根据 左中右 , 那么 中->右的这个情况是不可能了，
        
        所以只能是左->中， 
        
        也就是说，如果当前节点是父节点的左孩子的话，那么父节点就是后继节点了！
        
        如果当前节点是父节点的右节点， 那么说明当前节点是“以父节点为根的树"做中序遍历的最后一个节点，
        因此可以继续向上传递，即看父节点是不是爷爷节点的做节点...这么做下去，直到找到当前节点是父节点的左孩子为止

        如果到根都没找到，那就说明当前节点是中序遍历的最后一个元素了。

        因此, 在#272的栈中， succ就只保存了所有元素的左孩子节点. 
*/
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* parent;
};
*/
class Solution {
public:
    Node* inorderSuccessor(Node* node) {
        if ( !node ) return node;
        Node * res=node->right;
        if ( !res ){
            while( node->parent && node->parent->right==node ) node = node->parent;
            
            return node==NULL?node:node->parent;
        }
        while( res->left ) res = res->left;
        return res;
    }
};