/*
	水题，不多说了
*/
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i=0,j=0,k=0;
        vector<int> tmp(n+m+10,0);
        while( i<m && j<n ){
            if ( nums1[i]>nums2[j] )
                tmp[k++] = nums2[j++];
            else tmp[k++] = nums1[i++];
        }
        while( i<m )
            tmp[k++] = nums1[i++];
        while( j<n )
            tmp[k++] = nums2[j++];
        for ( i=0; i<k; ++i )
            nums1[i] = tmp[i];
    }
};