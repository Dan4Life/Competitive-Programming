#include "crocodile.h"
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define sz(a) (int)a.size()
using pii = pair<int,int>;
const int mxN = (int)1e5+10;
const int INF = (int)1e9;
vector<int> exits;
vector<pii> adj[mxN];
int n, m, dis[mxN], dis2[mxN], vis[mxN];
 
int dijkstra(){
    priority_queue<pii,vector<pii>,greater<pii>> pq;
    memset(dis,63,sizeof(dis)); memset(dis2,63,sizeof(dis2));
    for(auto u : exits) dis[u]=dis2[u]=0, pq.push({0,u});
    while(!pq.empty()){
        int s = pq.top().second; pq.pop();
        if(vis[s]) continue; vis[s]=1;
        for(auto [u,w] : adj[s]){
            if(dis[u]>dis2[s]+w)
                dis2[u]=dis[u], dis[u]=dis2[s]+w, pq.push({dis2[u],u});
            else if(dis2[u]>dis2[s]+w)
                dis2[u]=dis2[s]+w, pq.push({dis2[u],u});
        }
    }
    return dis2[0];
}
 
int travel_plan(int N, int M, int R[][2], int L[], int k, int p[])
{
    n = N, m = M;
    for(int i = 0; i < m; i++){
        int a = R[i][0], b = R[i][1], c = L[i];
        adj[a].pb({b,c}), adj[b].pb({a,c});
    }
    for(int i = 0; i < k; i++) exits.pb(p[i]);
    return dijkstra();
}
