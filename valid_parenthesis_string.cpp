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

// two stacks
class Solution {
public:
    bool checkValidString(string s) {
        stack<int> left, star;
        for (int i = 0; i < s.size(); ++i){
            if (s[i] == '(') left.push(i);
            else if (s[i] == '*') star.push(i);
            else {
                if (!left.empty()) left.pop();
                else if (!star.empty()) star.pop();
                else return false;
            }
        }
        
        while (! left.empty() && ! star.empty()){
            if (left.top() > star.top() ) return false;
            left.pop();
            star.pop();
        }
        return left.empty();
    }
    
};

// forward treating '*' as '(', then backward treating '*' as ')'
class Solution {
public:
    bool checkValidString(string s) {
        int ct = 0;
        for (auto c : s){
            if (c == ')'){
                --ct;
                if (ct < 0) return false;
            } else ++ct;
        }
        if (ct == 0) return true;
        ct = 0;
        for (int i = s.size()-1; i>=0; --i){
            if (s[i] == '(') {
                --ct;
                if (ct < 0) return false;
            } else ++ct;
        }
        return true;
    }    
};

// high treating all '*' as '(', low treating '*' as ')' when possible
class Solution {
public:
    bool checkValidString(string s) {
        int high = 0;
        int low = 0;
        for (auto c : s){
            if (c =='('){
                ++high;
                ++low;
            } else if (c == ')'){
                --high;
                if (low > 0) --low;     // meaning when possible
            } else {
                ++high;
                if (low > 0) --low;     // meaning when possible
            }
            if (high < 0) return false;
        }
        return low == 0;

    }   
};
