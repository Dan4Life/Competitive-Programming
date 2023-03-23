#include "factories.h"
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
using ll = long long;
const int mxN = (int)5e5+5;
const int mxLg = (int)20;
const ll LINF = (ll)3e18;
int n, sub[mxN], par[mxN], vis[mxN], lev[mxN];
ll best[mxN], dis[mxN][mxLg];
vector<pair<int,ll>> adj[mxN];
 
int fcen(int s, int p, int n){
    for(auto x : adj[s]){
        int u = x.fi;
        if(u!=p and sub[u]>n/2 and !vis[u])
            return fcen(u,s,n);
    }
    return s;
}
 
int dfs(int s, int p, int S, bool ok){
    sub[s]=1;
    for(auto x : adj[s]){
        int u = x.fi; ll w = x.se;
        if(u==p or vis[u]) continue;
        if(ok) dis[u][lev[u]-lev[S]]=dis[s][lev[s]-lev[S]]+w;
        sub[s]+=dfs(u,s, S,ok);
    }
    return sub[s];
}
 
void cen_decomp1(int s, int p){
    int n = dfs(s,p,s,0);
    int cen = fcen(s,p,n);
    vis[cen] = 1;
    if(p!=-1) lev[cen]=lev[p]+1;
    par[cen]=p;
    for(auto x : adj[cen]){
        int u = x.fi;
        if(u!=p and !vis[u])
            cen_decomp1(u,cen);
    }
}
 
void cen_decomp(int s, int p){
    int n = dfs(s,p,s,0);
    int cen = fcen(s,p,n);
    vis[cen] = 1; dfs(cen,p,cen,1);
    for(auto x : adj[cen]){
        int u = x.fi, w = x.se;
        if(u!=p and !vis[u]) cen_decomp(u,cen);
    }
}
 
void Init(int N, int a[], int b[], int d[]) {
    n = N; memset(par,-1,sizeof(par));
    for(int i = 0; i <= n; i++) best[i]=LINF;
    for(int i = 0; i < n-1; i++){
        adj[a[i]].pb({b[i],d[i]});
        adj[b[i]].pb({a[i],d[i]});
    }
    cen_decomp1(0,-1); fill(vis,vis+n,0); cen_decomp(0,-1);
}
 
ll Query(int s, int x[], int t, int y[]) {
    for(int i = 0; i < s; i++){
        int a = x[i], j = 0;
        while(a!=-1){
            ll DD = dis[x[i]][j];
            best[a]=min(best[a],DD), a = par[a], j++;
        }
    }
    ll ans = LINF;
    for(int i = 0; i < t; i++){
        int x = y[i], j = 0;
        while(x!=-1){
            ans = min(ans, dis[y[i]][j]+best[x]);
            x=par[x], j++;
        }
    }
    for(int i = 0; i < s; i++){
        int a = x[i];
        while(a!=-1) best[a]=LINF, a = par[a];
    }
    return ans;
}
