/*

Problem_Solving_Time PM 2:40 - 3:30

*/

#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

vector<pair<int,int>>arr;//key : abs, value

void push(int x) {
	arr.push_back({abs(x),x});
	int i = arr.size() - 1;

	//heapify_push
	while (i > 0) {
		int parent = i - 1;
		parent /= 2;
		int k1 = arr[parent].first, k2 = arr[i].first;
		
		int v1 = arr[parent].second, v2 = arr[i].second;
		if (k1 > k2 || (k1 == k2 && v1 > v2)) {
			swap(arr[parent], arr[i]);
			i = parent;
		}
		else break;

	}
}

int pop() {
	if (arr.empty())return 0;

	pair<int, int> result = arr[0];

	arr[0] = arr.back();
	arr.pop_back();
	int i = 0;
	while (1) {
		int l = 2 * i + 1;
		int r = 2 * i + 2;
		int small = i;
		
		if (l < arr.size()) {
			int small_k = arr[small].first, small_v = arr[small].second;
			int left_k = arr[l].first, left_v = arr[l].second;
			if ((left_k < small_k || (left_k == small_k && left_v < small_v))) {
				small = l;
			}
		}
		if (r < arr.size()) {
			int small_k = arr[small].first, small_v = arr[small].second;
			int right_k = arr[r].first, right_v = arr[r].second;
			if (r < arr.size() && (right_k < small_k || (right_k == small_k && right_v < small_v))) {
				small = r;
			}
		}
		if (small == i)break;
		swap(arr[i], arr[small]);  i = small;
	}
	return result.second;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, x;
	cin >> n;
	while (n--) {
		cin >> x;
		if (x == 0)cout << pop() << "\n";
		else push(x);
	}

}