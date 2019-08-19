#include <iostream>
#include <vector>
using namespace std;

const int N = 100;

/*
    看着教程自己写的板子... 
    过了lc上的板子题.. 不知道还有没有bug
    逻辑写的比较容易理解一些。。所以牺牲了一些效率
*/

struct {
    int lazy;
    int val;
    int l;
    int r;
    int maxi;
}tree[100];

// 重新更新tree[r]
void push_up(int r)
{
	tree[r].val = tree[r*2].val + tree[r*2+1].val;
    tree[r].maxi = max(tree[r*2].val, tree[r*2+1].val); 
}

// 建树
void build( int  arr[], int left, int right, int r ){
    if ( left==right ){
        tree[r].maxi = tree[r].val = arr[left-1];
        tree[r].l = tree[r].r = left;
        tree[r].lazy=0;
        return ;
    }
    int mid = (left+right)/2;
    build(arr, left, mid, 2*r);
    build(arr, mid+1, right, 2*r+1);
    tree[r].val = tree[r*2].val + tree[r*2+1].val ;
    tree[r].l = left;
    tree[r].r = right;
    tree[r].maxi = max(tree[r*2].val, tree[r*2+1].val); 
}

// 向下传递懒惰节点
void push_down( int i ){
    if ( tree[i].lazy==0 || tree[i].l==tree[i].r ) return ;
    int addition = tree[i].lazy;
    tree[i].lazy=0;
    tree[i*2].val += ( tree[i*2].r-tree[i*2].l+1 )*addition;
    tree[i*2+1].val += ( tree[i*2+1].r-tree[i*2+1].l+1 )*addition;
    tree[i*2].lazy += addition;
    tree[i*2+1].lazy += addition;
    tree[i*2].maxi += addition;
    tree[i*2+1].maxi += addition;   
}

// 最大值查询
int query_maxi( int i, int left, int right ){
     int res=0, mid=(tree[i].l+tree[i].r)/2;
    if ( left==tree[i].l && right==tree[i].r ) return tree[i].maxi;
    push_down(i);
    if ( right<=mid ) return query_maxi( 2*i, left, right );
    else if ( left>mid ) return query_maxi( 2*i+1, left, right );
    return max( query_maxi( i*2, left, mid ) , query_maxi(i*2+1,mid+1, right));
}

// 区间和查询
int query( int i, int left, int right ){
    int res=0, mid=(tree[i].l+tree[i].r)/2;
    if ( left==tree[i].l && right==tree[i].r ) return tree[i].val;
    push_down(i);
    if ( right<=mid ) return query( 2*i, left, right );
    else if ( left>mid ) return query( 2*i+1, left, right );
    return query( i*2, left, mid ) + query(i*2+1,mid+1, right);
}

// 区间更新
void range_update( int i, int left, int right, int val ){
    //if ( tree[i].l>right || tree[i].r<left ) return ; 
    if ( tree[i].l==left && tree[i].r==right ){
        tree[i].val += ( tree[i].r-tree[i].l+1 )*val;
        tree[i].maxi += ( val );
        //if ( tree[i].l!=tree[i].r )
        tree[i].lazy+=val;
        return ;
    }
    push_down( i );
    int mid = (tree[i].l+tree[i].r)/2;
    if ( mid>=right ) range_update( 2*i, left, right, val );
    else if ( mid<left ) range_update(2*i+1, left, right, val);
    else{
        range_update(2*i,left,mid,val);
        range_update(2*i+1,mid+1,right,val);   
    }
	push_up(i);
    return ;
}

// 单点更新
void update( int r, int idx, int val ){
    if ( tree[r].l==tree[r].r && tree[r].l==idx ){
        tree[r].val+=val;
        tree[r].maxi += val;
        return ;
    }
    int mid = ( tree[r].l + tree[r].r )/2;
    if ( idx<=mid ) update( 2*r, idx,val );
    else update(2*r+1, idx, val);
    push_up(r);
}

int main(void){
    int arr[] = {1,2,3,4,5,6,7};
    build( arr, 1, 8, 1 );
    cout<<query( 1, 1,5 )<<endl;
    range_update( 1, 1,3, 1 );
    //Add(1,3,1,1);
    range_update( 1, 2,4, -2 );
    //Add(2,4,1,-2);
    range_update( 1, 3,5, 3 );
    //Add(3,5,1,3 );
    cout<<query( 1, 2,5 )<<endl;
    cout<<query_maxi( 1, 2,5 )<<endl;
    return 0;
}