/*
	问题描述：
		将一个给定字符串根据给定的行数，以从上往下、从左到右进行 Z 字形排列。
		比如输入字符串为 "LEETCODEISHIRING" 行数为 3 时，排列如下：

		L   C   I   R
		E T O E S I I G
		E   D   H   N
		之后，你的输出需要从左往右逐行读取，产生出一个新的字符串，比如："LCIRETOESIIGEDHN"。

		请你实现这个将字符串进行指定行数变换的函数：

		string convert(string s, int numRows);
		示例 1:

		输入: s = "LEETCODEISHIRING", numRows = 3
		输出: "LCIRETOESIIGEDHN"
		示例 2:

		输入: s = "LEETCODEISHIRING", numRows = 4
		输出: "LDREOEIIECIHNTSG"
		解释:

		L     D     R
		E   O E   I I
		E C   I H   N
		T     S     G
		
	问题分析：
		方法一：
			模拟，每一行都抽象成一个队列，i游标遍历字符串s，每次按顺序把每个元素放在每一行上
			
		方法二：
			有点像找规律吧，规律为：
				每一个竖列之间的差距为numRows*2-2 (2*numsRows会多出来 上一列的最后一个元素和当前列的第一个元素 这两元素，所以要剪掉)
				除了第一行和最后一行，两竖列之间都会有一个元素
				这个元素的位置是 当前位置j + step - 2*当前所在行i (画个图就明白了)
				(注意要判断这个位置必须要小于s.size)

				
		PS： res += e; 
			比 res = res + e;
			快多啦！！！！！！
				
*/
class Solution1 {
public:
    string convert(string s, int numRows) {
        vector<vector<char>> row;
        row.resize(numRows);
        int i=0;
        int j=0;
        while( i<s.size() ){
            for ( j=0; j<numRows && i<s.size() ; j++ )
                row[j].push_back(s[i++]);
            for ( j=numRows-2; j>0 && i<s.size() ; j-- )
                row[j].push_back(s[i++]);
        }
        string res="";
        for ( int i=0; i<row.size(); ++i )
            for ( auto e:row[i] )
                res = res + e;
        return res;
    }
};

class Solution2 {
public:
    string convert(string s, int numRows) {
        //方法二：找规律
        string res = "";
        if ( numRows==1 ) return s;
        int step = 2 * numRows - 2 , mid;
        for ( int i=0; i<numRows; ++i ){
            for ( int j=i; j<s.size(); j+= step ){
                res += s[j];
				//中间元素的那个位置
                mid = j+step-i*2;
                if ( i!=0 && i!=numRows-1 && mid<s.size() ) 
                    res += s[mid];
            }
        }
        return res;
    }
};