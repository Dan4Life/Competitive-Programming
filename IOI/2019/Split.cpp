#include "split.h"
#include <bits/stdc++.h>
using namespace std;
 
#define pb push_back
#define sz(a) (int)a.size()
#define all(a) begin(a),end(a)
 
using ll = long long;
using vi = vector<int>;
using ar2 = array<int,2>;
const int mxN = (int)1e5+3;
 
bitset<mxN> vis;
vector<ar2> edges;
int par[mxN], sub[mxN];
int cen, pick, pickPar;
int n, a, b, c, A, B, C;
vector<int> ans, adj[mxN];
 
int dfs(int s, int p){
	sub[s] = 1; par[s]=p;
	for(auto u : adj[s]){
		if(u==p) continue;
		sub[s]+=dfs(u,s);
	}
	return sub[s];
}
 
struct Dsu{
	int p[mxN], sz[mxN];
	void init(int n){
		for(int i = 0; i < n; i++) p[i]=i,sz[i]=1;
	}
	int findSet(int i){ return p[i]==i?i:p[i]=findSet(p[i]); }
	bool isSameSet(int i, int j) { return findSet(i)==findSet(j); }
	void unionSet(int i, int j){
		int x = findSet(i), y = findSet(j);
		if(x==y) return;
		if(sz[x]<sz[y])swap(x,y);
		p[y]=x, sz[x]+=sz[y];
	}
	int findSz(int i){ return sz[findSet(i)]; }
} dsu;
 
void bfs(int s, int p, int d, int D){
	queue<int> Q = queue<int>();
	vis.reset(); Q.push(s); vis[s] = 1; 
	while(sz(Q)){
		auto s = Q.front(); Q.pop();
		if(d) ans[s]=D, d--;
		for(auto u : adj[s]){
			if(u==p) continue;
			if(vis[u]) continue;
			if(ans[u]!=C) continue;
			vis[u] = 1; Q.push(u);
		}
	}
}
 
int fcen(int s, int p, int n){
	for(auto u : adj[s]){
		if(u==p) continue;
		if(sub[u]>n/2) return fcen(u,s,n);
	}
	return s;
}
 
void dfs2(int s, int p){
	if(p!=cen and s!=cen) dsu.unionSet(s,p);
	for(auto u : adj[s]){
		if(u==p) continue;
		dfs2(u,s);
	}
}
 
vi find_split(int N, int _a, int _b, int _c, vi p, vi q) {
	n = N; a=_a, b=_b, c=_c; A=1,B=2,C=3; pick=-1;
	if(a>b) { swap(a,b), swap(A,B); }
	if(b>c) { swap(b,c), swap(B,C); }
	if(a>b) { swap(a,b), swap(A,B); }
	dsu.init(n); edges.clear();
	for(int i = 0; i < sz(p); i++){
		int x = p[i], y = q[i];
		if(!dsu.isSameSet(x,y)){
			adj[x].pb(y); adj[y].pb(x);
			dsu.unionSet(x,y);
		}
		else edges.pb({x,y});
	}
	dfs(0,-1); cen = fcen(0,-1,n); dfs(cen,-1);
	for(auto u : adj[cen]){
		if(sub[u]<a) continue;
		pick=u,pickPar=cen; break;
	}
	ans.clear(), ans.resize(n,C);
	if(pick!=-1){ 
		bfs(pick,pickPar,a,A); 
		bfs(pickPar,pick,b,B);
		return ans;
	}
	dsu.init(n); for(auto u : adj[cen]) dfs2(u,cen);
	for(auto [x,y] : edges){
		adj[x].pb(y), adj[y].pb(x);
		if(x==cen or y==cen) continue;
		dsu.unionSet(x,y);
		if(dsu.findSz(x)<a) continue;
		bfs(x,cen,a,A); bfs(cen,-1,b,B); return ans;
	}
	for(auto &u : ans) u=0; return ans;
}
