#include <bits/stdc++.h>
using namespace std;
#define int long long
#define sz(a) (int)a.size()
const int mxN = (int)5e5+1;
int n, m, ans, sum, mx;
array<int,2> v[mxN];
 
int32_t main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n;
	for(int i = 0; i < n; i++) 
		cin >> v[i][0] >> v[i][1], ans = max(ans, v[i][1]);
	sort(v,v+n);
	for(int i = 0; i < n; i++){
		sum+=v[i][1];
		ans = max(ans, sum-v[i][0]+mx);
		mx = max(mx,v[i][1]+v[i][0]-sum);
	}
	cout << ans;
}
