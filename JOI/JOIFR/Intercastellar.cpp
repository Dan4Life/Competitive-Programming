#include <bits/stdc++.h>
using namespace std;
 
#define int long long
#define fi first
#define se second
#define sz(a) (int)a.size()
#define all(a) a.begin(),a.end()
#define pb push_back
const int mxN = (int)2e5+10;
int n, q, x, i, sum, a[mxN];
 
void solve(){
    cin >> n; vector<pair<int,int>> v;
    for(int i = 1; i <= n; i++) {
        cin >> x; int num = 1;
        while(x%2==0) x/=2, num*=2;
        v.pb({num,x});
    }
    cin >> q;
    while(q--){
        cin >> x;
        while(sum+v[i].fi<x) sum+=v[i++].fi;
        cout << v[i].se << "\n";
    }
}
 
int32_t main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
	int t = 1; //cin >> t;
    while(t--) solve();
}
