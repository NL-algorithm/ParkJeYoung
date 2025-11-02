/*
* PST PM 00:38 - PM 2:22
* 
* 로직은 사진 첨부
* 
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<tuple>
#define REAL ios::sync_with_stdio(false); cin.tie(nullptr)

using namespace std;

typedef pair<int, int> PR;
typedef tuple<int, int, int>TP;
struct data_struct {
	int x;
	int y;
	vector<int> idx;

	data_struct(int _x, int _y, vector<int> _idx)
		: x(_x), y(_y), idx(std::move(_idx))
	{
	}
};

int N, M, L, K;

long long MAX_subset = 0;

vector<PR>node;
vector<TP>node_data;
//{ idx, 좌표 }

vector<data_struct>set_x, set_y;

void make_set(int start, int end, int i, int j, vector<data_struct>& set) {
	vector<int> temp;
	
	for (; i <= j; i++) {
		temp.push_back(get<0>(node_data[i]));
	}
	sort(temp.begin(), temp.end());

	set.emplace_back(start, end, temp);
}

void factory_set(bool type, vector<data_struct>&set) {

	for (int i = 0, j = 1; j < K; j++) {

		auto [a, x_i, y_i] = node_data[i];
		
		auto [b, x_j, y_j] = node_data[j];
		
		int interval = (type ? x_j - x_i : y_j - y_i);
		int start = type ? x_i : y_i;
		int end = type ? x_j : y_j;

		if (j + 1 < K) {
			
			auto [c, nxt_x_j, nxt_y_j] = node_data[j + 1];
			int nxt_interval = (type ? nxt_x_j - x_i : nxt_y_j - y_i);

			if (interval <= L && nxt_interval > L) {
				make_set(start, end, i, j, set);
				i++;
				
			}


			else if (interval > L) {
				j--;
				i++;
			}

		}
		else {
			if (interval > L) {
				j--;
				i++;
				continue; 
			}
			make_set(start, end, i, j, set);
		}
	}
}

void comparison_set() {

	

	for (int i = 0; i < (int)set_x.size(); i++) {
		int l = set_x[i].idx.front();
		int r = set_x[i].idx.back();

		for (int j = 0; j < (int)set_y.size(); j++) {
			long long stack = 0;
			for (int k : set_y[j].idx) {
				if (k >= l && k <= r)
					stack++;
			}
			MAX_subset = (MAX_subset > stack ? MAX_subset : stack);
		}

	}

}

int main() {
	REAL;
	
	cin >> N >> M >> L >> K;

	for (int i = 0; i < K; i++) {
		int x, y;
		cin >> x >> y;

		node.emplace_back(x, y);
	}
	if (K == 1) {

    cout << 0 << "\n";
    return 0;
}
	sort(node.begin(), node.end());

	for (int i = 0; i < K; i++) {
		node_data.emplace_back(i, node[i].first, node[i].second);
	}

	factory_set(1, set_x);

	sort(node_data.begin(), node_data.end(),
		[](auto const& A, auto const& B) {
			return make_pair(get<2>(A), get<1>(A))
				< make_pair(get<2>(B), get<1>(B));
		}
	);

	factory_set(0, set_y);

	comparison_set();

	cout << K - MAX_subset;

	return 0;
}
