/*
    问题描述:
        给你一个整数数组 digits，你可以通过按任意顺序连接其中某些数字来形成 3 的倍数，请你返回所能得到的最大的 3 的倍数。

        由于答案可能不在整数数据类型范围内，请以字符串形式返回答案。

        如果无法得到答案，请返回一个空字符串。

         

        示例 1：

        输入：digits = [8,1,9]
        输出："981"
        示例 2：

        输入：digits = [8,6,7,1,0]
        输出："8760"
        示例 3：

        输入：digits = [1]
        输出：""
        示例 4：

        输入：digits = [0,0,0,0,0,0]
        输出："0"
         

        提示：

        1 <= digits.length <= 10^4
        0 <= digits[i] <= 9
        返回的结果不应包含不必要的前导零。

    问题分析:
        是K的倍数，可以翻译成%K==0 (废话

        这题用到了整除性质..

        这个数字能被3整除 <=> 这个数字的各个位上的数字的和 能被3整除

        无语了.. 知道这个性质以后 就很简单了..

        

        求每一位上的数字和:
        1. sums % 3 == 0:
            按递减顺序，凑出结果
        2. sums % 3 == 1:
            多出来的1 有可能是 1个"mod3余1的数字"提供的： 1,4,7
                    也可能是2个 "mod3余2的数字"提供的: 2,5,8
        3. sums % 3 == 2:
            多出来的2 有可能是 1个"mod3余2的数字"提供的: 2,5,8
                    也可能是2个 "mod3余1的数字"提供的: 1,4,7

        所以我们先统计0～9的每个数字的出现次数，

        然后尝试删掉1个数，看结果能否满足..
        
        如果不存在这样的数, 那么就尝试删2个:
            9*9也就81种情况，枚举一下行了..

        如果都不行, 那说明组不成这样的数, 直接""
        如果是"00000"，记得过滤0
*/

class Solution {
public:
    int dp[10]={0};
        
    string largestMultipleOfThree(vector<int>& digits) {
        // 统计0～9数字的出现次数
        for(auto&d:digits)
            dp[d]++;
        int sums = accumulate(digits.begin(), digits.end(), 0);
        
        // 需要删数字，先尝试删一个
        if (sums%3!=0){
            for (int i=1; i<=9; ++i)
                if ( dp[i]>0 && (sums-i)%3==0 ){
                    --dp[i];
                    sums -= i;
                    break;
                }
        }
        
        // 如果删一个数字之后还不行，就删2个
        if (sums%3!=0){
            for (int i=1; i<=9; ++i)
                for(int j=1; j<=9; ++j)
                    if ( i!=j && dp[i]>0 && dp[j]>0 && (sums-i-j)%3==0 ){
                        --dp[i];
                        --dp[j];
                        sums-=(i+j);
                        goto dd;
                    // 如果i和j相等的话，就dp[i]就需要至少2个才行！
                    }else if (i==j && dp[i]>1 && (sums-(i+j))%3==0 ){
                        dp[i]-=2;
                        sums -= 2*i;
                        goto dd;
                    }
        }
        // 不可能的情况
        if (sums%3!=0) return "";
        dd:
        string res;
        // 递减构成结果
        for(int i=9; i>=0; --i)
            res += helper(dp[i], (char)(i+'0'));
        // 不存在的情况
        if (res.size()==0)
            return "";
        if (check(res))
            return "0";
        return res;
    }
   
    // 是否位全0
    bool check(string a){
        for(auto&c:a)
            if (c!='0')
                return false;
        return true;
    }
    
    string helper(int a, char c){
        string res;
        while(a--)
            res+=c;
        return res;
    }
    
};