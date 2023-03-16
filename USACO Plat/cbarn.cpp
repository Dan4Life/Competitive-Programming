#include <bits/stdc++.h>
using namespace std;
#define int long long
#define sz(a) (int)a.size()
const int mxN = (int)1e3+10;
const int LINF = (int)1e12;
int n, k, a[mxN], pr[mxN], pr2[mxN], dp[10][mxN];

double g(int i, int j, int k){
	int y = dp[--k][i]+pr2[i-1]; swap(i,j);
	y -= dp[k][i]+pr2[i-1]; swap(i,j);
	int x = -i - (-j);
	return (double)(y*1.0/x);
}

int32_t main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	ifstream cin("cbarn.in");
	ofstream cout("cbarn.out");
	cin >> n >> k; int ans = LINF;
	for(int i = 0; i < n; i++) cin >> a[i];
	for(int _ = 0; _ < n; _++){
		for(int i = 0; i < n; i++)
			pr[i+1]=pr[i]+a[i], pr2[i+1]=pr2[i]+pr[i+1];
		for(int i = 0; i <= k+1; i++)
			for(int j = 0; j <= n+1; j++)
				dp[i][j]=LINF;
		dp[1][1] = 0;
		for(int j = 2; j <= k+1; j++){
			deque<int> dq; dq.clear(); dq.push_back(1);
			for(int i = 2; i <= n+1; i++){
				while(sz(dq)>1 and g(dq[0],dq[1],j)>=-pr[i-1]) dq.pop_front();
				int x = dq[0]; dp[j][i] = min(dp[j][i],dp[j-1][x]+(i-x-1)*pr[i-1]-(pr2[i-2]-pr2[x-1]));
				while(sz(dq)>1 and g(end(dq)[-2],end(dq)[-1],j)<=g(end(dq)[-2],i,j)) dq.pop_back();
				dq.push_back(i);
			}
		}
		ans = min(ans, dp[k+1][n+1]); rotate(a,a+1,a+n);
	}
	cout << ans;
}
