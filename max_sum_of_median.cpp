/*

Distribute a vector of integers into n vectors. No vector is empty. What is the maximum possible sum of median for all the vectors?

The median of an array is the middle element if the array is sorted in non-decreasing order. If the size of the array is even, the median is the average of the two middle elements. Round up to the next integer.

1 <= n <= len(v)
*/

class Solution {
public:
    long MaxSum(vector<int> v, int n){
        int sz = v.size();
        sort(v.begin(), v.end());
        // distribute the max n-1 elements into n-1 vectors, and the rest into a single vector
        sz -= n-1;
        long res = accumulate(v.begin() + sz, v.end(), 0);
        if (sz % 2){
            res += v[sz/2];
        } else {
            res += (v[sz/2-1] + v[sz/2] + 1)/2;
        }
        return res;
    }
    
};
