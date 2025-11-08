#include <bits/stdc++.h>

using namespace std;

const int dr[] = {0, 1, 0, -1};
const int dc[] = {1, 0, -1, 0};

const int nextDir[4][3] = {
    {0, 1, 3},
    {1, 0, 2},
    {2, 3, 1},
    {3, 2, 0}
};

int solve() {
    int H, W;
    cin >> H >> W;
    vector<string> S(H);
    for (int i = 0; i < H; i++) {
        cin >> S[i];
    }

    auto mirrorToType = [](char c) {
        if (c == 'A') return 0;
        if (c == 'B') return 1;
        return 2;
    };

    vector<vector<vector<int>>> dist(H, vector<vector<int>>(W, vector<int>(4, 1e9)));
    deque<tuple<int, int, int, int>> dq;

    for (int mirror = 0; mirror < 3; mirror++) {
        int opCost = (mirrorToType(S[0][0]) == mirror ? 0 : 1);
        int exitDir = nextDir[0][mirror];
        
        if (opCost < dist[0][0][exitDir]) {
            dist[0][0][exitDir] = opCost;
            if (opCost == 0) {
                dq.push_front({opCost, 0, 0, exitDir});
            } else {
                dq.push_back({opCost, 0, 0, exitDir});
            }
        }
    }

    int minCostToGoal = 1e9;

    while (!dq.empty()) {
        auto [cost, r, c, exitDir] = dq.front();
        dq.pop_front();

        if (cost > dist[r][c][exitDir]) {
            continue;
        }

        if (r == H - 1 && c == W - 1 && exitDir == 0) {
             minCostToGoal = min(minCostToGoal, cost);
        }

        int nextR = r + dr[exitDir];
        int nextC = c + dc[exitDir];
        int entryDir = exitDir;

        if (nextR < 0 || nextR >= H || nextC < 0 || nextC >= W) {
            continue;
        }

        int currentMirror = mirrorToType(S[nextR][nextC]);
        
        for (int mirror = 0; mirror < 3; mirror++) {
            int opCost = (currentMirror == mirror ? 0 : 1);
            int newCost = cost + opCost;
            int newExitDir = nextDir[entryDir][mirror];

            if (newCost < dist[nextR][nextC][newExitDir]) {
                dist[nextR][nextC][newExitDir] = newCost;
                if (opCost == 0) {
                    dq.push_front({newCost, nextR, nextC, newExitDir});
                } else {
                    dq.push_back({newCost, nextR, nextC, newExitDir});
                }
            }
        }
    }

    return minCostToGoal;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int T;
    cin >> T;
    while (T--) {
        cout << solve() << "\n";
    }
    return 0;
}