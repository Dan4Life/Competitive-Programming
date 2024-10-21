#include "stations.h"
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define sz(a) (int)a.size()
#define all(a) begin(a),end(a)
using ll = long long;
using vi = vector<int>;
const int mxN = 1010;
int dfs_timer = 0;
vi labels, adj[mxN];
 
void dfs(int s, int p, int dep){
    if(!dep) labels[s] = dfs_timer++;
    for(auto u : adj[s])
        if(u!=p) dfs(u,s,dep^1);
    if(dep) labels[s] = dfs_timer++;
}
 
vi label(int n, int k, vi u, vi v) {
    labels.clear(); labels.resize(n,0); dfs_timer=0;
    for(int i = 0; i < n; i++) adj[i].clear();
    for(int i = 0; i < sz(u); i++){
        int a = u[i], b = v[i];
        adj[a].pb(b), adj[b].pb(a);
    }
    dfs(0,-1, 0); return labels;
}
 
int find_next_station(int s, int t, vi c) {
    if(sz(c)==1) return c[0];
    for(auto u : c) if(u==t) return u;
    if(s < c[0]){
        if(s<=t and t<=c.back())
            return *lower_bound(all(c),t);
        return c.back();
    }
    if(c[0]<=t and t<=s)
        return *--upper_bound(all(c),t);
    return c[0];
}
