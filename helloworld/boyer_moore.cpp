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

int main2() {
    string txt = "abababababcde";
    Boyer_Moore k("ababcde");
    cout<<k.search(txt)<<endl;
    return 0;
    
}

int main() {
    
    string txt = "From 1820 to 1850, Jacksonian democracy began a set of reforms which included wider white male suffrage; it led to the rise of the Second Party System of Democrats and Whigs as the dominant parties from 1828 to 1854.";
    Boyer_Moore k("white");
    int i =k.search(txt);
    cout<< i<<endl;
    cout<< txt.substr(i, 10)<<endl;
    return 0;
}

