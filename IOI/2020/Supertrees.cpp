#include "supertrees.h"
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define sz(a) (int)a.size()
#define all(a) begin(a), end(a)
using ar2 = array<int,2>;
using vi = vector<int>;
using ll = long long;
const int INF = (int)2e9;
const int mxN = 1010;
template<int SZ> struct DSU{
	int n, p[SZ], sz[SZ];
	void init(int _n){
		n = _n;
		for(int i = 0; i < n; i++) p[i]=i,sz[i]=1;
	}
	int findSet(int i){return i==p[i]?i:p[i]=findSet(p[i]);}
	bool isSameSet(int i, int j){return findSet(i)==findSet(j);}
	int findSz(int i){return sz[findSet(i)];}
	void unionSet(int i, int j){
		int x = findSet(i), y = findSet(j);
		if(x==y) return;
		if(sz[x]<sz[y])swap(x,y);
		p[y]=x,sz[x]+=sz[y];
	}
};
DSU<mxN> dsu1, dsu2;
vector<int> v[mxN], w[mxN];
 
int construct(vector<vi> p) {
	int n = sz(p);
	vector<vi> ans(n,vi(n,0));
	dsu1.init(n); dsu2.init(n);
	for(int i = 0; i < n; i++){
		for(int j = i+1; j < n; j++){
			if(p[i][j]==3) return 0;
			if(p[i][j]) dsu1.unionSet(i,j);
		}
	}
	for(int i = 0; i < n; i++) 
		v[dsu1.findSet(i)].pb(i);
	for(int _ = 0; _ < n; _++){
		if(sz(v[_])<=1) continue;
		bool justCycle=1, justLine=1;
		for(auto i : v[_]){
			for(auto j : v[_]){
				if(i==j) continue;
				if(p[i][j]==1) dsu2.unionSet(i,j),justCycle=0;
				if(p[i][j]==2) justLine=0;
				if(!p[i][j]) return 0;
			}
		}
		if(justCycle or justLine){
			for(int i = 0; i < sz(v[_])-1; i++)
				ans[v[_][i]][v[_][i+1]]=1;
			if(justCycle){
				ans[v[_][0]][v[_].back()]=1;
				if(sz(v[_])<=2) return 0;
			}
		}
		else{
			for(int i = 0; i < n; i++) w[i].clear();
			for(auto i : v[_]) w[dsu2.findSet(i)].pb(i);
			vector<int> rep; rep.clear();
			for(int i = 0; i < n; i++){
				if(!sz(w[i])) continue;
				for(int j = 0; j < sz(w[i])-1; j++)
					ans[w[i][j]][w[i][j+1]]=1;
				for(auto j : w[i])
					for(auto k : w[i])
						if(j!=k and p[j][k]!=1) return 0;
				rep.pb(w[i][0]);
			}
			if(sz(rep)<=2) return 0;
			for(int i = 0; i < sz(rep)-1; i++)
				ans[rep[i]][rep[i+1]]=1;
			ans[rep[0]][rep.back()]=1;
		}
	}	
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			ans[i][j]|=ans[j][i];
	build(ans); 
	return 1;
}
