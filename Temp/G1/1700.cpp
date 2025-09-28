#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
#include <climits>

using namespace std;

int main(){

    cin.tie(0)->sync_with_stdio(0);

    int n, k;

    cin >> n >> k;

    deque<int>tmp;
    
    for(int x, i = 0; i < k; i++){
        cin >> x;
        tmp.push_back(x);

    }

    vector<int>c;
    int ans = 0;
    while(!tmp.empty()){
        
        int u = tmp.front();
        tmp.pop_front();
        
        if(find(c.begin(),c.end(), u) != c.end()) 
            continue;

        if(c.size() < n){
            c.push_back(u);
            continue;    
        }
        vector<int>cIdx(n, INT_MAX);

        for(int i = 0; i < c.size(); i++){
            int& pos = c[i];
            for(int j = 0; j < tmp.size(); j++){
                if(pos == tmp[j]){
                    cIdx[i] = j;
                    break;
                }
            }
        }

        int& change = c[max_element(cIdx.begin(),cIdx.end()) - cIdx.begin()]; 
        change = u;
        ans++;
    }
    
    cout << ans;
    

    return 0;

}