#include <bits/stdc++.h>
using namespace std;
const int mxN = (int)2e3+10, LINF = (int)1e9;
int n, p, q, a[mxN], P[mxN], Q[mxN], dp[mxN][mxN];
 
bool work(int w){
	for(int i=2,j=1,k=1; i <= n; i++){
		while(a[i]-a[j]+1>w) j++;
		while(a[i]-a[k]+1>2*w) k++;
		P[i]=j-1,Q[i]=k-1;
	}
	for(int i = 1; i <= n; i++){
		for(int j = 0; j <= q; j++){
			dp[i][j] = min(LINF, dp[P[i]][j]+1);
			if(j) dp[i][j] = min(dp[i][j], dp[Q[i]][j-1]);
		}
	}
	return dp[n][q]<=p;
}
 
int32_t main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> p >> q;
	for(int i = 1; i <= n; i++) cin >> a[i];
	sort(a+1,a+n+1);
	if(p+q>=n){cout<<1;return 0;}
	int l = 1, r = (int)1e9;
	while(l<r){
		int mid = (l+r)/2;
		if(work(mid)) r=mid;
		else l=mid+1;
	}
	cout << l;
}
