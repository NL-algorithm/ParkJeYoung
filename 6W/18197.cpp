#include <bits/stdc++.h>

long long __gcd(long long a, long long b) {
    if (b == 0) return a;
    return __gcd(b, a % b);
}

using namespace std;
using ll = long long;
using PR = pair<ll, ll>;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<PR> num(n);
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        size_t pos = s.find('/');
        ll p = stoll(s.substr(0, pos));
        ll q = stoll(s.substr(pos + 1));
        ll g = (p == 0) ? 1 : __gcd(p, q);
        num[i] = {p, q};
    }

    int j = 1;
    for (int i = 0; i < n; i++) {
        PR u = num[i];
        
        while (j < i + 1) {
            j++;
        }

        while (j < i + n) {
            PR v = num[j % n];
            if (j >= n) {
                v.first += v.second; 
            }
            
            __int128 tp_diff = (__int128)v.first * u.second - (__int128)u.first * v.second;
            __int128 lhs = 2 * tp_diff;
            __int128 rhs = (__int128)u.second * v.second;

            if (lhs < rhs) {
                j++;
            } else {
                break;
            }
        }
        
        if (j - i > (n + 1) / 2) {
            cout << "YES";
            return 0;
        }
    }

    cout << "NO";
    return 0;
}