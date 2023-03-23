#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define fi first
#define se second
#define all(a) a.begin(), a.end()
using ll = long long;
using pii = pair<int,int>;
 
const int maxn = (int)3e4+10;
const ll LINF = (ll)1e18;
pii a[maxn];
int n, m, ans;
int dis[maxn];
bool vis[maxn];
vector<pii> adj[maxn];
vector<int> doge[maxn];
 
void dijkstra(int s){
	fill(dis,dis+maxn,LINF); fill(vis, vis+maxn,false);
	priority_queue<pii,vector<pii>,greater<pii>> pq;
	pq.push({0,s}); dis[s]=0;
	while(!pq.empty()){
		int a = pq.top().se; pq.pop();
		if(vis[a]) continue; vis[a]=1;
		for(auto u : adj[a]){
			int b = u.fi, w = u.se;
			if(dis[a]+w<dis[b]){
				dis[b]=dis[a]+w;
				pq.push({dis[b],b});
			}
		}
	}
}
 
/*
My proof on how the number of edges in the graph is bounded by N*sqrt(M)
1. A single doge with power P contributes at most N/P edges 
2. All doges with power P contribute at most N edges(P doges placed from 1 to P,each of them contributing N/P)
3. There are a total of M doges
 
If total number of doges with power P <= sqrt(M):
	From first observation: they only contribute at most N/P * sqrt(M) edges = O(N*sqrt(M)) in worst case
Else, there are > sqrt(M) doges with power P:
	From second observation: they contribute at most N edges
	BUT: This case can only happen at most sqrt(M) times, therefore edges = O(N*sqrt(M)) in worst case
Therefore, number of edges = O(2*N*sqrt(M)) = O(N*sqrt(M)) □
*/
int32_t main() {
	cin >> n >> m; ans = LINF;
	for(int i = 0; i < m; i++) cin >> a[i].fi >> a[i].se, doge[a[i].fi].pb(a[i].se);
	for(int i = 0; i < n; i++)
		sort(all(doge[i])), doge[i].erase(unique(all(doge[i])), doge[i].end());
	for(int i = 0; i < n; i++){
		for(auto p : doge[i]){
			for(int j = 1; ;j++){
				int b = i+j*p; if(b>=n) break;
				auto itr = lower_bound(doge[b].begin(), doge[b].end(), p)-doge[b].begin();
				adj[i].pb({b,j});if(itr!=doge[b].size() and doge[b][itr]==p) break;
			}
			for(int j = -1; ; j--){
				int b = i+j*p; if(b<0) break;
				auto itr = lower_bound(doge[b].begin(), doge[b].end(), p)-doge[b].begin();
				adj[i].pb({b,-j}); if(itr!=doge[b].size() and doge[b][itr]==p) break;
			}
		}
	}
	dijkstra(a[0].fi); cout << (dis[a[1].fi]==LINF?-1:dis[a[1].fi]);
}
