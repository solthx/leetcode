/*
    问题描述:
        如果出现下述两种情况，交易 可能无效：
            交易金额超过 ¥1000
            或者，它和另一个城市中同名的另一笔交易相隔不超过 60 分钟（包含 60 分钟整）
        每个交易字符串 transactions[i] 由一些用逗号分隔的值组成，这些值分别表示交易的名称，时间（以分钟计），金额以及城市。

        给你一份交易清单 transactions，返回可能无效的交易列表。你可以按任何顺序返回答案。


        示例 1：
            输入：transactions = ["alice,20,800,mtv","alice,50,100,beijing"]
            输出：["alice,20,800,mtv","alice,50,100,beijing"]
            解释：第一笔交易是无效的，因为第二笔交易和它间隔不超过 60 分钟、名称相同且发生在不同的城市。同样，第二笔交易也是无效的。
        示例 2：

            输入：transactions = ["alice,20,800,mtv","alice,50,1200,mtv"]
            输出：["alice,50,1200,mtv"]
        示例 3：

            输入：transactions = ["alice,20,800,mtv","bob,50,1200,mtv"]
            输出：["bob,50,1200,mtv"]
        

        提示：
            transactions.length <= 1000
            每笔交易 transactions[i] 按 "{name},{time},{amount},{city}" 的格式进行记录
            每个交易名称 {name} 和城市 {city} 都由小写英文字母组成，长度在 1 到 10 之间
            每个交易时间 {time} 由一些数字组成，表示一个 0 到 1000 之间的整数
            每笔交易金额 {amount} 由一些数字组成，表示一个 0 到 2000 之间的整数 

    问题分析:
        这种变量又多，看起来又复杂的匹配问题，可以用暴力解决:
            1. 用结构体把这些变量打包成一个Node节点，得到一个nodes数组
            2. 两层for循环，遍历nodes:
                for i from 0 to n-1:
                    for j from 0 to n-1:
                        ...
                    如果第i个节点符合/不符合条件，放入res中作文返回
                    这样遍历每一个i，最终得到结果
        
        
        对于本题:
            1. {name},{time},{amount},{city} 打包成一个结构体
            2.  for i from 0 to n-1:
                    if nodes[i].amount>1000:
                        放入第i个节点
                    else:
                        for j from 0 to n-1:
                            if i!=j and |nodes[i].time-nodes[j].time|<=60 and nodes[i].city != nodes[j].city and nodes[i].name==nodes[j].name:
                                不符合，放入res数组中
                返回res

        ps：
            可以使用流来实现split(' ')
            s = "1,abc,55"
            1. 把','换成' '
            2. stringstream input(s)
            3. input>>first>>second>>third
                first : 1
                second: abc
                third : 55
*/
typedef struct{
    string name, city;
    int amount, time;
}Node;
class Solution {
public:
    Node make_node( string name, string city, int amount, int time ){
        Node res;
        res.name = name;
        res.city=city;
        res.amount = amount;
        res.time = time;
        return res;
    }
    vector<string> invalidTransactions(vector<string>& transactions) {
        string name, city;
        int amount, time;
        vector<string> res;
        vector<Node> nums;
        for ( auto s:transactions ){
            /*int i=0,j=0, n=s.size();
            while( j<n && s[j]!=',' ) ++j;
            name = s.substr(i,j-i);
            i = ++j;
            while( j<n && s[j]!=',' ) ++j;
            time = stoi(s.substr(i,j-i));
            i = ++j;
            while( j<n && s[j]!=',' ) ++j;
            amount = stoi(s.substr(i,j-i));
            i = ++j;
            while( j<n ) ++j;
            city = s.substr(i,j-i);*/
            
            // 使用流来实现split
            for ( auto&e:s )
                if ( e==',' ) e=' ';
            stringstream ss(s);
            ss>>name>>time>>amount>>city;
            nums.push_back( make_node( name, city, amount, time ) );
        }
        int n = nums.size();
        for ( int i=0; i<n; ++i ){
            bool found = false;
            if ( nums[i].amount>1000 ) found = true;
            for ( int j=0; j<n && !found; ++j ){
                if ( i!=j && nums[i].name==nums[j].name && nums[i].city!=nums[j].city && abs(nums[i].time-nums[j].time)<=60 ) found = true;
            }
            if ( found ){
                res.push_back(  transactions[i] );
            }
        }
        
        return res;
    }
};