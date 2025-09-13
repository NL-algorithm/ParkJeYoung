#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <tuple>

using namespace std;


int r, c;
vector<string> v;
int dx[] = {0, 0, -1, 1};
int dy[] = {1, -1, 0, 0};

vector<vector<char>> onPath;
vector<vector<int>> dp;
bool hasCycle = false;
int ans = 1;

int dfs(int x, int y, int t){

    if (x < 0 || y < 0 || x >= r || y >= c) 
        return 0;
    if (v[x][y] == 'H') 
        return 0;
    
    if (onPath[x][y]) { hasCycle = true; return 0; }

    int &ret = dp[x][y];
    if (ret != -1) return ret;

    onPath[x][y] = 1;

    int jump = v[x][y] - '0';
    int best = 0;
    for (int i = 0; i < 4; i++){
        int nx = x + dx[i] * jump;
        int ny = y + dy[i] * jump;
        int child = dfs(nx, ny, t + 1);
        if (hasCycle) { onPath[x][y] = 0; return 0; }
        best = max(best, child);
    }

    onPath[x][y] = 0;
    return ret = best + 1;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> r >> c;
    v.assign(r, string());
    for (int i = 0; i < r; i++) cin >> v[i];

    onPath.assign(r, vector<char>(c, 0));
    dp.assign(r, vector<int>(c, -1));
    hasCycle = false;

    int res = dfs(0, 0, 1);
    if (hasCycle) cout << -1;
    else cout << res;
    return 0;
}
