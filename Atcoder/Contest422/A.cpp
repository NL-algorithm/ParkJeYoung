#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main(){

    cin.tie(0)->sync_with_stdio(0);

    string h;
    
    cin >> h;

    int f = h[2] - '0';

    if(f < 8){
        h[2] += 1;
        cout <<h;
        return 0;
    } else {
        h[2] = '1';
        h[0] += 1;
        cout <<h;
        return 0;
    }

}