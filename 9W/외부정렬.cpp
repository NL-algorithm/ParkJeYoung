#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <cmath>
#include <algorithm>

using namespace std;

vector<int> pWayMerge(const vector<vector<int>>& p_runs) {
    vector<int> merged_result;
    int p = p_runs.size();

    using HeapEntry = tuple<int, int, int>;
    priority_queue<HeapEntry, vector<HeapEntry>, greater<HeapEntry>> min_heap;

    for (int i = 0; i < p; ++i) {
        if (!p_runs[i].empty()) {
            min_heap.push(make_tuple(p_runs[i][0], i, 0));
        }
    }

    while (!min_heap.empty()) {
        HeapEntry smallest = min_heap.top();
        min_heap.pop();

        int value = get<0>(smallest);
        int run_index = get<1>(smallest);
        int element_index = get<2>(smallest);

        merged_result.push_back(value);

        int next_element_index = element_index + 1;
        if (next_element_index < p_runs[run_index].size()) {
            int next_value = p_runs[run_index][next_element_index];
            min_heap.push(make_tuple(next_value, run_index, next_element_index)); 
        }
    }

    //for(const auto& it : merged_result) cout << it <<' ';
    return merged_result;
}

int main() {
    long long N, M, p;
    cin >> N >> M >> p;

    vector<int> elements(N);
    for (int i = 0; i < N; ++i) {
        cin >> elements[i];
    }

    long long R = (long long)ceil((double)N / M);
    cout << R << '\n';

    long long k = 0;
    long long temp_R = R;
    while (temp_R > 1) {
        temp_R = (long long)ceil((double)temp_R / p);
        k++;
    }
    cout << k << ' ' << k + 1 << '\n';


    vector<vector<int>> all_runs;

    for (int i = 0; i < N; i += M) {
        vector<int> current_run;

        if (i + M > N) {
            current_run.assign(elements.begin() + i, elements.end());
        } else {
            current_run.assign(elements.begin() + i, elements.begin() + i + M);
        }

        sort(current_run.begin(), current_run.end());

        all_runs.push_back(current_run);
    }

    while (all_runs.size() > 1) {
        
        vector<vector<int>> next_pass_runs;

        for (int i = 0; i < all_runs.size(); i += p) {
            
            vector<vector<int>> runs_to_merge_now;
            
            int end_index = min((int)(i + p), (int)all_runs.size());
            for (int j = i; j < end_index; ++j) {
                runs_to_merge_now.push_back(all_runs[j]);
            }

            vector<int> merged_run = pWayMerge(runs_to_merge_now);
            
            next_pass_runs.push_back(merged_run);
        }

        all_runs = next_pass_runs;
    }

    for (const auto& it : all_runs[0]) {
        cout << it << ' ';
    }
    cout << '\n';

    return 0;
}