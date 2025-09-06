#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

constexpr int MOD = 998244353;

long long modpow(long long a, long long e) {
    long long r = 1 % MOD;
    a %= MOD;
    while (e) {
        if (e & 1) r = (r * a) % MOD;
        a = (a * a) % MOD;
        e >>= 1;
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int P;
    cin >> P;

    long long prod_F1 = 1;
    long long sum_ratio = 0;

    while(P--) {
        int N, M;
        cin >> N >> M;

        vector<int> S(N);
        for (int j = 0; j < N; j++) cin >> S[j];

        vector<unsigned int> pre(N, 0);
        for (int k = 0; k < M; k++) {
            int X, Y; 
            cin >> X >> Y;
            X--; Y--;
            pre[Y] |= (1u << X);
        }

       
        for (int v = 0; v < N; v++) {
            unsigned int pm = pre[v];
            for (int u = 0; u < v; u++) 
                if (pm & (1u << u)) pre[v] |= pre[u];
        }

        
        int LIM = 1 << N;
        vector<int> sumMask(LIM, 0);
        for (int mask = 1; mask < LIM; mask++) {
            int lsb = mask & -mask;
            int b = 0;
            while ((lsb >> b) != 1) 
                b++;
            sumMask[mask] = sumMask[mask ^ lsb] + S[b];
        }

        
        long long Fi1 = 0;
        long long Fip1 = 0;

        for (int mask = 0; mask < LIM; mask++) {
            bool ok = true;
       
            for (int v = 0; v < N; v++) 
                if (mask & (1 << v)) 
                    if ((pre[v] & (unsigned)mask) != pre[v]) 
                        { ok = false; break; }
                
            
            if (!ok) 
                continue;
            Fi1 = (Fi1 + 1) % MOD;
            Fip1 = (Fip1 + sumMask[mask]) % MOD;
        }

        
        prod_F1 = (prod_F1 * Fi1) % MOD;
        long long invFi1 = modpow(Fi1, MOD - 2);
        sum_ratio = (sum_ratio + (Fip1 % MOD) * invFi1) % MOD;
    }

    long long ans = (prod_F1 * sum_ratio) % MOD;
    cout << ans;
    return 0;
}