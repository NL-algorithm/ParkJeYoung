#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

using u64 = unsigned long long;
using i64 = long long;

vector<int> primes(int limit = 1'000'000){
    vector<bool> is(limit + 1, true);
    is[0] = is[1] = false;
    for(int i = 2; i * 1LL * i <= limit; i++){
        if(is[i])
            for(i64 j = 1LL*i*i; j <= limit;j+=i)
                is[j] = false;
    }
    vector<int>p;
    p.reserve(78498);
    for(int i = 2; i <= limit; i++)
        if(is[i])
            p.push_back(i);
    return p;
}

vector<pair<u64,int>> factorize(u64 n, const vector<int>& primes) {
    vector<pair<u64,int>> fac;
    for (int p : primes) {
        if (1ULL * p * p > n) break;
        if (n % p == 0) {
            int e = 0;
            while (n % p == 0) { n /= p; ++e; }
            fac.push_back({(u64)p, e});
        }
    }
    if (n > 1) fac.push_back({n, 1});
    return fac;
}

u64 euler(u64 n, const vector<pair<u64, int>>& fac){
    __uint128_t res = n;
    for(auto[p, e] : fac)
        res = res/p * (p - 1);
    return (u64)res;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);

    u64 n;
    cin >> n;

    auto p = primes();
    auto fac = factorize(n, p);
    u64 phi = euler(n,fac);
    cout << phi;
}