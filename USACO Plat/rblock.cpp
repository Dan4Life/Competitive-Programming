#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define all(a) a.begin(),a.end()
using ll = long long;
using pii = pair<int,int>;
const int mxN = (int)252;
const int LINF = (int)1e9;
int n, m, p[mxN], p2[mxN], edge[mxN][mxN];
int dis[mxN], vis[mxN];
vector<pii> adj[mxN];

int dijkstra(int s, int t, int p[]){
	priority_queue<pii,vector<pii>,greater<pii>> pq;
	fill(dis,dis+mxN, LINF), fill(vis,vis+mxN, 0);
	fill(p, p+mxN, -1); pq.push({0,s}); dis[s]=0;
	while(!pq.empty()){
		int a = pq.top().se; pq.pop();
		if(vis[a]) continue; vis[a]=1;
		for(int b = 1; b <= n; b++){
			int w = edge[a][b];
			if(dis[a]+w>=dis[b]) continue;
			dis[b]=dis[a]+w, p[b]=a; 
			pq.push({dis[b],b});
		}
	}
	return dis[t];
}

int32_t main() {
	ifstream cin("rblock.in"); ofstream cout("rblock.out");
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			edge[i][j]=LINF;
	for(int i = 0; i < m; i++){
		int a, b, c; cin >> a >> b >> c; 
		edge[a][b]=edge[b][a]=c;
	}
	int cur = n, orig_dis = dijkstra(1,n,p);
	int ans = orig_dis;
	while(cur!=1){
		int a  = p[cur], b = cur; int c = edge[a][b];
		edge[a][b]=edge[b][a]=c*2;
		ans = max(ans, dijkstra(1,n,p2));
		edge[a][b]=edge[b][a]=c; cur = a;
	}
	cout << ans-orig_dis;
}
