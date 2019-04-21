/*
    两遍循环，加打表，没什么好说的
*/

class Solution {
    public String getHint(String secret, String guess) {
        int bulls = 0, cows = 0,key;
        int [] table = new int[10];
        int [] nums = new int[secret.length()];
        for ( int i=0; i<secret.length(); ++i ){
            if ( secret.charAt(i) == guess.charAt(i) ){
                ++bulls;
                nums[i]=1;
            }else{
                key = (int)secret.charAt(i) - 48;
                ++table[key];
            }
        }
        for ( int i=0; i<secret.length(); ++i ){
            if ( nums[i]==0 ){
                key = (int)guess.charAt(i) - 48;
                if ( table[key]>0 ){
                    table[key]--;
                    cows++;
                }
            }
        }
        String res = bulls + "A" + cows + "B";
        return res;
    }
}