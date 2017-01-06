//
//  LFU_Allone.cpp
//  helloworld
//
//  Created by BETA on 1/6/17.
//  Copyright © 2017 BETA. All rights reserved.
//

#include <stdio.h>
#include <stack>
#include <queue>
#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
using namespace std;

// Runtime error!
class AllOne {
private:
    struct Node{
        string key;
        int val;
        Node* pre;
        Node* next;
        Node(string key, int val, Node* pre=nullptr, Node* next=nullptr): key(key),val(val),pre(pre),next(next){}
    };
    Node* root;
    Node* tail;
    unordered_map<string, Node*> m;
    unordered_map<int, pair<Node*, Node*>> freq;
public:
    /** Initialize your data structure here. */
    AllOne() {
        root = new Node("", 0, nullptr, nullptr);
        tail = new Node("", 0, nullptr, nullptr);
        tail->pre = root;
        root->next = tail;
        m = unordered_map<string, Node*>();
        freq = unordered_map<int, pair<Node*, Node*>>();
    }
    
    /** Inserts a new key <Key> with value 1. Or increments an existing key by 1. */
    void inc(string key) {
        if(m.find(key)==m.end()){
            auto tmp = new Node(key, 1);
            auto p = root->next;
            tmp->pre = root;
            tmp->next = p;
            root->next = tmp;
            p->pre = tmp;
            m[key] = tmp;
            if(freq.find(1)==freq.end()) freq[1] = make_pair(tmp, tmp);
            else freq[1].first = tmp;
        } else{
            auto tmp = m[key];
            auto oldnext = tmp->next;
            
            if(freq[tmp->val].second==tmp){ // I am head
                if(tmp->pre->val == tmp->val){
                    freq[tmp->val].second = tmp->pre;
                } else
                    freq.erase(tmp->val);
                freq[tmp->val +1].first = tmp;
            } else{ // if(freq.find(tmp->val +1)!=freq.end() || freq[tmp->val].second!=tmp){ // 也可以不用放在头部，只管放到原freq自己的头部即可
                tmp->pre->next = tmp->next;
                tmp->next->pre = tmp->pre;
                auto front = freq.find(tmp->val +1)!=freq.end() ? freq[tmp->val +1].second : freq[tmp->val].second;
                tmp->pre = front;
                tmp->next = front->next;
                front->next = tmp;
                tmp->next->pre = tmp;
                // Note! first not set
                if(freq[tmp->val].first == tmp)
                    freq[tmp->val].first = oldnext;
            }
            //Note! first not set
            if(freq.find(tmp->val+1)==freq.end()) freq[tmp->val+1].first = tmp;
            freq[tmp->val + 1].second = tmp;
            tmp->val++;
        }
    }
    
    /** Decrements an existing key by 1. If Key's value is 1, remove it from the data structure.
     两种写法，一是按事件分类处理（事件1中变量x如何，y如何），二是按变量处理（变量x在事件1中等于x1，在2中等于x2）
     */
    void dec(string key) {
        if(m.find(key)==m.end()) return;
        auto cur = m[key];
        auto oldpre = cur->pre;
        auto oldnext = cur->next;
        if(cur->val==1) m.erase(key);
        // 断
        if(cur->val==1 || freq[cur->val].first != cur){
            cur->pre->next = cur->next;
            cur->next->pre = cur->pre;
        }
        // 合
        if(cur->val != 1 && freq[cur->val].first != cur){
            auto rangetail = freq[cur->val].first;
            cur->next = rangetail;
            cur->pre = rangetail->pre;
            rangetail->pre->next = cur;
            rangetail->pre = cur;
        }
        
        // update frq
        if(freq[cur->val].first == freq[cur->val].second) // only one
            freq.erase(cur->val);
        else if(freq[cur->val].second == cur)
            freq[cur->val].second = oldpre;
        else if(freq[cur->val].first == cur)
            freq[cur->val].first = oldnext;
        else {} //do nothing when within a range
        
        if(cur->val!=1){
            if(freq.find(cur->val-1)!=freq.end())
                freq[cur->val-1].second = cur;
            else
                freq[cur->val-1] = make_pair(cur, cur);
            cur->val--;
        }
    }
    
    /** Returns one of the keys with maximal value. */
    string getMaxKey() {
        return tail->pre->key;
    }
    
    /** Returns one of the keys with Minimal value. */
    string getMinKey() {
        return root->next->key;
    }
};




/**
 * Your AllOne object will be instantiated and called as such:
 * AllOne obj = new AllOne();
 * obj.inc(key);
 * obj.dec(key);
 * string param_3 = obj.getMaxKey();
 * string param_4 = obj.getMinKey();
 */

int main(){
    AllOne obj;
    obj.inc("hello");
     obj.inc("hi");
     obj.inc("hi");
    obj.dec("hello");
    obj.inc("nihao");
    obj.inc("hix");
    obj.dec("hi");
    cout<<obj.getMaxKey()<<endl;
    cout<<obj.getMinKey()<<endl;
    
    
    return 0;
}
