#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using ll = long long;
const ll INF = (1LL<<62);

struct Node {
    ll val;
    int idx;
};
Node better(const Node& a, const Node& b){
    if (a.val != b.val) return (a.val < b.val) ? a : b;
    return (a.idx < b.idx) ? a : b;
}

int N, Q;
vector<ll> A;
vector<Node> seg;

void build(int node, int l, int r){

    if(l == r){
        seg[node] = {A[l], l};
        return;
    }

    int mid = (l + r) >> 1;

    build(node<<1, l, mid);

    build(node<<1|1, mid+1, r);

    seg[node] = better(seg[node<<1], seg[node<<1|1]);
}

void update(int node, int l, int r, int idx, ll val){

    if(l == r){
        A[idx] = val;
        seg[node] = {val, idx};
        return;
    }

    int mid = (l + r) >> 1;

    if(idx <= mid) 
        update(node<<1, l, mid, idx, val);
    else           
        update(node<<1|1, mid+1, r, idx, val);

    seg[node] = better(seg[node<<1], seg[node<<1|1]);
}

Node query(int node, int l, int r, int ql, int qr){

    if(qr < l || r < ql) 
        return Node{INF, INT_MAX};
    if(ql <= l && r <= qr) 
        return seg[node];
    int mid = (l + r) >> 1;

    Node L = query(node<<1, l, mid, ql, qr);

    Node R = query(node<<1|1, mid+1, r, ql, qr);
    
    return better(L, R);
}

int main(){
    
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    
    A.assign(N+1, 0);
    
    for(int i=1;i<=N;i++) 
        cin >> A[i];

    seg.assign(4*(N+1), Node{INF, INT_MAX});
    build(1, 1, N);

    cin >> Q;
    while(Q--){
        int t; 
        ll i, v;
        cin >> t >> i >> v;
        if(t == 1){
            update(1, 1, N, (int)i, v);
        } else {
            
            int j = (int)v;
            Node ans = query(1, 1, N, (int)i, j);
            cout << ans.idx << '\n';
            
        }
    }
    return 0;
}
