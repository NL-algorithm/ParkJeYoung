#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    int N;
    ll X, Y;
    cin >> N >> X >> Y;
    
    vector<ll> A(N);
    for(auto& a : A) cin >> a;
    
    ll D = Y - X;
    ll R = (1LL * X * A[0]) % D;
    ll Wmin = 0, Wmax = (ll)3e18; // 3e18? 1<<32
    
    // summation (1 to N)(wopt - X*A / D)
    for(ll a : A) {
        ll xa = 1LL * X * a;
        if (xa % D != R) {
            cout << -1;
            return 0;
        }
        Wmin = max(Wmin, xa);
        Wmax = min(Wmax, 1LL * Y * a);
    }
    


    if (Wmin > Wmax) {
        cout << -1;
        return 0;
    }
    
    ll Wopt = Wmax - (Wmax % D - R + D) % D;
    
    if (Wopt < Wmin) {
        cout << -1;
        return 0;
    }
    
    ll ans = 0;
    for(ll a : A) {
        ans += (Wopt - 1LL * X * a) / D;
    }
    
    cout << ans;
    return 0;
}