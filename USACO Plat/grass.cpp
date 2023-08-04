#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(a) begin(a),end(a)
const int N = (int)1e5+10;

bool vis[N];
int n, m, x, y, ans;
int cc[N], sz[N], to[N], fro[N];
vector<int> ts, v, adj[N], radj[N], cadj[N], cradj[N];

void dfs(int s, vector<int> adj[], vector<int> &v, int p=0){
    vis[s] = 1;
    for(auto u : adj[s])
        if(!vis[u]) dfs(u,adj,v,s);
    v.pb(s);
}

int main(){
    ifstream cin("grass.in");
    ofstream cout("grass.out");
    cin >> n >> m;
    for(int i = 1; i <= m; i++){
        int a, b; cin >> a >> b; 
        adj[a].pb(b); radj[b].pb(a);
    }
    for(int i = 1; i <= n; i++) if(!vis[i]) dfs(i,adj,ts);
    reverse(all(ts)); memset(vis,0,sizeof(vis));
    for(auto u : ts){
        if(vis[u]) continue;
        v.clear(); dfs(u,radj,v);
        for(auto x : v) cc[x]=u, sz[u]++;
    }
    for(int i = 1; i <= n; i++)
        for(auto u : adj[i]) if(cc[u]!=cc[i])
            cadj[cc[i]].pb(cc[u]),cradj[cc[u]].pb(cc[i]);
    for(int i = 1; i <= n; i++) to[i]=fro[i]=-2*n;
    memset(vis,0,sizeof(vis)); ts.clear(); dfs(cc[1],cadj,ts);
    to[cc[1]]= fro[cc[1]] = sz[cc[1]]; reverse(all(ts));
    for(auto u : ts) for(auto x : cadj[u]) to[x]=max(to[x],to[u]+sz[x]);
    memset(vis,0,sizeof(vis)); ts.clear(); dfs(cc[1],cradj,ts); reverse(all(ts));
    for(auto u : ts) for(auto x : cradj[u]) fro[x]=max(fro[x],fro[u]+sz[x]);
    for(int i = 1; i <= n; i++) for(auto u : cradj[cc[i]]) 
        ans = max(ans, to[cc[i]]+fro[u]-2*sz[cc[1]]);
    cout << ans+sz[cc[1]];
}
