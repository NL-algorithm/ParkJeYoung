#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main(){

    cin.tie(0)->sync_with_stdio(0);

    int h, w;

    cin >> h >> w;

    vector<vector<int>>v(h, vector<int>(w, 0));

    for(int i = 0; i < w; i++){

        int k; cin >> k;

        for(int j = 0; j < k; j++){
            v[j][i] = 1;
        }
        
    }

    {// throw-case
        int u = 0;
        for(int i = 0; i < w; i++)
            if(v[0][i]) u++;
        if(u == 1){
            cout << '0';
            return 0;
        }
    }
    
    int ans = 0;

    for(int i = 0; i < h; i++){

        bool check1 = false;

        int tmp = 0;

        {
            int u = 0;
            for(int j = 0; j < w; j++){
                if(v[i][j]) u++;
            }

            if(u == 1) continue;
        }




        for(int j = 0; j < w; j++){
            if(!check1 && !v[i][j]) continue;
            
            if(!check1){
                if(v[i][j]){
                    check1 = true;
                }
            } else {

                
                if(v[i][j]){    
                    ans += (tmp);
                    tmp = 0;
                    //check1 = false;
                } else {
                    tmp++;
                }
                
            }

        }
    } cout << ans;

}