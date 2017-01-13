//
//  concatenated-words.cpp
//  helloworld
//
//  Created by BETA on 1/13/17.
//  Copyright © 2017 BETA. All rights reserved.
//
#include <stdio.h>
#include <stack>
#include <queue>
#include <vector>
#include <string>
#include <iostream>
#include <unordered_set>


using namespace std;

// use Ternary search trie instead of 26-way trie
class Solution {
private:
    struct TrieNode{
        bool isWord = false;
        char c;
        TrieNode* left;
        TrieNode* mid;
        TrieNode* right;
    };
    
    TrieNode* root = nullptr;
    unordered_set<int> res;
    vector<string> words;
    //unordered_set<TrieNode*> avoidreuse;
    
    void put(string key, bool val){
        root = put(root, key, val, 0);
    }
    
    TrieNode* put(TrieNode* x, string& key, bool val, int d){
        char c = key[d];
        if(x==nullptr) {x = new TrieNode(); x->c = c;}
        if(c < x->c) x->left = put(x->left, key, val, d);
        else if( c> x->c) x->right = put(x->right, key, val, d);
        else if(d < key.length()-1)
            x->mid = put(x->mid, key, val, d+1);
        else x->isWord = val;
        return x;
    }
    
    void walk(int i, int pos, TrieNode* start, bool jump){
        // assert start is non-null
        auto w = words[i];
        if(pos==w.length() || start==nullptr)
            return;
        if(res.find(i)!=res.end()) return; //提早退出
        if(w[pos] < start->c) walk(i, pos, start->left, jump);
        else if(w[pos] > start->c) walk(i, pos, start->right, jump);
        else{
            if(start->isWord){
                if(pos==w.length()-1 && jump){
                    res.insert(i);
                    return;
                }
                // string cur = w.substr(0, pos+1); // ? 如果是从后面部分才开始的那这里就错了，比如xyzaaaaa
                // if(w.size()%cur.size()==0 && w!=cur){
                //     string tmp = "";
                //     tmp.append(cur.c_str(), w.size()/cur.size());
                //     if(tmp==w){
                //         res.insert(w);
                //         return;
                //     }
                // }
                
                walk(i, pos+1, root, true);
            }
            walk(i, pos+1, start->mid, jump);
        }
    }
    
public:
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        this->root = nullptr;
        this->res.clear();
        this->words = words;
        for(auto w: words)
            if(w!="")
                put(w, true);
        for(int i=0; i<words.size(); i++){
            //avoidreuse.clear();
            if(words[i]!="")
                walk(i, 0, root, false);
        }
        vector<string> v(res.size());
        int cnt = 0;
        for(auto it = res.begin(); it!=res.end(); ++it)
            v[cnt++] = words[*it];
        
        return v;
    }
};

int main() {
    Solution slu;
    vector<string> words{"a","b","ab","abc"};
    auto v = slu.findAllConcatenatedWordsInADict(words);
    for(auto c:v)
        cout<<c<<" ";
    cout<<endl;
    return 0;

}

