/*
678. Valid Parenthesis String
Given a string s containing only three types of characters: '(', ')' and '*', return true if s is valid.

The following rules define a valid string:

Any left parenthesis '(' must have a corresponding right parenthesis ')'.
Any right parenthesis ')' must have a corresponding left parenthesis '('.
Left parenthesis '(' must go before the corresponding right parenthesis ')'.
'*' could be treated as a single right parenthesis ')' or a single left parenthesis '(' or an empty string "".

Constraints:
1 <= s.length <= 100
s[i] is '(', ')' or '*'.

*/

// Recursion: time limit exceed
class Solution {
public:
    bool checkValidString(string s) {
        return check(s, 0, s.size(), 0);
    }
    
    bool check(string s, int idx, int sz, int curr){
        if (idx == sz ) return curr == 0;
        
        if (s[idx] == '(') {
            return check(s, idx+1, sz, curr+1);
        } else if (s[idx] == ')'){
            if (curr== 0) return false;
            return check(s, idx+1, sz, curr-1);
        } else {
            return check(s, idx+1, sz, curr) || check(s, idx+1, sz, curr+1) || (curr > 0 && check(s, idx+1, sz, curr-1));
        }
    }
};

// separate into blocks: time limit exceed
class Solution {
public:
    bool checkValidString(string s) {
        vector<vector<int>> parts;
        
        int left = 0;
        int m = 0;
        for (int i = 0; i < s.size(); ++i){
            if (s[i] == '(') left++;
            else if (s[i] == ')'){
                --left;
                m = min(m, left);
            } else {
                parts.push_back({left, m});
                parts.push_back({0, 0, 1, 0,-1, -1});
                left=m=0;
            }
        }
        parts.push_back({left,m});
        
        vector<int> prev{0};
        for (auto v : parts){
            vector<int> curr;
            if (prev.empty()) return false;
            for (auto left : prev){              
                for (int j = 0; j < v.size(); j = j + 2){
                    if (left + v[j+1] < 0) continue;
                    curr.push_back(left+v[j]);
                }
            }
            prev = move(curr);
        }
        return find(prev.begin(), prev.end(),0) != prev.end();
    }  
};
