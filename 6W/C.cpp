#include <bits/stdc++.h>

using namespace std;

int main() {

    cin.tie(0)->sync_with_stdio(0);

    int n , m, k;

    cin >> n >> m >> k;

    vector<int>h(n);
    vector<int>b(m);

    for(int& i : h) cin >> i;
    for(int& i : b) cin >> i;

    sort(h.begin(),h.end());
    sort(b.begin(), b.end());

    int cnt = 0;
    int hptr = 0;
    int bptr = 0;

    while(hptr < n && bptr < m) {
        if(h[hptr] <= b[bptr]) {
            cnt++;
            hptr++;
            bptr++;
        } else {
            bptr++;
        }
    }

    if(cnt >= k) cout << "Yes";
    else cout << "No";

    return 0;
}