#include <bits/stdc++.h>

using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;

    using ll = long long;

    vector<tuple<int ,ll ,ll>>parts(n);

    ll base = 0;
    int total = 0;

    for(int i = 0; i < n; i++) {
        int w; ll h, b;

        cin >> w >> h >> b;
        parts[i] = make_tuple(w,h,b);
        base += b;
        total += w;
    }

    const ll M = -5e18;

    vector<ll>dp(total + 1, M);

    dp[0] = 0;

    for(int i = 0; i < n; i++) {
        auto[w, h, b] = parts[i];
        ll diff = h - b;

        for(int j = total; j >= w; j--) {
            if(dp[j - w] != M) {dp[j] = max(dp[j], dp[j - w] + diff);}
        }
    }
    ll maxTotal = base;

    for(int j = 1; j <= total; j++) {
        if(2*j <= total)
            maxTotal = max(maxTotal, base + dp[j]);
    }
    cout << maxTotal;
}