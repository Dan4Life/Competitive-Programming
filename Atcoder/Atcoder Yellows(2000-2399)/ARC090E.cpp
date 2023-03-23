/*
Solved with help (partially with editorial, but mostly without help)
*/

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define fi first
#define se second
const int maxn = (int)2e5+10;
const int LINF = (int)1e18;
const int MOD = (int)1e9+7;
int n, m, S, T;
bool vis[2][maxn];
int dis[2][maxn], dp[2][maxn];
vector<pair<int,int>> adj[maxn];

void dijkstra(bool t){
    int s = S, d = T; if(t) swap(s,d);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    for(int i = 0; i <= n; i++) dis[t][i]=LINF;
    pq.push({0,s}); dis[t][s] = 0; dp[t][s] = 1;
    while(!pq.empty()){
        int a = pq.top().se; pq.pop();
        if(vis[t][a]) continue; vis[t][a]=1;
        for(auto u : adj[a]){
            int b = u.fi, w = u.se;
            if(dis[t][a]+w<dis[t][b]){
                dis[t][b]=dis[t][a]+w;
                pq.push({dis[t][b],b});
                dp[t][b]=dp[t][a];
            }
            else if(dis[t][a]+w==dis[t][b])
                dp[t][b]+=dp[t][a], dp[t][b]%=MOD;
        }
    }
}

inline int sq(int a){return ((a%MOD)*(a%MOD))%MOD;}

int32_t main(){
    cin >> n >> m >> S >> T;
    for(int i = 0; i < m; i++){
        int a, b, c; cin >> a >> b >> c;
        adj[a].pb({b,c}), adj[b].pb({a,c});
    }
    dijkstra(0), dijkstra(1);
    int ans = (dp[0][T]*dp[0][T])%MOD, X = 0;
    for(int i = 1; i <= n; i++)
        if(dis[0][i]+dis[1][i]==dis[0][T])  // Point is in shortest path
            if(dis[0][i]==dis[1][i])          // They meet at that point
                X+=sq(dp[0][i]*dp[1][i]), X%=MOD;
    for(int i = 1; i <= n; i++){
        for(auto x : adj[i]){
            if(x.fi<i) continue; // avoid overcounting
            int u = i, v = x.fi, c = x.se;
            if(dis[0][u]+dis[1][v]+c!=dis[0][T]) swap(u,v); // it could be S->v->u->T instead
            if(dis[0][u]+dis[1][v]+c!=dis[0][T]) continue; // not in shortest path
            if(abs(dis[0][u]-dis[1][v])>=c) continue; // they dont meet through that edge
            X+=sq(dp[0][u]*dp[1][v]), X%=MOD;
        }
    }
    ans-=X, ans+=MOD, ans%=MOD; cout << ans;
}
