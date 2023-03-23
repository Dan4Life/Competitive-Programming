#include <bits/stdc++.h>
using namespace std;
 
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define int long long 
#define sz(a) (int)a.size()
#define all(a) a.begin(),a.end()
const int mxN = (int)1e5+10;
const int LINF = mxN*mxN;
int n, a[mxN], dp[mxN][2][2];
vector<int> adj[mxN];
 
void dfs(int s, int p){
    vector<int> v; v.clear();
    for(auto u : adj[s]){
        if(u!=p) dfs(u,s), v.pb(u);
    }
    if(!sz(v)){ dp[s][a[s]][0]=0, dp[s][a[s]^1][1]=1; return; }
    int dp2[sz(v)+1][2];
    for(int i = 0; i <= sz(v); i++)
        dp2[i][0]=dp2[i][1]=LINF;
    dp2[0][0] = 0;
    for(int i = 1; i <= sz(v); i++){
        dp2[i][0] = min(dp2[i-1][0]+dp[v[i-1]][0][0], 
                        dp2[i-1][1]+dp[v[i-1]][0][1]);
        dp2[i][1] = min(dp2[i-1][1]+dp[v[i-1]][0][0], 
                        dp2[i-1][0]+dp[v[i-1]][0][1]);
    }
    dp[s][a[s]][0] = dp2[sz(v)][0];
    dp[s][a[s]^1][0] = dp2[sz(v)][1];
    for(int i = 0; i <= sz(v); i++)
        dp2[i][0]=dp2[i][1]=LINF;
    dp2[0][0] = 0;
 
    for(int i = 1; i <= sz(v); i++){
        dp2[i][0] = min(dp2[i-1][0]+dp[v[i-1]][1][0], 
                        dp2[i-1][1]+dp[v[i-1]][1][1]);
        dp2[i][1] = min(dp2[i-1][1]+dp[v[i-1]][1][0], 
                        dp2[i-1][0]+dp[v[i-1]][1][1]);
    }
    dp[s][a[s]][1] = dp2[sz(v)][1]+1;
    dp[s][a[s]^1][1] = dp2[sz(v)][0]+1;
}
 
int32_t main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for(int i = 1; i < n; i++){
        int a, b; cin >> a >> b;
        adj[a].pb(b), adj[b].pb(a);
    }
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= n; i++)
        for(int j = 0; j < 2; j++)
            for(int k = 0; k < 2; k++)
                dp[i][j][k] = LINF;
    dfs(1,-1);
    int ans = min(dp[1][0][0],dp[1][0][1]);
    if(ans<LINF) cout << ans;
    else cout << "impossible";
}
