#include<bits/stdc++.h>
#define ll long long
#define x first
#define y second

using namespace std;

const int N = 3e5+5;

int n,m;
ll ans=0;
int dx[4]={0,0,-1,1},dy[4]={1,-1,0,0};
int main() {
	cin>>n>>m;
	
	queue<pair<ll,ll> > q;
	char c[n+5][m+5];
	int vis[n+5][m+5];
	memset(vis,-1,sizeof(vis));
	
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>c[i][j];
			if(c[i][j]=='#')q.push(make_pair(i,j)),vis[i][j]=0,ans++;
		}
	}
	
	while(!q.empty()){
		int x=q.front().x,y=q.front().y;
		q.pop();
		for(int i=0;i<4;i++){
			int xx=x+dx[i],yy=y+dy[i];
			if(xx>0 && yy>0 && xx<=n && yy<=m && vis[xx][yy]==-1){
				bool flag=1;
				for(int j=0;j<4;j++){
					int px=xx+dx[j],py=yy+dy[j];
					if(px<=0 || py<=0 || px>n || py>m)continue;
					if(px==x && py==y)continue;
					if(vis[px][py]!=-1 && vis[px][py]<=vis[x][y]){
						flag=0;
						break;
					}
				}
				if(flag){
					vis[xx][yy]=vis[x][y]+1;
					q.push(make_pair(xx,yy));
					ans++;
				}
			}
		}
	}
	cout<<ans;
	return 0;
} 