#include <bits/stdc++.h>
using namespace std;
 
#define int long long
#define fi first
#define se second
#define sz(a) (int)a.size()
#define all(a) a.begin(),a.end()
#define pb push_back
const int mxN = (int)2e5+10;
int n, a[mxN], pre[mxN], suf[mxN];
 
void solve(){
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 2; i <= n; i++)
        pre[i] = pre[i-1]+max(0ll, a[i-1]-a[i]+1);
    for(int i = n-1; i >= 1; i--)
        suf[i] = suf[i+1]+max(0ll, a[i+1]-a[i]+1);
    int ans = min(suf[1], pre[n]);
    for(int i = 1; i < n; i++) 
        ans = min(ans, max(pre[i], suf[i]));
    cout << ans;
}
 
int32_t main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
	int t = 1; //cin >> t;
    while(t--) solve();
}
