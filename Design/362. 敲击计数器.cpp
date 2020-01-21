/*
    问题描述:
        设计一个敲击计数器，使它可以统计在过去5分钟内被敲击次数。

        每个函数会接收一个时间戳参数（以秒为单位），你可以假设最早的时间戳从1开始，且都是按照时间顺序对系统进行调用（即时间戳是单调递增）。

        在同一时刻有可能会有多次敲击。

        示例:

        HitCounter counter = new HitCounter();

        // 在时刻 1 敲击一次。
        counter.hit(1);

        // 在时刻 2 敲击一次。
        counter.hit(2);

        // 在时刻 3 敲击一次。
        counter.hit(3);

        // 在时刻 4 统计过去 5 分钟内的敲击次数, 函数返回 3 。
        counter.getHits(4);

        // 在时刻 300 敲击一次。
        counter.hit(300);

        // 在时刻 300 统计过去 5 分钟内的敲击次数，函数返回 4 。
        counter.getHits(300);

        // 在时刻 301 统计过去 5 分钟内的敲击次数，函数返回 3 。
        counter.getHits(301); 
        进阶:

        如果每秒的敲击次数是一个很大的数字，你的计数器可以应对吗？

    问题分析:
        方法一: 
            队列
            利用时间戳是递增的，且方法调用的时间戳参数也是递增的 这一特点, 
            hit则是直接把timestamp入队，因为timestamp是递增的，所以在githit的时候
            就不停的pop, 直到 timestamp - min{timstamp(队首)} < 300 ，此时
            队内所有元素就是在过去300秒内的hit次数.

            评价: 时空复杂度都很高
        
        方法二:
            树状数组..
            没啥好说的，记录每一个时间戳上的hit数，
            区间的单点修改和区间求和， BIT的应用..

            评价: 时间复杂度O(1), 空间复杂度O(N) , 开销会随着时间不断增加..
        
        方法三:
            进阶里，如果每秒的敲击次数是很大的数, 解决方法可以
            参考cache的直接映射法的思想.

            因为是要过去300秒内， 因此区域大小设置为300,

            开两个数组，分别保存timestamp和对应的hit数..

            将每一个timestap数都通过对300取模，保存到对应的位置中,
            time记录真实的timestamp, hits数组记录对应的hit数

            每次gethit的时候，就扫描这块区域，将 query_timestamp - timestamp < 300 对应的hits数加起来, 作为结果返回.

            评价: 时间复杂度O(1), 空间复杂度O(1)
*/

// BIT板子:
unordered_map<int,int> mp;
// map 可以替换成 vector或者 数组
int lowbit(int x){return x&-x;}

// 获取坐标[0,x]上元素的和
int search(int x){
    int res = 0;
    while( x>0 ){
        res += mp[x];
        x -= lowbit(x);
    }
    return res;
}

// 对mp[x] 加val
void add( long x, int val ){
    // INT_MAX可以换成idx的最大值
    while( x<=INT_MAX ){
        mp[x] += val;
        x += lowbit(x);
    }
}

// 获取sum{mp[a,b]}的和:
search(a) - search(b-1);


//=======================下面是三种Solution==========================

class HitCounter1 {
public:
    queue<int> q;
    HitCounter() {
        
    }
    void hit(int timestamp) {
        q.push(timestamp);
    }
    
    int getHits(int timestamp) {
        while( !q.empty() && timestamp - q.front()>=300 )
            q.pop();
        return q.size();
    }
};


class HitCounter2 {
public:
    unordered_map<int,int> mp;
    int lowbit(int x){return x&-x;}
    int search(int x){
        int res = 0;
        while( x>0 ){
            res += mp[x];
            x -= lowbit(x);
        }
        return res;
    }

    void add( long x, int val ){
        while( x<=INT_MAX ){
            mp[x] += val;
            x += lowbit(x);
        }
    }
    
    HitCounter() {
        
    }
    
    void hit(int timestamp) {
        add(timestamp, 1);
    }
    
    int getHits(int timestamp) {
        return search(timestamp+1) - search(timestamp-300);
    }
};


class HitCounter3 {
public:
    int hits[300]={0};
    int times[300]={0};
    HitCounter() {    
    }
    
    void hit(int timestamp) {
        int time = timestamp%300;
        if ( times[time] != timestamp ){
            times[time] = timestamp;
            hits[time] = 1;
        }else hits[time]++;
    }
    
    int getHits(int timestamp) {
        int res = 0;
        for ( int i=0; i<300; ++i )
            if ( timestamp - times[i]<300 )
                res  += hits[i];
        return res;
    }
};
