/*
    问题描述:
        给年月日，求这天是周几?
    
    问题分析:
        元年1月1日是周一
        
        陷阱一:
            因为要mod7 ， 所以周日是0, 周一到周六是1~6

        陷阱二:
            起始天数的确定！
            一定要从最早年份的前一年开始算！！！
            
            元年1月1日是周一，
            但是起始要从0开始，
            因为, 对于year, month, day
            我们是先计算 [ 1,year )
            然后单独计算 year
            
            而如果起始为1的话，在计算元年1月1日的时候，
            就会变成1+1=2 变成了周二！

            所以起始要从0开始！！！

            同理，如果year的取之范围是[a,b]的话，
            那么起始的时候可以是 a-1年 (a>1)
*/

class Solution {
public:
    int isLeap( int year ){
        if ( year%4==0 && year%100!=0 || year%400==0 ) return true;
        return false;
    }
    string dayOfTheWeek(int day, int month, int year) {
        vector<string> wk = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
        vector<int> mth = { 31,28,31,30,31,30,31,31,30,31,30,31 };
        int tot = 0; // 元年的前一年是不存在的，所以是0！
        for ( int i=1; i<year; ++i )
            tot += (365+isLeap(i));
        if ( isLeap(year) ) mth[1]++;
        for ( int i=0; i<month-1; ++i )
            tot += mth[i];
        tot += day;
        tot %= 7;
        return wk[tot];
    }
};