/*
    问题描述：
        给定一个由n个不重复非空字符串组成的数组，你需要按照以下规则为每个单词生成最小的缩写。
        初始缩写由起始字母+省略字母的数量+结尾字幕组成。
        若存在冲突，亦即多于一个单词有同样的缩写，则使用更长的前缀代替首字母，直到从单词到缩写的映射唯一。换而言之，最终的缩写必须只能映射到一个单词。
        若缩写并不比原单词更短，则保留原样。
        示例:

            输入: ["like", "god", "internal", "me", "internet", "interval", "intension", "face", "intrusion"]
            输出: ["l2e","god","internal","me","i6t","interval","inte4n","f2e","intr4n"]

    问题分析:
        每太懂这题想考什么, 应该是考 字符串处理, 排序. 本题可以用字典树来做进一步优化；

        先简单说一下这题思路,  先把字符串分成两批， 即: 编码成 “第一个字符+(长度-2)+最后一个字符”
        不存在冲突的为一批， 存在冲突的为一批.
        
        对于不存在冲突的，直接就是结果了.

        主要就是讨论存在冲突的那一批.

        对于存在冲突的那一批， 把冲突的那些字符串，放到一组里， 
        例如: "intrusion" 和 "intension" ，都是可以编码成i7n， 因此被分到一组

        
        分组完后，开始讨论组内的字符串。

        对组内的字符串进行排序， 之后，相邻的字符串就必定因为前缀而冲突。 

        这里引入一个 最短不冲突前缀长度数组，

        例如"intrusion"和"intension"， 那么这两个字符串对应的最短不冲突长度就是 4( inte和intr )

        最终，把每一个字符串的最短不冲突长度更新完毕后， 就根据这个数组来重新对字符串进行编码就行了。
*/

class Solution {
    private class node{
        public int index;
        public String word;
        public node( int i, String s ){
            index = i;  // 这个word在dict中的位置
            word = s;   // word
        }
    }
    public List<String> wordsAbbreviation(List<String> dict) {
        Map<String, ArrayList<node>> groups = new HashMap<>();
        int [] prev = new int[dict.size()];
        int idx = 0;
        for ( String s:dict ){
            String cur = encode(s,0);
            if ( groups.containsKey(cur)==false ){
                groups.put( cur, new ArrayList<node>() );
            }
            groups.get(cur).add( new node( idx++, s ) );
        }
        for ( Map.Entry<String, ArrayList<node>> entry: groups.entrySet() ){
            ArrayList<node> group = entry.getValue();
            if ( group.size()==1 ) continue;
            Collections.sort( group, (a,b)->{
                return a.word.compareTo(b.word);
            });
            for ( int i=1; i<group.size(); ++i ){
                int len = get_prev( group.get(i).word, group.get(i-1).word );
                prev[group.get(i).index] = len;
                prev[group.get(i-1).index] = Math.max( prev[group.get(i-1).index], len );
            }
        }
        List<String> res = new ArrayList<>();
        idx=0;
        for ( String s:dict )
            res.add( encode( s, prev[idx++] ) );
        return res;
    }
    
    int get_prev( String a, String b ){
        int i=0, n=Math.min(a.length(), b.length());
        while( i<n && a.charAt(i)==b.charAt(i) ) ++i;
        return i;
    }
    
    String encode( String s, int i ){
        if ( s.length()-i <=3 ) return s;
        return s.substring(0, i+1) + Integer.toString( s.length() - i - 2 ) + s.charAt(s.length()-1);
    }
}