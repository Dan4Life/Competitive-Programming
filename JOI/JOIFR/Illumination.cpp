#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int ll // delete if causing problems
#define pb push_back
#define pf push_front
#define mp make_pair
#define fi first
#define se second
#define all(a) a.begin(), a.end()
#define sz(a) (int)a.size()

const int mxN = (int)1e5+10;
const int MOD = (int)1e9+7;
const int INF = (int)2e9;
const ll LINF = (ll)4e18;
int n, m, x, y, l, r, k, q, t, ans;
int a[mxN];
vector<int> v;

int32_t main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n; v.pb(0);
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < n; i++){
        int j = i;
        while(i<n-1 and a[i]!=a[i+1]) i++;
        v.pb(i-j+1);
    }
	v.pb(0);
    for(int i = 0; i < sz(v)-2; i++)
        ans = max(ans, v[i]+v[i+1]+v[i+2]);
    cout << ans << endl;
}
