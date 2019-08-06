/*
    问题分析:
        假设我们以下述方式将我们的文件系统抽象成一个字符串:

        字符串 "dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext" 表示:

        dir
            subdir1
            subdir2
                file.ext
        目录 dir 包含一个空的子目录 subdir1 和一个包含一个文件 file.ext 的子目录 subdir2 。

        字符串 "dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext" 表示:

        dir
            subdir1
                file1.ext
                subsubdir1
            subdir2
                subsubdir2
                    file2.ext
        目录 dir 包含两个子目录 subdir1 和 subdir2。 subdir1 包含一个文件 file1.ext 和一个空的二级子目录 subsubdir1。subdir2 包含一个二级子目录 subsubdir2 ，其中包含一个文件 file2.ext。

        我们致力于寻找我们文件系统中文件的最长 (按字符的数量统计) 绝对路径。例如，在上述的第二个例子中，最长路径为 "dir/subdir2/subsubdir2/file2.ext"，其长度为 32 (不包含双引号)。

        给定一个以上述格式表示文件系统的字符串，返回文件系统中文件的最长绝对路径的长度。 如果系统中没有文件，返回 0。

        说明:

        文件名至少存在一个 . 和一个扩展名。
        目录或者子目录的名字不能包含 .。
        要求时间复杂度为 O(n) ，其中 n 是输入字符串的大小。

        请注意，如果存在路径 aaaaaaaaaaaaaaaaaaaaa/sth.png 的话，那么  a/aa/aaa/file1.txt 就不是一个最长的路径。

    问题分析:
        思路很简单， \t的数量表示层数，
        如果 栈空 或 当前word的层数大于栈顶word层数，那么入栈，
        否侧不停pop，直到栈空或当前word层数大于栈顶层数

        测试点真的秀。。居然还可以用四个空格代替\t，
        尽管各种波折最后实现了。。

        看了别人题解以后， 发现只要多加个操作，把字符串里的"\n    "换成"\n\t" 后面正常写就行了。。
 */

 class Solution {
public:
    int lengthLongestPath(string input) {
        bool find_file=false;
        if ( input.size()==0 ) return 0;
        int res = 0;
        int len = 0;
        stack<pair<int,int>> st;
        int i=0;
        input = '\n' + input;
        
        input  = replace(input, "\n    ", "\n\t");
        
        // 开始
        while( i<input.size() ){
            bool is_file = false;
            int pri_cnt = 0;
            i+=1; // 过滤掉当前\n
            // 计算/t的个数，并过滤 
            while( i<input.size() && input[i]=='\t'){
                ++i;
                ++pri_cnt;
            }
               
            // 当前字符串
            int word_len = 0;
            while( i<input.size() && input[i]!='\n' ){
                if ( input[i]=='.' ){
                    find_file = true;
                    is_file = true;
                }
                word_len++;
                i++;
            }
            while( !st.empty() && st.top().first >= pri_cnt ){
                len -= st.top().second;
                st.pop();
            }
            // 是/word，不是word，别忘了/
            len += (word_len+1);
            if ( is_file )
                res = max(len, res);
            st.push({pri_cnt,word_len+1});
        }
        return (find_file)?max(res,len)-1:0;
    }
    
    string replace(string  s, string a, string b){
        string res;
        int pos = s.find(a);
        while( pos>=0 ){
            s = s.substr(0,pos) + b + s.substr(pos+a.size());
            pos = s.find(a);
        }
        return s;
    }
    
};