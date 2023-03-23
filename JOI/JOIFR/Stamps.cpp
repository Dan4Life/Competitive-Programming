#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define int long long
#define sz(a) (int)a.size()
const int mxN = (int)4e2+10;
const int LINF = (int)2e18;
int dp[2][mxN][mxN][2], x[mxN], t[mxN];
// Coding this shouldn't have taken as long as it did #ImplCancer
int32_t main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int n, L; cin >> n >> L; int ans = 0;
	for(int i = 1; i <= n; i++) cin >> x[i], x[n+i+1]=x[i];
	for(int i = 1; i <= n; i++) cin >> t[i], t[n+i+1]=t[i];
	for(int i = 0; i < 2; i++)
		for(int j = 0; j < mxN; j++)
			for(int k = 0; k < mxN; k++)
				for(int l = 0; l < 2; l++)
					dp[i][j][k][l] = LINF;
	dp[0][n+1][n+1][0]=dp[0][n+1][n+1][1]=0; t[n+1] = -LINF;
	for(int kk = 0, k=0, lk=1; kk <= n; kk++,k^=1,lk^=1){
		for(int len = 2; len <= n+1; len++){
			for(int l = 1, r=l+len-1; l <= n+1; l++, r++){
				dp[k][l][r][0] = min({ dp[k][l][r][0],
					dp[k][l+1][r][0]+min(abs(x[l+1]-x[l]),L-abs(x[l+1]-x[l])),
					dp[k][l+1][r][1]+min(abs(x[r]-x[l]),L-abs(x[r]-x[l]))
				});
				dp[k][l][r][1] = min({ dp[k][l][r][1],
					dp[k][l][r-1][0]+min(abs(x[l]-x[r]),L-abs(x[l]-x[r])),
					dp[k][l][r-1][1]+min(abs(x[r-1]-x[r]),L-abs(x[r-1]-x[r]))
				});
				if(kk){
					int tm = abs(x[l+1]-x[l]); tm=min(tm,L-tm); tm+=dp[lk][l+1][r][0];
					if(tm<=t[l]) dp[k][l][r][0] = min(dp[k][l][r][0], tm);
					tm = abs(x[r]-x[l]); tm=min(tm,L-tm); tm+=dp[lk][l+1][r][1];
					if(tm<=t[l]) dp[k][l][r][0] = min(dp[k][l][r][0], tm);
					tm = abs(x[l]-x[r]); tm=min(tm,L-tm); tm+=dp[lk][l][r-1][0];
					if(tm<=t[r]) dp[k][l][r][1] = min(dp[k][l][r][1],tm);
					tm = abs(x[r-1]-x[r]); tm=min(tm,L-tm); tm+=dp[lk][l][r-1][1];
					if(tm<=t[r]) dp[k][l][r][1] = min(dp[k][l][r][1],tm);
				}
				if(len==n+1 and (dp[k][l][r][0]<LINF or dp[k][l][r][1]<LINF)) ans = max(ans, kk);
			}
		}
		for(int i = 0; i < mxN; i++)
			for(int j = 0; j < mxN; j++)
				for(int l = 0; l < 2; l++)
					dp[lk][i][j][l]=LINF;
	}
 
	cout << ans;
}
