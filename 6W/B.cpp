#include <bits/stdc++.h>

using namespace std;

int main() {

    cin.tie(0)->sync_with_stdio(0);

    int x, n;

    cin >> x >> n;

    long long currw = x;

    vector<int> w(n);

    for(int& i : w) cin >> i;

    vector<bool>isatt(n, 0);

    int q; cin >> q;

    for(int i = 0; i < q; i++) {
        int p; cin >> p;
        p-=1;
        if(isatt[p]){
            currw -= w[p];
            isatt[p] = false;
        } else {
            currw += w[p];
            isatt[p] = true;
        }
        cout << currw <<'\n';

    }

    return 0;
}