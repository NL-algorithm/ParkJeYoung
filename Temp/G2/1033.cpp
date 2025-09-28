#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <stack>
#include <numeric>


using namespace std;

using ll = long long;


static inline ll lcm_ll(ll a, ll b) {
    if (a == 0 || b == 0) return 0;
    ll g = std::gcd(a, b);
    ll t = (ll)(a / g) * b;
    return (ll)t;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<vector<tuple<int,int,int>>> adj(N);
    for (int i = 0; i < N - 1; i++) {
        int a, b, p, q;
        cin >> a >> b >> p >> q;

        int g = std::gcd(p, q);
        p /= g; q /= g;

        adj[a].push_back({b, p, q});
        adj[b].push_back({a, q, p});
    }

    vector<ll> num(N, 0), den(N, 1);
    vector<char> vis(N, 0);

    num[0] = 1; den[0] = 1; vis[0] = 1;

    // DFS
    stack<int> st;
    st.push(0);
    while (!st.empty()) {
        int u = st.top(); st.pop();
        for (auto [v, p, q] : adj[u]) {
            if (vis[v]) continue;

            ll nu = num[u], du = den[u];
            ll pp = p, qq = q;

            ll g1 = std::gcd(nu, pp); nu /= g1; pp /= g1;
            ll g2 = std::gcd(qq, du); qq /= g2; du /= g2;

            num[v] = nu * qq;
            den[v] = du * pp;

            ll g3 = std::gcd(num[v], den[v]);
            num[v] /= g3; den[v] /= g3;

            vis[v] = 1;
            st.push(v);
        }
    }

    // 모든 분모의 LCM을 구해 한 번에 정수화
    ll L = 1;
    for (int i = 0; i < N; ++i) {
        L = lcm_ll(L, den[i]);
    }

    vector<ll> mass(N);
    for (int i = 0; i < N; i++) {
        ll scale = L / den[i];
        ll t = (ll)scale * num[i];
        mass[i] = (ll)t;
    }

    ll gAll = 0;
    for (int i = 0; i < N; i++) gAll = std::gcd(gAll, mass[i]);
    for (int i = 0; i < N; i++) mass[i] /= gAll;

    for (int i = 0; i < N; i++) {
        if (i) cout << ' ';
        cout << mass[i];
    }
    return 0;
}
