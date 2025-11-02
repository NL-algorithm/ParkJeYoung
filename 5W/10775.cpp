#include<iostream>
#include<vector>

using namespace std;

vector<int>parent;

int find(int x){
	return (parent[x] == x ? x : parent[x] = find(parent[x]));
}

int main() {

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int g, p;
	cin >> g >> p;

	parent.assign(g + 1, 0);

	for(int i = 1; i <= g; i++)parent[i] = i;
	
	int ans = 0;
	
	for(int i = 0; i < p; i++){
		
		int want = 0;
		
		cin >> want;
		
		int tmp = find(want);

		if(tmp == 0){
			break;
		}
		
		parent[tmp] = tmp - 1;

		ans++;

	}
	cout<<ans;

	return 0;
}