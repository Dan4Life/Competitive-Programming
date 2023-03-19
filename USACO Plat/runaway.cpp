#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define int long long
#define sz(a) (int)a.size()
const int mxN = (int)2e5+10;
vector<pair<int,int>> adj[mxN];
priority_queue<pair<int,int>> S[mxN];
int n, L, ans[mxN], depth[mxN];

void dfs(int s, int p){
    S[s].push({depth[s],s});
    for(auto [u,w] : adj[s]){
        if(u==p) continue;
        depth[u] = depth[s]+w; dfs(u,s);
        if(sz(S[s])<sz(S[u])) S[s].swap(S[u]);
        while(!S[u].empty()){
            auto cur = S[u].top(); S[u].pop();
            if(cur.fi-depth[s]<=L) S[s].push(cur);
        }
        while(!S[s].empty() and S[s].top().fi-depth[s]>L) S[s].pop();
    }
    ans[s] = sz(S[s]);
}

int32_t main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    ifstream cin("runaway.in");
    ofstream cout("runaway.out");
    cin >> n >> L;
    for(int i = 2; i <= n; i++){
        int a, b; cin >> a >> b;
        adj[a].pb({i,b}), adj[i].pb({a,b});
    }
    dfs(1,-1);
    for(int i = 1; i <= n; i++) cout << ans[i] << "\n";
}
