//
//  shortestencoding.cpp
//  helloworld
//
//  Created by BETA on 1/1/17.
//  Copyright © 2017 BETA. All rights reserved.
//

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

class Solution {
private:
    vector<int> get_z(string s){
        int n = s.length();
        vector<int> z(n);
        vector<int> res;
        int L = 0, R = 0;
        for (int i = 1; i < n; i++) {
            if (i > R) {
                L = R = i;
                while (R < n && s[R-L] == s[R]) R++;
                z[i] = R-L; R--;
            } else {
                int k = i-L;
                if (z[k] < R-i+1) z[i] = z[k];
                else {
                    L = i;
                    while (R < n && s[R-L] == s[R]) R++;
                    z[i] = R-L; R--;
                }
            }
            if(z[i]>=i) res.push_back(i);
        }
        return z;
    }
    
public:
    string encode(string s) {
        int n = s.length();
        vector<string> dp(n+1, "");
        
        for(int i=1; i<=n; i++){
            //1' not taken
            //dp[i] =  string(1, s[n-i]) + dp[i-1];
            
            //2' taken
            vector<int> p = get_z(s.substr(i));
            for(auto x : p)
                cout<<x;
        }
        return "";
    }
};

int main() {
    Solution slu;
    slu.encode("aaaaa");
    return 0;
}
