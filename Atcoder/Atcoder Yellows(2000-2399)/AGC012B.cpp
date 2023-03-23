/*
Solved with help (editorial)
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define int ll // delete if causing problems
#define pb push_back
#define fi first
#define se second

const int maxn = (int)2e5+10; 

int n, m, q;
bool vis[maxn][12];
vector<int> adj[maxn];
int v[maxn], d[maxn], c[maxn], col[maxn];

void recur(int s, int d, int c){
    if(vis[s][d]) return; vis[s][d]=1;
    if(d==0){col[s]=c; return;}
    recur(s,d-1,c);
    for(auto u : adj[s])
        recur(u, d-1, c);
}

int32_t main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m;
    for(int i = 0; i < m; i++){
        int a, b; cin >> a >> b;
        adj[a].pb(b); adj[b].pb(a);
    }
    cin >> q;
    for(int i = 0; i < q; i++) cin >> v[i] >> d[i] >> c[i];
    for(int i = q-1; i >= 0; i--) recur(v[i],d[i],c[i]);
    for(int i = 1; i <= n; i++) cout << col[i] << "\n";
}
