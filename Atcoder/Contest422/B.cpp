#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int H, W;
    cin >> H >> W;
    vector<string> S(H);
    
    for (int i = 0; i < H; i++) 
        cin >> S[i];

    int di[4] = {0, 0, -1, 1};
    int dj[4] = {1, -1, 0, 0};

    /*

        upsidedown
            > vertical or horizontal point checking.

    */

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (S[i][j] == '#') {
                int c = 0;
                for (int k = 0; k < 4; k++) {
                    int ni = i + di[k], nj = j + dj[k];

                    if(ni < 0 || nj < 0 || ni >= H || nj >= W) continue;

                    if (S[ni][nj] == '#') 
                        c++;
                }
                if (!(c == 2 || c == 4)) {
                    cout << "No";
                    return 0;
                }
            }
        }
    }
    cout << "Yes";
    return 0;
}
