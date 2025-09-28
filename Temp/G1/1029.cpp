#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>

using namespace std;

/*

    dp[mask][u][p]
        := 방문집합, 노드, 직전 가격 에서 앞으로 가능 한 최대 노드수

    전이
        모든 v 에 대해 아직 방문하지 않았고,
        price[u][v] >= p 이면
        dp = max(dp, 1 + dfs(mask | (1<<v), v, price[u][v]))

    시작
        dfs(1<<0,0,0)

*/

constexpr int MAXN = 15;
constexpr int MAXP = 10;
constexpr int MAXMASK = 1<<MAXN;

int n;
int priceMat[MAXN][MAXN];
int dp[MAXMASK][MAXN][MAXP];

int dfs(int mask, int u, int p){
    int &ret = dp[mask][u][p];

    if(ret != -1)
        return ret;
    ret = 1;
    for(int v = 0; v < n; v++){
        if(mask & ( 1 << v ) )
            continue;
        int w = priceMat[u][v];
        if(w >= p)
            ret = max(ret, 1 + dfs(mask | (1 << v), v, w));
    }
    return ret;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;

    vector<string>adj(n);
    for(auto& iter : adj)
        cin >> iter;

    for(int i = 0 ; i < n; i++)
        for(int j = 0; j < n; j++)
            priceMat[i][j] = adj[i][j] - '0';

    memset(dp, -1, sizeof(dp));

    int ans = dfs(1<<0, 0, 0);

    cout << ans; return 0;
    
}
