/*
*
* Problem_Solving_Time PM 3:00 - 5:20
*
*/
#include <iostream>
#include <vector>

#define REAL ios::sync_with_stdio(false); cin.tie(nullptr);

using namespace std;

typedef long long LL;

const LL MOD = 1000000007;

int n, m, k;

class SegmentTree {

private:
    int n;
    vector<LL> A;
    vector<LL> tree;

public:
    SegmentTree(int _n) : n(_n), A(_n + 1), tree(4 * _n, 1LL) {}

    void setValue(int idx, LL val) {
        A[idx] = val;
    }

    void build(int node, int l, int r) {
        if (l == r) {
            tree[node] = A[l] % MOD;
        }
        else {
            int mid = (l + r) >> 1;
            build(node << 1, l, mid);
            build(node << 1 | 1, mid + 1, r);
            tree[node] = (tree[node << 1] * tree[node << 1 | 1]) % MOD;
        }
    }

    void build() {
        build(1, 1, n);
    }

    LL query(int node, int l, int r, int L, int R) {
        if (r < L || R < l) return 1LL;
        if (L <= l && r <= R) return tree[node];
        int mid = (l + r) >> 1;
        LL left = query(node << 1, l, mid, L, R);
        LL right = query(node << 1 | 1, mid + 1, r, L, R);
        return (left * right) % MOD;
    }

    LL query(int L, int R) {
        return query(1, 1, n, L, R);
    }

    void update(int node, int l, int r, int idx, LL val) {
        if (idx < l || r < idx) return;
        // 범위 밖이면 무시
        if (l == r) {
            tree[node] = val % MOD;
            // 리프 노드 갱신
        }
        else {
            int mid = (l + r) >> 1;
            update(node << 1, l, mid, idx, val);
            update(node << 1 | 1, mid + 1, r, idx, val);
            // 덧셈이 아니라 곱셈으로 재결합
            tree[node] = (tree[node << 1] * tree[node << 1 | 1]) % MOD;
        }
    }

    void update(int idx, LL val) {
        update(1, 1, n, idx, val);
    }
};

int main() {
    REAL;
    cin >> n >> m >> k;

    SegmentTree st(n);

    for (int i = 1; i <= n; i++) {
        LL x; cin >> x;
        st.setValue(i, x);
    }

    st.build();

    for (int i = 0; i < m + k; i++) {
        int op, b;
        LL c;
        cin >> op >> b >> c;
        if (op == 1) {
            // A[b] = c
            st.update(b, c);
        }
        else {
            // product on [b to c]
            cout << st.query(b, c) << "\n";
        }
    }
  
    return 0;
}
