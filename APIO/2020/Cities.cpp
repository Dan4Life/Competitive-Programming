#include "swap.h"
#include <bits/stdc++.h>
using namespace std;
 
#define all(a) begin(a),end(a)
#define sz(a) (int)a.size()
#define pb push_back
 
const int mxN = (int)4e5+10;
const int mxLg = 20;
int n, m, newN, dfs_time;
int st[mxN], en[mxN], deg[mxN];
int p[mxN], line[mxN], good[mxN]; 
vector<array<int,3>> edges;
int jmp[mxLg][mxN], dep[mxN];
vector<int> adj[mxN];
 
int findSet(int i){return p[i]==i?i:p[i]=findSet(p[i]);}
bool isSameSet(int i, int j) { return findSet(i)==findSet(j); }
 
void unionSet(int i, int j){
	deg[i]++, deg[j]++;
	
	int x = findSet(i), y = findSet(j);
	
	if(x==y) line[x] = 0;
	if(!line[x] or !line[y] or deg[i]>=3 or deg[j]>=3 or good[x] or good[y])
		line[x]=line[y]=0, good[newN]=1;
		
	adj[newN].pb(y),adj[y].pb(newN);
	if(x!=y) adj[newN].pb(x),adj[x].pb(newN);
	
	p[y] = p[x] = p[newN] = newN; newN++;
}
 
void dfs(int s, int p){
	if(p!=-1) dep[s] = dep[p]+1;
	else dep[s] = 0;
	jmp[0][s] = p;
	st[s] = dfs_time++;
	for(auto u : adj[s]) 
		if(u!=p) dfs(u,s);
	en[s] = dfs_time;
}
 
void init(int N, int M, vector<int> U, vector<int> V, vector<int> W) {
	n = N, m = M; newN = N;
	for(int i = 0; i < N+M; i++) 
		p[i]=i,deg[i]=0,line[i]=1;
	for(int i = 0; i < M; i++)
		edges.pb({W[i],U[i],V[i]});
	sort(all(edges),[&](array<int,3> a, array<int,3> b){
		return a[0]<b[0];
	});
	
	memset(jmp,-1,sizeof(jmp));
	
	for(int i = 0; i < M; i++)
		unionSet(edges[i][1],edges[i][2]);
		
	for(int i = newN-1; i>=0; i--) 
		if(!dep[i]) dfs(i,-1);
		
	for(int i = 1; i < mxLg; i++)
		for(int j = 0; j < newN; j++)
			if(jmp[i-1][j]!=-1) jmp[i][j] = jmp[i-1][jmp[i-1][j]];
}
 
inline bool anc(int a, int b){
	return st[a]<=st[b] and en[a]>=en[b];
}
 
int lca(int a, int b){
	if(anc(a,b)) return a;
	if(anc(b,a)) return b;
	for(int i = mxLg-1; i>=0; i--)
		if(jmp[i][a]!=-1 and !anc(jmp[i][a],b))
			a = jmp[i][a];
	if(!anc(jmp[0][a],b)) return -1;
	return jmp[0][a];
}
 
int findNearestAnc(int s){
	if(s==-1 or good[s]) return s;
	for(int i = mxLg-1; i>=0; i--)
		if(jmp[i][s]!=-1 and !good[jmp[i][s]])
			s = jmp[i][s];
	if(jmp[0][s]==-1 or !good[jmp[0][s]]) return -1;
	return jmp[0][s];
}
 
int getMinimumFuelCapacity(int X, int Y) {
	int Z = findNearestAnc(lca(X,Y));
	return Z==-1?-1:edges[Z-n][0];
}
