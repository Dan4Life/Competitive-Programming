#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define int long long
#define sz(a) (int)a.size()
#define all(a) a.begin(),a.end()

const int mxN = 752;
const int MOD = (int)1e9+7;

int n, m, k;
vector<int> v[mxN*mxN];
int a[mxN][mxN], dp[mxN][mxN];

struct Fenwick{
	int n;
	vector<int> fen;
	void init(int N){
		n = N; fen.resize(n+1);
		for(int i = 1; i <= n; i++) fen[i]=0;
	}
	int sum(int x){
		int s = 0;
		for(++x; x; x-=x&-x) 
			s+=fen[x], s%=MOD;
		return s;
	}
	void upd(int x, int v){
		for(++x; x<=n; x+=x&-x) fen[x]+=v,fen[x]%=MOD;
	}
} f[mxN*mxN];

int32_t main() {
	ifstream cin("hopscotch.in");
	ofstream cout("hopscotch.out");
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m >> k;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			cin >> a[i][j], v[a[i][j]].pb(j);
	f[0].init(m);
	for(int i = 1; i <= n*n; i++)
		sort(all(v[i])), v[i].erase(unique(all(v[i])),end(v[i])), f[i].init(sz(v[i]));
	dp[1][1] = 1;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			int c = a[i][j];
			dp[i][j]+=f[0].sum(j-1);
			dp[i][j]-=f[c].sum(lower_bound(all(v[c]),j)-begin(v[c])-1);
			dp[i][j]+=MOD; dp[i][j]%=MOD;
		}
		for(int j = 1; j <= m; j++){
			int c = a[i][j]; f[0].upd(j,dp[i][j]);
			f[c].upd(lower_bound(all(v[c]),j)-begin(v[c]),dp[i][j]);
		}
	}
	cout << dp[n][m] << "\n";
}
