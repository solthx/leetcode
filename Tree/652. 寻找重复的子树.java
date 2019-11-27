/*
    问题描述:
        给定一棵二叉树，返回所有重复的子树。对于同一类的重复子树，你只需要返回其中任意一棵的根结点即可。

        两棵树重复是指它们具有相同的结构以及相同的结点值。

        示例 1：

                1
               / \
              2   3
             /   / \
            4   2   4
               /
              4
        下面是两个重复的子树：

             2
            /
           4
        和
           4

    问题分析:
        方法一: 后续遍历+HashMap+HashSet tle
            后续遍历来记录每一棵树，HashMap保存的entry为 { 值val : { 值为val的节点(同一个形状的只出现一个) } }
            HashSet来控制 同一个形状的只出现一次.

            后续遍历得到每一个子树， 然后去对应的val里 扫描看是否有相同的，并且只出现一次的。 
            复杂度较高...
        
        方法二: 序列化
            尽管知道肯定是用后续遍历，但上面的做法复杂度略高... 
            
            看了题解以后，发现居然还能把访问路径来编码成字符串，

            这个编码的字符串一定要保证 1对1的关系，

            即这个字符串唯一对应这个树， 这个树唯一对应这个字符串.

            因此，编码方法就是对空指针也进行标记。

            一旦对空指针的访问也记进前序遍历， 那么，其遍历序列将能和一颗树唯一对应。（注意，如果是中序遍历的话，那么即使记录的空指针，也可能出现二意性）

            因此，就对空指针也进行访问，然后保存其前序遍历或后续遍历就可以啦！

            （ps: 这个思想第一次了解， 居然还能这么玩TAT... 真是太棒了！
*/

class Solution {
    HashMap<String, Integer> cnt = new HashMap<>();
    ArrayList<TreeNode> res = new ArrayList<>();
    public List<TreeNode> findDuplicateSubtrees(TreeNode root) {
        last_order( root );
        return res;
    }

    private String last_order( TreeNode rt ){
        if ( rt==null ) return "#";
        String left = last_order(rt.left);
        String right = last_order(rt.right);
        String cur =  left  +  right + String.valueOf(rt.val) ;
        int state = cnt.getOrDefault( cur, 0 );
        if (state==1){  // 控制访问次数
            res.add(rt);    
        }
        cnt.put( cur, state+1 );
        return cur;
    }
}

/* 下面是TLE的写法 */

class Solution {
    HashMap<Integer, ArrayList<TreeNode>> mp = new HashMap<>();
    ArrayList<TreeNode> res = new ArrayList<>();
    HashSet<TreeNode> vis = new HashSet<>();

    public List<TreeNode> findDuplicateSubtrees(TreeNode root) {
        last_order( root );
        return res;
    }

    private void last_order( TreeNode rt ){
        if ( rt==null ) return ;
        last_order(rt.left);
        last_order(rt.right);
        if ( mp.containsKey(rt.val) ){
            boolean found = false;
            for ( TreeNode node:mp.get(rt.val) ){
                if ( Same(node, rt) ){
                    found = true;
                    if ( !vis.contains(node)  ){
                        vis.add(node);
                        res.add( rt );
                    }
                    break;
                }
            }
            if ( !found ){
                mp.get(rt.val).add( rt );
            }
        }else{
            mp.put( rt.val, new ArrayList<TreeNode>(){{add(rt);}} );
        }
    }

    private boolean Same( TreeNode a, TreeNode b ){
        if ( a==null && b==null ) return true;
        if ( a==null || b==null ) return false;
        if ( a.val!=b.val ) return false;
        return Same(a.left, b.left) && Same( a.right, b.right );
    }
}