/*
    问题描述:
        给定一个字符串 S，找出 S 中不同的非空回文子序列个数，并返回该数字与 10^9 + 7 的模。

        通过从 S 中删除 0 个或多个字符来获得子字符序列。

        如果一个字符序列与它反转后的字符序列一致，那么它是回文字符序列。

        如果对于某个  i，A_i != B_i，那么 A_1, A_2, ... 和 B_1, B_2, ... 这两个字符序列是不同的。

         

        示例 1：

        输入：
        S = 'bccb'
        输出：6
        解释：
        6 个不同的非空回文子字符序列分别为：'b', 'c', 'bb', 'cc', 'bcb', 'bccb'。
        注意：'bcb' 虽然出现两次但仅计数一次。
        示例 2：

        输入：
        S = 'abcdabcdabcdabcdabcdabcdabcdabcddcbadcbadcbadcbadcbadcbadcbadcba'
        输出：104860361
        解释：
        共有 3104860382 个不同的非空回文子字符序列，对 10^9 + 7 取模为 104860361。
         

        提示：

        字符串 S 的长度将在[1, 1000]范围内。
        每个字符 S[i] 将会是集合 {'a', 'b', 'c', 'd'} 中的某一个。

    问题分析：

        方法一: 三维区间Dp

            两个提示给的线索很大.. 因为长度在1000以内，所以一维dp或二维dp都可..

            当遇到值域范围比较小的时候( 例如 %K , 本题中{'a', 'b', 'c', 'd'} 中的某一个 )
            可以把这个范围比较小的值域作为一个状态保存...

            因为回文串是对称的，所以需要从两边的信息来入手， 因此需要用两维来保存 区间信息..

            进行更新的时候，应该是先检查两边的端点是否相等，  然后讨论.. 这样子的更新

            所以 dp[i][j][k] 就是 区间[i,j]内 以字符k为回文串左右端点的 不同回文串的个数..

            状态更新:
                for c from 'a' to 'd':
                    1. s[i] == s[j] == c :
                        dp[i][j][s[i]] = sum{ dp[i+1][j-1]['a'~'d'] } + 2  
                    多说两句，左右端点的相等，相当于外面加了层套子，我们得到的是 "c[区间[i+1,j-1]所有不同回文串]c"  
                    
                    而 多出来的那个常数2， 是 c 和 , cc 这两种情况..

                    2. s[i] != s[j]:
                        c != s[i] && c!=s[j]:
                            dp[i][j][s[i]] = dp[i+1][j-1][s[i]]
                        c != s[i]:
                            dp[i][j][s[i]] = dp[i+1][j][s[i]]
                        c != s[j]:
                            dp[i][j][s[i]] = dp[i][j-1][s[j]]
                    这个挺好理解的，就不多解释了..

        方法二: 二维区间Dp
            我们在讨论端点的情况时， 可以看出，对于s[i]==s[j] 和 s[i]!=s[j]的情况，
            我们只是关心在 [i+1,j-1]区间内的不同回文串的个数，

            回文串端点字符的状态 仅仅是在 s[i]!=s[j]的情况中 进行状态更新的时候，才用到..

            我们可以使用容斥原理 来优化掉 保存端点的这个状态..

            dp[i][j]保存了区间[i,j]内不同回文串的个数..

            当s[i]!=s[j]时，根据容斥原理,
                dp[i][j] = dp[i][j-1] + dp[i+1][j] - dp[i+1][j-1]
            

            当s[i]==s[j]时，
                状态更新为:
                    dp[i][j] = [i+1][j-1]区间内传递上来的情况 + 传递上来的情况在两边套上s[i]的情况 + 新增的两个字符能否构成新的回文的情况 
                    
                情况一:

                    index     s[i] ....s[l].....s[r]......s[j]
                    s[index]   c, ......c, ..... c ....... c

                    dp[i][j] = dp[i+1][j-1] + ( dp[i+1][j-1] - dp[l+1][r-1] ) 
                             = dp[i+1][j-1] * 2 - dp[l+1][r-1]
                解释:
                    1. [i+1][j-1]区间内传递上来的情况  ： 
                        dp[i+1][j-1]  没啥好说的
                    2. 传递上来的情况在两边套上s[i]的情况 + 新增的两个字符能否构成新的回文的情况 :
                        dp[i+1][j-1] - dp[l+1][r-1]
                    难点主要在这里.. 对于[l,r]区间里的不同回文串， 用s[i], s[j] 作为两端， 和用s[l], s[r]作为两端，组成的将回重复。。
                    因此，要减去这个重复..

                    3. 新增的两个字符能否构成新的回文的情况 :
                        因为两个c都出现过了，所以为0 
                
                后面的几种情况都是类似的来推..

                情况二:

                    index     s[i] ....s[l].......s[j]
                    s[index]   c, ......c, ....... c

                dp[i][j] = dp[i+1][j-1] + dp[i+1][j-1] + 1
                         = dp[i+1][j-1] * 2 + 1 
                    加的那个1 就是 “cc” 这个情况..

                情况三:
                    index     s[i] .........s[j]
                    s[index]   c, .......... c

                dp[i][j] = dp[i+1][j-1] + dp[i+1][j-1] + 2
                         = dp[i+1][j-1] * 2 + 2
                    加的那个2 就是 "c", “cc” 这2个情况.
*/

