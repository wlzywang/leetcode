/*

The imbalance of an array is the difference between its max and min elements.
imbalance = max - min
What is the sum of the imbalance of all the possible subarrays?
An subarray is contiguous.

*/

Solution1: brute force exceed time limit
class Solution1 {
public:
    long SumImbalance(vector<int> v){
        long res = 0;
        for (int i = 0; i < v.size(); ++i){
            int mx = v[i];
            int mn = v[i];
            int curr = 0;
            for (int j = i + 1; j < v.size(); ++j){
                if (v[j] < mn){
                    mn = v[j];
                    curr = mx - mn; 
                } else if (v[j] > mx){
                    mx = v[j];
                    curr = mx - mn;
                }
                res += curr;
            }
        }
        return res;
    }    
};

Solution2: dp with monostack
class Solution2 {
public:
   int SumImbalance(vector<int>& arr){
        int sz = arr.size();
        vector<int> vmx(sz+1);
        vector<int> vmn(sz+1);
        stack<int> smx{{-1}};
        stack<int> smn{{-1}};
        int res = 0;
        for (int i = 0; i < sz; ++i){
            while (smn.top()!=-1 && arr[smn.top()] > arr[i]) smn.pop();
            int j = smn.top();
            vmn[i+1] = vmn[j+1] + (i-j) * arr[i];
            smn.push(i);
            while (smx.top()!=-1 && arr[smx.top()] < arr[i]) smx.pop();
            j = smx.top();
            vmx[i+1] = vmx[j+1] + (i-j) * arr[i];
            smx.push(i);
            res += vmx[i+1] - vmn[i+1];
        }
        return res;
    }
};
