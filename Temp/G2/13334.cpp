#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

using ll = long long;

using pr = pair<ll, ll>;

constexpr ll INF = 1LL<<61;

int main(){

	cin.tie(0)->sync_with_stdio(0);

	int n;
	cin >> n;

	vector<pr>axis;
	
	while(n--){
		int x, y;
		
		cin >> x >> y;
		if(x > y)
			swap(x, y);
		axis.emplace_back(x, y);

	}

	ll d;
	
	sort(axis.begin(),axis.end(),[](const pr& A, const pr& B){
		return A.second < B.second;
	});
	
	cin >> d;
	priority_queue<ll, vector<ll>, greater<ll>>pq;

	ll Ans = 0;

	for(auto&[L, R] : axis){

		if(L == INF) continue;

		pq.push(L);
		if(pq.top() < R - d){
			pq.pop();
		}
		Ans = max(Ans, (ll)pq.size());
	}
	
	cout << Ans;
	
}