/*

Queues at the Gate
A two-way gate default to exit. People form two queues to pass. Each person labeled as index i arrive at time[i] with direction[i] (0 for enter and 1 for exit). People take turns to pass the gate according to the following rules:

1) First come, first pass.
2) Gate remains priority for entrance at time t if at time t - 1 is used for entrance.
3) Gate offers priority for exit at all other times.

1 <= n <= 10^5
1 <= time[i] <= 10^9
time is non-decreasing

*/

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <iterator>
using namespace std;

class Solution{
  public:
  int next(const vector<int>& dr, int type, int curr){
      curr++;
      while (curr < dr.size()){
          if (dr[curr] == type) return curr;
          else ++curr;
      }
      return curr;
  }
  
  vector<int> gate(const vector<int>& tm, const vector<int>& dr){
      int sz = tm.size();
      vector<int> res(sz);
      int idx0 = next(dr, 0, -1);
      int idx1 = next(dr, 1, -1);
      int now = 0;
      bool fg = true;
      while (idx0 < sz && idx1 < sz){
          int t0 = max(now, tm[idx0]);
          int t1 = max(now, tm[idx1]);
          if (t0 > now && t1 > now) fg = true;
          if (t0 < t1 || (!fg && t0 == t1)){
              // process idx0
              res[idx0] = t0; 
              idx0 = next(dr, 0, idx0);
              fg = false;
          } else {
              // process idex1
              res[idx1] = t1;
              idx1 = next(dr, 1, idx1);
          }
          now = min(t0, t1);
          now += 1;
      }
      while (idx0 < sz){
          int t = max(now,tm[idx0]);
          res[idx0] = t;
          idx0 = next(dr, 0, idx0);
          now = t + 1;
      }
      while (idx1 < sz){
          int t = max(now, tm[idx1]);
          res[idx1] = t;
          idx1 = next(dr, 1, idx1);
          now = t + 1;
      }
      return res;
  }
};

int main()
{
    
    Solution s;
    auto res = s.gate({0,0,1,5},{0,1,1,0});
    copy(res.begin(), res.end(), ostream_iterator<int>(cout, " ")); cout << endl;
    return 0;
}
