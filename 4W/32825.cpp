#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int inputs[8];
int vars[13];

bool used[14];

long long solution_count = 0;

void back(int k){
    if(k == 13){
        if(vars[0] + vars[4] + vars[8] + vars[11] == inputs[0] &&
        vars[1] + vars[5] + vars[9] + vars[12] == inputs[1]){
            solution_count++;
        }
        return;
    }

    for(int i = 1; i <= 13; i++){
        if(!used[i]){
            vars[k] = i;
            used[i] = true;

            bool slice = false;

            if(k == 3){
                if(vars[0] + vars[1] + vars[2] + vars[3] != inputs[4])
                    slice = true;
                
            } else if (k == 7) {
                if(vars[4] + vars[5] + vars[6] + vars[7] != inputs[5])
                    slice = true;
                if(!slice && vars[3] + vars[7] != inputs[3])
                    slice = true;
            } else if (k == 10) {
                if(vars[8] + vars[9] + vars[10] != inputs[6]) 
                    slice = true;
                if(!slice && vars[2] + vars[6] + vars[10] != inputs[2])
                    slice = true;
            } else if (k == 12) {
                if(vars[11] + vars[12] != inputs[7])
                    slice = true;
            }
            if(!slice)
                back(k + 1);
            used[i] = false;
        }

    }
}


int main(){

    cin.tie(0)->sync_with_stdio(0);

     for (int i = 0; i < 8; ++i) {
        cin >> inputs[i];
    }

    int sum_col = inputs[0] + inputs[1] + inputs[2] + inputs[3]; // A+B+C+D
    int sum_row = inputs[4] + inputs[5] + inputs[6] + inputs[7]; // E+F+G+H
    int sum_1_to_13 = 91;

    if (sum_col != sum_1_to_13 || sum_row != sum_1_to_13) {
        cout << 0;
        return 0;
    }

    back(0);

    cout << solution_count;

    return 0;
}