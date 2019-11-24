/*
    问题描述:
        给你一个产品数组 products 和一个字符串 searchWord ，products  数组中每个产品都是一个字符串。
        请你设计一个推荐系统，在依次输入单词 searchWord 的每一个字母后，推荐 products 数组中前缀与 searchWord 相同的最多三个产品。如果前缀相同的可推荐产品超过三个，请按字典序返回最小的三个。
        请你以二维列表的形式，返回在输入 searchWord 每个字母后相应的推荐产品的列表。

        示例 1：

        输入：products = ["mobile","mouse","moneypot","monitor","mousepad"], searchWord = "mouse"
        输出：[
            ["mobile","moneypot","monitor"],
            ["mobile","moneypot","monitor"],
            ["mouse","mousepad"],
            ["mouse","mousepad"],
            ["mouse","mousepad"]
        ]
        解释：按字典序排序后的产品列表是 ["mobile","moneypot","monitor","mouse","mousepad"]
        输入 m 和 mo，由于所有产品的前缀都相同，所以系统返回字典序最小的三个产品 ["mobile","moneypot","monitor"]
        输入 mou， mous 和 mouse 后系统都返回 ["mouse","mousepad"]
        示例 2：

        输入：products = ["havana"], searchWord = "havana"
        输出：[["havana"],["havana"],["havana"],["havana"],["havana"],["havana"]]
        示例 3：

        输入：products = ["bags","baggage","banner","box","cloths"], searchWord = "bags"
        输出：[["baggage","bags","banner"],["baggage","bags","banner"],["baggage","bags"],["bags"]]
        示例 4：

        输入：products = ["havana"], searchWord = "tatiana"
        输出：[[],[],[],[],[],[],[]]
         

        提示：

            1 <= products.length <= 1000
            1 <= Σ products[i].length <= 2 * 10^4
            products[i] 中所有的字符都是小写英文字母。
            1 <= searchWord.length <= 1000
            searchWord 中所有字符都是小写英文字母。

    问题分析:
        
        字符串的比较都是字典序的比较.

        可以用二分查找来做.

        一个信息是:
            1. 假设前缀字符串是predix
            如果一个字符串s是以 predix 为起始的, 那么 一定有: s>=predix

            2.  1的逆否命题依然为真:
                如果 s<predix，那么predix一定不是s的前缀！！

            3. 1仅仅是充分条件，不是充要条件，因此：
                如果s>=predix， 那么只能说predix可能是s的前缀：
                    3.1  s = "abcd" predix = "abc" 是前缀
                    3.2  s = "z"    predix = "abc" 不是前缀

        因此，利用逆否命题的结论，就可以先按字典序排序，再二分去找首个 满足s>=predix的s。
        
        找到以后，从第一个找到的位置开始向后遍历，只要 第i个字符串的前缀不是predix，那么后面都一定不是了。
*/

class Solution {
public:
    vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
        vector<vector<string>> res;
        // 按字典序排序
        sort( products.begin(), products.end());
        string pre = "";
        for ( auto c:searchWord ){
            pre += c;
            int mid, l = 0, r = (int)products.size()-1;

            // 二分查找
            while( l<=r ){
                mid = l + (r-l)/2;
                int state = products[mid].compare(pre);
                if ( state>=0 ) r = mid -1;
                else l = mid +1;
            }
            vector<string> cur;
            for ( int i=l; i<products.size() && cur.size()<3 ; ++i ){
                if ( startWith( products[i], pre ) ){
                    cur.push_back( products[i] );
                }else break;
            }
            res.push_back( cur ); 
        }
        return res;
    }

    bool startWith( string a, string pre ){
        int i=0, j=0;
        while( i<a.size() && j<pre.size() && a[i]==pre[j] ){
            ++i; ++j;
        }
        return j>=pre.size();
    }
};