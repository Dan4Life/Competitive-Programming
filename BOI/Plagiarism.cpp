#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
 
#define int ll // delete if causing problems
#define ld long double
#define pb push_back
#define pf push_front
#define mp make_pair
#define fir first
#define sec second
#define all(a) a.begin(), a.end()
#define fast_io ios_base::sync_with_stdio(false); cin.tie(0);
 
const int maxn = 200010;
const int MOD = 1e9+7;
const int MOD2 = 998244353;
const int INF = 1e9;
const ll LINF = 1e18;
int n, m, a[maxn], b[maxn];
map<int, int> M, N;
string s, ss;
set<pair<int,int> > S;
 
void solve()
{
    cin >> n;
    for(int i = 0; i < n; i++) cin >> a[i];
    sort(a, a+n); int cnt = 0;
    for(int i = 0; i < n; i++)
        cnt+=upper_bound(a, a+n, 10*a[i]/9)-a-i-1;
    cout << cnt;
}
 
int32_t main()
{
    fast_io;
    int t=1; //cin >> t;
    while(t--) solve();
}
