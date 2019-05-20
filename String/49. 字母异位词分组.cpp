/*
	问题描述：
		给定一个字符串数组，将字母异位词组合在一起。字母异位词指字母相同，但排列不同的字符串。

		示例:
		
		输入: ["eat", "tea", "tan", "ate", "nat", "bat"],
		输出:
		[
		  ["ate","eat","tea"],
		  ["nat","tan"],
		  ["bat"]
		]
		说明：

		所有输入均为小写字母。
		不考虑答案输出的顺序。

	问题分析；
		方法一：
			O(K*N*N)force  超时
		
		方法二：
			O(K*logK*N)	Hashmap
			
			key是排好序的序列，
			value是第i个位置，
			维护一个长为len的序列，
			对于每一个strs[i]
				如果map里存有sorted(strs[i]), 那就得到这个位置，然后push进去
				如果不存在，那就存在len处，然后++len
			最后记得resize一下
*/


class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        // O(K*N*N)force  超时
        /*int i,j,len=0;
        vector<vector<string>> res(strs.size()+1);
        for (  i=0; i<strs.size(); ++i ){
            for (  j=0; j<len; ++j ){
                if ( isAnagram(res[j][0],strs[i]) ){
                    res[j].push_back(strs[i]);
                    break;
                }
            }
            if ( j==len ){
                res[len++].push_back(strs[i]);
            }
        }
        res.resize(len);
        return res;*/
        
        //方法二： O(KlogK * N)
        int idx,len=0;
        unordered_map<string,int> mp;
        vector<vector<string>> res(strs.size()+1);
        for ( int i=0; i<strs.size(); ++i ){
            string tmp = strs[i].substr(0, strs[i].size());
            sort(tmp.begin(),tmp.end());
            if ( mp.find(tmp)!=mp.end() ){
                idx = mp[tmp];
                res[idx].push_back(strs[i]);
            }else{
                res[len].push_back(strs[i]);
                mp[tmp] = len++;
            }
        }
        res.resize(len);
        return res;
    }
    
    bool isAnagram(string s, string t) {
        char table[26]={0};
        for ( auto e:s )
            table[e-'a']++;
        for ( auto e:t )
            table[e-'a']--;
        for ( int i=0; i<26; ++i )
            if ( table[i]!=0 )
                return false;
        return true;
    }
};