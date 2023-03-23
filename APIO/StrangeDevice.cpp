#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define int long long
const int maxn = (int)1e6+10;
int n, A, B, mod, ans;
vector<pair<int,int>> v;
 
int32_t main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> A >> B; A/=__gcd(A, B+1);
	if(A<=4*maxn*maxn*maxn/B) mod = A*B;
	else mod = (int)1e18+1;
	for(int i = 1; i <= n; i++){
		int l, r; cin >> l >> r;
		if(r-l+1>=mod){cout<<mod; return 0;}
		l%=mod, r%=mod;
		if(l<=r) v.pb({l,r});
		else v.pb({l,mod-1}), v.pb({0,r});
	}
	sort(v.begin(),v.end());
	int l = v[0].fi, r = v[0].se;
	for(auto u : v){
		if(r<u.fi) ans+=r-l+1, l=u.fi,r=u.se;
		else r = max(r, u.se);
	}
	cout << ans+r-l+1;
}
