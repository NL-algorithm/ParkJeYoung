#include <iostream>
#include <algorithm>
#include <array>
using namespace std;

int main(){
    cin.tie(0)->sync_with_stdio(0);

    int n; long long H;
    cin >> n >> H;

    long long ans = 0;
    for(int i = 0; i < n; i++){
        array<long long,3> a;
        cin >> a[0] >> a[1] >> a[2];
        sort(a.begin(), a.end());
        if(H < a[0]){
            cout << "impossible\n";
            return 0;
        }
        ans += (H < a[1] ? a[1] : a[0]);
    }
    cout << ans << '\n';
    return 0;
}
