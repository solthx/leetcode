/*
    问题描述:
        给出基数为 -2 的两个数 arr1 和 arr2，返回两数相加的结果。
        数字以 数组形式 给出：数组由若干 0 和 1 组成，按最高有效位到最低有效位的顺序排列。例如，arr = [1,1,0,1] 表示数字 (-2)^3 + (-2)^2 + (-2)^0 = -3。数组形式 的数字也同样不含前导零：以 arr 为例，这意味着要么 arr == [0]，要么 arr[0] == 1。
        返回相同表示形式的 arr1 和 arr2 相加的结果。两数的表示形式为：不含前导零、由若干 0 和 1 组成的数组。

        示例：
            输入：arr1 = [1,1,1,1,1], arr2 = [1,0,1]
            输出：[1,0,0,0,0]
            解释：arr1 表示 11，arr2 表示 5，输出表示 16 。
         
        提示：
            1 <= arr1.length <= 1000
            1 <= arr2.length <= 1000
            arr1 和 arr2 都不含前导零
            arr1[i] 为 0 或 1
            arr2[i] 为 0 或 1

    问题分析：
        二进制加法的变种，
        二进制加法，某一位上计算结果的值域为{ 0,1,2 }
        负数二进制加法，某一位上计算结果的值域为{ -1,0,1,2,3 }
        
        正常当前位的进位，进位到下一位都要取个反，所以 0 + 0 + 进位(-1) = -1
        如果当前结果为-1， 那么就要借位，借位一般是-1，但取个反就变成正1了
        ( 之所以取反是因为 01+01==10 而10不再是02，而是-02，也就是减去02，即-10 )

        同时最后不要忘记 处理最后一个进位。
        以及过滤最前面冗余的“0”


        理解了上面的这个规则后，然后就可以像二进制加法那样，来进行负二进制加法。
*/

class Solution {
public:
    vector<int> addNegabinary(vector<int>& arr1, vector<int>& arr2) {
        int i=arr1.size()-1, j=arr2.size()-1;
        int jin=0, cur;
        vector<int> res;
        while ( i>=0 && j>=0 ){
            cur = arr1[i] + arr2[j] +jin;
            if ( cur==-1 ){
                jin = 1;
                res.push_back(1);
            }else{
                res.push_back(cur%2);
                jin = ( cur/2 )*-1;
            }
            --i;--j;
        }
        while( i>=0 ){
            cur = arr1[i] +jin;
            if ( cur==-1 ){
                jin = 1;
                res.push_back(1);
            }else{
                res.push_back(cur%2);
                jin = ( cur/2 )*-1;
            }
            --i;
        }
        while( j>=0 ){
            cur = arr2[j] +jin;
            if ( cur==-1 ){
                jin = 1;
                res.push_back(1);
            }else{
                res.push_back(cur%2);
                jin = ( cur/2 )*-1;
            }
            --j;
        }
        // 处理最后一个进位
        if ( jin==-1 ){
            res.push_back(1);
            res.push_back(1);
        }else if ( jin==1 ){
            res.push_back(1);
        }
        // 反转一下
        reverse( res.begin(), res.end() );
        // 处理冗余的0
        while( res.size()>1 && res[0]==0 ) res.erase(res.begin());
        return res;
    }
};