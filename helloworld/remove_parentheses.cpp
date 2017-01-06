//
//  remove_parentheses.cpp
//  helloworld
//
//  Created by BETA on 1/3/17.
//  Copyright © 2017 BETA. All rights reserved.
//

#include <stdio.h>
#include <stack>
#include <queue>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

// bfs find shorted
class Solution {
private:
    bool isValid(string& s) {
        stack<char> test;
        for(auto e: s){
            if(e=='(')
                test.push(e);
            else if(e==')'){
                if(test.empty()||test.top()!='(')
                    return false;
                test.pop();
            }
        }
        return test.empty(); // fix wrong answer, input "["
    }
    
public:
    vector<string> removeInvalidParentheses(string s) {
        if(isValid(s)) return vector<string>{s};
        vector<string> res;
        bool found;
        queue<pair<string, int>> q;
        q.push(make_pair(s, -1));
        while(!q.empty()){
            int n = q.size();
            for(int i=0; i<n; i++){
                auto cur = q.front(); q.pop();
                string cur_s = cur.first;
                int cur_k = cur.second;
                for(int k=cur_k+1; k<cur_s.length(); k++){ // 补丁 cur_s.length()
                    if(cur_s[k]!='(' && cur_s[k]!=')') continue;
                    
                    /* string tmp = cur_s; tmp[k]='*'; */
                    string tmp = cur_s.substr(0, k) + cur_s.substr(k+1);
                    if(isValid(tmp)){
                        found = true;
                        /* tmp.erase( std::remove(tmp.begin(), tmp.end(), '*'), tmp.end()); */
                        res.push_back(tmp);
                    } else
                        q.push(make_pair(tmp, k-1)); /* (tmp, k) */
                    
                    //skip same chars to last one, eg.'a(((()'  不能提前，因为小＋大，一开始skip到大了
                    // 就不能实现删多个这个符号
                    while(k+1<cur_s.length() && cur_s[k+1]==cur_s[k]) //补丁 cur_s
                        k++;
                }
            }
            if(found) break;
        }
        
        return res;
    }
};

int main(){
    Solution slu;
    auto r = slu.removeInvalidParentheses("))");
    for(auto c: r)
        cout<<c<<"."<<endl;
    return 0;
}
