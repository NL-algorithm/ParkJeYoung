#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
const ll INF = 1e18;
const int K = 29;

struct Node {
    Node *c[2];
    ll val;
    Node(ll v = INF) : val(v) { c[0] = c[1] = nullptr; }
};

Node node_pool[30000005];
int pool_ptr;

Node* newNode(ll v = INF) {
    node_pool[pool_ptr].c[0] = node_pool[pool_ptr].c[1] = nullptr;
    node_pool[pool_ptr].val = v;
    return &node_pool[pool_ptr++];
}

void pull(Node* u) {
    u->val = INF;
    if (u->c[0]) u->val = min(u->val, u->c[0]->val);
    if (u->c[1]) u->val = min(u->val, u->c[1]->val);
}

Node* create_cost(ll add, int k) {
    Node* u = newNode();
    if (k < 0) {
        u->val = add;
        return u;
    }
    u->c[0] = create_cost(add, k - 1);
    u->c[1] = create_cost(add + (1LL << k), k - 1);
    pull(u);
    return u;
}

Node* create_zero(int k) {
    Node* u = newNode();
    if (k < 0) {
        u->val = 0;
        return u;
    }
    u->c[0] = create_zero(k - 1);
    pull(u);
    return u;
}

Node* create_base(int a, int k) {
    Node* u = newNode();
    if (k < 0) {
        u->val = 0;
        return u;
    }
    int p = (a >> k) & 1;
    int a_prime = a & ((1 << k) - 1);
    if (p == 0) {
        u->c[0] = create_base(a_prime, k - 1);
        u->c[1] = create_cost((1LL << k) - a_prime, k - 1);
    } else {
        u->c[0] = create_zero(k - 1);
        u->c[1] = create_base(a_prime, k - 1);
    }
    pull(u);
    return u;
}

Node* min_merge(Node* u, Node* v) {
    if (!u) return v;
    if (!v) return u;
    Node* res = newNode(min(u->val, v->val));
    if (u->c[0] || u->c[1] || v->c[0] || v->c[1]) {
        res->c[0] = min_merge(u->c[0], v->c[0]);
        res->c[1] = min_merge(u->c[1], v->c[1]);
    }
    return res;
}

Node* convolve(Node* f, Node* g, int k) {
    if (!f || !g) return nullptr;
    Node* h = newNode();
    if (k < 0) {
        h->val = f->val + g->val;
        return h;
    }
    
    Node *f0 = f->c[0], *f1 = f->c[1];
    Node *g0 = g->c[0], *g1 = g->c[1];
    
    Node* h0 = min_merge(convolve(f0, g0, k - 1), convolve(f1, g1, k - 1));
    Node* h1 = min_merge(convolve(f0, g1, k - 1), convolve(f1, g0, k - 1));
    
    h->c[0] = h0;
    h->c[1] = h1;
    if (h0 || h1) pull(h);
    
    return h;
}

Node* solve(int l, int r, const vector<int>& a) {
    if (l == r) {
        return create_base(a[l], K);
    }
    int m = (l + r) / 2;
    Node* left = solve(l, m, a);
    Node* right = solve(m + 1, r, a);
    return convolve(left, right, K);
}

ll query(Node* u, int c, int k) {
    if (!u) return INF;
    if (k < 0) {
        return u->val;
    }
    int p = (c >> k) & 1;
    return query(u->c[p], c, k - 1);
}

void run_test() {
    pool_ptr = 0;
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    
    Node* final_trie = solve(0, n - 1, a);
    
    for (int i = 0; i < q; ++i) {
        int c;
        cin >> c;
        cout << query(final_trie, c, K) << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while (t--) {
        run_test();
    }
    return 0;
}