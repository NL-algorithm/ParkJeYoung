#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <deque>

using namespace std;

void distribute(vector<long long>& a, long long l, long long len, long long r){

    if(len == 1){
        if(r) a[l]++;
        return;
    }

    long long half = len >> 1;

    long long left = r >> 1;

    long long right = r - left;

    distribute(a, l, half, left);

    distribute(a, l + half, half, right);

}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, k;
    cin >> n >> k;

    long long len = 1LL << n;

    if(k % len == 0){
        long long q = k / len;
        cout << 0 << '\n';
        for(long long i = 0; i < len; i++){
            if(i) cout << ' ';
            cout << q;
        }
        return 0;
    }

    long long q = k / len;

    long long r = k % len;

    vector<long long> a(len, q);
    distribute(a, 0, len, r);

    cout << 1 << '\n';

    for(long long i = 0; i < len; i++){
        if(i) cout << ' ';
        cout << a[i];
    }
    return 0;
}
