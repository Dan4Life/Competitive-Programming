#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = (int)2e3+10;
const ll LINF = (ll)1e18;
int n, A, B;
ll a[maxn], pre[maxn]; ll ans=LINF;
 
bool needs(ll mask, int bit){
	bool dp[110][110]; bool ok=1;
	for(int i = 0; i <= n; i++)
		for(int j = 0; j <= B; j++)
			dp[i][j]=false;
	dp[0][0]=true;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= B; j++){
			for(int k = 0; k<i; k++){
				ll sum = pre[i]-pre[k];
				ll sm=sum>>(bit+1), mm = mask>>(bit+1); mm=~mm;
				if(sum&(1ll<<bit) or sm&mm) continue;
				dp[i][j] |= dp[k][j-1];
			}
		}
	}
	for(int i = A; i <= B; i++) if(dp[n][i]) ok=0;
	return ok;
}
 
bool needs2(ll mask, int bit){
	int dp[2010];
	for(int i = 0; i <= n; i++) dp[i]=n+1;
	dp[0]=0;
	for(int i = 1; i <= n; i++){
		for(int k = 0; k<i; k++){
			ll sum = pre[i]-pre[k];
			ll sm=sum>>(bit+1), mm = mask>>(bit+1); mm=~mm;
			if(sum&(1ll<<bit) or sm&mm) continue;
			dp[i] = min(dp[i], dp[k]+1);
		}
	}
	return dp[n]>B;
}
 
int32_t main() {
	cin >> n >> A >> B; ans = 0;
	for(int i = 0; i < n; i++) cin >> a[i], pre[i+1]=pre[i]+a[i];
	for(int i = 40; i >= 0; i--)
		ans|=(A>1?needs(ans|(1ll<<i),i):needs2(ans|(1ll<<i),i))*(1ll<<i);
	cout << ans;
}
