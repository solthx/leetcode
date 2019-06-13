/*
	问题描述：
		给定一个单词数组和一个长度 maxWidth，重新排版单词，使其成为每行恰好有 maxWidth 个字符，且左右两端对齐的文本。

		你应该使用“贪心算法”来放置给定的单词；也就是说，尽可能多地往每行中放置单词。必要时可用空格 ' ' 填充，使得每行恰好有 maxWidth 个字符。

		要求尽可能均匀分配单词间的空格数量。如果某一行单词间的空格不能均匀分配，则左侧放置的空格数要多于右侧的空格数。

		文本的最后一行应为左对齐，且单词之间不插入额外的空格。

		说明:

		单词是指由非空格字符组成的字符序列。
		每个单词的长度大于 0，小于等于 maxWidth。
		输入单词数组 words 至少包含一个单词。
		示例:

		输入:
		words = ["This", "is", "an", "example", "of", "text", "justification."]
		maxWidth = 16
		输出:
		[
		   "This    is    an",
		   "example  of text",
		   "justification.  "
		]

		解释: 注意最后一行的格式应为 "shall be    " 而不是 "shall     be",
		     因为最后一行应为左对齐，而不是左右两端对齐。       
			 第二行同样为左对齐，这是因为这行只包含一个单词。

	问题分析：
		先计算好每行能放哪几个单词 rows_idx[i] 的意思是 第i行可以放[rows_idx[i-1] ,  rows_idx[i]) 这个区间内的单词
		然后在计算单词间的空格数
		即使 空格总数space = maxWidth - 字符数
		    最小空格数space_base = space // (当前行的单词数-1)
			然后 mod =  space % (当前行的单词数-1)
			对前mod个空格，每个间隔都加1个空格
			
		最后一行单独处理
*/

class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> res;
        int n = words.size() , i, rlen,space=0;
        vector<int> vlen(n,0);
        for ( int i=0; i<n; ++i )
            vlen[i] = words[i].size();
        vector<int> rows_idx; // 这一行的最后一个元素的位置
        vector<int> rows_sum; // 当前行所占的字符总数
        i=0;
        int space_cnt=0;
		// 确定每一行保存哪几个单词
        while( i<n ){
            rlen = 0;
            space_cnt=0; //空格数，第一个元素前没有空格，初始是0
            int st = 0; 
			
			//满足 当前长度+第i个单词的长度+第i个单词前的空格的长度 <= maxWidth
			//就可以把当前元素加进来
            while( i<n && rlen+words[i].size()+space_cnt <= maxWidth ){
    
                rlen  += (words[i].size()+space_cnt) ;
                space_cnt = 1;
                
                st += words[i].size();  //用来记录第i行的字符长度
                i++;
            }
            rows_idx.push_back(i); // [ x , y ) 
            rows_sum.push_back(st); // 这行长度
        }
        
        // 把这些单词放入每一行，并且计算单词间的空格
        for ( i=0; i<rows_idx.size(); ++i ){
            int start = (i==0)?0:rows_idx[i-1];  //当前行的其实位置
            int end = rows_idx[i];				 //当前行结束位置的后一个元素 因为这里是开区间
            int diff = end - start; // 这一行的元素个数 
            int space_base ,mod  ; // 这一行单词间的最少空格数
            
            // 计算空格大小
            if ( diff>1 ){
                space_base = ( maxWidth-rows_sum[i] ) / (diff-1);
                mod = (maxWidth-rows_sum[i]) % (diff-1);
            }else{
                space_base = maxWidth-rows_sum[i] ;
                mod = 0;
            }
            
			// 合并出当前行的string s
            string s = words[start];
            if ( end-start==1 )
                s = s + get_space(space_base);
            
            if ( i!=rows_idx.size()-1 ){
                //不是最后一行
                string spc = get_space(space_base);
                int plus=0;
                for ( int t=start+1; t<end; ++t ){
                    // 给前mod个元素加一个空格
					// plus控制加的空格数是0还是1
                    if ( mod>0 ){
                        plus = 1;
                        mod--;
                    }else plus = 0;
                    s = s + spc + get_space(plus) + words[t];
                }
            }else{
                //是最后一行，单独处理
                for ( int t=start+1; t<end; ++t ){
                    s = s + ' ' + words[t];
                }
                int d = maxWidth - s.size();
                while( d-- ){
                    s = s + ' ';
                }
            }
            res.push_back(s);    
        }
        
        return res;
    }
    
	// 获取n个空格
    string get_space(int n){
        string s="";
        for ( int i=0; i<n; ++i )
            s += ' ';
        return s;
    }
};

/*
["Science  is  what we","understand      well","enough   to  explain","to  a  computer. Art","is  everything  else","we do               "]


["Science  is  what we","understand      well","enough to explain to","a  computer.  Art is","everything  else  we","do                  "]
*/