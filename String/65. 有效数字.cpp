/*
	问题描述：
		验证给定的字符串是否可以解释为十进制数字。

		例如:

		"0" => true
		" 0.1 " => true
		"abc" => false
		"1 a" => false
		"2e10" => true
		" -90e3   " => true
		" 1e" => false
		"e3" => false
		" 6e-1" => true
		" 99e2.5 " => false
		"53.5e93" => true
		" --6 " => false
		"-+3" => false
		"95a54e53" => false

	问题分析：
		见代码注释

*/

# include <algorithm>
class Solution {
public:
    bool isNumber(string s) {
        trim_str(s); //消除两边空格
        int sign_cnt, dot_cnt, e_cnt,i;
        // 长度为0 或是 长度为1 但是非数字字符
		if( s.size()==0 || s.size()==1 && !is_digit(s[0]) ) return false;
        
		// .的个数 和 e的个数
        dot_cnt = count(s.begin(),s.end(),'.');
        e_cnt = count(s.begin(),s.end(),'e');
        // .,e出现超过一次
        if (  dot_cnt>1 || e_cnt>1 ) 
            return false;
        //分类讨论
        if ( e_cnt==0 ){
            // 非科学计数
            if ( dot_cnt==1 ){
                // 小数
                return is_deci(s);
            }else{
                // 非小数
                return is_integer(s);       
            }
        }else{
            //科学计数
            //先判断e之前是整数或小数
            int i=0,e_idx=s.find('e');
			
			//e的前面或后面没东西 算错误
            if ( e_idx==s.size()-1 || e_idx==0 ) 
                return false; 
			
			// e的前面可以是整数可以是小数，但e的后面只能是整数
            if ( e_idx==0 || is_deci(s.substr(0, e_idx )) || is_integer(s.substr(0, e_idx )) ){
                if (  is_integer(s.substr(e_idx+1)) )
                    return true;
                else return false;
            }else return false;
            
        }
        return true;
    }
    
	// 判断是否是整数
    bool is_integer(string s){
        int i=0;
        if ( s.size()==0 || (s.size()==1 && ( s[0]=='+' || s[0]=='-' )) ) return false;
        if ( s[i]=='+' || s[i]=='-' )
            i++;
        
        while( i<s.size() ){
            if ( is_digit(s[i]) )
                i++;
            else return false;
        }
        return i==s.size(); 
    }
    
	// 判断是否是小数
	// ps: .1算合法
    bool is_deci(string s){
        int i=0;
        if ( s.size()==0 ) return false;
        if ( s[i]=='+' || s[i]=='-' )
            s.erase(0,1);
        if ( s.size()==1 && s[0]=='.' )
            return false;
        while( i<s.size() && s[i]!='.' ){
            if ( is_digit(s[i]) )
                i++;
            else return false;
        }
        // 首个是'.'
        //if ( i==0 ) return false;
        i++; // 过滤dot
        while( i<s.size() ){
            if ( is_digit(s[i]) )
                i++;
            else return false;
        }
        return i==s.size();  
    }
    
    bool is_digit(char c){
        return c>='0' && c<='9';
    }
    
	//去掉左右空格
    void trim_str(string & s){
        int l=0, r = s.size()-1;
        while( l<=r && s[l]==' ' )
            l++;
        while( l<=r && s[r]==' ' )
            r--;
        s = s.substr(l,r-l+1);
    }
};