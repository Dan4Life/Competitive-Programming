#include <bits/stdc++.h>
using namespace std;
 
#define int long long
#define fi first
#define se second
#define sz(a) (int)a.size()
#define all(a) a.begin(),a.end()
#define pb push_back
const int mxN = (int)3e5+10;
int n, m, a[mxN], b[mxN];
 
bool chk(int lim){
    int tot = n*m;
    for(int i = 1; i <= n; i++){
        int num = min((lim+a[i]-1)/a[i], m);
        int x = num*a[i]; tot-=num;
        if(lim>x) tot-=((lim-x)+b[i]-1)/b[i];
        if(tot<0) return 0;
    }
    return 1;
}
 
void solve(){
    cin >> n >> m;
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= n; i++) cin >> b[i], a[i]=max(a[i],b[i]);
    int l = 0, r = (int)1e18;
    while(l<r){
        int mid = (l+r+1)/2;
        if(chk(mid)) l=mid;
        else r=mid-1;
    }
    cout << l;
}
 
int32_t main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
	int t = 1; //cin >> t;
    while(t--) solve();
}
