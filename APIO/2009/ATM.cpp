#include <bits/stdc++.h>
using namespace std;
#define pb push_back
using vi = vector<int>;
using ar = array<int,2>;
const int N = (int)5e5+9;
vi ts, v;
int n, m, x, s, p;
bitset<N> vis, pub;
int cc[N], dp[N], cost[N];
ar adj[N], radj[N], cadj[N], cradj[N];
int adjH[N], radjH[N], cadjH[N], cradjH[N];

void dfs(int s, ar adj[], int adjH[], vi &v){
	vis[s]=1;
	for(int x = adjH[s]; x; x=adj[x][1]){
		int u = adj[x][0];
		if(!vis[u]) dfs(u,adj,adjH,v);
	}	
	v.pb(s);
}

int main(){
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;
	for(int i = 1; i <= m; i++){
		int a, b; cin >> a >> b;
		adj[i] = {b,adjH[a]}; adjH[a]=i;
		radj[i] = {a,radjH[b]}; radjH[b]=i;
	}
	for(int i = 1; i <= n; i++) cin >> cost[i];
	cin >> s >> p;
	for(int i = 1; i <= p; i++) cin >> x, pub[x]=1;
	for(int i = 1; i<=n; i++)
		if(!vis[i]) dfs(i,adj,adjH,ts);
	vis.reset(); reverse(begin(ts),end(ts));
	for(auto u : ts){
		if(!vis[u]){
			v.clear(); dfs(u,radj,radjH,v);
			for(auto x : v){
				cc[x]=u; if(x==u) continue;
				pub[u]=pub[u]|pub[x], cost[u]+=cost[x];
			}
		}
	}
	int tot = 1;
	for(int i = 1; i <= n; i++){
		for(int y = adjH[i]; y; y=adj[y][1]){
			auto u = adj[y][0];
			if(cc[i]!=cc[u]){
				int a = cc[i], b = cc[u];
				cadj[tot] = {b,cadjH[a]}; cadjH[a]=tot;
				cradj[tot] = {a,cradjH[b]}; cradjH[b]=tot; tot++;
			}
		}
	}
	ts.clear(); vis.reset();
	for(int i = 1; i <= n; i++)
		if(!vis[cc[i]]) dfs(cc[i],cadj,cadjH,ts);
	for(int i = 1; i <= n; i++) dp[i]=-2e9;
	for(auto u : ts){
		if(pub[u]) dp[u]=max(dp[u],cost[u]);
		for(int y = cradjH[u]; y; y=cradj[y][1]){
			auto x = cradj[y][0];
			if(x!=u) dp[x] = max(dp[x], dp[u]+cost[x]);
		}	
	}
	cout << dp[cc[s]];
}
