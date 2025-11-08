#include <bits/stdc++.h>

using namespace std;

constexpr long long MOD = 998244353;

long long power(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

long long modInverse(long long n) {
    return power(n, MOD - 2);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int N;
    long long D;
    cin >> N >> D;

    vector<long long> A(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }

    sort(A.begin(), A.end());

    vector<long long> dp(N + 1);
    dp[0] = 1;
    map<long long, int> counts;

    for (int i = 1; i <= N; i++) {
        long long currentVal = A[i - 1];
        long long threshold = currentVal - D;

        int k = lower_bound(A.begin(), A.begin() + (i - 1), threshold) - A.begin();

        int m = ++counts[currentVal];

        long long validPositions = (i - k);

        dp[i] = (dp[i - 1] * validPositions) % MOD;
        dp[i] = (dp[i] * modInverse(m)) % MOD;
    }

    cout << dp[N];

    return 0;
}