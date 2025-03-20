// Had to use mem-saving adj list trick
// Still doesn't work with 128Mib Lim, but works easily for >=150MB eg DMOJ
// UPD: I converted the dfs functions to iterative dfs and it passes under 100Mib easily now,
//      but iterative dfs looks ugly so I'm not changing this

#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define sz(a) (int)a.size()
using ll = long long;
using ar2 = array<int,2>;
using ar3 = array<int,3>;
using vi = vector<int>;
const int mxN = (int)1e6+2;

vi w;
ll n, far, SS;
bitset<mxN> cyc, vis;
int adj[mxN*2][3];
int adjH[mxN];
int allowed_S;
vi xd;

array<ll,2> dfs2(int s){
	array<ll,2> ans = {0,s}; vis[s] = 1; xd.pb(s);
	for(int x = adjH[s]; x; x=adj[x][1]){
		int u = adj[x][0]; ll w = adj[x][2];
		if(vis[u]) continue;
		auto [xx,y] = dfs2(u);
		ans = max(ans, {xx+w,y});
	}
	return ans;
}

ll dfs(int s, int p){
	ll ans = 0;
	for(int x = adjH[s]; x; x=adj[x][1]){
		int u = adj[x][0], w = adj[x][2];
		if(u==p or cyc[u]) continue;
		ans = max(ans, dfs(u,s)+w);
	}
	return ans;
}

ll compute_diam(int s){
	allowed_S = s; xd.clear();
	int a = dfs2(s)[1]; 
	for(auto u : xd) vis[u]=0; xd.clear();
	return dfs2(a)[0];
}

int main(){
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n; ll ans = 0;
	for(int i = 1; i <= n; i++){
		int x, w; cin >> x >> w;
		adj[i*2-1][0]=i, adj[i*2-1][1]=adjH[x],adj[i*2-1][2]=w; adjH[x]=i*2-1;
		adj[i*2][0]=x, adj[i*2][1]=adjH[i],adj[i*2][2]=w; adjH[i]=i*2;
	}
	for(int i = 1; i <= n; i++){ 
		if(vis[i]) continue;
		int x = i; vi v; v.clear(); ll sum = 0, totP=0;
		while(!vis[x]) vis[x]=1,v.pb(x),x=adj[x*2][0];
		for(auto u : v) vis[u]=0; v.clear();
		while(!cyc[x]) cyc[x]=1,v.pb(x),x=adj[x*2][0];
		for(auto u : v) sum = max(sum, compute_diam(u));
		int m = sz(v); for(int i = 0; i < m; i++) v.pb(v[i]);
		multiset<ll> S; S.clear();
		for(int i = 0; i < m; i++){
			ll dis = dfs(v[i],0);
			sum=max(sum,dis); S.insert(dis-totP);	
			totP+=(ll)adj[v[i]*2][2];
		}
		ll ss = 0;
		if(sz(v)>2){
			for(int i = m; i < sz(v); i++){
				ll dis = dfs(v[i],0); 
				S.erase(S.find(dis-ss));
				sum=max(sum, dis+totP+ss+*prev(end(S))); 
				S.insert(dis-(totP+ss)); ss+=(ll)adj[v[i]*2][2];
			}
		}
		ans+=sum;
	}
	cout << ans << "\n";
}
