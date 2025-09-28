#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
#include <functional>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int n, m; 
    cin >> n >> m;

    vector<vector<int>> adj(m + 1);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; ++j) {
            int x; cin >> x;
            if (x) adj[j].push_back(i);
        }
    }

    vector<int> match(n + 1, 0);

    vector<int> seen(m + 1, 0);
    int vis_token = 1;

    function<bool(int)> dfs = [&](int r) -> bool {

        if (seen[r] == vis_token)
            return false;

        seen[r] = vis_token;

        for (int l : adj[r]) {

            int r2 = match[l];

            if (r2 && seen[r2] == vis_token) 
                continue;

            if (r2 == 0 || dfs(r2)) {
                match[l] = r;
                return true;
            }
        }
        return false;
    };

    int ans = 0;

    vector<int> picked; picked.reserve(m);

    for (int r = m; r >= 2; r--) {

        bool ok = true;
        
        for (int j = 0; j < (int)picked.size(); j++) {
            if (2 * (ans + 1 - j) > picked[j]) {
                 ok = false; break; 
                }
        }
        
        if (!ok) break;

        ++vis_token;
        if (dfs(r)) {
            ++ans;
            picked.push_back(r);
        }
    }

    cout << ans ;
    return 0;
}
