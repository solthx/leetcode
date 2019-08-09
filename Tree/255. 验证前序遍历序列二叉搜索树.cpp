/*
    问题描述：
        给定一个整数数组，你需要验证它是否是一个二叉搜索树正确的先序遍历序列。
        你可以假定该序列中的数都是不相同的。
        参考以下这颗二叉搜索树：

             5
            / \
           2   6
          / \
         1   3

        示例 1：
        输入: [5,2,6,1,3]
        输出: false

        示例 2：
        输入: [5,2,1,3,6]
        输出: true

    问题分析：
        方法一:
            第一个元素肯定是跟节点 l,
            然后 nums[l+1, .. ,mid] 全小于 nums[l]
            然后 nums[mid+1, .., r] 全大于 num[l]
            那么当前根合法，
            然后递归判断nums[l+1, .. ,mid], nums[mid+1, .., r]
        
        方法二:
            用栈来做, 模拟前序遍历
            保证栈是递减的，发现元素大于栈顶元素，就说明是节点遍历要返回父节点了，
            此时，栈顶元素就是父节点，
            接着就是去父节点的右子树，那么一定都大于父亲节，
            所以设一个下限值 lower = 父节点，
            然后每次扫描的时候，都要和lower比，
            如果小于等于lower，说明不合法，
            lower初始为负无穷. 
            复杂度O(N)
 */


class Solution1 {
public:
    bool verifyPreorder(vector<int>& preorder) {
        return helper( preorder,0, preorder.size()-1 );
    }
    
    bool helper( vector<int>& nums, int l, int r ){
        if ( l>=r  ) return true;
        int i=l+1, mid, hi;
        while( i<=r && nums[i]<=nums[l] ){
            if ( nums[i]==nums[l] ) return false;
            ++i;
        }
        mid = i-1;
        while( i<=r && nums[i]>nums[l] ){
            ++i;
        }
        if ( i<=r ) return false;
        hi = i-1;
        return helper( nums,l+1, mid ) && helper( nums, mid+1, hi );
    }
};

class Solution2 {
public:
    bool verifyPreorder(vector<int>& preorder) {
        long long lower = -INT_MAX; 
        stack<int> st;
        for ( auto e:preorder ){
            if ( st.empty() || st.top()>e )
                if ( e>lower )
                    st.push(e);
                else return false;
            else if ( st.top()==e ) return false;
            else{
                while( !st.empty() && st.top()<e ){
                    lower = st.top();
                    st.pop();
                }
                st.push(e);
            }
        }
        return true;
    }
    
};

