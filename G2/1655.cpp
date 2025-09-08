#include <queue>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

priority_queue<int>lo;
priority_queue<int, vector<int>, greater<int>>hi;

void rebalance() {
    if (lo.size() > hi.size() + 1) {

        hi.push(lo.top()); lo.pop();
    
    } else if (hi.size() > lo.size()) {
    
        lo.push(hi.top()); hi.pop();
    
    }
}

void push(int x){

    if(lo.empty() || x <= lo.top())
        lo.push(x);
    else
        hi.push(x);
    rebalance();

}

int median(){
    return lo.size() == hi.size() ? 
    min(lo.top(), hi.top()) 
    :
    lo.top();
}




int main(){

    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int n;

    cin >> n;

    for(int i = 0 ; i < n ; i++){
        int k; cin >> k;
        push(k); 
        cout << median() << '\n';
    }

    return 0;
}