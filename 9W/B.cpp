#include<bits/stdc++.h>
using namespace std;

template<typename T>
struct BIT {
    int n;
    vector<T> tree;
    BIT(int _n) : n(_n), tree(_n + 1, 0) {}

    void update(int idx, T val) { 
        for (++idx; idx <= n; idx += idx & -idx) {
            tree[idx] += val;
        }
    }

    T query(int idx) { 
        T sum = 0;
        for (++idx; idx > 0; idx -= idx & -idx) {
            sum += tree[idx];
        }
        return sum;
    }
    
    T query(int l, int r) {
        return query(r) - query(l - 1);
    }
};

const int V_MAX = 500000;
const int BIT_SIZE = V_MAX + 2; 

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int N, Q;
    cin >> N >> Q;
    
    using ll = long long;

    vector<ll> A(N);
    
    BIT<ll> bit_count(BIT_SIZE);
    
    BIT<ll> bit_sum(BIT_SIZE);

    for (int i = 0; i < N; ++i) {
        cin >> A[i];
        bit_count.update(A[i] + 1, 1);
        bit_sum.update(A[i] + 1, A[i]);
    }

    while (Q--) {
        int type;
        cin >> type;
        if (type) {
            int x;
            ll y;
            cin >> x >> y;
            --x; 

            ll old_val = A[x];
            bit_count.update(old_val + 1, -1);
            bit_sum.update(old_val + 1, -old_val);

            bit_count.update(y + 1, 1);
            bit_sum.update(y + 1, y);

            A[x] = y;
        } else {
            ll l, r;
            cin >> l >> r;

            if (l > r) {
                ll total_count = bit_count.query(BIT_SIZE - 1);
                cout << total_count * l << "\n";
                continue;
            }

            ll ans = 0;

            ll count_less_l = bit_count.query(l - 1);
            ans += count_less_l * l;

            ll sum_mid = bit_sum.query(l, r);
            ans += sum_mid;
            
            ll total_count = bit_count.query(BIT_SIZE - 1);
            ll count_le_r = bit_count.query(r);
            ll count_greater_r = total_count - count_le_r;
            ans += count_greater_r * r;

            cout << ans << "\n";
        }
    }

    return 0;
}