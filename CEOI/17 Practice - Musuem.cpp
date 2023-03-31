#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define sz(a) (int)a.size()
#define all(a) a.begin(),a.end()
const int mxN=(int)1e4+2;
const int LINF = (int)1e9;
int n, k, s, sub[mxN];
vector<pair<int,int>> adj[mxN];
int dp[mxN][mxN][2];
 
int findSize(int s, int p){
	sub[s]=1;
	for(auto [u,w] : adj[s])
		if(u!=p) sub[s]+=findSize(u,s);
	return sub[s];
}
 
void dfs(int s, int p){
	for(int tot = 1; auto [u,w] : adj[s]){ 
		if(u==p) continue; 
		dfs(u,s); tot+=sub[u];
		for(int i = tot; i >= 2; i--)
            for(int j = max(0, i-tot+sub[u]); j<=min(i,sub[u]); j++)
				dp[s][i][0] = min(dp[s][i][0], dp[s][i-j][0] + dp[u][j][1]+2*w),
				dp[s][i][0] = min(dp[s][i][0], dp[s][i-j][1]+dp[u][j][0]+w),
				dp[s][i][1] = min(dp[s][i][1], dp[s][i-j][1]+dp[u][j][1]+2*w);
	}
}
 
int32_t main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> k >> s;
	for(int i = 1; i < n; i++){
		int a, b, c; cin >> a >> b >> c;
		adj[a].pb({b,c}), adj[b].pb({a,c});
	}
	for(int i=1; i<=n; i++){
        for(int j=2; j<=n; j++){
            dp[i][j][0] = dp[i][j][1] = LINF;
        }
    }
	findSize(s,-1); dfs(s,-1); cout << dp[s][k][0];
}
