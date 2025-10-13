#include <iostream>
#include <vector>
using namespace std;

struct Wave{ long long p, r, a; };

int main(){
    cin.tie(0)->sync_with_stdio(0);

    int n; long long w;
    cin >> n >> w;

    vector<Wave> waves;
    for(int i = 0; i < n; i++){
        char t; cin >> t;
        if(t=='!'){
            long long p,l,a; cin >> p >> l >> a;
            waves.push_back({p, p+l-1, a});
        }else{
            long long x; cin >> x;
            long long ans = 0;
            for(const auto& qw : waves){
                if(x < qw.p || x > qw.r) continue;
                long long d = x - qw.p;
                if(d & 1) continue;
                ans += (d & 2) ? -qw.a : qw.a;
            }
            cout << ans << '\n';
        }
    }
    return 0;
}
