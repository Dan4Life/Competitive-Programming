#include "race.h"
#include <bits/stdc++.h>
using namespace std;
 
int answ, KK, cnt[1000010], subtree[200010], timer=-1, a[1000010];
set<pair<int,int>> adj[200010];
 
void dfs(int s, int p){
    subtree[s]=1;
    for(auto x : adj[s]){
        int u = x.first;
        if(u!=p) dfs(u,s), subtree[s]+=subtree[u];
    }
}
 
void dfs2(int s, int p, int dep, int weight, bool ok){
    if(weight>KK) return;
    for(auto u : adj[s])
        if(u.first!=p)
            dfs2(u.first,s,dep+1,weight+u.second, ok);
    int D = KK-weight;
    if(!ok){
        if(D and a[D]<timer) cnt[D] = cnt[KK+1], a[D]=timer;
        answ = min(answ, dep+cnt[D]);
    }
    else{
        if(a[weight]<timer) cnt[weight] = cnt[KK+1];
        a[weight]=timer; cnt[weight] = min(cnt[weight], dep);
    }
}
 
int find_centroid(int s, int p, int sz){
    for(auto u : adj[s])
        if(u.first!=p and subtree[u.first]>sz/2)
            return find_centroid(u.first, s, sz);
    return s;
}
 
void centroid_decomp(int s, int p){
    dfs(s,-1); int sz = subtree[s];
    int centroid = find_centroid(s,-1,sz);
    // at each level, i should reset cnt[], but that will take O(K) every time so...
    // I use another array, a[], which stores the last time i updated cnt[]
    timer++;
    for(auto w : adj[centroid]){
        int u = w.first; if(u==p) continue;
        dfs2(u,centroid,1,w.second,0), dfs2(u,centroid,1,w.second,1);
    }
    while(!adj[centroid].empty()){
        int x = adj[centroid].begin()->first;
        adj[x].erase(adj[x].lower_bound({centroid,-1}));
        adj[centroid].erase(adj[centroid].begin());
        centroid_decomp(x,centroid);
    }
}
 
int best_path(int N, int K, int H[][2], int L[])
{
    answ = N+1; KK = K; cnt[0]=0;
    for(int i = 1; i <= K+1; i++) cnt[i]=N+1;
    for(int i = 0; i < N-1; i++)
        adj[++H[i][0]].insert({++H[i][1],L[i]}),
        adj[H[i][1]].insert({H[i][0],L[i]});
    centroid_decomp(1,-1);
    return (answ==N+1?-1:answ);
}
