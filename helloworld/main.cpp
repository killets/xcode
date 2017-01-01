#include <vector>
#include<iostream>
using namespace std;

void key_indexed_counting(vector<int>& arr, int R){
    int N = arr.size();
    vector<int> count(R+1);
    vector<int> aux(N);
    
    for(int i=0; i<N; i++)
        count[arr[i]+1]++;
    
    for(int r=0; r<R; r++) // 注意是<R
        count[r+1] += count[r];
    
    for(int i=0; i<N; i++)
        aux[count[arr[i]]++] = arr[i];
    
    for(int i=0; i<N; i++)
        arr[i] = aux[i];
}



//int main(){
//    vector<int> arr{0,2,1,2,1,0,1};
//    key_indexed_counting(arr,3);
//    for(auto e: arr)
//        cout<<e<<" ";
//    
//    return 0;
//}
