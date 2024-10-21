#include "towns.h"
#include <bits/stdc++.h>
using namespace std;
#define sz(a) (int)a.size()
using ar2 = array<int,2>;
const int mxN = 115;
int n, mem[mxN][mxN];
map<int,int> M, leafs;
 
int dis(int a, int b){
	if(a==b) return 0;
	if(mem[a][b]!=-1) return mem[a][b];
	if(mem[b][a]!=-1) return mem[b][a];
	return mem[a][b]=mem[b][a]=getDistance(a,b);
}
 
int p[mxN], sz[mxN], bad[mxN];
int findSet(int i) { return p[i]==i?i:p[i]=findSet(p[i]); }
bool isSameSet(int i, int j) { return findSet(i)==findSet(j); }
void unionSet(int i, int j){
	int x = findSet(i), y = findSet(j);
	if(x==y) return;
	if(sz[x]<sz[y]) swap(x,y);
	p[y]=x; sz[x]+=sz[y];
}
 
int a, b, diameter; 
 
int getD(int i, int pos){
	int i_0 = (dis(0,i)+dis(0,a)-dis(a,i))/2;
	if(i_0<=pos) return dis(a,i)-dis(0,a)+pos;
	return dis(0,i)-pos;
}
 
bool same(int i, int j, int hubpos){
	int i_u = getD(i,hubpos);
	int u_j = getD(j,hubpos);
	return i_u+u_j != dis(i,j);
}
 
int hubDistance(int N, int sub) {
	n = N; ar2 mx = {0,0}; 
	M.clear(); leafs.clear();
	memset(mem,-1,sizeof(mem));
	for(int i = 0; i < n; i++) 
		mx=max(mx,{dis(0,i),i});
	a = mx[1]; mx = {0,0};
	for(int i = 0; i < n; i++)
		mx=max(mx,{dis(a,i),i});
	b = mx[1]; diameter = mx[0];
	int ans = diameter;
	
	for(int i = 0; i < n; i++){
		int i_0 = (dis(0,i)+dis(0,a)-dis(a,i))/2;
		int lpos = dis(0,a) - i_0; 
		int rpos = diameter-lpos;
		M[i_0] = max(lpos, rpos), leafs[i_0]++;
	}
	for(auto u : M) ans=min(ans, u.second);
	
	int tot = 0;
	for(auto u : M){
		int pos = u.first, mx_dis = u.second;
		tot+=leafs[pos];
		if(mx_dis!=ans) continue;
		if(tot-leafs[pos] > n/2) continue;
		if(n-tot > n/2) continue;
		
		stack<int> S = stack<int>();
		for(int i = 0; i < n; i++) 
			p[i]=i, sz[i]=1, bad[i]=0;
		for(int i = 0; i < n; i++){
			if(!sz(S)) S.push(i);
			else if(same(S.top(),i,pos)) 
				unionSet(i,S.top()), S.push(i);
			else S.pop();
		}
		if(!sz(S)) return ans;
		int i = S.top();
		for(int j = 0; j < n; j++){
			if(isSameSet(i,j)) continue;
			if(bad[findSet(j)]) continue;
			if(same(i,j,pos)) unionSet(i,j);
			else bad[findSet(j)]=1;
		}
		if(sz[findSet(i)]<=n/2) return ans;
	}
	return -ans;
}
