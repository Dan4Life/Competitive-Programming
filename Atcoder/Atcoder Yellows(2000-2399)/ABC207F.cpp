/*
Combining subtree tree-dp trick to speed up O(N^3) -> O(N^2)
*/

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define fi first
#define se second
#define pb push_back
#define sz(a) (int)a.size()
#define all(a) a.begin(),a.end()
const int mxN = (int)2e3+10;
const int MOD = (int)1e9+7;
int n, dp[mxN][mxN][3], tmp[mxN][3], sub[mxN];
vector<int> adj[mxN];

void dfs(int s, int p){
    dp[s][0][2] = 0;
    sub[s] = dp[s][0][0] = dp[s][1][1] = 1;
    for(auto u : adj[s]){
        if(u==p) continue;
        dfs(u,s); memset(tmp, 0, sizeof(tmp));
        for (int i = 0; i <= sub[s]; i++){ 
            for (int j = 0; j <= sub[u]; j++) {
                tmp[i+j][0]+=dp[s][i][0]*(dp[u][j][0]+dp[u][j][2]);
                tmp[i+j][1]+=dp[s][i][1]*((j?dp[u][j-1][0]:0)+dp[u][j][2]+dp[u][j][1]);
                tmp[i+j][2]+=dp[s][i][2]*(dp[u][j][0]+dp[u][j][1]+dp[u][j][2])+(i?dp[s][i-1][0]*dp[u][j][1]:0);
                for(int k = 0; k < 3; k++) tmp[i+j][k]%=MOD;
            }
        }
        sub[s]+=sub[u]; memcpy(dp[s], tmp, sizeof(tmp));
    }
}

int32_t main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for(int i = 1; i < n; i++){
        int a, b; cin >> a >> b;
        adj[a].pb(b), adj[b].pb(a);
    }
    dfs(1,-1);
    for(int i = 0; i <= n; i++) 
        cout << (dp[1][i][0]+dp[1][i][1]+dp[1][i][2])%MOD << "\n";
}
