#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>
#include <unordered_set>
#define fast cin.tie(0)->sync_with_stdio(0);

using namespace std;

vector<int>tmp;

int k;
int best = -1;


int main(){

    fast
    
    int n, k; 
    cin >> n >> k;

    string s = to_string(n);
    int L = (int)s.size();
    if (L == 1) {
        cout << -1;
        return 0;
    }

    // visited[swap_count] 에서 이미 본 문자열은 재탐색 금지
    vector<unordered_set<string>> visited(k + 1);
    queue<pair<string,int>> q;

    visited[0].insert(s);
    q.push({s, 0});

    int answer = -1;

    while (!q.empty()) {
        auto [cur, c] = q.front(); q.pop();

        if (c == k) {
            answer = max(answer, stoi(cur));
            continue;
        }
        for (int i = 0; i < L - 1; i++) {
            for (int j = i + 1; j < L; j++) {
                string nxt = cur;
                swap(nxt[i], nxt[j]);
                if (nxt[0] == '0') continue;
                if (visited[c + 1].insert(nxt).second) {
                    q.push({nxt, c + 1});
                }
            }
        }
    }

    cout << answer;
    return 0;
}