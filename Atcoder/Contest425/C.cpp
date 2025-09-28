#include<bits/stdc++.h>
#define ll long long

using namespace std;

const int N = 5e5+5;
int n,m;
ll a[N];
int main() {
	cin>>n>>m;
	
	for(int i=1;i<=n;i++)
		cin>>a[i],a[i+n]=a[i];
	
	for(int i=1;i<=2*n;i++)
		a[i]+=a[i-1];
	ll tot=0;
	while(m--){
		int opt;
		cin>>opt;
		if(opt==1){
			int x;
			cin>>x;
			tot+=x;
			tot=(tot-1)%n+1;
		}
		else {
			int x,y;
			cin>>x>>y;
			cout<<a[tot+y]-a[tot+x-1]<<"\n";
		}
	}
	return 0;
} 