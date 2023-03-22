#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, L, dp[1<<21], d[21], c[21][1010];

int32_t main() {
	ifstream cin("movie.in"); ofstream cout("movie.out");
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> L; int ans = n+1;
	for(int i = 0; i < n; i++){
		cin >> d[i] >> c[i][0];
		for(int j = 1; j <= c[i][0]; j++) cin >> c[i][j];
	}
	for(int mask = 0; mask < (1<<n); mask++){
		for(int i = 0; i < n; i++){
			if(!((mask>>i)&1)) continue; int nmask = mask ^ (1<<i);
			int pos = upper_bound(c[i]+1,c[i]+c[i][0]+1,dp[nmask])-c[i]-1;
			if(pos>0) dp[mask] = max({dp[mask], dp[nmask], c[i][pos]+d[i]});
		}
		if(dp[mask]>=L) ans = min(ans,  (int)__builtin_popcountll(mask));
	}
	cout << (ans==n+1?-1:ans);
}
