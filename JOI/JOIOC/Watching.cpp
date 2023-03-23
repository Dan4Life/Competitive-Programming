#include <bits/stdc++.h>
using namespace std;
const int mxN = (int)2e3+10, LINF = (int)1e9;
int n, p, q, a[mxN], P[mxN], Q[mxN], dp[mxN][mxN];
 
bool work(int w){
	for(int i=1,j=1,k=1; i <= n; i++){
		while(j<=n and a[j]-a[i]<w)j++;
		while(k<=n and a[k]-a[i]<2*w)k++;
		P[i]=--j, Q[i]=--k;
	}
	for(int i = 0; i <= p; i++){
		for(int j = 0; j <= q; j++){
			dp[i][j]=0;
			if(i) dp[i][j] = max(dp[i][j], P[dp[i-1][j]+1]);
			if(j) dp[i][j] = max(dp[i][j], Q[dp[i][j-1]+1]);
			if(dp[i][j]>=n) return 1;
		}
	}
	return 0;
}
 
main() {
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
