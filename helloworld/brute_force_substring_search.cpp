//
//  brute_force_substring_search.cpp
//  helloworld
//
//  Created by BETA on 12/14/16.
//  Copyright © 2016 BETA. All rights reserved.
//

#include <stdio.h>
#include <vector>
#include<iostream>
using namespace std;

// brute force substring search, O(MN)
int search(string txt, string pat){
    int N = txt.length();
    int M = pat.length();
    for(int i=0; i<N; i++){
        int j;
        for(j=0; j<M; j++){
            if(txt[i+j]!=pat[j])
                break;
        }
        if(j==M)
            return i;
    }
    return N;
}

// another implementation of brute force,O(MN)
int search_v2(string txt, string pat){
    int N = txt.length();
    int M = pat.length();
    int i, j;
    for(i=0, j=0; i<N && j<M; i++){
        if(txt[i]==pat[j]) j++;
        else{ i-=j; j = 0;}
    }
    if(j==M) return i-M;
    return N;
}


void test(){
    string txt = "abcabcdefabcde";
    cout<<search(txt, "abcd")<<endl;
    cout<<search_v2(txt, "abcd")<<endl;
}

int main(){
    test();
    return 0;
}
