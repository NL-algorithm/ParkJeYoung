#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;

/*
    plan : 
    
        벡터 값을 입력 받고

        P 집합에 벡터 좌표가 들어 있을때,

        P에 있는 점의 절반을 이용해서 

        합의 길이가 최소가 되는 걸 구한다.
*/

int n;

vector<pair<long double,long double>> p;

long double sumx, sumy;

long double best;

void dfs(int idx, int picked, long double sx, long double sy) {

    // 남은 점 개수와 필요한 선택 개수로 가지치기

    int need = n/2 - picked;
    
    int left = n - idx;

    if (need < 0 || need > left) return;

    if (idx == n) { 

        if (picked == n/2) {

            long double dx = 2*sx - sumx;

            long double dy = 2*sy - sumy;
            
            long double val = hypotl(dx, dy);

            if (val < best) best = val;

        }

        return;
    }

    dfs(idx + 1, picked + 1, sx + p[idx].first, sy + p[idx].second);

    dfs(idx + 1, picked, sx, sy);
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; 
    cin >> T;

    cout.setf(std::ios::fixed);
    cout << setprecision(15);

    while (T--) {
        cin >> n;
        
        p.assign(n, {0,0});

        sumx = sumy = 0;
        
        for (int i = 0; i < n; ++i) {
            long double x, y; 
            cin >> x >> y;
            p[i] = {x, y};
            sumx += x; 
            sumy += y;
        }
        best = numeric_limits<long double>::infinity();
        
        dfs(0, 0, 0, 0);
        
        cout << (double)best << '\n';
    }
    return 0;
}
