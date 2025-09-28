#include<bits/stdc++.h>
#define ll long long

using namespace std;

const ll N = 23,mod = 998244353;

int n;
ll f[1<<N];
string s;

ll qpow(ll a,ll b){
	ll res=1;
	while(b){
		if(b&1)res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
int main() {
	cin>>n;
	cin>>s;
	s="0"+s;
	f[0]=1;
	for(int i=1;i<(1<<n);i++){
		char c=0;
		bool flag=0;
		for(int j=1;j<=n;j++){
			if(i&(1<<j-1)){
				if(flag && c!=s[j])flag=0;
				if(!flag){
					f[i]=(f[i]+f[i^(1<<j-1)])%mod;
					c=s[j],flag=1;
				}
			}
		}
	}
	
	cout<<f[(1<<n)-1];
	return 0;
} 