#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define all(a) a.begin(),a.end()

const int mxN = (int)2e4+10;
const int LINF = (int)1e9;
using pii = pair<int,int>;
vector<pii> adj[mxN], radj[mxN];
int n, m, k, q, a, b, c, tot, cnt;
int hub[mxN], dis[2][210][mxN], vis[mxN];

void dijkstra(int s, int k, int t, vector<pii> adj[]){
	priority_queue<pii,vector<pii>,greater<pii>> pq;
	fill(dis[t][k],dis[t][k]+mxN,LINF); dis[t][k][s]=0;
	memset(vis,0,sizeof(vis)); pq.push({0,s});
	while(!pq.empty()){
		int a = pq.top().se; pq.pop();
		if(vis[a]) continue; vis[a]=1;
		for(auto [b,w] : adj[a]){
			if(dis[t][k][a]+w<dis[t][k][b]){
				dis[t][k][b]=dis[t][k][a]+w;
				pq.push({dis[t][k][b],b});
			}
		}
	}
}

int32_t main() {
	ifstream cin("vacationgold.in"); 
	ofstream cout("vacationgold.out");
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m >> k >> q;
	for(int i = 0; i < m; i++){
		cin >> a >> b >> c;
		adj[a].pb({b,c}), radj[b].pb({a,c});
	}
	for(int i = 0; i < k; i++){
		cin >> hub[i]; 
		dijkstra(hub[i],i,0,adj);
		dijkstra(hub[i],i,1,radj);
	}
	while(q--){
		cin >> a >> b; int ans = LINF;
		for(int i = 0; i < k; i++) 
			ans = min(ans, dis[0][i][b]+dis[1][i][a]);
		if(ans!=LINF) cnt++, tot+=ans;
	}
	cout << cnt << "\n" << tot << "\n";
}
