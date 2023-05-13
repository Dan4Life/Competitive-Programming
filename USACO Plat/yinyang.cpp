#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int ll // delete if causing problems
#define pb push_back
#define pf push_front
#define mp make_pair
#define fi first
#define se second
#define mod(a) (a+MOD)%MOD
#define all(a) a.begin(), a.end()
#define sz(a) (int)a.size()

const int maxn = (int)1e5+10; // change when needed!
const int MOD = (int)1e9+7; // same!
const int INF = (int)2e9;
const ll LINF = (ll)4e18;
int n, x, y, l, r, k, q, t;
unordered_map<int, int> m;
set<int> S, SS;
string s, ss;
int sub[maxn], vis[maxn]{0}, ans;
vector<pair<int,int>> adj[maxn];
int dp[maxn][2][2];
// dp[i][j][k] means current path has abs(sum) = i.
// If j = 0, its first time encountering, else already encountered previously.
// If k = 0, it means the path is negative, else non-negative
// I did this to prevent an extra logN with the use of maps(but then i could just use unordered map...idc)
int dfs(int s, int p){
	sub[s] = 1;
	for(auto w : adj[s]){
		int u = w.fi;
		if(u!=p and !vis[u])
			sub[s]+=dfs(u, s);
	}
	return sub[s];
}

int f_centroid(int s, int p, int sz){
	for(auto w : adj[s]){
		int u = w.fi;
		if(!vis[u] and u!=p and sub[u]>sz/2)
			return f_centroid(u,s,sz);
	}
	return s;
}

void dfs2(int s, int p, int tot, bool ok, unordered_map<int,int>& m){
	for(auto w : adj[s]){
		int u = w.fi;
		if(u!=p and !vis[u]){
			m[tot]++;
			dfs2(u,s,tot+w.se,ok,m);
			m[tot]--;
		}
	}
	if(ok) dp[abs(tot)][!!m[tot]][(tot>=0)]++;
	else{
		if(tot==0) ans+=dp[0][0][1]+dp[0][1][1]+!!m[0];
		else{
			if(m[tot]==0) ans+=dp[abs(tot)][1][(tot<0)];
			else ans+=dp[abs(tot)][0][(tot<0)]+dp[abs(tot)][1][(tot<0)];
		}
	}
}

void centroid_decomp(int s, int p){
	int sz = dfs(s,p);
	int centroid = f_centroid(s,-1,sz);
	vis[centroid]=1;
	for(int i = 0; i <= sz; i++)
		dp[i][0][0]=dp[i][0][1]=dp[i][1][0]=dp[i][1][1]=0;
	for(auto w : adj[centroid]){
		int u = w.fi; if(vis[u]) continue;
		dfs2(u,centroid,w.se,0,m);
		dfs2(u,centroid,w.se,1,m);
	}
	for(auto w : adj[centroid]){
		int u = w.fi;
		if(!vis[u]) centroid_decomp(u,centroid);
	}
}

int32_t main()
{
	ios_base::sync_with_stdio(false); cin.tie(0);
	ifstream cin("yinyang.in");
	ofstream cout("yinyang.out");
	cin >> n;
	for(int i = 1; i < n; i++){
		int a, b, c; cin >> a >> b >> c; if(c==0)c--;
		adj[a].pb({b,c}), adj[b].pb({a,c});
	}
	centroid_decomp(1,-1); cout << ans << '\n';
}
