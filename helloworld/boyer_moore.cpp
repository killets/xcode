//
//  boyer_moore.cpp
//  helloworld
//
//  Created by BETA on 12/15/16.
//  Copyright © 2016 BETA. All rights reserved.
//

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

class Boyer_Moore {
private:
    int R;
    int M;
    string pat;
    vector<int> right;
    
public:
    Boyer_Moore(string pat){
        R = 256;
        M = pat.length();
        this->pat = pat;
        right = vector<int>(R, -1); // -1 for chars not in pattern
        for(int j=0; j<M; j++)
            right[pat[j]] = j; // rightmost occurence
    }
    
    int search(string txt){
        int skip;
        for(int i=0; i<=txt.length()-M; i+=skip){
            // does pattern match the text at position i? :
            skip = 0;
            for(int j=M-1; j>=0; j--){
                if(txt[i+j]!=pat[j]) {
                    skip = max(1, j-right[txt[i+j]]);
                    break;
                }
            }
            if(skip==0) return i; //found
        }
        return txt.length(); // not found
    }
};

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
int main2() {
    string txt = "abababababcde";
    Boyer_Moore k("ababcde");
    cout<<k.search(txt)<<endl;
    return 0;
    
}


int main() {
    
//    string txt = "From 1820 to 1850, Jacksonian democracy began a set of reforms which included wider white male suffrage; it led to the rise of the Second Party System of Democrats and Whigs as the dominant parties from 1828 to 1854.";
//    Boyer_Moore k("white");
//    int i =k.search(txt);
//    cout<< i<<endl;
//    cout<< txt.substr(i, 10)<<endl;
    

    cout<<"hi"<<endl;
   
    Solution slu;
//    unordered_set<string> wordList({"hot","dot","dog","lot","log"});
//    auto res = slu.findLadders("hit", "cog", wordList);
  
    vector<int> nums({1,2,31,33});
    slu.encode("aaaaa");
    return 0;
}

