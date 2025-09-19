#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>
#include <numeric>

using namespace std;

/*
    두 샘플 차를 
    이때 까지 구한 값을 응용하여
    교수님께 답을 해줘야 한다.

    이때, 구한 값이 존재하느냐 마느냐로, 답이 결정 될 것 같다.


    근데 a < b 라 하고,

    a b w 가 들어오면 누적합 알고리즘을 쓸려 했지만,

    값이 저장되어 있지 않는 상태에선 전파시키기가 까다롭다

    고로 어느 값이 연결이 되어 있는지 판단하는 DSU 를 씀과 동시에

    값이 들어오면 Prefix-Sum 으로 전파를 한뒤에

    두 원소 값의 차가 구현이 되어 있는지 안되어 있는지를 판단 해 줘야 될 것 같다.



*/

using ll = long long;

struct WUF{
    int n;
    vector<int>p, sz;
    vector<ll>pot; // pot[x] : p[x] - p[parent[x]];

    WUF(int n) : n(n), p(n), sz(n, 1), pot(n, 0) { iota(p.begin(),p.end(), 0);}

    int find(int x){
        if(p[x] == x)
            return x;
        int r = find(p[x]);
        pot[x] += pot[p[x]];
        return p[x] = r;
    }
    ll potential(int x){
        find(x);
        return pot[x];
        //P[x] - P[root(x)];
    }

    //P[v] = P[u] + w == u, v, w

    bool unite(int u, int v, ll w){
        int ru = find(u), rv = find(v);
        ll Pu = potential(u), Pv = potential(v);
        if(ru == rv)
            return (Pv - Pu == w);
        if(sz[ru] < sz[rv]){
            p[ru] = rv;
            pot[ru] = Pv - Pu - w; // (P[ru]-P[rv])
            sz[rv] += sz[ru];
        } else {
            p[rv] = ru;
            pot[rv] = Pu + w - Pv; // (P[rv]-P[ru])
            sz[ru] += sz[rv];
        }
        return true;
    }

};

int main(){

    cin.tie(0)->sync_with_stdio(0);

    int n, m;

    while(cin >> n >> m){
        if(n == 0 && m == 0) return 0;

        WUF uf(n);

        while(m--){

            char sign;
            cin >> sign;
            if(sign == '!') {

                int a, b;
                ll c;
                cin >> a >> b >> c;
                if(a > b){
                    c=-c;
                    swap(a, b);
                }
                uf.unite(a - 1, b - 1, c);

            } else {

                int x, y;
                cin >> x >> y;
                bool pos = false;
                
                x--;
                y--;
                bool sign = false;
                if(x > y){
                    swap(x, y);
                    sign = true;
                }
                if(uf.find(x) != uf.find(y)){
                    cout << "UNKNOWN" << '\n';
                    continue;
                } else {
                    ll val = uf.potential(y) - uf.potential(x);
                    if(sign) val=-val;
                    cout << val << '\n';
                }

            }

        }
    }
    


    return 0;
}