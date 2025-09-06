#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
#include <tuple>

using namespace std;

using ll = long long;
const int MOD = 998244353;

struct Mint {
    int v;

    Mint(ll x = 0) {
        x %= MOD;
        if (x < 0)
            x += MOD;
        v = int(x);

    }


    Mint& operator+=(const Mint& o) {
        v += o.v;

        if (v >= MOD)
            v -= MOD;
        return *this;
    }

    Mint& operator-=(const Mint& o) {
        v -= o.v;
        if (v < 0)
            v += MOD;
        return *this;
    }

    Mint& operator*=(const Mint& o) {
        v = int((1LL * v * o.v) % MOD);
        return *this;
    }

    friend Mint operator+(Mint a, const Mint& b) { return a += b; }

    friend Mint operator-(Mint a, const Mint& b) { return a -= b; }

    friend Mint operator*(Mint a, const Mint& b) { return a *= b; }

};

Mint mod_pow(Mint a, ll e) {
    Mint r = 1;
    while (e) {
        if (e & 1) r *= a;
        a *= a;
        e >>= 1;
    }
    return r;
}

struct Edge {
    int to;
    ll w2;
};

int N;

ll K, L;

vector<vector<Edge>> G;

vector<tuple<int, int, long long>> E_raw;

static inline ll count_within_arm(int start, int parent, ll rem2) {
    if (rem2 < 0) return 0;
    ll cnt = 1;
    struct Node { int u, p; ll rem; };
    vector<Node> st; st.reserve(64);
    st.push_back({ start, parent, rem2 });
    while (!st.empty()) {
        auto [u, p, rem] = st.back();
        st.pop_back();
        for (const auto& e : G[u]) {
            if (e.to == p) continue;
            ll nr = rem - e.w2;
            if (nr < 0) continue;
            ++cnt;
            st.push_back({ e.to, u, nr });
        }
    }
    return cnt;
}

static inline pair<int, ll> farthest_from(int s) {
    vector<char> vis(N + 1, 0);
    pair<int, ll> best = { s, 0 };
    struct It { int u, p; ll d2; };
    vector<It> st; st.reserve(N);
    st.push_back({ s, 0, 0 });
    while (!st.empty()) {
        auto [u, p, d2] = st.back(); st.pop_back();
        if (vis[u]) continue;
        vis[u] = 1;
        if (d2 > best.second) best = { u, d2 };
        for (auto& e : G[u]) {
            if (e.to == p) continue;
            st.push_back({ e.to, u, d2 + e.w2 });
        }
    }
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> K >> L;

    G.assign(N + 1, {});
    E_raw.clear();
    E_raw.reserve(N - 1);

    for (int i = 0; i < N - 1; i++) {
        int a, b; ll c;
        cin >> a >> b >> c;
        G[a].push_back({ b, 2 * c });
        G[b].push_back({ a, 2 * c });
        E_raw.emplace_back(a, b, c);
    }


    const ll L2 = 2 * L;


    if (L == 0) {
        Mint P = Mint(N);
        Mint Q = mod_pow(Mint(N), K);
        Mint R = P * mod_pow(Q, MOD - 2);
        cout << R.v << '\n';
        return 0;
    }


    auto p1 = farthest_from(1);
    auto p2 = farthest_from(p1.first);
    ll diam2 = p2.second;
    if (L2 >= diam2) {
        cout << 1 << '\n';
        return 0;
    }
    Mint P = 0;
    for (int v = 1; v <= N; v++) {
        ll S = 0;
        vector<ll> arm; arm.reserve(G[v].size());
        for (const auto& e : G[v]) {
            ll si = count_within_arm(e.to, v, L2 - e.w2);
            arm.push_back(si);
            S += si;
        }
        Mint term = mod_pow(Mint(1 + (S % MOD)), K);
        for (ll si : arm) term -= mod_pow(Mint(1 + (si % MOD)), K);
        term += Mint((int)G[v].size());
        P += term;
    }

    for (auto [u, v, c] : E_raw) {
        ll a = count_within_arm(u, v, L2 - c);
        ll b = count_within_arm(v, u, L2 - c);
        Mint term = mod_pow(Mint(((a + b) % MOD)), K)
            - mod_pow(Mint(a % MOD), K)
            - mod_pow(Mint(b % MOD), K);
        P += term;
    }

    Mint Q = mod_pow(Mint(N), K);
    Mint R = P * mod_pow(Q, MOD - 2);
    cout << R.v << '\n';
    return 0;
}