// 三维Dp
# define mod 1000000007
class Solution1 {
public:
    int countPalindromicSubsequences(string s) {
        // O(N^2 * 4)
        long dp[1001][1001][4] = {0};
        // 初始化
        for ( int i=0; i<s.size(); ++i )
                dp[i][i][s[i]-'a'] = 1;
        // 枚举端点
        for ( int len=2; len<=s.size(); ++len ){
            for ( int i=0; i<s.size(); ++i ){
                int j = i+len-1;
                if ( j>=s.size() ) break;    
                for ( char c='a'; c<='d'; ++c ){
                    // 讨论
                    if ( s[i] == c && s[j] == c )
                        dp[i][j][c-'a'] = (2 + dp[i+1][j-1][0] + dp[i+1][j-1][1]+ dp[i+1][j-1][2] + dp[i+1][j-1][3]) % mod; 
                    else if ( s[i]==c )
                        dp[i][j][c-'a'] = dp[i][j-1][c-'a'];
                    else if ( s[j]==c )
                        dp[i][j][c-'a'] = dp[i+1][j][c-'a'];
                    else dp[i][j][c-'a'] = dp[i+1][j-1][c-'a'];
                }
            }
        }
        int n = s.size();
        return (dp[0][n-1][0]+ dp[0][n-1][1]+ dp[0][n-1][2]+ dp[0][n-1][3])%mod;
    }
};


// 容斥原理 + 二维Dp
# define mod 1000000007
class Solution2 {
public:
    int countPalindromicSubsequences(string s) {
        long dp[1001][1001] = {0};
        // 初始化
        for ( int i=0; i<s.size(); ++i )
                dp[i][i] = 1;
        for ( int len=2; len<=s.size(); ++len ){
            for ( int i=0; i<s.size(); ++i ){
                int j = i+len-1;
                if ( j>=s.size() ) break;
                // 端点相等的情况
                if ( s[i] == s[j] ){
                    int l = i+1 , r=j-1;
                    while( l<=r && s[l]!=s[i] ) ++l;
                    while( r>=l && s[r]!=s[i] ) --r;
                    // 几种情况的讨论
                    if ( l>r ) dp[i][j] = 2*dp[i+1][j-1]+ 2;
                    else if ( l<r ) dp[i][j] = 2*dp[i+1][j-1] - dp[l+1][r-1];
                    else dp[i][j] = 2*dp[i+1][j-1]+1;
                }else{
                    // 端点不相等的情况
                    dp[i][j] = ( dp[i+1][j] + dp[i][j-1] - dp[i+1][j-1])%mod;
                }
                dp[i][j] %=mod;
                // 在mod时，遇到减号都可能回导致负数。。。回补一下就好了
                if ( dp[i][j]<0 ) dp[i][j] += mod;
            }
        }
        int n = s.size();
        return dp[0][n-1];
    }
};