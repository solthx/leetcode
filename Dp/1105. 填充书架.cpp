/*
    问题描述:
        这个题看了半天才看懂...这里提炼一下.
        建一个书架，把书本放到架子上。
        架子宽度固定， 高度是要求的
        第i本书有两个属性
            book[i][0]是这本书的厚度，对应的是架子的宽度
            book[i][1]是这本书的高度，对应当前层的高度.
        
        一层放满了，可以再建一层，那么上一层的高度，就是上一层里所有书的最高的那本书的高度。
        现问，建一个书架，要求按顺序(一定是按顺序！！！)把书放满，并要求这个书架的高度最低，
        问这个最低的高度是多少.

    问题分析:
        虽然看题看的一头雾水，但看懂以后还是一头雾水...
        提示里给了状态：
            dp[i]是前i本书构成的书架的最小高度...
        但还是没想出怎么更新..
        看了题解才知道。。忽略了个条件。。就是书是按顺序放的，
        也就是说，第i本书一定放在第i-1本书的后面...

        这样就变成背包变种了(多了个宽度限制)...
        
        状态:
            dp[i]是前i本书构成的书架的最小高度
        状态转移:
            把新来的那本书一定是放在书架最高层的，
            那么就向前遍历所有情况，直到最高层的书的都放满。
            
            if ( sum{ book[j~i][宽度] } <= width ) 
                dp[i] = min( dp[i], dp[j-1] + max( book[j~i][高度] ) )
        
        ps：这题怎么看都是披着medium的hard...
 */


class Solution {
public:
    int minHeightShelves(vector<vector<int>>& books, int shelf_width) {
        // dp[i]表示放好前i本书的最小高度
        // 状态转移:
        //  if ( sum{ book[j~i][宽度] } <= width ) 
        //     dp[i] = min( dp[i], dp[j-1] + max( book[j~i][高度] ) )
        int n = books.size();
        vector<int> dp( n+1, INT_MAX );
        dp[0] = 0;
        for ( int i=1; i<=books.size(); ++i ){
            int j=i, h = 0, width=0;
            while( j>0 && width + books[j-1][0] <= shelf_width ){
                //可以把第j个加进来
                h = max( h, books[j-1][1]);
                dp[i] = min( dp[i], dp[j-1]+h );
                width += books[j-1][0];
                --j;
            }
        }
        return dp.back();    
    }
};