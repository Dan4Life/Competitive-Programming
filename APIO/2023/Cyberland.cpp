#include "cyberland.h"
#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using ar = pair<double,int>;
const int mxN = (int)1e5+10;
const double LINF = 1e105;
double ans;
int n, m, h;
bool vis[mxN];
double dis[mxN], dis2[mxN];
vector<pair<int,int>> adj[mxN];
priority_queue<ar,vector<ar>,greater<ar>> pq;
 
void dijkstra(){
	fill(vis,vis+n+1,0);
	for(int i = 0; i < n; i++) 
		if(dis[i]<LINF) pq.push({dis[i],i});
	while(!pq.empty()){
		auto [D,a] = pq.top(); pq.pop(); 
		if(vis[a] or a==h) continue; vis[a]=1;
		for(auto [b,w] : adj[a]) if(dis[b]>dis[a]+w) 
			dis[b]=dis[a]+w, pq.push({dis[b],b});
	}
	ans = min(ans, dis[h]);
}
 
double solve(int N, int M, int K, int H, vi x, vi y, vi c, vi A) {
	n = N, m = M, h = H, K = min(K, 67);
	fill(dis,dis+n,LINF); ans = LINF;
	for(int i = 0; i < n; i++) adj[i].clear();
	for(int i = 0; i < m; i++) 
		adj[x[i]].push_back({y[i],c[i]}),
		adj[y[i]].push_back({x[i],c[i]});
	dis[0]=0; dijkstra(); if(dis[h]>=LINF) return -1;
	for(int i = 0; i < n; i++)
		if(dis[i]!=LINF) dis[i]=A[i]&&i?LINF:0;
	for(int i = 0; i <= K; i++){
		dijkstra(); fill(dis2,dis2+n,LINF);
		for(int j = 0; j < n; j++)
			if(A[j]>1) for(auto [u,w] : adj[j])
				dis2[u]=min(dis2[u],dis[j]/2+w);
		for(int j = 0; j < n; j++) dis[j]=dis2[j];
	}
	return ans;
}
