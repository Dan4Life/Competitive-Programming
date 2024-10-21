#include "dreaming.h"
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define sz(a) (int)a.size()
#define all(a) a.begin(),a.end()
const int mxN = (int)1e5+10;
int n, m, l,CC=1,ans2;
vector<int> path, v;
int vis[mxN], dis[mxN];
vector<pair<int,int>> adj[mxN];
vector<int> comp;
 
bool dfs2(int s, int p, int t){
    if(s==t) return 1;
    for(auto x : adj[s]){
        int u = x.fi, w = x.se;
        if(u==p) continue;
        if(dfs2(u,s,t)){ path.pb(w); return 1; }
    }
    return 0;
}
 
void dfs(int s, int p){
    vis[s]=CC;
    if(p==-1) comp.clear();
    comp.pb(s);
    for(auto x : adj[s]){
        int u = x.fi, w = x.se;
        if(u==p) continue;
        dis[u] = dis[s]+w; dfs(u,s);
    }
}
 
void calcDiam(int s){
    int a=s, b=s, mx = 0;
    dis[s]=0; dfs(s,-1);
 
    for(auto i : comp)
        if(mx<=dis[i]) mx=dis[i],a=i;
    dis[a]=0; mx = 0; dfs(a,-1);
    for(auto i : comp)
        if(mx<=dis[i]) mx=dis[i],b=i;
    path.clear(); dfs2(a,-1,b);
    if(path.empty()) v.pb(0);
    else{
        int dis1 = accumulate(all(path),0), dis2 = 0;
        int ans = dis1; ans2 = max(ans2, dis1);
        for(auto u : path){
            dis1-=u, dis2+=u;
            ans = min(ans, max(dis1,dis2));
        }
        v.pb(ans);
    }
    for(int i = sz(v)-2; i>=0; i--)
        if(v[i]<v[i+1])swap(v[i],v[i+1]);
    if(sz(v)==4) v.pop_back();
}
 
int travelTime(int N, int M, int L, int a[], int b[], int c[]) {
    n = N; m = M; l = L; int ans;
    for(int i = 0; i < m; i++){
        a[i]++, b[i]++;
        adj[a[i]].pb({b[i],c[i]});
        adj[b[i]].pb({a[i],c[i]});
    }
    for(int i = 1; i <= n; i++)
        if(!vis[i]) calcDiam(i),CC++;
    if(sz(v)==1) return ans2;
    if(sz(v)>=2) ans = v[0]+l+v[1];
    if(sz(v)>=3) ans = max(ans,v[1]+l*2+v[2]);
    return max(ans, ans2);
}
