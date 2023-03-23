#include <bits/stdc++.h>
using namespace std;
 
#define fi first
#define se second
#define sz(a) (int)a.size()
#define all(a) a.begin(),a.end()
#define pb push_back
const int mxN = (int)2e5+10;
int n, a[mxN], b[mxN], ans[mxN];
 
void solve(){
    cin >> n; multiset<int> S;
    for(int i = 1; i <= n+1; i++) cin >> a[i];
    for(int i = 1; i <= n; i++) cin >> b[i];
    vector<int> ord(n+1,0); iota(all(ord),1);
    sort(all(ord), [&](int i, int j){ return a[i]<a[j]; });
    sort(a+1,a+n+2), sort(b+1,b+n+1);
    for(int i = 2; i <= n+1; i++) S.insert(a[i]-b[i-1]);
    ans[ord[0]] = *prev(S.end());
    for(int i = 1; i <= n; i++){
        S.erase(S.find(a[i+1]-b[i]));
        S.insert(a[i]-b[i]);
        ans[ord[i]] = *prev(S.end());
    }
    for(int i = 1; i <= n+1; i++) cout << max(0,ans[i]) << " ";
}
 
int32_t main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
	int t = 1; //cin >> t;
    while(t--) solve();
}
