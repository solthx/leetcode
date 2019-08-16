/*
    问题描述:
        定义由 n 个连接的字符串 s 组成字符串 S，即 S = [s,n]。例如，["abc", 3]=“abcabcabc”。
        另一方面，如果我们可以从 s2 中删除某些字符使其变为 s1，我们称字符串 s1 可以从字符串 s2 获得。例如，“abc” 可以根据我们的定义从 “abdbec” 获得，但不能从 “acbbe” 获得。
        现在给出两个非空字符串 S1 和 S2（每个最多 100 个字符长）和两个整数 0 ≤ N1 ≤ 106 和 1 ≤ N2 ≤ 106。现在考虑字符串 S1 和 S2，其中S1=[s1,n1]和S2=[s2,n2]。找出可以使[S2,M]从 S1 获得的最大整数 M。

        示例：

            输入：
                s1 ="acb",n1 = 4
                s2 ="ab",n2 = 2

        返回：
                2

    问题分析:
        这题真的是很难啊。。。

        方法一：
            暴力，c++TLE, java 1800ms
            就是遍历S1(也就是n1个s1)， 看里面能有多少个s2。
            因为S2里有n2个s2，
            所以有S1里有cnt个s2也就是有cnt/n2个S2
        
        方法二:
            参数说明
            repeatCount[i]是指 前i个s1里包括了多少个s2
            nextIdx[i] 是指 扫描完第i个s1之后，s2中下一个要匹配的位置是几

            举个例子:
                Input:
                    s1="abacb", n1=6
                    s2="bcaa", n2=1

                Return:
                    3


            j --------------->  1 2    3 0 1      2    3 0 1      2    3 0   
            S1 --------------> abacb | abacb | abacb | abacb | abacb | abacb 

            repeatCount ----->    0  |   1   |   1   |   2   |   2   |   3

            nextIndex ------->    2  |   1   |   2   |   1   |   2   |   1
                                b c    a a,b      c    a a,b    ...     ...      
                              
        s2[nextIndex]----->   s2[2]=a , s2[1]=c, s2[2]=a,  

            由此，我们发现，在这n1个s1中找有多少个s2的时候，中间有一部分是有周期循环的，
            这一周期循环的特点就是 "以nextIndex为周期循环"， 正如上面的例子中，
            2 1 2 1 .. 当我们第二次遇到2的时候，就说明周期开始了。

            我们的目标是求n1个s1中 包含了多少个s2， 
            也就等于  所有周期区间包含的s2个数 + 非周期区间包含的s2个数
            下面具体来讲怎么求

            我们每次扫描完一个s1都记录下“此刻下一个待匹配的s2[j]也就是nextIdx[i]”, 
            然后，每扫描完一个周期，我们就看当前周期的nextIndex是否第一次出现，如果是，那就存起来等待下次匹配，如果不是，那么说明周期开始( nextIndex[start]==nextIndex[c1] ) 说明start是周期开始

            找到周期开始位置start后， 就可以计算周期长度
            例如 nextIndex[start]==nextIndex[c1] // c1表示当前刚扫描完第c1个的s1
            那么 周期区间长度interval = c1-start
            该区间内，包含的s1的数量，就是 repeatCount[c1] - repeatCount[start]
            
            所以，所有周期区间内 包含的s2的个数就是
                    cnt1 = (c1-start) * (repeatCount[c1] - repeatCount[start])
            
            然后就是非周期区间内的s2个数，
                就是由 [0,start] + 周期区间 + 尾巴 
                补充一下：所谓的尾巴就是 长度不够一个区间 ( ( n1-start ) % interval )，但是跟前缀区间[0,start]可以组合。
                同时，因为每个周期内的区间都是相同的，所以这个尾巴可以理解成一个周期区间的前缀，然后等价的由第一个区间的前 "尾巴" 个组成

                所以，非周期区间内包含的s1个数就是:
                    cnt2 = repeatCount[ start + (n1-start)%interval ] 
                
                所以最后返回的结果就是
                        (cnt1+cnt2)/n2

        方法三:
            对方法二查找是否开始第一个区间的时候进行优化，
            用map来代替暴力循环。


        参考博客:
            https://www.cnblogs.com/grandyang/p/6149294.html
*/

class Solution1 {
public:
    // 暴力 TLE
    int getMaxRepetitions(string s1, int n1, string s2, int n2) {
        int i=0,j=0;
        int c1=0, cnt=0;
        while( c1<n1 ){
            i=0;
            while( i<s1.size() ){
                if ( s1[i]==s2[j] ){
                    if ( ++j>=s2.size() ){
                        cnt++;
                        j=0;
                    }
                }
                ++i;
            }
            c1++;
        }
        return cnt/n2;
    }
};

class Solution2 {
public:
    int getMaxRepetitions(string s1, int n1, string s2, int n2) {
        int i=0,j=0;
        int c1=1, cnt=0;
        int interval=0;
        
        vector<int> repeatCnt(n1 + 1, 0);
        vector<int> nextIdx(n1 + 1, 0);
        
        while( c1<=n1 ){
            i=0;
            while( i<s1.size() ){
                if ( s1[i]==s2[j] ){
                    if ( ++j>=s2.size() ){
                        cnt++;
                        j=0;
                    }
                }
                ++i;
            }
            repeatCnt[c1] = cnt;
            nextIdx[c1] = j;
            for ( int start=0; start<c1; ++start ){
                if ( nextIdx[start]==j ){
                    int interval = c1-start;
                    int repeat = ( n1-start )/interval;
                    int cnt1 =repeat * ( repeatCnt[c1]-repeatCnt[start] );
                    int cnt2 = repeatCnt[ start+(n1-start)%interval ];
                    return (cnt1+cnt2)/n2;
                }
            }
            c1++;
        }
        return cnt/n2;
    }
};


class Solution {
public:

    // 用unordered_map来查找 start
    int getMaxRepetitions(string s1, int n1, string s2, int n2) {
        int i=0,j=0;
        int c1=1, cnt=0;
        unordered_map<int,int> mp;
        vector<int> predix(n1+1,0);
        int interval=0;
        while( c1<=n1 ){
            i=0;
            while( i<s1.size() ){
                if ( s1[i]==s2[j] ){
                    if ( ++j>=s2.size() ){
                        cnt++;
                        j=0;
                    }
                }
                ++i;
            }
            
            predix[c1] = cnt;
            if ( mp.count(j)>0 ){
                int start = mp[j];
                interval = c1-start;
                int cnt1 = (( n1 - start )/interval) * ( predix[c1]-predix[start] );
                int cnt2 = predix[start+(n1-start)%interval];
                return (cnt1+cnt2)/n2;
            }else mp[j] = c1;
            c1++;
        }
        return cnt/n2;
    }
};